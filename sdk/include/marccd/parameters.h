#ifndef parameters_h
#define parameters_h

#include <stdint.h>

/*#include "collect_frame.h"*/

#define NEW_SEGMENT_FORM 0
#if NEW_SEGMENT_FORM
#define MAXSEGMENTS		512
#else
#define MAXSEGMENTS		64
#endif
#define MAXAXES			32
#define MAX_PERIODIC_COMMANDS	8
#define MAX_COMMAND_LENGTH	256
#define MAX_DIRECTORY_LENGTH	256


typedef enum {
     FRAME_TYPE_DATA,
     FRAME_TYPE_BIAS,
     FRAME_TYPE_DARK,
     FRAME_TYPE_FLAT,
     FRAME_TYPE_SPECIAL
   } FrameType;

typedef enum {
	PERIODIC_MODE_TIME,
	PERIODIC_MODE_TIME_MINUTES,
	PERIODIC_MODE_FRAMES,
	PERIODIC_MODE_EXPOSURES,
	PERIODIC_MODE_SEGMENTS,
	PERIODIC_MODE_DOSE,
	PERIODIC_MODE_CRYSTAL_MOUNTS,
	PERIODIC_MODE_CRYSTAL_ALIGNMENTS,
	PERIODIC_MODE_CRYSTAL_DATA,
	PERIODIC_MODE_CAROUSELS
   } PeriodicMode;

typedef enum {
	PERIODIC_START_PHASE_BEFORE,
	PERIODIC_START_PHASE_AFTER
   } PeriodicStartPhase;

#define SEGMENT_STATUS_PENDING		0
#define SEGMENT_STATUS_UNUSED		1
#define SEGMENT_STATUS_SKIPPED		2
#define SEGMENT_STATUS_IN_PROGRESS	3
#define SEGMENT_STATUS_OK		4
#define SEGMENT_STATUS_ERROR		5

typedef struct _segment_parameters {
  int  status;
  char root_filename_template[MAX_DIRECTORY_LENGTH];
  char root_filename_segment_number_format[32];
  intptr_t root_filename_segment_number_offset;
  char root_filename_frame_number_format[32];
  intptr_t root_filename_frame_number_offset;
  int segment_number;
  char segment_name[MAX_DIRECTORY_LENGTH];
  char comment[512];
  int sample_number;
  char sample_code[64];
  int carousel_number;
  char carousel_code[64];
  int open_shutter;
  int exposure_mode; /* time or dose */
  int exposure_parameter; /* time or dose */
  int detector_binning;
  int multi_read;
  int nreads;
  int frame_shift;
  int shift_size;
  int stabilize_baseline;
  double baseline_stabilization_target;
  int overscan_size;
  int frame_1;
  int frame_current;
  int frame_type;
  int frame_n;
  int interleave;
  int interleaved_segments;
  int interleave_size;
  int bias_exposures_needed;
  int bias_exposures_done;
  int dark_exposures_needed;
  int dark_exposures_done;
  int flat_exposures_needed;
  int flat_exposures_done;
  int special_exposures_needed;
  int special_exposures_done;
  intptr_t moving_axis_GVoffset;
  char moving_axis_display_name[32];
  int motion_type;
  int detector_resolution_option;
  int detector_gain_option;
  int detector_speed_option;
  double angular_width;
  double angular_gap;
  int n_axes;
  char   axis_display_name[MAXAXES][32];
  intptr_t   axis_GVoffset[MAXAXES];
  double axis_position[MAXAXES];
  void *user_data;
} segment_parameters;

typedef struct _dataset_parameters {
   /* General Info */
   int  state;
   char comment[512];
   char experiment_name[128];
   char project_id[128];
   char operator_name[64];
   char date[64];
   char filename_example[128];
   char protocol_filename[128];
   char auxillary_apparatus_server[128];
   int  max_segments;
   int  multi_crystal;
   int  autostart;
   int  autoquit;

   /* stuff */
   char sample_name[64];
   char spacegroup_name[8];
   char pointgroup_name[8];
   char spindle[8];
   char beam[8];

   /* X-ray Source */
   int source_type;
   int source_dx;
   int source_dy;
   double source_wavelength;
   double source_power;
   double source_voltage;
   double source_current;
   double source_bias;
   double source_polarization_x;
   double source_polarization_y;

   /* X-ray Optics */
   int optics_type;
   int optics_dx;
   int optics_dy;
   double optics_wavelength;
   double optics_dispersion;
   double optics_crossfire_x;
   double optics_crossfire_y;
   double optics_angle;
   double optics_polarization_x;
   double optics_polarization_y;

  int n_active_axes;
  char   axis_active_display_name[MAXAXES][32];
  intptr_t   axis_active_GVoffset[MAXAXES];
  double axis_active_start_position[MAXAXES];
  int n_static_axes;
  char   axis_static_display_name[MAXAXES][32];
  intptr_t   axis_static_GVoffset[MAXAXES];
  double axis_static_position[MAXAXES];

   /* ...  */

   /* other stuff */
   int nreads;
   int multi_read;
   int detector_binning;
   int frame_shift;
   int shift_size;
   int stabilize_baseline;
   double baseline_stabilization_target;
   int overscan_size;
   int exposure_mode; /* time or dose */
   int do_roi; //do region-of-interest
   int roi_x0;
   int roi_y0;
   int roi_x1;
   int roi_y1;

   /* ...  */

   /* other stuff */
   char detector1_distance;
   char detector1_type;
   /* ...  */

   /* other stuff */
   int  save_dark_frames;
   int  save_raw_frames;
   int  save_corrected_frames;
   int  save_thumbnails;
   int  save_video_stills;
   char video_still_suffix[128];
   int  video_still_mode;
   int  video_still_interval;
   int  save_crystal_alignment_verification_stills;
   int  beam_alignment;
   int  beam_alignment_before;
   int  beam_alignment_periodic;
   int  beam_alignment_mode;
   int  beam_alignment_interval;
   int  save_segment_summaries;
   int  save_to_disk;
   int  save_to_archive;
   int  n_periodic_commands;
   int  run_periodic_command[MAX_PERIODIC_COMMANDS];
   int  periodic_mode[MAX_PERIODIC_COMMANDS];
   int  periodic_start[MAX_PERIODIC_COMMANDS];
   int  periodic_start_phase[MAX_PERIODIC_COMMANDS];
   int  periodic_start_mode[MAX_PERIODIC_COMMANDS];
   int  periodic_interval[MAX_PERIODIC_COMMANDS];
   int  update_darkframe;
   int  darkframe_update_interval;
   int center_crystals;
   int centering_mode;
   int multicarousel_in_use;
   int unload_last_sample;
   int unload_last_carousel;
   int use_pipeline_method;
   char disk_directory[MAX_DIRECTORY_LENGTH];
   char archive_command[MAX_COMMAND_LENGTH];
   char periodic_command[MAX_PERIODIC_COMMANDS+1][MAX_COMMAND_LENGTH];
   int	thumbnail_type;
   char thumbnail_suffix[128];
   int	thumbnail_binning;
   int	thumbnail_size_x;
   int	thumbnail_size_y;

   // YET OTHER STUFF!
   int beam_alignment_enable;
   int beam_alignment_find_enable; 
   int beam_alignment_failure_interval;
   /* ...  */
   /* other stuff */
   segment_parameters data_segment[MAXSEGMENTS];
   /* ...  */

   char error_message[256];
   void *user_data;

} dataset_parameters;


typedef struct _crystal_parameters {
   double a,b,c,alpha,beta,gamma;
   double a_sigma,b_sigma,c_sigma,alpha_sigma,beta_sigma,gamma_sigma;

   int mosaicity_model;
   double mosaicity_parameters[16];
   double mosaicity_parameters_sigma[16];

   double theta1, theta2, theta3;
   double theta1_sigma, theta2_sigma, theta3_sigma;

   int space_group;
   int lattice_type;

} crystal_parameters;

typedef struct _source_parameters {
   double wavelength;
   double wavelength_sigma;
   double direction_parameters[3];
   double direction_parameters_sigma[3];
   int profile_model;
   double profile_parameters[4];
   double profile_parameters_sigma[4];
} source_parameters;

typedef struct _detector_parameters {
   /* These are settings - really due to goniostat,
   but if there is more than one detector, then will
   need these for each.  They are usually not refined. */
   double distance, two_theta;
   double distance_sigma, two_theta_sigma;
} detector_parameters;

typedef struct _detector_misset_parameters {
   /* These are missettings - usually refined from data */
   double distance, center_x, center_y,
	  rotation_x, rotation_y, rotation_z;
   double distance_sigma, center_x_sigma, center_y_sigma,
	  rotation_x_sigma, rotation_y_sigma, rotation_z_sigma;
} detector_misset_parameters;

typedef struct _goniostat_parameters {

   int    drive_axis, drive_error_model;
   double drive_error_parameters[16];
   double drive_error_parameters_sigma[16];

   double frame_width, frame_increment;
   double frame_width_sigma, frame_increment_sigma;

   int    n_detectors;
   detector_parameters detector[8];
   detector_misset_parameters detector_misset[8];
} goniostat_parameters;

/* These parameters duplicate other information,
   but are useful to have precalculated for
   speeding calculations
*/
typedef struct _convenience_parameters {
  double Amatrix_by_lambda[9];
  double Bmatrix_by_lambda[9];
} convenience_parameters;

typedef struct _geometry_parameters {
   crystal_parameters		crystal;
   source_parameters		source;
   goniostat_parameters		goniostat;
   convenience_parameters	convenience;
} geometry_parameters;


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */



extern int open_dataset_parameter_file(
#if NeedFunctionPrototypes
const char *filename
#endif
);

extern int close_dataset_parameter_file(
#if NeedFunctionPrototypes
void
#endif
);

extern int write_dataset_parameter_file(dataset_parameters *tdp);

extern int read_dataset_parameter_file(dataset_parameters *tdp);

extern  dataset_parameters *get_dataset_parameter_structure(
#if NeedFunctionPrototypes
void
#endif
);

extern int compare_dataset_parameters(dataset_parameters *set1, dataset_parameters *set2);

void set_diffraction_geometry_parameters(
#if NeedFunctionPrototypes
geometry_parameters some_parameters
#endif
);

geometry_parameters *get_diffraction_geometry_parameters(
#if NeedFunctionPrototypes
geometry_parameters *some_parameters
#endif
);

#endif /* parameters_h */
