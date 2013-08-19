#ifndef resources_h
#define resources_h

#include <X11/Intrinsic.h>

#include "goniostat.h"
#include "detector.h"
#include "beamline_control.h"
#include "frame.h"
#include "mmx_frames.h"

#define MAXFILENAME	512

/* Some Default values */
#define  MAIN_IMAGE_WIDTH	256
#define  MAIN_IMAGE_HEIGHT	256
#define  ZOOM_IMAGE_WIDTH	128
#define  ZOOM_IMAGE_HEIGHT	128


/* Maximum possible number of enumerated values for a single resource */
#define MAX_RESOURCE_VALUE_ENUMERATIONS 40


/* Resource names and classes */
#define MmxNvalueDisplayFormat		"valueDisplayFormat"
#define MmxCValueDisplayFormat		"ValueDisplayFormat"
#define MmxNuserOriginX			"userOriginX"
#define MmxCUserOriginX			"UserOriginX"
#define MmxNuserOriginY			"userOriginY"
#define MmxCUserOriginY			"UserOriginY"
#define MmxNuserCoordTransformation	"userCoordTransformation"
#define MmxCUserCoordTransformation	"UserCoordTransformation"
#define MmxNviewDirection		"viewDirection"
#define MmxCViewDirection		"ViewDirection"
#define MmxNplotItem			"plotItem"
#define MmxCPlotItem			"PlotItem"
#define MmxNrenderTransformation	"renderTransformation"
#define MmxCRenderTransformation	"RenderTransformation"
#define MmxNuserCoordinateType		"userCoordinateType"
#define MmxCUserCoordinateType		"UserCoordinateType"
#define MmxNcolorScheme			"colorScheme"
#define MmxCColorScheme			"ColorScheme"
#define MmxNcolorScalingMethod		"colorScalingMethod"
#define MmxCColorScalingMethod		"ColorScalingMethod"
#define MmxNcolorGamma			"colorGamma"
#define MmxCColorGamma			"ColorGamma"
#define MmxNgoniostatDevice		"goniostatDevice"
#define MmxCGoniostatDevice		"GoniostatDevice"
#define MmxNgoniostatType		"goniostatType"
#define MmxCGoniostatType		"GoniostatType"
#define MmxNgoniostatPort		"goniostatPort"
#define MmxCGoniostatPort		"GoniostatPort"
#define MmxNgoniostatID			"goniostatID"
#define MmxCGoniostatID			"GoniostatID"
#define MmxNdetectorDevice		"detectorDevice"
#define MmxCDetectorDevice		"DetectorDevice"
#define MmxNdetectorType		"detectorType"
#define MmxCDetectorType		"DetectorType"
#define MmxNdetectorPort		"detectorPort"
#define MmxCDetectorPort		"DetectorPort"
#define MmxNdetectorID			"detectorID"
#define MmxCDetectorID			"DetectorID"
#define MmxNbeamlineControlType		"beamlineControlType"
#define MmxCBeamlineControlType		"BeamlineControlType"
#define MmxNxRaySourceType		"xRaySourceType"
#define MmxCXRaySourceType		"XRaySourceType"
#define MmxNxRayOpticsType		"xRayOpticsType"
#define MmxCXRayOpticsType		"XRayOpticsType"
#define MmxNsaturatedColor		"saturatedColor"
#define MmxCSaturatedColor		"SaturatedColor"
#define MmxNdisplaySource		"displaySource"
#define MmxCDisplaySource		"DisplaySource"
#define MmxNshrinkRendering		"shrinkRendering"
#define MmxCShrinkRendering		"ShrinkRendering"
#define MmxNrootDirectory		"rootDirectory"
#define MmxCRootDirectory		"RootDirectory"
#define MmxNframeFileFormat		"frameFileFormat"
#define MmxCFrameFileFormat		"FrameFileFormat"
#define MmxNbiasFrame			"biasFrame"
#define MmxCBiasFrame			"BiasFrame"
#define MmxNbackFrame			"backFrame"
#define MmxCBackFrame			"BackFrame"
#define MmxNdarkFrame			"darkFrame"
#define MmxCDarkFrame			"DarkFrame"
#define MmxNflatFrame			"flatFrame"
#define MmxCFlatFrame			"FlatFrame"
#define MmxNbadPixFrame			"badPixFrame"
#define MmxCBadPixFrame			"BadPixFrame"
#define MmxNxGeomFrame			"xGeomFrame"
#define MmxCXGeomFrame			"XGeomFrame"
#define MmxNyGeomFrame			"yGeomFrame"
#define MmxCYGeomFrame			"YGeomFrame"
#define MmxNareaFrame			"areaFrame"
#define MmxCAreaFrame			"AreaFrame"
#define MmxNdistortionMap		"distortionMap"
#define MmxCDistortionMap		"DistortionMap"
#define MmxNcorrectionTable		"correctionTable"
#define MmxCCorrectionTable		"CorrectionTable"
#define MmxNframeMathPrecision		"frameMathPrecision"
#define MmxCFrameMathPrecision		"FrameMathPrecision"

/* Resource types */
#define MmxRString 	        "string"
#define MmxRExposure 	        "exposure"
#define MmxRDose 	        "dose"
#define MmxRAngle	 	"angle"
#define MmxRTime	  	"time"
#define MmxRValueFormat	 	"valueFormat"
#define MmxRFileFormat  	"fileFormat"
#define MmxRDataType 		"dataType"
#define MmxRCoordinateType	"coordinateType"
#define MmxRCoordinateType	"coordinateType"
#define MmxRViewDirection	"viewDirection"
#define MmxRPlotItem		"plotItem"
#define MmxRColorScheme		"colorScheme"
#define MmxRColorScalingMethod	"colorScalingMethod"
#define MmxRGoniostatType	"goniostatType"
#define MmxRDetectorType	"detectorType"
#define MmxRBeamlineControlType	"beamlineControlType"
#define MmxRXRaySourceType	"xRaySourceType"
#define MmxRXRayOpticsType	"xRayOpticsType"
#define MmxRMMXFrame		"MMXFrame"
#define MmxRImageSampling	"imageSampling"
#define MmxRFrameMathPrecision  "frameMathPrecisoin"

/* Resource value names */

/* MmxRGoniostatType */
#define MmxVGoniostatNone	"None"
#define MmxVGoniostatUnknown	"Unknown"
#define MmxVGoniostatVirtual	"Virtual"
#define MmxVGoniostatMmx	"Mmx"
#define MmxVGoniostatMmx0	"Mmx0"
#define MmxVGoniostatMmx1	"Mmx1"
#define MmxVGoniostatMmx2	"Mmx2"
#define MmxVGoniostatMar	"Mar"
#define MmxVGoniostatMarSCSI	"MarSCSI"
#define MmxVGoniostatMar345V1	"Mar345V1"
#define MmxVGoniostatMar345V2	"Mar345V2"
#define MmxVGoniostatMarNetV1	"MarNetV1"
#define MmxVGoniostatMarNetV2	"MarNetV2"
#define MmxVGoniostatMarDTB	"MarDTB"
#define MmxVGoniostatSPEC	"SPEC"
#define MmxVGoniostatEPICS	"EPICS"
#define MmxVGoniostatTACO	"TACO"
#define MmxVGoniostatACE	"ACE"
#define MmxVGoniostatGRACE	"GRACE"
#define MmxVGoniostatRemote	"Remote"
#define MmxVGoniostatSoftware	"Software"

/* MmxRDetectorType */
#define MmxVDetectorNone	"None"
#define MmxVDetectorUnknown	"Unknown"
#define MmxVDetectorVirtual 	"Virtual"
#define MmxVDetectorMmx 	"Mmx"
#define MmxVDetectorMmx0 	"Mmx0"
#define MmxVDetectorMmx1 	"Mmx1"
#define MmxVDetectorMmx2 	"Mmx2"
#define MmxVDetectorNwu0 	"Nwu0"
#define MmxVDetectorNwu1 	"Nwu1"
#define MmxVDetectorSI500 	"SI500"
#define MmxVDetectorMarCCD 	"MarCCD"
#define MmxVDetectorMarMosaic 	"MarMosaic"
#define MmxVDetectorRayonix	"Rayonix"
#define MmxVDetectorMar 	"Mar"
#define MmxVDetectorMar180 	"Mar180"
#define MmxVDetectorMar300 	"Mar300"
#define MmxVDetectorMar345 	"Mar345"
#define MmxVDetectorMar345V1 	"Mar345V1"
#define MmxVDetectorMar345V2 	"Mar345V2"

/* MmxRBeamlineControlType */
#define MmxVBeamlineControlNone	"None"
#define MmxVBeamlineControlUnknown	"Unknown"
#define MmxVBeamlineControlVirtual 	"Virtual"
#define MmxVBeamlineControlSPEC		"SPEC"
#define MmxVBeamlineControlEPICS	"EPICS"
#define MmxVBeamlineControlTACO		"TACO"
#define MmxVBeamlineControlACE		"ACE"
#define MmxVBeamlineControlGRACE	"GRACE"
#define MmxVBeamlineControlRemote	"Remote"

/* MmxRXraySourceType */
#define MmxVXRaySourceCu	"CuAnode"
#define MmxVXRaySourceMo	"MoAnode"
#define MmxVXRaySourceSynch 	"Synchrotron"

/* MmxRXrayOpticsType */
#define MmxVNickelMirror	"NickelMirror"
#define MmxVNickelFilter	"NickelFilter"
#define MmxVMonochromator	"Monochromator"

/* MmxRFileFormat */
#define MmxVFormatUnknown	"Unknown"
#define MmxVFormatNative	"Native"
#define MmxVFormatRaw		"Raw"
#define MmxVFormatPCS		"PCS"

/* Careful - these may be used as array indices. Use 0,1,2... */
#if 0
typedef enum _ValueFormat {
   decimal,hexadecimal,octal,binary
   } ValueFormat;

typedef enum _DataType {
   MMXInteger, MMXShort, MMXLong, MMXFloat, MMXDouble, MMXChar, MMXString, MMXAngle, MMXTime 
   } DataType;

typedef enum _CoordinateType {
   COORDS_NATIVE, COORDS_AUTOMAR, COORDS_MOSFLM, COORDS_DENZO, COORDS_BUDDHA, COORDS_XENGEN, COORDS_CADMUS_PCS, COORDS_SIEMENS_PC, COORDS_XEDAR
   } CoordinateType;

/* Resource Type definitions */

typedef enum _ViewDirection {
   FromSource, TowardSource
   } ViewDirection;

typedef enum _ColorScheme {
   WHITE_ON_BLACK, BLACK_ON_WHITE, WARM_ON_COOL, XENTRONICS, EGELMAN, CASPAR
   } ColorScheme;

typedef enum _ColorScalingMethod {
   LinearScaling, LogScaling, CustomScaling, HistogramUniformScaling, HistogramGaussianScaling, HistogramCustomScaling
   } ColorScalingMethod;
#endif

typedef enum _PlotItem {
   PlotPosition, PlotErrorVector, PlotIndex2D, PlotIndex3D
   } PlotItem;

typedef enum _XRaySource {
   CU_ANODE, MO_ANODE, SYNCHROTRON 
   } XRaySource;

typedef enum _XRayOptics {
   NICKEL_MIRROR, NICKEL_FILTER, MONOCHROMATOR
   } XRayOptics;

#define MAX_KEY_LENGTH	512

/* application resource structure */
typedef struct {
   //Be sure to mirror changes in AppOptionData in application.h
   int			verbose;
   int			debug;
   int			dump_parameters;
   int			extended_log;
   int			skiprc;
   int			alert_timeout;
   char			configuration_filename[MAXFILENAME];
   char			configuration_basename[MAXFILENAME];
   int			multithread_enable;
   int			multithread_X11_enable;
   int			max_processors;
   int			main_window_width;
   int			main_window_height;
   int			main_image_width;
   int			main_image_height;
   int			main_image_window_width;
   int			main_image_window_height;
   int			zoom_image_width;
   int			zoom_image_height;
   int			zoom_image_window_width;
   int			zoom_image_window_height;
   int			render_n_rank;
   int			render_top_rank;
   int			render_bottom_rank;
   int			plot_object_scale;
   int			value_display_format;
   int			user_coord_transformation;
   int			user_origin_x;
   int			user_origin_y;
   int			startup_remote_mode;
   int			startup_dataset_mode;
   int			program_user_mode;
   char			dataset_protocol_file[MAXFILENAME];
   char			dataset_default_experiment_name[MAXFILENAME];
   int			kill_old;
   int			view_direction;
   int			plot_item;
   int			render_transformation;
   int			user_coordinate_type_default;
   int			user_coordinate_type;
   int			color_scheme;
   unsigned long	color_scaling_method;
   unsigned long	warning_color;
   unsigned long	error_color;
   unsigned long	shutter_open_color;
   unsigned long	shutter_closed_color;
   unsigned long	go_color;
   unsigned long	stop_color;
   unsigned long	warning_tape_bright_color;
   unsigned long	warning_tape_dark_color;
   unsigned long	progress_bar_trough_color;
   unsigned long	progress_bar1_done_color;
   unsigned long	progress_bar2_done_color;
   unsigned long	progress_bar3_done_color;
   unsigned long	progress_bar4_done_color;
   unsigned long	saturated_color;
   unsigned long	bubble_help_background_color;
   unsigned long	bubble_help_foreground_color;
   unsigned long	pending_segment_background_color;
   unsigned long	pending_segment_foreground_color;
   unsigned long	unused_segment_background_color;
   unsigned long	unused_segment_foreground_color;
   unsigned long	skipped_segment_background_color;
   unsigned long	skipped_segment_foreground_color;
   unsigned long	inprogress_segment_background_color;
   unsigned long	inprogress_segment_foreground_color;
   unsigned long	finished_segment_background_color;
   unsigned long	finished_segment_foreground_color;
   unsigned long	error_segment_background_color;
   unsigned long	error_segment_foreground_color;
   unsigned long	video_cursor_beam_color;
   unsigned long 	video_cursor_crystal_color;
   double		color_gamma;
   int			no_goniostat;
   char			goniostat_device[MAXFILENAME];
   int			goniostat_type;
   int			goniostat_port;
   char			goniostat_ID[128];
   char			goniostat_alignment_command[MAXFILENAME];
   char			goniostat_alignment_command_name[MAXFILENAME];
   double		goniostat_alignment_command_delay;
   int			no_detector;
   char			detector_device[MAXFILENAME];
   int			detector_type;
   int			detector_port;
   char			detector_ID[128];
   int			detector_correction_required;
   char			warning_color_name[128];
   char			error_color_name[128];
   char			shutter_open_color_name[128];
   char			shutter_closed_color_name[128];
   char			go_color_name[128];
   char			stop_color_name[128];
   char			warning_tape_bright_color_name[128];
   char			warning_tape_dark_color_name[128];
   char			progress_bar_trough_color_name[128];
   char			progress_bar1_done_color_name[128];
   char			progress_bar2_done_color_name[128];
   char			progress_bar3_done_color_name[128];
   char			progress_bar4_done_color_name[128];
   char			saturated_color_name[128];
   char			bubble_help_background_color_name[128];
   char			bubble_help_foreground_color_name[128];
   char			pending_segment_background_color_name[128];
   char			pending_segment_foreground_color_name[128];
   char			unused_segment_background_color_name[128];
   char			unused_segment_foreground_color_name[128];
   char			skipped_segment_background_color_name[128];
   char			skipped_segment_foreground_color_name[128];
   char			inprogress_segment_background_color_name[128];
   char			inprogress_segment_foreground_color_name[128];
   char			finished_segment_background_color_name[128];
   char			finished_segment_foreground_color_name[128];
   char			error_segment_background_color_name[128];
   char			error_segment_foreground_color_name[128];
   char 		video_cursor_beam_color_name[128];
   char 		video_cursor_crystal_color_name[128];
   char			beamline_control_device[128];
   int			beamline_control_type;
   int			beamline_control_port;
   char			beamline_control_ID[128];
   int			display_source;
   int			shrink_rendering;
   int			frame_file_format;
   int			frame_math_precision;
   int			correction_model_type;
   /* Where the files are kept - relative path names are with respect to this */
   char			root_directory[MAXFILENAME];
   char			configuration_directory[MAXFILENAME];
   char			calibration_directory[MAXFILENAME];
   char			help_directory[MAXFILENAME];
   char			log_directory[MAXFILENAME];
   char			protocol_directory[MAXFILENAME];
   char			working_directory[MAXFILENAME];
   /* Files, in the form of frames,  used to correct data */
   char                 scratch_frame[MAXFILENAME];
   char                 bias_frame[MAXFILENAME];
   char                 back_frame[MAXFILENAME];
   char                 dark_frame[MAXFILENAME];
   char                 flat_frame[MAXFILENAME];
   char                 postflat_frame[MAXFILENAME];
   char                 badpix_frame[MAXFILENAME];
   char                 xgeom_frame[MAXFILENAME];
   char                 ygeom_frame[MAXFILENAME];
   char                 area_frame[MAXFILENAME];
   char                 correction_table[MAXFILENAME];
   /* Other files used to correct data */
   char                 distortion_map[MAXFILENAME];
   /* The following are in config file - not Xresources */
   /* Data collection configuration */
   int		dataframe_correction_reorientation;
   double	beam_coordinates_default[2];
   double	beam_coordinates[2];
   double	beam_slopes[2];
   double	beam_reference_distance;
   int		intensity_counts_min;
   int		intensity_counts_max;
   int		decimal_places_axis;
   int		decimal_places_angle;
   int		decimal_places_wavelength;
   int		decimal_places_energy;
   int		decimal_places_exposure_time;
   int		decimal_places_exposure_dose;
   int		punctuation_angle;

   int		demonstration_mode;
   int		background_update_interval;
   int		single_frame_background_update_interval;
   int		keep_timing_statistics;
   int		thumbnail_enable;
   int		thumbnail_type;
   char         thumbnail_suffix[128];
   int		thumbnail_binning;
   int		thumbnail_size_x;
   int		thumbnail_size_y;
   int		image_type;
   int		image_binning;
   int		image_size_x;
   int		image_size_y;
   int		use_convert;
   char		video0_input_device[MAXFILENAME];
   char		video1_input_device[MAXFILENAME];
   char		video0_output_device[MAXFILENAME];
   char		video1_output_device[MAXFILENAME];
   char		video_display_command_prefix[MAXFILENAME];
   char		video0_input_encoding[256];
   char		video1_input_encoding[256];
   int		video0_input_encoding_id;
   int		video1_input_encoding_id;
   int		video0_input_enable;
   int		video1_input_enable;
   int		video0_output_enable;
   int		video1_output_enable;
   int		video0_input_port;
   int		video1_input_port;
   int		video0_output_port;
   int		video1_output_port;
   int		video_image_width;
   int		video_image_height;
   double	video_crosshair_x;
   double	video_crosshair_y;
   int		video_scale_enable;
   double	video_field_width;
   double	video_field_height;
   double	video_mm_per_pix_x;
   double	video_mm_per_pix_y;
   int		video_zoom_bug;
   char		video_still_command[MAXFILENAME];
   char		video_still_command_2[MAXFILENAME];
   char		video_still_initialize_command[MAXFILENAME];
   char		video_still_type[256];
   int		video_still_width;
   int		video_still_height;
   int		beam_alignment_window_enable;
   int          beam_alignment_bug_scan_delay;
   double	beam_alignment_slit1hori;
   double	beam_alignment_slit1vert;
   double	beam_alignment_slit2hori;
   double	beam_alignment_slit2vert;
   double	beam_alignment_axis_correction_th;
   double	beam_alignment_axis_correction_tv;
   double	beam_alignment_axis_correction_rh;
   double	beam_alignment_axis_correction_rv;
   double	beam_alignment_axis_correction_s1v;
   double	beam_alignment_axis_correction_s1h;
   double	beam_alignment_axis_correction_s2v;
   double	beam_alignment_axis_correction_s2h;
   double	beam_alignment_peak_fraction;
   int          beam_alignment_ignore_errors;
   double	beam_param_rotv_cntr_slit1v_d;
   double	beam_param_rotv_cntr_slit2v_d;
   double	beam_param_roth_cntr_slit1h_d;
   double	beam_param_roth_cntr_slit2h_d;
   int		beam_simulation_enable;
   double	beam_simulation_xt_offset;
   double	beam_simulation_yt_offset;
   double	beam_simulation_xr_offset;
   double	beam_simulation_yr_offset;
   double	default_beam_intensity_offset_1;
   double	default_beam_intensity_offset_2;
   double	default_beam_intensity_sigma_1;
   double	default_beam_intensity_sigma_2;
   double	beam_intensity_offset_timeout;
   int		beam_intensity_offset_prompt_enable;
   int		beam_intensity_offset_measure_enable;
   int		crystal_alignment_window_enable;
   char		sidebar_tab_default[128];
   int		dataset_warn_nounload;
   int		frame_display_enable;
   int		sample_changer_max_mount_failures;
   int		sample_changer_max_unmount_failures;
   int		max_buffers_read;
   int		max_buffers_holding;
   int		max_buffers_corrected;
   int		remote_mode_enable;
   char		remote_mode_license_key[MAX_KEY_LENGTH];
   int		remote_mode_extended_enable;
   char		remote_mode_extended_license_key[MAX_KEY_LENGTH];
   int		continuous_mode_enable;
   int		frameshift_mode_enable;
   char		frameshift_mode_license_key[MAX_KEY_LENGTH];
   int		frameshift_lines;
   int		frameshift_single_file;
   int		baseline_stabilization_mode_enable;
   char		baseline_stabilization_mode_license_key[MAX_KEY_LENGTH];
   double	baseline_stabilization_target;
   int		region_of_interest_enable;
   char		region_of_interest_license_key[MAX_KEY_LENGTH];
   int		view_mode;
   int		expert_mode;
   char		expert_mode_license_key[MAX_KEY_LENGTH];
   int		administrator_mode;
   char		administrator_mode_license_key[MAX_KEY_LENGTH];
   int		proprietary_mode;
   char		proprietary_mode_license_key[MAX_KEY_LENGTH];
   int		menu_acquire_enable;
   int		menu_acquire_dataset_enable;
   int		menu_acquire_single_enable;
   int		menu_acquire_remote_enable;
   int		menu_configure_enable;
   int		cbf_read_ignore_embedded_header;
   int		cbf_read_use_embedded_header;
   int		cbf_write_embed_native_header;
   char		cbf_write_compression_scheme[MAXFILENAME];
   char		cbf_template_file[MAXFILENAME];
   char		cbf_supplementary_data_file[MAXFILENAME];
   char		initial_data_filename[MAX_MMX_SCRATCH_BUFFERS][MAXFILENAME];
   int		logfile_minimum_update_interval_seconds;
   int		logfile_maximum_update_interval_seconds;
   //Be sure to mirror changes in AppOptionData in application.h
} AppResData;

/* Global application resource strucutre */
extern AppResData app_res_data;

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void init_application_resources(Widget widget, int *argc, char **argv, char *error_buffer, int error_buffer_size);

extern Boolean MmxCvtStringToString(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToValueFormat(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToCoordinateType(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToViewDirection(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToPlotItem(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToColorScheme(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToColorScalingMethod(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToMMXFrame(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToGoniostatType(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToDetectorType(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToBeamlineControlType(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToImageSampling(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean MmxCvtStringToFileFormat(
#if NeedFunctionPrototypes
Display *display,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal,
XtPointer *converter_data
#endif
);

extern Boolean get_resource_value_pairs(
#if NeedFunctionPrototypes
char *resource_type,
char ***resource_names,
int **resource_values
#endif
);

extern Boolean convert_enumerated_resource(
#if NeedFunctionPrototypes
Display *display,
char *resource_type,
char **resource_names,
int  *resource_values,
XrmValue *args,
Cardinal *num_args,
XrmValue *fromVal,
XrmValue *toVal
#endif
);


#endif /* resources_h */
