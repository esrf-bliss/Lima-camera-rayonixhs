#ifndef overlay_h
#define overlay_h



/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void overlay_spots(
#if NeedFunctionPrototypes
int overlay
#endif
);

void set_overlay_size (
#if NeedFunctionPrototypes
int size,
int magnify
#endif
);

extern void refresh_overlay(
#if NeedFunctionPrototypes
void *imagep
#endif
);

#endif /* overlay_h */
