#ifndef graph_window_h
#define graph_window_h

#include <stdio.h>

#define GRAPH_INTENSITY_BY_PIXEL	0
#define GRAPH_INTENSITY_BY_ANGLE	1
#define GRAPH_HISTOGRAM			2



#define MAXDATASETS	5
#define MAXPOINTS	10000
#define MAXLABELS	MAXPOINTS
#define LABELSIZE	16
#define NLABELS		5
#define TEXT_LENGTH	64

typedef struct {
	int		x, y;
	int		width, height;
} Rectangle;


#include <X11/Intrinsic.h>

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget create_graph_window(
#if NeedFunctionPrototypes
Widget parent_w,
int width,
int height
#endif
);

extern void update_graph_window(
#if NeedFunctionPrototypes
void
#endif
);

extern void graphframevalueonxy(
#if NeedFunctionPrototypes
Widget parent_w,
int fast,
double dstart_x,
double dstart_y,
double dend_x,
double dend_y,
double dwidth,
double min,
double max,
data_frame *source_frame
#endif
);

extern void graphhistogramonxy(
#if NeedFunctionPrototypes
Widget parent_w,
int fast,
double dstart_x,
double dstart_y,
double dend_x,
double dend_y,
double min,
double max,
data_frame *source_frame
#endif
);

extern void fill_graph_data(
#if NeedFunctionPrototypes
Widget graph_widget,
int option,
int log_axis,
int fast,
int npoints,
float *xdata,
float *ydata,
float *tmp1,
float *tmp2,
float *tmp3
#endif
);

extern void handle_graph_pointer(
#if NeedFunctionPrototypes
Widget graph_widget,
void *data,
XEvent *event
#endif
);

extern void position_cross(
#if NeedFunctionPrototypes
XEvent *event
#endif
);

extern int print_graph_window(
#if NeedFunctionPrototypes
char *output
#endif
);

extern void zoom(
#if NeedFunctionPrototypes
Rectangle *rect
#endif
);

extern void unzoom(
#if NeedFunctionPrototypes
void
#endif
);

extern void rubber_band(
#if NeedFunctionPrototypes
Rectangle *rect
#endif
);

extern void mark_line(
#if NeedFunctionPrototypes
int set, int width
#endif
);

extern void delta_set(
#if NeedFunctionPrototypes
int set, float xdel, float ydel
#endif
);

extern void dump_graph_window_data(
#if NeedFunctionPrototypes
FILE *stream
#endif
);


#endif /* graph_window_h */
