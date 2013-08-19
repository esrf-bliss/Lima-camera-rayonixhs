#ifndef frame_correction_h
#define frame_correction_h

#include "frame.h"
#include "geometry.h"

#define APPLY_BIAS		(1)
#define APPLY_DARKCURRENT	(1 << 1)
#define APPLY_FLATFIELD		(1 << 2)
#define APPLY_GEOMETRIC		(1 << 3)
#define APPLY_DEFECTMAP_RAW	(1 << 4)
#define APPLY_DEFECTMAP_POST	(1 << 5)
#define APPLY_FLATFIELD_POST	(1 << 6)
#define APPLY_BACKGROUND	(APPLY_BIAS | APPLY_DARKCURRENT)
#define APPLY_DISTORTION	(APPLY_GEOMETRIC | APPLY_FLATFIELD)
#define APPLY_FULLCORRECTION    (APPLY_BACKGROUND | APPLY_FLATFIELD | APPLY_DEFECTMAP_RAW | APPLY_GEOMETRIC | APPLY_DEFECTMAP_POST)

#define DEFECTMAP_RAW	(1)
#define DEFECTMAP_POST	(1 << 1)

#define REORDER_TYPE_MULTISENSOR	0
#define REORDER_TYPE_FRAMESHIFT		1
#define REORDER_TYPE_CACHE_FINESSE	2

#define CORRECTION_MODEL_MDA_RECTANGLE			0
#define CORRECTION_MODEL_RECTANGLE_RECTANGLE		1
#define CORRECTION_MODEL_QUADRILATERAL_QUADRILATERAL	2

#define SENSOR_CHANNEL_ORDER 1
#define CHANNEL_SENSOR_ORDER 2

#define CORRECT_COMMAND_INITIALIZE	(1)
#define CORRECT_COMMAND_WORK		(1 << 1)
#define CORRECT_COMMAND_FINISH		(1 << 2)
#define CORRECT_COMMAND_ABORT		(1 << 3)
#define CORRECT_COMMAND_DOITALL		(1 << 4)

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

struct ctbl2_entry {  //Added for region of interest
	UINT32 offset;
	UINT8 extra_entry;
	UINT16 ff_denom;
	UINT8 neighbors_flag;
	UINT8 neighbor_fracs[8];
	unsigned int entry_size;
};

extern int reset_frame_correction_output_bias(void);
extern int set_frame_correction_output_bias(int bias);
extern int get_frame_correction_output_bias(void);

extern int frame_correct(int *percent_complete, int correction_type, data_frame *outputfp, data_frame *inputfp, data_frame *ctbfp, void *back_argp, data_frame *flatframep, data_frame *postflatframep, int saturation_level);
extern int frame_correct_in_thread(void **thread_handle, int correction_type, data_frame *outputfp, data_frame *inputfp, data_frame *ctbfp, void *back_argp, data_frame *flatframep, data_frame *postflatframep, int saturation_level);
extern int finished_frame_correct_thread(void *thread_struct);
extern int percent_remaining_frame_correct_thread(void *thread_struct);
extern int cancel_frame_correct_thread(void *thread_struct);

extern int modify_channel_gains_in_correction_table(int *percent_complete, data_frame *output_ctbp, data_frame *input_ctbp, int nfast, int nslow, int ngains, double *gains);

#if 0
extern int frame_correct_worker(int initialize, int requested_n_to_do, int correction_type, data_frame *p1, data_frame *p2, data_frame *p3, void *p4, data_frame *flatframep, data_frame *postflatframep);
#endif

extern int create_complete_correction_table( int verbose, int table_type, int model_type, int has_notch, int free_flag, int no_geometric, int no_flatfield, int scale_fff, double scale_factor, data_frame *crct_tablep, data_frame *xc_framep, data_frame *yc_framep, data_frame *ac_framep, data_frame *ff_framep, data_frame *dm_framep, data_frame *pff_framep, char *error_message_buffer, int error_message_len, int debug);

extern int mux_demux_correction_table(int *percent_complete, int multiplex, data_frame *output_correction_table, data_frame *input_correction_table, int nfast, int nslow, int nfastimages, int nslowimages, int readout_pattern, char *error_message_buffer, int error_message_len);

extern int mask_and_flatfield_a_frame( int verbose, int free_flag, int scale_fff, double scale_factor, data_frame *brs_framep, data_frame *ff_framep, data_frame *imask_framep, char *error_message_buffer, int error_message_len);

extern int create_correction_table_worker(int initialize, int requested_n_to_do, int model_type, data_frame *p1, data_frame *p2, data_frame *p3, void *p4, void *p5, data_frame *p6, int table_type);

extern int mask_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3, void *p4);

extern int flatfield_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3);

extern int defectmap_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3, int tabletype);

extern int modify_gains_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3, int nfastsections, int nslowsections, double *gains);

extern int postflatfield_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3);

extern int reorient_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, int nfast, int nslow, int reorientation_type);

extern int convert_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3, int outtable_type);

extern int expand_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3);

extern int collapse_correction_table_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3);

extern int create_overlap_map_worker(int initialize, int requested_n_to_do, data_frame *p1, data_frame *p2, data_frame *p3);

extern int modify_flatfield_regions_correction_table_worker(int initialize, int requested_n_to_do, int in_nfast, int in_nslow, int in_depth, int M, int N, double *constants, data_frame *p1, data_frame *p2);

extern int optimize_multimask_worker(int initialize, int requested_n_to_do, int correction_type_arg, data_frame *new_mask, data_frame *input_mask, data_frame *ctbfp, data_frame *value_framep, data_frame *output_value_frame, data_frame *output_mask_frame);

extern void reorder_defectmap_table(int table_type, void *tablep, int table_size);
extern int setup_reorder_offset(int reorder_type, int sensors_nfast, int sensors_nslow, int nfast, int nslow, int pattern, int frameshift_lines);
extern int reorder_offset(unsigned long input_offset, unsigned long *output_offset);
extern int get_calibration_filename_root (char *filename_format, int filename_format_size, const char *path, const char *template_filename);
extern int extract_calibration_filename_format (char *filename_format, int filename_format_size, const char *filename);
extern int edit_channel_values_list(int edited_readout_pattern, double **edited_values, int *n_edited_values, int original_readout_pattern, double *original_values, int n_original_values);
extern int reorder_gain_list(double *output_gains, int output_order, double *input_gains, int input_order, int nsensors, int nports);

//Added for region of interest...
int create_corr_tbl_for_roi(void);
UINT8 *get_ctbl2_entry(struct ctbl2_entry *ctbl_entry, UINT8 *curr_ctbl_pos);
UINT8 *add_entry_to_ctbl2_data(struct ctbl2_entry *ctbl_entry, UINT8 *curr_ctbl_pos);
void print_ctbl_entry(struct ctbl2_entry *entry);
struct PointCartInt offset_to_point(UINT32 offset, unsigned long nfast);
UINT32 point_to_offset(const struct PointCartInt point, int nfast);
void check_neighbors(struct ctbl2_entry entry);
int convert_corr_rect_to_raw_rect(struct RectCartInt *RawRect, struct RectCartInt *CorrRect);

#endif /* frame_correction_h */
