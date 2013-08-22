#define GRAPH_SLIT1V_SCAN	1
#define GRAPH_SLIT1H_SCAN	2
#define GRAPH_SLIT2V_SCAN	3
#define GRAPH_SLIT2H_SCAN	4
#define GRAPH_TRANSVER_SCAN	5
#define GRAPH_TRANSHOR_SCAN	6
#define GRAPH_ROTVER_SCAN	7
#define GRAPH_ROTHOR_SCAN	8
#define GRAPH_RECENT_SCAN	9
#define GRAPH_TIME		0

#define MAXDATASETS		5
#define MAXPOINTS		10001
#define MAXLABELS		MAXPOINTS
#define LABELSIZE		16
#define NLABELS			5
#define TEXT_LENGTH		64
#define DYNAMIC_TITLES		1  //This also needs to be changed in beam_alignment.c if changed

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


extern Widget create_scan_graph_window(
#if NeedFunctionPrototypes
Widget parent_w,
Dimension width,
Dimension height
#endif
);

extern void update_scan_graph_window(
#if NeedFunctionPrototypes
void
#endif
);

extern void fill_scan_graph_data(
#if NeedFunctionPrototypes
//Widget graph_widget,
int option,
int fast,
int npoints,
double *xdata,
double *x2data,
double *ydata,
double tmp1,
double *tmp2,
#if DYNAMIC_TITLES
double *tmp3,
int graphing_axis
#else
double *tmp3
#endif
#endif
);

