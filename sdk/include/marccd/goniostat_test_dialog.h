#ifndef goniostat_test_dialog_h
#define goniostat_test_dialog_h

#include "goniostat.h"

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */



extern void create_goniostat_test_dialog(
#if NeedFunctionPrototypes
Widget w,
int item_no
#endif
);

extern Widget create_goniostat_test_subform(
#if NeedFunctionPrototypes
Widget parent_w,
GoniostatType type
#endif
);

extern void goniostat_test_dialog_cb(
#if NeedFunctionPrototypes
Widget calling_pb,
void *data,
XmPushButtonCallbackStruct *cbs
#endif
);


extern void goniostat_test_cb(
#if NeedFunctionPrototypes
Widget calling_pb,
void *data,
XmPushButtonCallbackStruct *cbs
#endif
);


#endif /* goniostat_test_dialog_h */
