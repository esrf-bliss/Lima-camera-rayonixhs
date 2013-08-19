#ifndef mmx_h
#define mmx_h

#include <X11/Intrinsic.h>
#include <Xm/FileSB.h>

#include "frame.h"


/* data structure type definitions */


/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void initialize_radiobox(
#if NeedFunctionPrototypes
Widget widget,
void (*callback_proc)(),
void *callback_data
#endif
);

extern void file_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void edit_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void view_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void option_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void plot_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void help_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void config_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void acquire_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void display_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void reduce_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void test_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void load_bitmap(
#if NeedFunctionPrototypes
Widget dialog,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);

extern void load_xrayimage_cb(
#if NeedFunctionPrototypes
Widget dialog,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);

extern void load_sequential_file(
#if NeedFunctionPrototypes
Widget dialog,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);

extern void save_frame_cb(
#if NeedFunctionPrototypes
Widget dialog,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);


extern void sum_files_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void merge_files_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void average_files_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void stat_files_cb(
#if NeedFunctionPrototypes
Widget w,
void * callback_data,
void * cbs
#endif
);

extern void add_to_file_list(
#if NeedFunctionPrototypes
Widget dialog,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);

extern void sum_images(
#if NeedFunctionPrototypes
Widget parent_w,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);

extern void merge_images(
#if NeedFunctionPrototypes
Widget parent_w,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);

extern void average_images(
#if NeedFunctionPrototypes
Widget parent_w,
XtPointer client_data,
XmFileSelectionBoxCallbackStruct *cbs
#endif
);

extern void demux_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void swap_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void togglesign_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void applyflatfield_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void subtractbackground_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void special_operation_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void createconstant_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void createspecial_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void applyspatial_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

extern void showheader_image(
#if NeedFunctionPrototypes
Widget parent_w,
void *client_data,
void *cbs
#endif
);

#endif /* mmx_h */

