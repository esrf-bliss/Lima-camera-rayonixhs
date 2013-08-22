#ifndef detector_dialog_h
#define detector_dialog_h

#include "xmupdate.h"

#include "detector.h"

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */



extern Widget config_detector_dialog(
#if NeedFunctionPrototypes
Widget w,
const char *name
#endif
);

extern Widget create_detector_subwindow(
#if NeedFunctionPrototypes
Widget parent_w,
char *name,
DetectorValues *detector_valuesp
#endif
);

extern void detector_dialog_cb(
#if NeedFunctionPrototypes
Widget calling_pb,
void *data,
XmPushButtonCallbackStruct *cbs
#endif
);

extern Widget create_detector_forms(
#if NeedFunctionPrototypes
Widget parent_w,
char *name,
int ndetectors,
DetectorValues *detector_valuesp
#endif
);

extern void detector_type_cb(
#if NeedFunctionPrototypes
Widget calling_w,
void *data,
XmPushButtonCallbackStruct *tbcbs
#endif
);

extern void update_detector_forms(
#if NeedFunctionPrototypes
void
#endif
);

extern Widget create_detector_configuration_form(
#if NeedFunctionPrototypes
Widget parent_w,
char *name,
DetectorValues *detector_valuesp
#endif
);


#endif /* detector_dialog_h */
