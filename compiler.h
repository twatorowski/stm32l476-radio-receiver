/**
 * @file compiler.h
 *
 * @date 23.06.2019
 * @author twatorowski (tw@mightydevices.com)
 *
 * @brief Compiler defines
 */


#ifndef COMPILER_H_
#define COMPILER_H_

/* inline assembler */
#define ASM					__asm__

/* section attribute */
#define SECTION(x)			__attribute__ ((section (x)))
/* optimization attribute */
#define OPTIMIZE(x)			__attribute__ ((optimize (x)))
/* packed */
#define PACKED				__attribute__ ((packed))
/* alignment */
#define ALIGNED(x)			__attribute__ ((aligned (x)))
/* enfoce function being always inline */
#define ALWAYS_INLINE		__attribute__ ((always_inline))
/* variable unused */
#define UNUSED				__attribute__ ((unused))
/* variable unused */
#define USED				__attribute__ ((used))
/* naked function */
#define NAKED				__attribute__ ((naked))
/* prevent inlining */
#define NOINLINE			__attribute__ ((noinline))
/* loop unrolling attribute */
#define LOOP_UNROLL         __attribute__ ((optimize ("unroll-loops")))


/* additional helpers/shorthands, used has to go here otherwise the optimizer may
 * clear out the function call, thus removing it from section */
#define RAM_CODE			NOINLINE SECTION(".ram_code")

#endif /* COMPILER_H_ */
