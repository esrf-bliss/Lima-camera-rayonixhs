#ifndef priority_h
#define priority_h

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


int set_high_priority(
#if NeedFunctionPrototypes
void
#endif
);

int set_normal_priority(
#if NeedFunctionPrototypes
void
#endif
);


#endif /* priority_h */
