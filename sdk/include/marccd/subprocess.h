#ifndef subprocess_h
#define subprocess_h

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


void register_subprocess(
#if NeedFunctionPrototypes
int pid,
char *description
#endif
);

char *find_subprocess(
#if NeedFunctionPrototypes
int pid
#endif
);

void remove_subprocess(
#if NeedFunctionPrototypes
int pid 
#endif
);

#endif /* subprocess_h */
