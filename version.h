/*
 * version.h
 *
 *	Created on: 15-03-2016
 *		Author: Tomek
 */

#ifndef VERSION_H_
#define VERSION_H_

#include <stdint.h>

#include "util/concatstr.h"

/* software version: major */
#ifndef VERSION_SW_MAJOR
#define VERSION_SW_MAJOR						1
#endif
/* software version: minor */
#ifndef VERSION_SW_MINOR
#define VERSION_SW_MINOR						0
#endif
/* software version: build */
#ifndef VERSION_SW_BUILD
#define VERSION_SW_BUILD						0
#endif

/* hardware version: major */
#ifndef VERSION_HW_MAJOR
#define VERSION_HW_MAJOR						1
#endif
/* hardware version: minor */
#ifndef VERSION_HW_MINOR
#define VERSION_HW_MINOR						0
#endif
/* hardware version: build */
#ifndef VERSION_HW_BUILD
#define VERSION_HW_BUILD						0
#endif


/* software version as a string */
#define VERSION_SW_STR						    \
    CONCATSTR(VERSION_SW_MAJOR) "."             \
    CONCATSTR(VERSION_SW_MINOR) "."             \
    CONCATSTR(VERSION_SW_BUILD)

/* hardware version as a string */
#define VERSION_HW_STR					        \
    CONCATSTR(VERSION_HW_MAJOR) "."             \
    CONCATSTR(VERSION_HW_MINOR) "."             \
    CONCATSTR(VERSION_HW_BUILD)

/* version type */
typedef struct version {
    /* build number */
    uint16_t build;
    /* minor and major version numbers */
    uint8_t minor, major;
} version_t;

#endif /* VERSION_H_ */
