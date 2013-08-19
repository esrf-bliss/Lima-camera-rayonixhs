#ifndef entry_callbacks_h
#define entry_callbacks_h

#if defined(_XBAE)
#include <Xbae/Matrix.h>
#endif

typedef struct _toggle_strings {
   char true[32];
   char false[32]; } toggle_strings;

typedef struct {
   int value;
   void *storage;
   int  size;
   } updatable_radio_toggle_callback_data;
   
/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void free_data_cb (Widget widget, void *data, void *cbs);

extern void integer_entry_cb(
#if NeedFunctionPrototypes
Widget text_w,
int *new_int,
XmTextVerifyCallbackStruct *cbs
#endif
);

extern void hex_entry_cb(
#if NeedFunctionPrototypes
Widget text_w,
int *new_int,
XmTextVerifyCallbackStruct *cbs
#endif
);

extern void float_entry_cb(
#if NeedFunctionPrototypes
Widget text_w,
double *new_float,
XmTextVerifyCallbackStruct *cbs
#endif
);

extern void time_entry_cb(
#if NeedFunctionPrototypes
Widget text_w,
int *new_time,
XmTextVerifyCallbackStruct *cbs
#endif
);

extern void msec_entry_cb(
#if NeedFunctionPrototypes
Widget text_w,
int *new_msecs,
XmTextVerifyCallbackStruct *cbs
#endif
);

extern void angle_entry_cb(
#if NeedFunctionPrototypes
Widget text_w,
double *new_angle,
XmTextVerifyCallbackStruct *cbs
#endif
);

void axis_entry_cb( Widget text_w, double *new_axis, XmTextVerifyCallbackStruct *cbs);
void wavelength_entry_cb( Widget text_w, double *new_wavelength, XmTextVerifyCallbackStruct *cbs);
void energy_entry_cb( Widget text_w, double *new_energy, XmTextVerifyCallbackStruct *cbs);
void width_entry_cb( Widget text_w, double *new_width, XmTextVerifyCallbackStruct *cbs);
void baseline_stabil_entry_cb( Widget text_w, double *new_baseline, XmTextVerifyCallbackStruct *cbs);

extern void true_false_toggle_cb(
#if NeedFunctionPrototypes
Widget tb_w,
void *data,
XmToggleButtonCallbackStruct *cbs
#endif
);

extern void dtrue_false_toggle_cb(
#if NeedFunctionPrototypes
Widget tb_w,
void *data,
XmToggleButtonCallbackStruct *cbs
#endif
);

extern void enumerated_option_menu_cb( Widget calling_w, void *data, void *pbcbs);

extern void string_entry_cb(
#if NeedFunctionPrototypes
Widget text_w,
char *new_string,
XmTextVerifyCallbackStruct *cbs
#endif
);


extern void radio_toggle_cb(
#if NeedFunctionPrototypes
Widget widget,
void * callback_data,
XmToggleButtonCallbackStruct * cbs
#endif
);

#if defined(_XBAE)
extern void matrix_data_entry_cb( Widget calling_w, void *data, XbaeMatrixAnyCallbackStruct *cbs);
#endif

#endif /* entry_callbacks_h */
