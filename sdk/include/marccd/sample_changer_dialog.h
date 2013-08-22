#ifndef sample_changer_dialog_h
#define sample_changer_dialog_h

#include <X11/Xlib.h>

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget create_sample_changer_window( Widget parent_w, char *name, Arg *al, int ac);

extern void update_sample_changer_dialog(void);

extern void set_vial_just_read(int vial_read);  //Justin - Mar, 2008 - Extended Command Set - Phase2
extern void set_loaded_sample_number(int loaded_samp_num);  //Justin - Mar, 2008 - Extended Command Set - Phase2

#endif /* sample_changer_dialog_h */

