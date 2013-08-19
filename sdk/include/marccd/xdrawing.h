#ifndef xdrawing_h
#define xdrawing_h

#include <X11/Intrinsic.h>


/* Global Variables */


/* Function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void	draw_set_context(
#if NeedFunctionPrototypes
Widget widget
#endif
);

extern void	draw_set_graphics_context(
#if NeedFunctionPrototypes
GC gc
#endif
);

extern void	draw_open(
#if NeedFunctionPrototypes
void
#endif
);

extern void	draw_close(
#if NeedFunctionPrototypes
void
#endif
);

extern void	draw_flush(
#if NeedFunctionPrototypes
void
#endif
);

extern void	draw_clip(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_clear(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_line(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_circle_fill(
#if NeedFunctionPrototypes
int r,
int xc,
int yc
#endif
);

extern void	draw_circle_open(
#if NeedFunctionPrototypes
int r,
int xc,
int yc
#endif
);

extern void	draw_box_fill(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_box_open(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_cross(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_star(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_triangle_open(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void	draw_triangle_fill(
#if NeedFunctionPrototypes
int x1,
int y1,
int x2,
int y2
#endif
);

extern void draw_text(
#if NeedFunctionPrototypes
int x,
int y,
char *string
#endif
);

extern void	draw_angle(
#if NeedFunctionPrototypes
int x,
int y,
double length1, 
double angle1,
double length2,
double angle2
#endif
);

extern void	draw_scale(
#if NeedFunctionPrototypes
int x,
int y,
int length,
int major_ticks,
int minor_ticks,
int orientation
#endif
);

extern void draw_set_context_pm(
Pixmap*
);

extern void draw_index_pair(int x, int y, int h, int k);
extern void draw_index_triplet(int x, int y, int h, int k, int l);

#endif /* xdrawing_h */
