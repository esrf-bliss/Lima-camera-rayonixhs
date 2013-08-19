#ifndef crystal_alignment_window_h
#define crystal_alignment_window_h

typedef enum {
      STATE_INITIALIZE_CRYSTAL_ALIGNMENT,
      STATE_CAPTURE_BACKGROUND_IMAGE,
      STATE_MONITOR_BACKGROUND_IMAGE,
      STATE_START_SETUP_CRYSTAL_ENVIRONMENT,
      STATE_WAIT_CHANGE_CRYSTAL_ENVIRONMENT,
      STATE_START_RESTORE_CRYSTAL_ENVIRONMENT,
      STATE_CAPTURE_CRYSTAL_IMAGE,
      STATE_START_FIND_CRYSTAL,
      STATE_WAIT_FIND_CRYSTAL,
      STATE_WAIT_CRYSTAL_MOTION,
      STATE_END_CRYSTAL_ALIGNMENT,
      STATE_FAILURE,
      STATE_EXIT
   } to_states_align;

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */



extern Widget create_crystal_alignment_window(
#if NeedFunctionPrototypes
Widget parent_w,
int width,
int height
#endif
);

extern void update_crystal_alignment_window(
#if NeedFunctionPrototypes
void
#endif
);

extern int query_crystal_alignment_automatic(void);

extern void set_crystal_alignment_mode(int mode);

extern void start_crystal_alignment(int identifier);

extern void stop_crystal_alignment(void);

extern void set_crystal_aligned(int aligned, int slave_mode);

extern void define_crystal_alignment_window_focus(Widget focus_parent, Widget focus_widget);

extern void set_crystal_alignment_window_focus(void);

extern int query_crystal_aligned(void);

extern void query_crystal_aligned_position(double *x, double *y, double *z, double *xsig, double *ysig, double *zsig);

extern void enable_crystal_alignment_window(int state);

extern int save_video_still(char *filename);

extern void get_crystal_background_image(void);

extern int rotate_crystal_to(double degrees);

extern int center_xtal_in_2d(int use_gui, Widget *calling_pb, int *goniostat_started);  //Justin - Mar, 2008 - Extended Command Set - Phase2

extern void center_xtal_in_3d(int use_gui, Widget *calling_pb);  //Justin - Mar, 2008 - Extended Command Set - Phase2

void draw_cursors_in_clipmask(Window window);

int get_current_xtal_alignment_state();

void kill_mplayer();

#endif /* crystal_alignment_window_h */
