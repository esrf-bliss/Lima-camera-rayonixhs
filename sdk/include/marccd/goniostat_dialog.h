#ifndef goniostat_dialog_h
#define goniostat_dialog_h

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */



extern void config_goniostat_dialog(
#if NeedFunctionPrototypes
Widget w,
int item_no
#endif
);

extern Widget create_config_goniostat_subwindow(
#if NeedFunctionPrototypes
Widget parent_w,
char  *name
#endif
);

extern Widget create_goniostat_configuration_form(
#if NeedFunctionPrototypes
Widget parent_w,
char *name
#endif
);

extern void config_goniostat_cb(
#if NeedFunctionPrototypes
Widget calling_pb,
void *data,
XmPushButtonCallbackStruct *cbs
#endif
);

extern void goniostat_type_cb(
#if NeedFunctionPrototypes
Widget calling_pb,
void *data,
XmPushButtonCallbackStruct *cbs
#endif
);

extern void update_config_goniostat(void);

extern int goniostat_alignment_dialog(Widget parent_w);

#endif /* goniostat_dialog_h */
