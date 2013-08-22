#ifndef tool_window_h
#define tool_window_h

#include "frame.h"


/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget create_tool_window(
#if NeedFunctionPrototypes
Widget parent_w,
int width,
int height
#endif /* NeedFunctionPrototypes */
);

Widget createpixmaptoggle(
#if NeedFunctionPrototypes
Widget parent_w,
char *name,
Pixmap labelpixmap,
Pixmap selectpixmap
#endif /* NeedFunctionPrototypes */
);

extern void handle_tool_change(
#if NeedFunctionPrototypes
Widget calling_w,
void *data,
XmRowColumnCallbackStruct *cbs
#endif /* NeedFunctionPrototypes */
);

extern void update_tool_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_pointer_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_zoom_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_angle_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_aoi_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_lattice_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_spot_selector_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_profile_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);

extern void update_crystal_display(
#if NeedFunctionPrototypes
Widget calling_w,
data_image *imagep,
int button_x,
int button_y,
int fast
#endif /* NeedFunctionPrototypes */
);


void reset_zoom_cursor(
#if NeedFunctionPrototypes
Widget calling_w
#endif /* NeedFunctionPrototypes */
);

int xm_setup_stack_from_frame(
#if NeedFunctionPrototypes
Widget calling_w,
data_frame *framep,
int position,
int stack_size
#endif /* NeedFunctionPrototypes */
);

extern void show_goniostat_window(void);
extern void show_graph_window(void);

struct RectCartInt get_aoi_coords(void);

#endif /* tool_window_h */
