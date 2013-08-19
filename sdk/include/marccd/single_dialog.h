#ifndef single_dialog_h
#define single_dialog_h

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void config_single_dialog( Widget w, int item_no);

extern int rebuild_single_frame_dialog(void);

extern void update_single_dialog( void);

extern void track_exposure_to( void *data);
extern void detector_exposure_to( void);

extern void set_correct_and_save_filename(const char *filename, const char *image_filename, int type, int size_x, int size_y);
extern int correct_new_detector_frame_wp (int *result);
extern int correct_new_detector_frame_worker(int command, void *out, void *in);

extern int correct_and_save_new_detector_frame(const char *filename);

#endif /* single_dialog_h */
