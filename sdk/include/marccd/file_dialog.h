#ifndef _file_dialog_h
#define _file_dialog_h

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


extern Widget create_frame_file_selection_dialog(Widget parent_w, const char *name);

extern Widget create_image_file_selection_dialog(Widget parent_w, const char *name);

extern void update_frame_memory_dest_menu(void);

#endif /* _file_dialog_h */
