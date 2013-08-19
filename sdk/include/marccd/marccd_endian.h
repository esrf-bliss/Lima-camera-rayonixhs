#ifdef __cplusplus
    extern "C" {
#endif
#ifndef _marccd_endian_h
#define _marccd_endian_h


/* Try to figure out from the sytem, what the byte order is */

#if defined(sgi)
#include <sys/endian.h>
#elif defined(__alpha)
#include <machine/endian.h>
#elif defined(__hpux)
#define __LITTLE_ENDIAN	1234
#define __BIG_ENDIAN	4321
#define __BYTE_ORDER 	__BIG_ENDIAN
#elif defined (__APPLE__)
#else
#include <endian.h>
#endif


#ifndef BYTE_ORDER
#define BYTE_ORDER	__BYTE_ORDER
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN	__LITTLE_ENDIAN
#endif
#ifndef BIG_ENDIAN
#define BIG_ENDIAN	__BIG_ENDIAN
#endif

#if (BYTE_ORDER == LITTLE_ENDIAN)
#define BYTE_SWAPPED BIG_ENDIAN
#else
#define BYTE_SWAPPED LITTLE_ENDIAN
#endif


#endif /* _marccd_endian_h */
#ifdef __cplusplus
}
#endif
