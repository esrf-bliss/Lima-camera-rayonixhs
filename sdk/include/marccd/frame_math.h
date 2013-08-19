#ifndef frame_math_h
#define frame_math_h

#include <stdint.h>

#include "frame.h"

typedef enum _MathOperation {
	ADD_FRAME,
	SUB_FRAME,
	MUL_FRAME,
	DIV_FRAME,
	MASK_FRAME,
	OR_FRAME,
	AND_FRAME,
	XOR_FRAME,
	AVE_FRAME,
	MIN_FRAME,
	ADD_CONSTANT,
        ADD_CONSTANT_OUTSIDE_CIRCLE,
        MULT_CONSTANT_OUTSIDE_CIRCLE,
        SET_CONSTANT_UNDER_LINE,
        ADD_CONSTANT_UNDER_LINE,
        MUL_CONSTANT_UNDER_LINE,
	SUB_CONSTANT,
	MUL_CONSTANT,
	DIV_CONSTANT,
	SET_CONSTANT,
	MUL_GRADIENT,
	CALCULATE_OVERSCAN_CORRECTION,
	CC_FRAMES,
	DUPLICATE_FRACTION,
	DEMUX_FRAME,
	MUX_FRAME,
	CFDEMUX_FRAME,
	CFMUX_FRAME,
	FSDEMUX_FRAME,
	FSMUX_FRAME,
	BSWAP_FRAME,
	COMPARE_FRAME,
	COUNTDIFFS_FRAME,
	FLATFIELD_FRAME,
	UNDISTORT_FRAME,
	SET_GAUSSIAN,
        SIMULATE_SHUTTERLESS_FRAME,
	COUNT_FRAME,
	SPECOP_FRAME,
	CONVERT_TO_SIGNED,
	CONVERT_TO_UNSIGNED,
	DISTORT_SMOOTH_FRAME,
	BIN_FRAME,
	MARK_FRAME,
	THRESHOLD_FRAME,
	COUNT_PARTICLES,
	NUMBER_PARTICLES,
	INVERT_FRAME,
	INVERT_FLATFIELD,
	LOW_PIXEL,
	HIGH_PIXEL,
	SUM_QUADRATURE_FRAME,
	SQUARE_FRAME,
	SQUAREROOT_FRAME,
	MAKE_UNDISTORT_LOOKUP_TABLE,
	UNDISTORT_FRAME_WITH_LOOKUP_TABLE,
	UNSCRAMBLE_FRAME_FROM_CORNERS,
	CORRECT_FRAME_WITH_LOOKUP_TABLE,
	MAKE_FULL_CORRECTION_TABLE,
	PAD_FRAME,
	UNBIN_FRAME,
	COPY_FRAME,
	EXTRACT_SUBFRAME,
	EXTRACT_SUBFRAME_CENTERED,
	CROP_FRAME,
	EXTEND_FRAME
   } MathOperation;


#define FILTER_AND		0
#define FILTER_OR		1
#define FILTER_OPEN		2
#define FILTER_CLOSE		3
#define FILTER_MEAN		4
#define FILTER_RANGE		5
#define FILTER_RMS		6
#define FILTER_HORIZONTAL_FILL	7
#define FILTER_VERTICAL_FILL	8
#define FILTER_EDGE_INCLUDED	9
#define FILTER_EDGE_EXCLUDED	10
#define FILTER_LIMITED_AND	11


/* Options to SUB_FRAME */
/* Do not use 0, as NULL is a possible alternative, meaning use defalut behaviour */
#define PRESERVE_LSB		1
#define PRESERVE_MSB		2
#define PRESERVE_RANGE		3

#define FSMUX_CORRECTION_TABLE		1
#define FSMUX_DATAFRAME_SIMULATION	2
#define FSMUX_DATAFRAME			3

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int compatible_frames(data_frame *f1, data_frame *f2);

int frame_math(data_frame* p1, data_frame* p2, data_frame* p3, data_frame* p4, data_frame* p5, int operation );

extern int frame_math_with_errors(
#if NeedFunctionPrototypes 
data_frame *out,
data_frame *errout,
data_frame *noversout,
data_frame *in1,
data_frame *err1,
data_frame *in2,
data_frame *err2,
int operation
#endif /* Need Function Prototypes */
);

extern int mark_array(
#if NeedFunctionPrototypes 
void  *data1,
void *data2,
int type,
int low_limit,
int high_limit,
int new_value,
int depth,
int size
#endif /* Need Function Prototypes */
);

int threshold_array(void *data1, void *data2, int threshold, int type, int depth, int size, int modify);

extern int bin_frame(data_frame *output_framep, data_frame *input_framep, int binning_x, int binning_y, int adjust_bias, int rescale_data);
extern int unbin_frame(data_frame *output_framep, data_frame *input_framep, int binning_x, int binning_y, int adjust_bias, int rescale_data);
extern int calculate_frametransfer_artifact_frame(data_frame *input_framep, data_frame *preceeding_framep, data_frame *succeeding_framep, data_frame *background_framep, double exposure_time, double transfer_time, double decay_time, double pre_transfer_delay, double post_transfer_delay, data_frame *simulated_framep, data_frame *artifact_framep);

//int subframe_math(int ix0, int iy0, int ix1, int iy1, data_frame* p1, data_frame* p2, data_frame* p3, data_frame* p4, data_frame* p5, int operation );
int subframe_math(int ix0, int iy0, int ix1, int iy1, void* p1, void* p2, void* p3, void* p4, void* p5, int operation );

extern int apply_absorption(
#if NeedFunctionPrototypes 
data_frame *frp1,
data_frame *frp2,
double x,
double y, 
double To, 
double radius
#endif /* Need Function Prototypes */
);

extern int apply_phosphor_response_model(
#if NeedFunctionPrototypes 
data_frame *frp1,
data_frame *frp2,
double x,
double y, 
double radius,
double PRC1,
double PRC2
#endif /* Need Function Prototypes */
);

extern int apply_point_source_geometry(
#if NeedFunctionPrototypes 
data_frame *frp1,
data_frame *frp2,
double x,
double y, 
double radius
#endif /* Need Function Prototypes */
);

int apply_sourceprofile(
#if NeedFunctionPrototypes 
data_frame *frp1,
data_frame *frp2,
double x,
double y, 
double radius
#endif /* Need Function Prototypes */
);

extern int add_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
void *data3,
int type,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int sum_quadrature_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
void *data3,
int type,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int specop_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
void *data3,
void *data4,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int convert_to_signed_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int convert_to_unsigned_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int convert_float_to_signed_array(
#if NeedFunctionPrototypes 
void  *data1,
int   depth1,
void  *data2,
int depth2,
int size,
double offset,
double scale
#endif /* Need Function Prototypes */
);

extern int set_constant_array(
#if NeedFunctionPrototypes 
void *data1, 
int constant,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int set_gaussian_array(
#if NeedFunctionPrototypes 
void *data1, 
double mean,
double sigma,
int depth,
int size,
int type
#endif /* Need Function Prototypes */
);

extern int add_constant_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
int constant,
int type,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int count_blobs_2Darray(void *data1, void *data2, int threshold, int type, int fast, int slow, int depth, int *pixel_count);

extern int evaluate_marked_blobs(int fractional, void *data, void *particle_mask, void *part_bck_mask, int type, int fast, int slow, int depth, int n_blobs, double *mean_background_list, int *n_pixels, double *mean, double *sigma, double *x, double *y, double *sigma_x, double *sigma_y, double *sum, double *raw_sum, double *raw_background);

extern int copy_array( void  *data1, void *data2, int depth1, int depth2, int size);

extern int mult_constant_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
double constant,
int type,
int depth,
int size
#endif /* Need Function Prototypes */
);

int subtract_array(void  *data1, void *data2, void *data3, int type, int depth, int size, int precision, int bias);

extern int mul_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
void *data3,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int div_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
void *data3,
double scale_factor,
int type,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int mask_array( void *data1, void *data2, void *data3, int depth, int size);
extern int count_array( void *data1, int depth, int size);
extern void or_array( void *data1, void *data2, void *data3, int depth, int size);
extern void and_array( void *data1, void *data2, void *data3, int depth, int size);
extern void xor_array( void *data1, void *data2, void *data3, int depth, int size);
extern double cc_arrays( void *data1, void *data2, void *ref_data, int depth, int size);
extern double check_duplicate_fraction_arrays( void *data1, void *data2, int depth, int size);

extern int min_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
void *data3,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int low_pixel_array(void *data1, void *data2, void *data3, intptr_t maxdiff, int weight2, int weight3, int type, int depth, int size );

extern int high_pixel_array(void *data1, void *data2, void *data3, intptr_t maxdiff, int weight2, int weight3, int type, int depth, int size );

extern int ave_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
void *data3,
int maxdiff,
int weight2,
int weight3,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int flatfield_array(
#if NeedFunctionPrototypes 
void *data1,
void *data2,
void *data3,
void *data4,
double mean_flatfield,
int type, 
int depth, 
int size,
int precision
#endif /* Need Function Prototypes */
);

extern int compare_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int countdiffs_array(
#if NeedFunctionPrototypes 
void *data1, 
void *data2, 
int depth,
int size
#endif /* Need Function Prototypes */
);

extern int demux_array( void  *data1, void *data2, int depth, int nfast, int nslow, int nfastimages, int nslowimages, int multiplex_pattern); 

extern int mux_array( void  *data1, void *data2, int depth, int nfast, int nslow, int nfastimages, int nslowimages, int multiplex_pattern); 

extern int cfdemux_array(void *data1, void *data2, int depth, int nfast, int nslow, int nfastimages, int nslowimages, int multiplex_pattern, int blocksize);

extern int cfmux_array(void *data1, void *data2, int depth, int nfast, int nslow, int nfastimages, int nslowimages, int multiplex_pattern, int blocksize);

extern int fsdemux_array(void *data1, void *data2, int depth, int nfast, int nslow, int nlines, int multiplex_pattern, int repeat_input);

extern int fsmux_array(void *data1, void *data2, int depth, int nfast, int nslow, int nlines, int multiplex_pattern, int repeat_input);

int transform_frame(
#if NeedFunctionPrototypes 
data_frame  *framep1,
data_frame  *framep2,
int transformation
#endif /* Need Function Prototypes */
);

/* create a test pattern image */
int fill_test_frame (
#if NeedFunctionPrototypes 
data_frame    *framep,
int           pattern_type
#endif /* Need Function Prototypes */
);

/* calculate statistics on a frame */
extern void fullframe_stats (
#if NeedFunctionPrototypes 
data_frame    *framep,
int           nth,
long *min, 
long *max,
double *mean, 
double *rms,
int *histo,
int nhisto,
long *rank,
long nrank
#endif /* Need Function Prototypes */
);


/* calculate statistics on a frame */
extern void subframe_stats(int ix0, int iy0, int ix1, int iy1, data_frame *framep, int nth, long *min, long *max, double *mean, double *rms, long *n_zeros, long *n_saturated, int *histo, int nhisto, long *rank, long nrank);

#if 0
extern void subframe_stats(
#if NeedFunctionPrototypes 
int ix0,
int iy0,
int ix1,
int iy1,
data_frame    *framep,
int           nth,
long *min, 
long *max,
double *mean, 
double *rms,
int *histo,
int nhisto,
long *rank,
long nrank
#endif /* Need Function Prototypes */
);
#endif

extern void estimate_biases( data_frame *framep, double *biases);

extern void subtract_biases( data_frame *framep1, data_frame *framep2, double *biases, double nominal_bias);

extern int stat_frame_stack(data_frame **stack, data_frame *mean_frame, data_frame *sigma_frame, data_frame *stderr_frame, data_frame *nused_frame);

extern int stat_frame_stack_worker(int begin, double scale_factor, data_frame **stack, data_frame *mean_frame, data_frame *sigma_frame, data_frame *stderr_frame, data_frame *nused_frame , int ttest_option);

extern int calculate_gain_frame(data_frame *gain_frame, data_frame *mean_frame1, data_frame *mean_frame2, data_frame *sigma_frame1, data_frame *sigma_frame2);
extern int calculate_mean_variance_frame(double scale, data_frame *mv_frame, data_frame *mean_frame, data_frame *sigma_frame);

extern int stat_histo_with_ttest( int *histo, int nhisto, int badvalue_flag, double static_min_P, double *mean, double *median, double *mode, double *sigma, double *std_error, int *nused, int *nlow, int ttest_option, int max_reject_number);

extern int stat_array(int *values, int nvalues, int nth, int badpix_flag, double test_t, double *mean, double *sigma, double *std_error, int *nused, int *nlow);
extern int stat_farray( double *values, int nvalues, int nth, double badvalue_flag, double max_deviate, double *mean, double *sigma, double *std_error, double *min, double *max, int *nused, int *n_rejected);

extern int stat_array_with_ttest( int *values, int nvalues, int nth, int badvalue_flag, double min_P, double *mean, double *median, double *mode, double *sigma, double *std_error, int *nused, int *nlow, int ttest_option);

extern int stat_farray_with_ttest( double *values, int nvalues, int nth, double badvalue_flag, double static_min_P, double min_error, int *used_values, double *mean, double *median, double *mode, double *sigma, double *std_error, int *nused, int *nlow);

extern int unscramble_buffer_from_corners(int command, void *output_image, void *input_buffer, int depth, int nfast, int nslow, int buffer_size);

extern int invert_unsigned_array(void *dataout, void *datain, int significant_bits, int depth, int size);
extern void *create_maxerror_array(void *buffer, int depth, int maxvalue, int bias, double multiplier, double minsigma, double counts_per_unit);
extern void *create_maxerror_array_for_depth(void *array, int depth, int added_bias, double gain);

extern int filter_frame(data_frame *frp1, data_frame *frp2, int x_size, int y_size, double *filter, int operation);
extern int binary_filter_frame(data_frame *frp1, data_frame *frp2, int x_size, int y_size, int *filter, int operation, int iterations);

extern int find_best_threshold_array(void *datain, int size, int depth, int method, double *mean_above, double *mean_below, double *sigma_above, double *sigma_below);

extern int histogram_array(int *histogram, int nhisto, int min_test, int max_test, void *datain, int nth, int size, int depth, double *mean, double *sigma, int *minimum, int *maximum, double *argsum, double *argsumsqrs, int *argntotal);

extern int analyze_partial_histogram(int *histogram,  int size, int min_test, int max_test, double *mean, double *sigma, double *probability);

extern int calculate_statistics_from_stack(const char *search_path, const char *input_filename, data_frame *template_frame_ptr, int template_position, data_frame *mean_frame_ptr, data_frame *sigma_frame_ptr, data_frame *stderr_frame_ptr, data_frame *nused_frame_ptr, int nframes, int write_frames, const char *output_path, char *error_buffer, int error_buffer_size, char *progress_buffer, int progress_buffer_size, int skip_t_test_option, double scale_factor);

extern int find_missing_values(int *histo, int nhisto, int **missing_list);

extern int find_non_uniform_values(int *histo, int nhisto, int **weak_list, int **weak_list_freq, int *n_weak_list, int **strong_list, int **strong_list_freq, int *n_strong_list);

extern int find_bit_usage(int *histo, int nhisto, int **bit_freq, int *n_bits);

extern void convert_histo_to_rank(int nused, int *histo, int nhisto, int underflow_value, int overflow_value, int signed_values, int depth, long *rank, long nrank);

extern unsigned long multiplex_offset(unsigned long input_offset, int nfast, int nslow, int nfastimages, int nslowimages, int multiplex_pattern);

extern int calculate_stats_from_stack(int stack_size, int write_frames, data_frame template_frame_ptr, data_frame *mean_frame_ptr, data_frame *sigma_frame_ptr, data_frame *stderr_frame_ptr, data_frame *nused_frame_ptr);

extern int count_readouts(int nfastimages, int nslowimages, int readout_pattern, int *nreadoutsp, int *nreadouts_fastp, int *nreadouts_slowp);
extern int count_channels_in_readout_pattern(int readout_pattern);

extern int test_parse_postscan_regions(data_frame *input_framep);

extern int parse_postscan_regions(data_frame *input_framep, int correction_type, int target_bias, data_frame *corrected_framep, data_frame *data_framep_arg, data_frame *fast_postscan_framep_arg, data_frame *slow_postscan_framep_arg, data_frame *double_postscan_framep_arg, data_frame *pseudo_overscan_framep_arg);

extern int calculate_linearity_curve_from_two_images(data_frame *outfp, data_frame *in1fp, data_frame *in2fp, data_frame *back1fp, data_frame *back2fp);

extern double *calculate_sensor_usage_efficiency_from_mask(data_frame *mask_framep, int *arg_nsensors);

extern void set_frame_edges(data_frame *framep, int value, int width);

#endif /* frame_math_h */
