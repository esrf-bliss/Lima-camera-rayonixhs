#ifndef graphobj_h
#define graphobj_h


/* Graphical object types */
#define GRAPHOBJ_NULL		  0
#define GRAPHOBJ_LINE		  1
#define GRAPHOBJ_CIRCLE		  2
#define GRAPHOBJ_CIRCLE_OPEN	102
#define GRAPHOBJ_CIRCLE_FILL	202
#define GRAPHOBJ_SQUARE		  3
#define GRAPHOBJ_SQUARE_OPEN	103
#define GRAPHOBJ_SQUARE_FILL	203
#define GRAPHOBJ_RECTANGLE	  4
#define GRAPHOBJ_RECTANGLE_OPEN	104
#define GRAPHOBJ_RECTANGLE_FILL	204
#define GRAPHOBJ_CROSS		  5
#define GRAPHOBJ_STAR		  6
#define GRAPHOBJ_VECTOR		  7
#define GRAPHOBJ_TRIANGLE	  8
#define GRAPHOBJ_TRIANGLE_OPEN	108
#define GRAPHOBJ_TRIANGLE_FILL	208
#define GRAPHOBJ_ANGLE		  9
#define GRAPHOBJ_ANGLE_OPEN	109
#define GRAPHOBJ_ANGLE_FILL	209
#define GRAPHOBJ_SCALE		 10
#define GRAPHOBJ_TEXT		 11
#define GRAPHOBJ_INDEX_2D	 12
#define GRAPHOBJ_INDEX_3D	 13

/* Graphical object properties */
#define LINE_START		1
#define LINE_END		2
#define CIRCLE_CENTER		3
#define CIRCLE_RADIUS		4
#define CIRCLE_EDGE		5
#define BOX_CENTER		6
#define BOX_CORNER		7
#define BOX_ANCHOR_CORNER	8
#define BOX_MOVING_CORNER	9
#define BOX_WIDTH		10
#define ANGLE_VERTEX		11
#define ANGLE_ANGLE		12
#define ANGLE_VECTOR1		13
#define ANGLE_VECTOR2		14
#define ANGLE_ENDPOINT1		15
#define ANGLE_ENDPOINT2		16
#define ANGLE_LENGTH1		17
#define ANGLE_LENGTH2		18
#define ANGLE_ANGLE1		19
#define ANGLE_ANGLE2		20
#define OBJECT_CENTER		21
#define OBJECT_CORNER_1		22
#define OBJECT_CORNER_2		23
#define OBJECT_CORNER_3		24
#define OBJECT_CORNER_4		25
#define OBJECT_EDGE_1		26
#define OBJECT_EDGE_2		27
#define OBJECT_EDGE_3		28
#define OBJECT_EDGE_4		29
#define OBJECT_SIZE		30
#define OBJECT_SIZE_WIDTH	31
#define OBJECT_SIZE_HEIGHT	32
#define OBJECT_CENTER_VERTICAL	33
#define OBJECT_CENTER_HORIZONTAL	34
#define OBJECT_INDEX_2D		35
#define OBJECT_INDEX_3D		36

#define INTERNAL_ACTIVE_SELECTOR	100

#define GRAPHOBJ_MAXSELECTORS	8

typedef struct _graphobj_generic {
   int type;
   void  (*draw_function)(int arg1, int arg2, int arg3, ...);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int arg1,arg2;
   int arg3,arg4;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_generic;

typedef struct _graphobj_square {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x,y;
   int width;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_square;

typedef struct _graphobj_line {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_line;

typedef struct _graphobj_circle {
   int type;
   void  (*draw_function)(int r, int x, int y);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x,y;
   int r;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_circle;

typedef struct _graphobj_circle_open {
   int type;
   void  (*draw_function)(int r, int x, int y);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x,y;
   int r;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_circle_open;

typedef struct _graphobj_circle_fill {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x,y;
   int r;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_circle_fill;

typedef struct _graphobj_square_open {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x,y;
   int width;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_square_open;

typedef struct _graphobj_square_fill {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x,y;
   int width;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_square_fill;

typedef struct _graphobj_rectangle {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_rectangle;

typedef struct _graphobj_rectangle_open {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_rectangle_open;

typedef struct _graphobj_rectangle_fill {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_rectangle_fill;

typedef struct _graphobj_cross {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_cross;

typedef struct _graphobj_star {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_star;

typedef struct _graphobj_vector {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_vector;

typedef struct _graphobj_triangle {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_triangle;

typedef struct _graphobj_triangle_open {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_triangle_open;

typedef struct _graphobj_triangle_fill {
   int type;
   void  (*draw_function)(int x1, int y1, int x2, int y2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x1,y1;
   int x2,y2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_triangle_fill;

typedef struct _graphobj_angle {
   int type;
   void  (*draw_function)(int x, int y, double length1, double angle1, double length2, double angle2);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x, y;
   double length1, angle1;
   double length2, angle2;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_angle;

typedef struct _graphobj_scale {
   int type;
   void  (*draw_function)(int x, int y, int length, int major_ticks, int minor_ticks, int orientation);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x, y;
   int length;
   int major_ticks, minor_ticks;
   int orientation;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_scale;

typedef struct _graphobj_text {
   int type;
   void  (*draw_function)(int x, int y, char *text);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x, y;
   char *text;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_text;

typedef struct _graphobj_index_2D {
   int type;
   void  (*draw_function)(int x, int y, int h, int k);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x, y;
   int h, k;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_index_2D;

typedef struct _graphobj_index_3D {
   int type;
   void  (*draw_function)(int x, int y, int h, int k);
   int filled;
   int visible;
   int selected;
   int active_selector;
   int x, y;
   int h, k, l;
   struct _graphobj_generic *selector[GRAPHOBJ_MAXSELECTORS];
} graphobj_index_3D;

typedef union _graphobj {
   int type;
   graphobj_generic		any;
   graphobj_line		line;
   graphobj_rectangle		rectangle;
   graphobj_rectangle_open	rectangle_open;
   graphobj_rectangle_fill	rectangle_fill;
   graphobj_circle		circle;
   graphobj_circle_open		circle_open;
   graphobj_circle_fill		circle_fill;
   graphobj_square		square;
   graphobj_square_open		square_open;
   graphobj_square_fill		square_fill;
   graphobj_triangle		triangle;
   graphobj_triangle_open	triangle_open;
   graphobj_triangle_fill	triangle_fill;
   graphobj_cross		cross;
   graphobj_star		star;
   graphobj_vector		vector;
   graphobj_angle		angle;
   graphobj_scale		scale;
   graphobj_text		text;
   graphobj_index_2D		index_2D;
   graphobj_index_3D		index_3D;
   long				pad[16];
} graphobj;


/* Function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void draw_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj
#endif
);

extern void *create_graphobj(
#if NeedFunctionPrototypes
int type
#endif
);

extern void destroy_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj
#endif
);

extern int  testhit_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj,
int x,
int y,
int tolerance
#endif
);

extern int  testselect_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj
#endif
);

extern int  select_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj
#endif
);

extern int  deselect_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj
#endif
);

extern int  toggleselect_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj
#endif
);

extern void set_graphobj_selector(
#if NeedFunctionPrototypes
graphobj *graphobj,
int selector
#endif
);

void set_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj,
int property,
int p1,
int p2
#endif
);

void query_graphobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj,
int property,
int *p1,
int *p2
#endif
);

extern void draw_dataobj(
#if NeedFunctionPrototypes
graphobj *the_graphobj,
void *imagep
#endif
);

#endif /* graphobj_h */
