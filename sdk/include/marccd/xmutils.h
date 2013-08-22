#ifndef xmutils_h
#define xmutils_h


#include <stdarg.h>
#include <stdio.h>

#include <Xm/Xm.h>
#include <Xm/SelectioB.h>

typedef struct {
   int done;
   int check_for_valid_file;
   int allow_directory_creation;
   char filename[256];
} browse_cb_struct;

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void lprintf( Widget widget, const char *format, ...);

extern void tfprintf( Widget widget, char *format, ...);

extern Widget update_alertf(Widget parent_w, Widget old_alert, int type, char *format, ...);
extern Widget alertf( Widget parent_w, int type, char *format, ...);
extern Widget xtarg_alertf(Widget parent_w, ArgList arglist, Cardinal ac, int type, char *format, ...);
extern void cancel_alert(Widget alert);
extern void reraise_alert( void);

extern void TurnOffSashTraversal( Widget paned_w);

extern int tprintf( void *text_w, const char *format, ...);

extern int vtprintf( void *text_w, const char *format, va_list args);

extern char *stringofXmString( XmString xmstring);

extern void flash_label( Widget widget, Pixel fg, Pixel bg);

extern int yes_no_dialogf( Widget parent_w, int default_answer, char *yes_label, char *no_label, char *format, ...);

extern int switch_dialogf(Widget parent_w, int *return_answer, int default_answer, int ncases, int *cases, char **case_labels, char *format, ...);

extern Widget waitf( Widget parent_w, int type, char *format, ...); 

extern void finish_waitf(Widget wait_notice);

extern void force_update( Widget widget);

extern Widget update_waitf(Widget wait_notice, Widget parent_w, int type, char *format, ...);

extern char * prompt_dialogf( Widget parent_w, char *yes_label, char *no_label, int supply_default, char *format, ...);

extern char * text_dialogf(Widget parent_w, char *yes_label, char *no_label, char *text_buffer, int buffer_length, int supply_default, char *format, ...);

extern Widget OptionButtonFromOptionMenuPushButton( Widget w);

extern Widget wait_scalef(Widget parent_w, int min, int current, int max, int decimal_places, char *format, ...);
extern void update_wait_scalef(Widget dialog, int current);
extern void destroy_wait_scalef(Widget dialog);

extern void browse_file_cb( Widget dialog, XtPointer client_data, XmFileSelectionBoxCallbackStruct *cbs);
extern void browse_directory_cb( Widget dialog, XtPointer client_data, XmFileSelectionBoxCallbackStruct *cbs);

#endif /* xmutils_h */
