#ifndef collect_frame_h
#define collect_frame_h

#include "parameters.h"
#include "goniostat.h"
#include "geometry.h"

/*
****#if defined(MULTI_THREADING)
****#if defined(_SGI_SOURCE)
****#elif defined(_POSIX_THREADS) && defined(_MIT_POSIX_THREADS)
****#include <pthread.h>
****#endif
****#endif
*/

#define COLLECTION_ROUTINE_SINGLE_FRAME		1
#define COLLECTION_ROUTINE_DATASET		2
#define COLLECTION_ROUTINE_REMOTE_CONTROL	3

typedef struct {
	int save_menu;
	int auto_save;
	int save_dark_frames;
	int save_raw_frames;
	int save_corrected_frames;
	int save_thumbnails;
	int save_video_stills;
	int beam_alignment;
	int beam_alignment_before;
	int beam_alignment_periodic;
	int save_to_disk;
	int save_to_archive;
        int next_frame_number;
	char save_dir[256];
	char archive_command[256];
        char filename_root[256];
        char example_filename[256];
	char video_still_suffix[128];
} AutoSaveValues ;

typedef struct _SingleFrameValues {
   /* Values */
   double first_field;
   int n_axes;
   intptr_t   axis_GVoffset[MAXAXES];
   char	  axis_display_name[MAXAXES][32];
   double axis_position[MAXAXES];
   int    n_exposure_capable_axes;
   intptr_t   axis_exposure_capable_GVoffset[MAXAXES];
   char	  axis_exposure_capable_display_name[MAXAXES][32];
   intptr_t   exposure_axis_GVoffset;
   char	  exposure_axis_display_name[32];
   int 	  do_exposure;
   int 	  n_exposures;
   double exposure_size;
   double exposure_parameter;
   int pre_unload_sample;
   int pre_unload_sample_number;
   int load_sample;
   int load_sample_number;
   int center_crystal;
   int centering_mode;
   int post_unload_sample;
   int post_unload_sample_number;
   char sample_id[16];
   /* Flags */
   int apply_correction;
   int get_background;
   int detector_binning;
   int exposure_mode;
   int nreads;
   int shift_size;
   int overscan_size;
   double baseline_stabilization_target;
   int segment_number;
   int frame_number;
   int frame_type;
   int multi_read;
   int frame_shift;
   int stabilize_baseline;
   int expose;
   int dark;
   int bias;
   int new_frame;
   int add_frame;
   int sub_frame;
   AutoSaveValues asv;

   int first_state_field;
   /******/
   /* Keep these four together - in order - for detector routeines */
   int integration_active;
   int exposure_time_remaining;
   int exposure_dose_remaining;
   int exposure_movement_remaining;
   int read_active;
   int readout_time_remaining;
   /******/
   int multi_thread;
   int collection_routine_active;
   int collection_routine_waiting;
   int abort_flag;
   int shutter_open;
   int hold_goniostat;
   int calling_routine_active;
   int calling_routine_type;
   int continuous;
   int result;
   int state;
   int parent_id;
   int child_id;
   int parent_blocked;
   int child_blocked;
   char error_message[256];
   void *user_data;
   int roi; //boolean set if single dialog has an ROI to set
   struct RectCartInt roi_rect; //actual ROI rect. coords. from single dialog
} SingleFrameValues;


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int collect_frame(
#if NeedFunctionPrototypes
SingleFrameValues *sfvp
#endif
);

extern int start_collect_frame(
#if NeedFunctionPrototypes
SingleFrameValues *gsfvp
#endif
);

extern void cancel_collect_frame(
#if NeedFunctionPrototypes
void
#endif
);


extern void * create_maxdiffarray(void *diffarray);

extern void init_sfv_parameter_axis_definitions(SingleFrameValues *sfvp, GoniostatValues *gvp);


#endif /* collect_frame_h */
