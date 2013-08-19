#ifndef xmupdate_h
#define xmupdate_h

#include <X11/Intrinsic.h>

#include "entry_callbacks.h"

/* Pass this the update procedure */
typedef struct _UpdateList {
   Widget widget;
} UpdateList;


/* The address of this structure should be stored in userData to
   allow proper updating.
*/
typedef struct _UpdateData {
   void	*data_addr;
   void	*data_type;
   void	*data_format;
   void	*callback_proc;
   void	*callback_data;
} UpdateData;

typedef struct {
   char *label;
   void * callback;
   updatable_radio_toggle_callback_data cb_data;
   int flag;
} updatable_radiobox_button_configuration;

Widget make_updatable_rbtoggle_button(Widget parent_w, const char *label, void *callback, void *cb_data);

Widget make_updatable_radiobox(Widget parent_w, int frame, const char *title, UpdateData *update_data,  updatable_radiobox_button_configuration *configuration_list);


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void update_widget_list(
#if NeedFunctionPrototypes
UpdateList *update_list
#endif
);

extern Widget make_updatable_textfield(
#if NeedFunctionPrototypes
Widget parent_w,
UpdateData *update_data,
UpdateList *update_list,
void *data,
void *type,
const char *format,
int ncolumns,
int maxlength,
void *entry_cb
#endif
);

extern Widget create_updatable_label(Widget parent, String name, ArgList arglist, Cardinal argcount, const char *initial_label, UpdateData *update_data, void *data_pointer, const char *data_type, const char *format);

extern Widget create_updatable_textfield(Widget parent, String name, ArgList arglist, Cardinal argcount, const char *initial_label, UpdateData *update_data, void *data_pointer, const char *data_type, const char *format, XtCallbackProc callbackproc, void *callbackdata);

extern Widget create_updatable_toggle_button(Widget parent, String name, ArgList arglist, Cardinal argcount, const char *initial_label, UpdateData *update_data, void *data_pointer, const char *data_type, const char *format, XtCallbackProc callbackproc, void *callbackdata);

extern Widget create_updatable_scale(Widget parent, String name, ArgList arglist, Cardinal argcount, const char *initial_label, UpdateData *update_data, void *data_pointer, const char *data_type, const char *format, XtCallbackProc callbackproc, void *callbackdata);


#if defined(_XBAE)

extern Widget create_updatable_matrix(Widget parent, String name, int nrows, int ncols, ArgList arglist, Cardinal argcount, UpdateData *update_data, char **row_labels, char **col_labels, void **cell_data, char **cell_data_types, char **cell_formats, XtCallbackProc **call_callback_procs, void **cell_callback_data, XtCallbackProc *callback_proc, void *callback_data);

#else

extern Widget create_updatable_row_col( Widget parent_w, String name, int nrows, int ncols, ArgList arglist, Cardinal argcount, UpdateList *update_list, UpdateData *update_data, int *nwidgets, char **row_labels, char **col_labels, void **cell_data, char **cell_data_types, char **cell_formats, XtCallbackProc **cell_callback_procs, void **cell_callback_data, XtCallbackProc *callback_proc, void *callback_data);

#endif

#endif /* xmupdate_h */
