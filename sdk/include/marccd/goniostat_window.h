#ifndef goniostat_window_h
#define goniostat_window_h

#include "goniostat.h"

#define BLINK_INTERVAL 500
#define ANGLE_UPDATE_INTERVAL 100
#define SHUTTER_CHECK_INTERVAL 500


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget create_goniostat_window(
#if NeedFunctionPrototypes
Widget parent_w
#endif
);

extern Widget rebuild_goniostat_subwindow(
#if NeedFunctionPrototypes
void
#endif
);

extern void update_goniostat_window(
#if NeedFunctionPrototypes
int update_next
#endif
);

extern void enable_goniostat_window(int state);

extern int track_goniostat_wp(
#if NeedFunctionPrototypes
XtWorkProcId  *WPIdp
#endif
);

int track_goniostat_color_to(
#if NeedFunctionPrototypes
XtIntervalId *TOIdp
#endif
);

void flash_goniostat_window(
#if NeedFunctionPrototypes
int state
#endif
);

extern int operate_shutter_wp(
#if NeedFunctionPrototypes
#endif
);

extern void get_axis_type_format_and_entry_cb( axis_parameters *axisp, char **data_typep, char **formatp, void **entry_cb);


#endif /* goniostat_window_h */
