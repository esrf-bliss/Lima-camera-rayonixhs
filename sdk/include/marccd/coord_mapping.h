#ifndef coord_mapping_h
#define coord_mapping_h

#include "frame.h"

#define MAPPING_MAPPING_MASK				0x00ff
#define MAPPING_UNIFORM_SPECIFIED			0x0001
#define MAPPING_UNIFORM_FRAMEHEADER			0x0002
#define MAPPING_BUDDHA_SPLINE				0x0004

#define MAPPING_POSITION_MASK				0xff00
#define MAPPING_DETECTOR_POSITION_SPECIFIED		0x0100
#define MAPPING_DETECTOR_POSITION_FROM_FRAMEHEADER	0x0200
#define MAPPING_DETECTOR_POSITION_FROM_PARAMETERS	0x0400

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int init_coordinate_mapping(
#if NeedFunctionPrototypes
data_frame *framep,
int mapping_type,
...
#endif
);

extern int pix_to_mm(
#if NeedFunctionPrototypes
data_frame *framep, double *x_mm, double *y_mm, double x_pix, double y_pix
#endif
);

extern int mm_to_pix(
#if NeedFunctionPrototypes
data_frame *framep, double *x_pix, double *y_pix, double x_mm, double y_mm
#endif
);

extern int mean_pix_to_mm(
#if NeedFunctionPrototypes
data_frame *framep, double *pixelsize_x, double *pixelsize_y
#endif
);

extern int init_diffraction_geometry_mapping(
#if NeedFunctionPrototypes
data_frame *framep, int mapping_type, ...
#endif
);

extern int detmm_to_E(
#if NeedFunctionPrototypes
data_frame *framep, double *x_E, double *y_E, double *z_E, double x_mm, double y_mm
#endif
);

extern int E_to_detmm(
#if NeedFunctionPrototypes
data_frame *framep, double *x_mm, double *y_mm, double x_E, double y_E, double z_E
#endif
);

extern int pix_to_rhkl(
#if NeedFunctionPrototypes
data_frame *framep, double *rh, double *rk, double *rl, double x_pix, double y_pix
#endif
);

extern int pix3d_to_rhkl(
#if NeedFunctionPrototypes
data_frame *framep, double *rh, double *rk, double *rl, double x_pix, double y_pix, double angle
#endif
);

#endif /* coord_mapping_h */
