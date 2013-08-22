#ifndef ascdate_h
#define ascdate_h

#include <time.h>

#define MD struct mdstruct
MD {
   char *month;
   int days;
   };

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern char *asciidate (
#if NeedFunctionPrototypes
char *s,
long date
#endif
);

extern char *asciitime(
#if NeedFunctionPrototypes
char *s,
long time
#endif
);

extern void systime(
#if NeedFunctionPrototypes
long buff[]
#endif
);

extern long ticktime(
#if NeedFunctionPrototypes
#endif
);

extern time_t cputime(
#if NeedFunctionPrototypes
#endif
);

extern char *decima (
#if NeedFunctionPrototypes
char *s,
long val
#endif
);

#endif /* ascdate_h */
