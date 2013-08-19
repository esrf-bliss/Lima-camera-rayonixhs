#ifndef status_window_h
#define status_window_h

#include <X11/Intrinsic.h>

#define PROTOCOL_FUNCTION_STOP	0
#define PROTOCOL_FUNCTION_PAUSE	1
#define PROTOCOL_FUNCTION_SKIP	2

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget create_status_window(Widget parent_w, const char *name);

extern void restart_status_window(void *data);

extern void register_protocol_function(int type, int (*function)(void));

extern void execute_protocol_function(int type);

void update_server_temp(double new_temp);

void update_server_press(double new_press);

void disable_status_menu_items_for_remote_mode();

void enable_status_menu_items_after_remote_mode();

#endif /* status_window_h */
