#ifndef coordinates_h
#define coordinates_h

#include "frame.h"
#include "image.h"

#define FIXED_POINT_CONSTANT 10000000   /* Allows maximum coordinate of +/- 214.7418113  to be stored in signed long */

typedef enum _CoordinateType {
   CoordsNative, CoordsAutomar, CoordsMosflm, CoordsDenzo, CoordsBuddha, CoordsXengen, CoordsCadmusPCS, CoordsSiemensPC, CoordsXedar
   } CoordinateType;

typedef struct _UserCoordinates {
   int user_coord_transformation;
   int user_origin_x;
   int user_origin_y;
} UserCoordinates;


/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int set_user_coordinate_type(int coordinate_type);

extern int get_user_coordinate_type(void);

extern void set_data_to_graphics_transformation ( data_image *imagep, int render_transformation, int data_xorigin, int data_yorigin, int image_xorigin, int image_yorigin, double zoom);

extern void get_data_to_graphics_transformation ( data_image *imagep, int *render_transformation, int *data_xorigin, int *data_yorigin, int *image_xorigin, int *image_yorigin, double *data_pixels_per_graphics_pix); 

extern void data_to_graphics( data_image *imagep, int *gx, int *gy, int dx, int dy);

extern void graphics_to_data( data_image *imagep, int *dx, int *dy, int gx, int gy);

extern void fgraphics_to_data( data_image *imagep, double *dx, double *dy, int gx, int gy);

extern int data_to_user_image(data_image *imagep, int *ux, int *uy, int dx, int dy);

extern int data_to_user_frame(data_frame *framep, int *ux, int *uy, int dx, int dy);

extern int data_to_user(int *ux, int *uy, int dx, int dy, int fast, int nslow);

extern int fdata_to_fuser_image(data_image *imagep, double *ux, double *uy, double dx, double dy);

extern int fmm_data_to_fmm_user_frame(data_frame *framep, double *ox, double *oy, double ix, double iy);

extern int fdata_to_fuser_frame(data_frame *framep, double *ux, double *uy, double dx, double dy);

extern int fdata_to_fuser(double *ux, double *uy, double dx, double dy, int nfast, int nslow);

extern int fuser_to_fdata_image(data_image *imagep, double *ox, double *oy, double ix, double iy);

extern int fmm_user_to_fmm_data_frame(data_frame *framep, double *ox, double *oy, double ix, double iy);

extern int fuser_to_fdata_frame(data_frame *framep, double *ox, double *oy, double ix, double iy);

extern int fuser_to_fdata(double *ox, double *oy, double ix, double iy, int nfast, int nslow);

extern int fmm_user_to_fmm_user_frame(data_frame *framep, double *ox, double *oy, int user_type_out, double ix, double iy, int user_type_in);

extern char * coordinate_system_name(int coordinate_type);

#endif /* coordinates_h */
