#ifndef memory_h
#define memory_h

#include <sys/types.h>
#if defined (__linux)
#include <sys/ipc.h>
#endif

#define MAX_SHARED_FRAMES		4

#define SHARED_GONIOSTAT_VALUES_KEY	(key_t)152
#define SHARED_DETECTOR_VALUES_KEY	(key_t)153
#define SHARED_FRAMEVALUES_KEY		(key_t)154
#define SHARED_FRAME_KEY		(key_t)155
#define SHARED_FRAME0_KEY		(key_t)(SHARED_FRAME_KEY)
#define SHARED_FRAME1_KEY		(key_t)(SHARED_FRAME_KEY+1)
#define SHARED_FRAME2_KEY		(key_t)(SHARED_FRAME_KEY+2)
#define SHARED_FRAME3_KEY		(key_t)(SHARED_FRAME_KEY+3)


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern void *allocate_shared_memory(key_t key, int size, int *new);

extern int lock_memory(void *ptr, size_t size);

static inline void CacheLine_Preload(unsigned long addr)
{
       asm volatile("" : : "r" (addr));
}

#if 1
/* Intel P6+ specific - Temporal, into all caches */
static inline void CacheLine_Prefetch(unsigned long addr)
{
       asm volatile("prefetcht0 (%0)" :: "r" (addr));
}
#else
/* Intel P6+ specific - Non-Temporal, non-polluting */
static inline void CacheLine_Prefetch(unsigned long addr)
{
       asm volatile("prefetchnta (%0)" :: "r" (addr));
}
#endif
#if 0
/* AMD specific */
static inline void CacheLine_Prefetch(unsigned long addr)
{
       asm volatile("PREFETCHW (%0)" :: "r" (addr));
}
#endif



#endif /* memory_h */
