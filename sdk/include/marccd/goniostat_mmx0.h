#ifndef goniostat_mmx0_h
#define goniostat_mmx0_h

#include "goniostat.h"

/*----------------------------------------------------------------------------*/

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


/* A Function for each type of goniostat */
extern goniostat_functions *get_goniostat_mmx0(
#if NeedFunctionPrototypes
int verbose
#endif
);

#endif	/* goniostat_mmx0_h */
