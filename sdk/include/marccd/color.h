#ifndef color_h
#define color_h

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int rgb_to_hsv(
#if NeedFunctionPrototypes
float r,
float g,
float b,
float *hp,
float *sp,
float *vp
#endif
);

extern int hsv_to_rgb(
#if NeedFunctionPrototypes
float h,
float s,
float v,
float *rp,
float *gp,
float *bp
#endif
);

#endif /* color_h */
