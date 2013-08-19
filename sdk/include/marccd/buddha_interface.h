#ifndef buddha_interface_h
#define buddha_interface_h

#include "parameters.h"

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int read_buddha_params(
#if NeedFunctionPrototypes
const char *name_ptr
#endif
);

extern void import_buddha_params(
#if NeedFunctionPrototypes
geometry_parameters *diffraction_geometry_parameters
#endif
);

extern void export_buddha_params(
#if NeedFunctionPrototypes
geometry_parameters *diffraction_geometry_parameters
#endif
);

extern int write_centroids_file(int fractional, const char *filename, int npoints, double *xdata, double *ydata, double *sumdata, int nfast, int nslow);
extern int write_fortran_file(const char *filename, void *data, size_t itemsize, size_t nitems);



#endif /* buddha_interface_h */
