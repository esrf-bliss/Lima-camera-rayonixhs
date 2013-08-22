#ifndef goniostat_none_h
#define goniostat_none_h

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
extern goniostat_functions *get_goniostat_none(
#if NeedFunctionPrototypes
int verbose
#endif
);

#endif	/* goniostat_none_h */
