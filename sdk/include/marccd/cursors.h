#ifndef cursors_h
#define cursors_h

#include "graphobj.h"

#define DATAFRAME_CONTEXT	(1)
#define VIDEO_CONTEXT		(1 << 1)

typedef enum {
CURSOR_NULL,
CURSOR_VECTOR,
CURSOR_LAYER_0,
CURSOR_LAYER_N,
CURSOR_BEAM,
CURSOR_VIDEO_CROSSHAIR_BEAM,
CURSOR_VIDEO_CROSSHAIR_CRYSTAL,
CURSOR_VIDEO_SCALE,
CURSOR_ZOOM,
CURSOR_SPOT_SELECTOR,
CURSOR_AOI,
CURSOR_ANGLE,
CURSOR_SPOT_MARKER,
CURSOR_PROFILE,
CURSOR_RESOLUTION,
CURSOR_TEXT,
CURSOR_INDEX_2D,
CURSOR_INDEX_3D
} CursorType;

#define CURSOR_LATTICE_LINE	CURSOR_VECTOR
#define CURSORS_MAX		16


#if 0
#define CURSOR_NULL		0
#define CURSOR_VECTOR		1
#define CURSOR_LAYER_0		2
#define CURSOR_LAYER_N		3
#define CURSOR_BEAM		4
#define CURSOR_VIDEO_CROSSHAIR_BEAM:
#define CURSOR_VIDEO_CROSSHAIR_CRYSTAL:
#define CURSOR_ZOOM		5
#define CURSOR_SPOT_SELECTOR	6
#define CURSOR_AOI		7
#define CURSOR_ANGLE		8
#define CURSOR_SPOT_MARKER	9
#define CURSOR_PROFILE		10
#define CURSOR_RESOLUTION	11
#define CURSOR_LATTICE_LINE	CURSOR_VECTOR
#endif
	

#define CURSOR_IMAGE_COORDS		1
#define CURSOR_DATA_COORDS		2
#define CURSOR_RECIPROCAL_COORDS	3


typedef struct _cursor_any {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
} cursor_any;

typedef struct _cursor_lattice_line {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int length;
   int azimuth;
   int n_orders;
   int reciprocal_spacing;
   int max;
   int min;
   int mean;
} cursor_lattice_line;

typedef struct _cursor_layer_0 {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int radius;
   int orientation_theta1;
   int orientation_theta2;
} cursor_layer_0;

typedef struct _cursor_layer_n {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int radius;
   int layer_number;
   int direct_spacing;
} cursor_layer_n;

typedef struct _cursor_beam {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int dx, dy;
   int value;
   int sum;
   int max;
   int min;
   int mean;
   int intensity;
   int sigma;
   int background;
} cursor_beam;

typedef struct _cursor_resolution {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int radius;
} cursor_resolution;

typedef struct _cursor_zoom {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
} cursor_zoom;

typedef struct _cursor_spot_selector {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int dx, dy;
   int value;
   int sum;
   int max;
   int min;
   int mean;
   int intensity;
   int sigma;
   int background;
} cursor_spot_selector;

typedef struct _cursor_angle {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int length1;
   int order1;
   int angle1;
   int length2;
   int order2;
   int angle2;
   int angle;
} cursor_angle;

typedef struct _cursor_profile {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int width;
   int height;
} cursor_profile;

typedef struct _cursor_aoi {
   int type;
   int x, y;
   graphobj *glyph;
   graphobj *data_glyph;
   void (*getdata_f)();
   void (*image_to_data)();
   void (*data_to_image)();
   int selected;
   int active;
   int visible;
   int active_context;
   int active_selector;
   int drag_resizable;
   int width;
   int height;
} cursor_aoi;

typedef union _cursor {
   int 			type;
   cursor_any		any;
   cursor_lattice_line	lattice_line;
   cursor_layer_0	layer_0;
   cursor_layer_n	layer_n;
   cursor_beam		beam;
   cursor_resolution	resolution;
   cursor_zoom		zoom;
   cursor_spot_selector	spot_selector;
   cursor_angle		angle;
   cursor_aoi		aoi;
   cursor_profile	profile;
   int 			pad[32];
} cursor;


/* Function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void set_default_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern cursor *default_cursor(
#if NeedFunctionPrototypes
void
#endif
);

extern void set_default_video_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern cursor *default_video_cursor(
#if NeedFunctionPrototypes
void
#endif
);

extern void set_selected_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern cursor *selected_cursor(
#if NeedFunctionPrototypes
void
#endif
);

extern void set_cursor_selector(
#if NeedFunctionPrototypes
cursor *the_cursor,
int selector
#endif
);

extern void draw_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int coord_type,
void *imagep,
int context
#endif
);

extern void *create_cursor(
#if NeedFunctionPrototypes
int type
#endif
);

extern void destroy_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern int testhit_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int x,
int y,
int coord_type,
int tolerance
#endif
);

extern int select_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern int deselect_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern int toggleselect_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern int testselect_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor
#endif
);

extern void set_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int property,
int p1,
int p2,
int coord_type
#endif
);

extern void move_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int property,
int p1,
int p2,
int coord_type
#endif
);

extern void query_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int property,
int *p1,
int *p2,
int coord_type
#endif
);


extern cursor *register_cursor(
#if NeedFunctionPrototypes
int type
#endif
);

extern cursor *retrieve_cursorbyid(
#if NeedFunctionPrototypes
int id
#endif
);

extern cursor *retrieve_cursorbytype(
#if NeedFunctionPrototypes
int type
#endif
);

extern cursor *retrieve_hit_cursor(
#if NeedFunctionPrototypes
int x,
int y,
int coord_type,
int tolerance,
int context
#endif
);

extern void refresh_cursors(
#if NeedFunctionPrototypes
void *imagep,
int context
#endif
);

extern int activate_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int context
#endif
);

extern int deactivate_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int context
#endif
);

extern int toggleactivate_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int context
#endif
);

extern int testactivate_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int context
#endif
);

extern int testvisible_cursor(
#if NeedFunctionPrototypes
cursor *the_cursor,
int context
#endif
);

extern void update_cursor_coords(
#if NeedFunctionPrototypes
cursor *the_cursor,
int coord_type,
void *imagep
#endif
);

#endif /* cursor_h */
