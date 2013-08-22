#ifndef pixmaps_h
#define pixmaps_h

#include <X11/Intrinsic.h>

#include "image.h"

#define LEFT_POINTER	0
#define CROSSHAIR	1
#define LAYER_0		2
#define LAYER_N		3
#define VECTOR		4
#define BOX		5
#define TARGET		6
#define MAGGLASS	7
#define AOI		8
#define ANGLE		9
#define ALIGNMENT	10
#define SPOTS		11
#define PROFILE		12
#define PLUS		13
#define MINUS		14
#define BLANK		15
#define RESOLUTION	16
#define CRYSTAL		17
#define LETTERL		18
#define LETTERM		19


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Pixmap create_pixmap_from_internal_bitmap_list(
#if NeedFunctionPrototypes
Display *display,
int image_number,
unsigned long fg,
unsigned long bg
#endif
);

extern char *create_named_image_from_internal_bitmap_list(
#if NeedFunctionPrototypes
Screen *screen,
int image_number
#endif
);

extern void destroy_named_image_from_internal_bitmap_list(
#if NeedFunctionPrototypes
int image_number
#endif
);

extern XImage *create_named_image_from_bitmapdata(
#if NeedFunctionPrototypes
Screen  *screen,
char *name,
unsigned char *data,
int width,
int height
#endif
);

extern void put_image_on_widget_pixmap(
#ifdef NeedFunctionPrototypes
Widget widget,
data_image *image
#endif
);

extern Pixmap startup_screen_pixmap(
#ifdef NeedFunctionPrototypes
Screen *screen
#endif
);


#endif /* pixmaps_h */
