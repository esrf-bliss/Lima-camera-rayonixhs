#ifndef frame_display_h
#define frame_display_h

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include "image.h"
#include "mmx_frames.h"

#define COLORTABLE_FROM_FULL_IMAGE		1
#define COLORTABLE_FROM_ZOOMED_IMAGE		2
#define COLORTABLE_FROM_AREA_OF_INTEREST	3
#define COLORTABLE_FROM_MANUAL_ENTRY		4

static char *image_extensions[] = {
   ".pgm",
   ".gray",
   ".tiff",
   ".jpg",
   ".gif",
   ".png",
   ".eps",
   ".miff",
   ".html",
   ".fits",
   };


typedef struct _DisplayParameters {
   MMXFrame    displayed_frame;
} DisplayParameters;

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern Widget create_frame_display_menu(
#if NeedFunctionPrototypes
Widget parent_w,
const char *name
#endif
);

extern void handle_frame_display_change_cb(
#if NeedFunctionPrototypes
Widget pb,
void *data,
void *cbs
#endif
);

extern void update_frame_display_menu(
#if NeedFunctionPrototypes
void
#endif
);

extern int update_frame_display(void);
extern int finished_frame_display_thread(void *thread_struct, char *error_buffer, int buflen);
extern int cancel_frame_display_thread(void *thread_struct);
extern int update_frame_display_in_thread(void **thread_handle, char *error_buffer, int buflen);


extern void set_frame_display(
#if NeedFunctionPrototypes
MMXFrame frame
#endif
);

extern MMXFrame get_frame_display(
#if NeedFunctionPrototypes
void
#endif
);


extern int display_frame_on_widget(
#if NeedFunctionPrototypes
Widget display_widget,
data_frame *a_frame
#endif
);

extern void update_displayed_filename(
#if NeedFunctionPrototypes
char *filename,
data_frame *framep
#endif
);

extern void set_write_image( int file_format); 

extern void get_write_image( int *file_format);

extern int write_image_formats(int **formats_handle);

extern int write_image(data_frame *dataframep, char *filename, int file_format, int size_fast, int size_slow, int depth);
extern int write_image_in_thread(void **thread_handle, data_frame *dataframep, char *filename, int format, int size_fast, int size_slow, int depth, char *error_buffer, int buflen);
extern int cancel_write_image_thread(void *thread_struct);
extern int finished_write_image_thread(void *thread_struct, char *error_buffer, int buflen);

extern void get_color_scaling_source(int *autoscaling, int *min, int *max);
extern void set_color_scaling_source(int autoscaling, int min, int max);
extern int test_new_color_scaling_limits(void);
extern void determine_frame_rendering_limits(data_frame *framep, long *render_min, long *render_max);

#endif /* frame_display_h */
