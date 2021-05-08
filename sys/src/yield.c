/**
 * @file yield.c
 * 
 * @author Tomasz Watorowski (tomasz.watorowski@gmail.com)
 * @date 2021-03-27
 * 
 * @brief Yield - context switcher
 */

#include <stdint.h>
#include <stddef.h>

#include "assert.h"
#include "compiler.h"
#include "config.h"
#include "err.h"
#include "linker.h"
#include "arch/arch.h"
#include "stm32h743/stm32h743.h"
#include "stm32h743/nvic.h"
#include "stm32h743/scb.h"
#include "sys/heap.h"
#include "sys/time.h"
#include "sys/yield.h"
#include "util/elems.h"

/* tasks stack frame - backwards since it it placed on stack, in basic mode: 
 * a.k.a no floating point registers */
typedef struct {
    /* exception return code */
    uint32_t exc_return;
    /* registers that we put manually on stack */
    uint32_t r11, r10, r9, r8, r7, r6, r5, r4;
    /* general purpose registers that are put by the interrupt */
    uint32_t r0, r1, r2, r3, r12;
    /* link register, program counter and status register */
    uint32_t lr, pc, xpsr;
} task_frame_basic_t;

/* tasks stack frame - backwards since it it placed on stack, in extended mode: 
 * a.k.a with floating point registers */
typedef struct {
    /* exception return code */
    uint32_t exc_return;
    /* 16 general purpose floating point registers */
    float s16_31[16];
    /* registers that we put manually on stack */
    uint32_t r11, r10, r9, r8, r7, r6, r5, r4;
    /* general purpose registers that are put by the interrupt */
    uint32_t r0, r1, r2, r3, r12;
    /* link register, program counter and status register */
    uint32_t lr, pc, xpsr;
    /* 16 general purpose floating point registers */
    float s00_15[16];
    /* floating point control register */
    uint32_t fpcsr;
} task_frame_ext_t;

/* task stack frame in two modes */
typedef union {
    /* basic mode - no fpu */
    task_frame_basic_t basic;
    /* extended mode - with fpu */
    task_frame_ext_t ext;
} task_frame_t;

/* task descriptor */
typedef struct task {
    /* stack pointer address */
    task_frame_t *sp;

    /* task state */
    enum task_state { TASK_FREE, TASK_PENDING, TASK_ACTIVE } state;

    /* task handler */
    void (* handler) (void *);
    /* task handler argument */
    void *handler_arg;

    /* stack and stack size */
    void *stack;
    /* size of stack */
    size_t stack_size;
} task_t;

/* list of tasks in the system */
task_t tasks[OS_MAX_TASKS];
/* current task pointer */
static task_t *task = tasks;
/* context switch counter */
static volatile uint32_t switch_cnt;

/* initiate context switch procedure */
static void Yield_CallScheduler(void)
{
    /* set pend sv, ensure that we've reached the switcher routine */
    // for (uint32_t cnt = switch_cnt; cnt == switch_cnt; )
    SCB->ICSR |= SCB_ICSR_PENDSVSET;
}

/* task executor wrapper */
static void Yield_ExecuteTask(task_t *t)
{
    /* execute task handler */
    t->handler(t->handler_arg);
    /* free up the task descriptor */
    t->state = TASK_FREE;

    /* switch the context */
    Yield_CallScheduler();
}

/* validate that tasks' stack was not corrupted */
static void Yield_CheckStack(void)
{
    /* these checks are valid only for tasks that have their own stack: i.e. 
     * subtasks of the main task */
    if (task->stack) {
        /* check for overflows */
        assert((uintptr_t)task->sp > (uintptr_t)task->stack, "stack overflow", 
            task->handler);
        /* check the stack guard */
        assert(*(uint32_t *)task->stack == 0xdeadc0de, "stack guard corrupted", 
            task->handler);
    }
}

/* select next task to be executed */
static void Yield_Schedule(void)
{
    /* bump up the counter */
    switch_cnt++;
    
    /* look for the next task that is ready for the execution */
    for (;; task = (task == &tasks[elems(tasks) - 1]) ? tasks : task + 1) {
        /* active tasks are now pending */
        if (task->state == TASK_ACTIVE) {
            task->state = TASK_PENDING;
        /* got a pending task? */
        } else if (task->state == TASK_PENDING) {
            task->state = TASK_ACTIVE; break;
        }
    }
}

/* context switch interrupt */
void NAKED OPTIMIZE ("O0") Yield_PendSVHandler(void)
{
    /* stack pointer holding register */
    register task_frame_t *sp;

    /* we are in the naked function, and as such the mcu has already built the 
     * stack frame that consists of xpsr, pc, lr, r12, r3, r2, r1, r0 */
    ASM volatile (

        /* load the stack pointer */
        "mrs r0, psp                    \n"
        "isb                            \n"

        /* store all other registers */
        "stmdb r0!, {r4-r11}            \n"

        /* second thing that is encoded in EXC RETURN's value is the presence of 
         * fpu registers stacking: if the 4th bit is set to zero then we need 
         * to stack the floating point registers */
        "tst lr, #0x00000010            \n"
        "it eq                          \n"
        "vstmdbeq r0!, {s16-s31}	    \n"

        /* let's store the RETURN value to have all the information needed for 
         * stack restoration process */
        "stmdb r0!, {lr}                \n"

        /* copy the stack pointer value */
        "mov %[sp], r0                  \n"
        /* write operands */
        : [sp] "=r" (sp)
    );

    /* store stack pointer of current task */
    task->sp = sp;
    /* validate stack of task that yielded */
    Yield_CheckStack();
    /* select next task for the execution */
    Yield_Schedule();
    /* use it's stack pointer to restore it's stack frame */
    sp = task->sp;
    
    /* load registers r4-r11 from next task frame */
    ASM volatile (

        /* read the EXC_RETURN code for the next task */
        "ldmia %[sp]!, {r0}             \n"

        /* test for the floating point context */
        "tst r0, #0x00000010            \n"
        "it eq                          \n"
        "vldmiaeq %[sp]!, {s16-s31}	    \n"

        /* read all the registers that we need to read manually */
        "ldmia %[sp]!, {r4-r11}         \n"
        
        /* restore the stack pointer */
        "msr psp, %[sp]                 \n"
        "isb                            \n"
        /* continue with next task by returning appropriate EXC_RETURN code */
        "bx r0                          \n"
        /* write operands */
        : [sp] "+r" (sp)
    );
}

/* start the yield context switcher */
err_t Yield_Init(void)
{
    /* set the context switcher priority to the lowest possible level */
    SCB_SETEXCPRI(STM32_EXC_PENDSV, INT_PRI_YIELD);

    /* return status */
    return EOK;
}

/* start the context switcher */
void Yield_Start(void)
{
    /* setup initial stack value. since we are making a normal call to handler 
     * we do not need to create stack frame */
    task->sp = (task_frame_t *)((uintptr_t)task->stack + task->stack_size);
    task->sp = (task_frame_t *)((uintptr_t)task->sp & ~0x7);
    task->state = TASK_ACTIVE;

    /* setup stack pointer */
    Arch_WritePSP(task->sp);
    Arch_ISB();
    /* start using the program stack pointer */
    Arch_WriteCONTROL(0x02);
    /* call the handler */
    tasks->handler(tasks->handler_arg);

    /* shall never be reached */
    while (1);
}

/* prepare task for the execution */
err_t Yield_CreateTask(void (*handler)(void *), void *arg, size_t stack_size)
{
    /* this pointer will hold the task descriptor table entry */
    task_t *t;

    /* look for a free entry within the task descriptor table */
    for (t = tasks;; t = t == (tasks + elems(tasks) - 1) ? tasks: t + 1) {
        /* found a free task? */
        if (t->state == TASK_FREE) {
            break;
        /* no free tasks so far, let's wait for free slot in task descriptor 
         * table */
        } else if (t == tasks + elems(tasks) - 1) {
            Yield();
        }
    }

    /* allocate memory for the stack */
    void * stack = Heap_Malloc(stack_size);
    /* initial checks */
    assert(stack, "stack memory cannot be allocated", handler);
    assert(((uintptr_t)stack & 3) == 0, "stack must be word-aligned", handler);
    assert((stack_size & 3) == 0, "stack size must be a multiple of 4", handler);
    assert(stack_size >= sizeof(task_frame_t), "stack size is too small", handler);

    /* store execution handler and it's argument */
    t->handler = handler; t->handler_arg = arg;
    /* store task stack and and it's size for further stack corruption 
     * analysis */
    t->stack = stack; t->stack_size = stack_size;
    /* word with lowest address shall carry the guard word */
    *(uint32_t *)stack = 0xdeadc0de;

    /* set stack pointer to the top of the stack - the size of the stack frame. 
     * this will allow the context switch routine to load the values from the 
     * stack */
    t->sp = (task_frame_t *)((uintptr_t)stack + stack_size);
    /* ensure that we are aligned to 8 byte boundary after the context switcher 
     * pops all the registers from the stack - this is what calling 
     * convention expects. Then, move the pointer back by the amount required to 
     * fit the basic stack frame */
    t->sp = (task_frame_t *)(((uintptr_t)t->sp & ~0x7) - 
        sizeof(task_frame_basic_t));

    /* default status register value: Thumb bit set */
    t->sp->basic.xpsr = 0x01000000;
    /* set the program counter to point to the task routine */
    t->sp->basic.pc = (uint32_t)Yield_ExecuteTask;
    /* debug value */
    t->sp->basic.lr = 0xdeadc0de;
    /* set the task pointer address within the r0 as the r0 is where the 1st 
     * function argument is kept by ARM calling convention */
    t->sp->basic.r0 = (uint32_t)t;
    /* exc return code indicates basic stack frame (no fpu) and psp as stack 
     * pointer - every new task starts that way, but things may evolve if user 
     * uses floating point arithmetic operations */
    t->sp->basic.exc_return = 0xFFFFFFFD;
    /* set task state to pending - scheduler will take it from here */
    t->state = TASK_PENDING;

    /* return task id number */
    return t - task;
}

/* yield from current task */
void Yield(void)
{
    /* call the scheduler */
    Yield_CallScheduler();
}