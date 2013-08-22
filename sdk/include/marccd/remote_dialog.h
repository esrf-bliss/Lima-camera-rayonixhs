#ifndef remote_dialog_h
#define remote_dialog_h

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#define REMOTE_POPUP		0x1
#define REMOTE_START_REMOTE	0x2
#define REMOTE_POPDOWN		0x4

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void config_remote_dialog(
#if NeedFunctionPrototypes
Widget w,
int item_no,
int options
#endif
);

extern Widget create_remote_subwindow(
#if NeedFunctionPrototypes
Widget parent_w
#endif
);

extern void update_remote_dialog(
#if NeedFunctionPrototypes
void
#endif
);

int dtb_busy(void);

extern int correct_new_detector_frame(int command);

#endif /* remote_dialog_h */
