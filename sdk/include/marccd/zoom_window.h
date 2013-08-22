#ifndef zoom_window_h
#define zoom_window_h

#include "frame.h"


/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget create_zoom_window(
#if NeedFunctionPrototypes
Widget parent_w,
int width,
int height
#endif
);

extern void fill_zoom_window(
#if NeedFunctionPrototypes
Widget parent_w,
int zoom,
int zoom_x,
int zoom_y,
data_frame *source_frame
#endif
);

extern data_image *get_zoomed_image( 
#if NeedFunctionPrototypes
void
#endif
);


extern void set_zoom_state(
#if NeedFunctionPrototypes
int *zoom,
int *x,
int *y
#endif
);


extern void get_zoom_state(
#if NeedFunctionPrototypes
int *zoom,
int *x,
int *y
#endif
);

extern void handle_mag_change_cb(
#if NeedFunctionPrototypes
Widget w,
void *data,
void *cbs
/*data_image * (*source_image)(),
XmPushButtonCallbackStruct *cbs
*/
#endif
);


extern Widget create_color_swatch(
#if NeedFunctionPrototypes
Widget parent_w
#endif
);

extern void render_color_swatch(
#if NeedFunctionPrototypes
int render_min,
int render_max,
unsigned long *colortable,
size_t n_colortable_entries
#endif
);

extern void write_values_on_widget(
#if NeedFunctionPrototypes
Widget widget,
int zoom,
int zoom_x,
int zoom_y,
int transformation,
data_frame *framep
#endif
);

extern void update_zoom_window(
#if NeedFunctionPrototypes
void
#endif
);


#endif /* zoom_window_h */
