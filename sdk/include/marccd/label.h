#ifndef label_h
#define label_h

#include "image.h"

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern XtEventHandler handle_label_pointer(
#if NeedFunctionPrototypes
Widget     w,
data_image * (*data)(),
XEvent     *event,
Boolean    *continue_to_dispatch
#endif
);

extern XtEventHandler handle_label_exposure(
#if NeedFunctionPrototypes
Widget w,
data_image * (*data)(),
XEvent *event,
Boolean    *continue_to_dispatch
#endif
);


#endif /* label_h */
