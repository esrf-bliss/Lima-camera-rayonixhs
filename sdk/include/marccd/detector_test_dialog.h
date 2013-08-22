#ifndef detector_test_dialog_h
#define detector_test_dialog_h

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



extern void create_detector_test_dialog(
#if NeedFunctionPrototypes
Widget w,
int item_no
#endif
);

extern Widget create_detector_test_subform(
#if NeedFunctionPrototypes
Widget parent_w,
char *name,
DetectorType type
#endif
);

extern void detector_test_dialog_cb(
#if NeedFunctionPrototypes
Widget calling_pb,
void *data,
XmPushButtonCallbackStruct *cbs
#endif
);


extern void detector_test_cb(
#if NeedFunctionPrototypes
Widget calling_pb,
void *data,
XmPushButtonCallbackStruct *cbs
#endif
);


#endif /* detector_test_dialog_h */
