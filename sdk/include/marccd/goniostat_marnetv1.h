#ifndef goniostat_marnetv1_h
#define goniostat_marnetv1_h

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
extern goniostat_functions *get_goniostat_marnetv1(
#if NeedFunctionPrototypes
int verbose
#endif
);

#endif	/* goniostat_marnetv1_h */
