#ifndef sidebar_h
#define sidebar_h

#include <X11/Intrinsic.h>


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget create_sidebar (Widget parent_w, const char *name, int ac_in, Arg *al_in);

extern void set_sidebar_window_focus(Widget parent_widget, Widget focus_widget);

#endif /* sidebar_h */
