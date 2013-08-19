#ifndef graphics_h
#define graphics_h

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

/* graphics.h - for handling graphical windows
 *              Currently this is only for X11 system
 */


// Will only build lookup table this many bits for larger data types
#define MAXRENDERBITS 20

/* Constant Definitions */
#define MAX_PLANES 8		/* Maximum # of allocated planes for overlays */
#define MAX_COLORS 256		/* Maximum # of colors to be allocated */


#define LINEAR_SCALE 1
#define LOG_SCALE 2

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int create_graphics_window(
#if NeedFunctionPrototypes
int argc, char **argv
#endif
);

extern void destroy_graphics_window(
#if NeedFunctionPrototypes

#endif
);

extern void monitor_graphics_window(
#if NeedFunctionPrototypes

#endif
);

extern void update_window(
#if NeedFunctionPrototypes
XRectangle *rectangles, int nrects
#endif
);

extern void mergeDatabases(
#if NeedFunctionPrototypes

#endif
);

extern void extractOpts(
#if NeedFunctionPrototypes

#endif
);

extern void usage (
#if NeedFunctionPrototypes

#endif
);

extern char *getHomeDir(
#if NeedFunctionPrototypes
char *dest 
#endif
);

extern void create_image_store(
#if NeedFunctionPrototypes

#endif
);

extern void MBperror (
#if NeedFunctionPrototypes
char *string
#endif
);

extern void MBxerror(
#if NeedFunctionPrototypes
Display *disp, XErrorEvent *event
#endif
);

extern void MBxioerror(
#if NeedFunctionPrototypes
Display *disp
#endif
);

extern void lock_colors(void);
extern void unlock_colors(void);

extern void setup_colors(
#if NeedFunctionPrototypes
Widget widget,
int colortable_type
#endif
);

extern int reset_colors(
#if NeedFunctionPrototypes
Widget w,
int spectrum_type
#endif
);

extern void scale_colors( int scale_type, size_t startarray, size_t endarray, int minvalue, int maxvalue, unsigned long **colortable, unsigned long *colors, size_t ncolors, double gamma);

extern void get_color_info(
#if NeedFunctionPrototypes
int *ncolors,
int *ncolorcells,
unsigned long **colors,
int *nplanes,
unsigned long **planemasks,
unsigned long **colortable
#endif
);

extern int get_display_image_depth(void);

extern unsigned long  get_color_overlay(
#if NeedFunctionPrototypes
void
#endif
);

extern unsigned long  get_color_overlay_planemask(
#if NeedFunctionPrototypes
void
#endif
);

extern unsigned long  get_color_background(
#if NeedFunctionPrototypes
void
#endif
);

extern unsigned long  get_color_foreground(
#if NeedFunctionPrototypes
void
#endif
);

extern XtEventHandler handle_color_swatch_pointer(
#if NeedFunctionPrototypes
Widget calling_w,
void *data,
XEvent *event
#endif
);

int get_special_color(
#if NeedFunctionPrototypes
Widget widget,
char *colorname,
unsigned long *pixelvalue
#endif
);

extern int get_a_color(
#if NeedFunctionPrototypes
Widget widget,
char *colorname,
unsigned long *pixelvalue
#endif
);

extern void copy_color_to_image_pixel(void *image_pixel, unsigned long color, int depth);
extern void copy_color_from_image_pixel(void *image_pixel, unsigned long *color, int depth);

#endif /* graphics_h */
