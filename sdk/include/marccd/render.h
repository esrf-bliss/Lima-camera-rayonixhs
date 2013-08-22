#ifndef render_h
#define render_h


/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

#include "frame.h"
#include "image.h"


/* Render a frame as a graphics image */
extern int render_frame (
data_image * imagep,
data_frame * framep,
double zoom,
int zoom_x,
int zoom_y,
int transformation,
unsigned long * colortable,
int sampling
);


#endif /* render_h */
