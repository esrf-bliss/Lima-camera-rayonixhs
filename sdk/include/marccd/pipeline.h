#ifndef pipeline_h
#define pipeline_h

#include "task_macros.h"

#include "goniostat.h"
#include "collect_frame.h"
#include "sample_changer.h"
/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


typedef struct {
   int type;
} pipeline_command_any;

typedef struct {
   int type;
   int integrate;
   int expose;
   int exposure_type;
   int exposure_parameter;
   int buffer;
   int correct;
   char *frame_name;
   char *thumb_name_1;
   int thumbnail_type_1;
   int thumbnail_x_1;
   int thumbnail_y_1;
   char *thumb_name_2;
   int thumbnail_type_2;
   int thumbnail_x_2;
   int thumbnail_y_2;
} pipeline_command_integrate;

typedef struct {
   int type;
   int readout;
   int read_buffer;
   int dezinger;
   int dezinger_buffer;
   int correct;
   int write_buffer;
   char *frame_name;
   char *thumb_name_1;
   int thumbnail_type_1;
   int thumbnail_x_1;
   int thumbnail_y_1;
   char *thumb_name_2;
   int thumbnail_type_2;
   int thumbnail_x_2;
   int thumbnail_y_2;
   SingleFrameValues framevalues;
   GoniostatValues goniostatvalues;
   frame_header user_header;
   segment_parameters *dspp;
} pipeline_command_readout;

typedef struct {
   int type;
   int dezinger;
   int dezinger_buffer;
   int correct;
   int write_buffer;
   char *frame_name;
   char *thumb_name_1;
   int thumbnail_type_1;
   int thumbnail_x_1;
   int thumbnail_y_1;
   char *thumb_name_2;
   int thumbnail_type_2;
   int thumbnail_x_2;
   int thumbnail_y_2;
} pipeline_command_dezinger;

typedef struct {
   int type;
   int correct;
   int buffer;
   char *frame_name;
   char *thumb_name_1;
   int thumbnail_type_1;
   int thumbnail_x_1;
   int thumbnail_y_1;
   char *thumb_name_2;
   int thumbnail_type_2;
   int thumbnail_x_2;
   int thumbnail_y_2;
} pipeline_command_correct;

typedef struct {
   int type;
   int write_frame;
   int write_thumb_1;
   int write_thumb_2;
   int buffer;
   char *frame_name;
   char *thumb_name_1;
   int thumbnail_type_1;
   int thumbnail_x_1;
   int thumbnail_y_1;
   char *thumb_name_2;
   int thumbnail_type_2;
   int thumbnail_x_2;
   int thumbnail_y_2;
   SingleFrameValues framevalues;
   GoniostatValues goniostatvalues;
   frame_header user_header;
} pipeline_command_writefile;

typedef union {
   pipeline_command_any		any;
   pipeline_command_integrate	integrate;
   pipeline_command_readout	readout;
   pipeline_command_dezinger	dezinger;
   pipeline_command_correct	correct;
   pipeline_command_writefile	writefile;
} pipeline_command;

extern void initialize_pipeline(void);
extern void intialize_pipeline_state(int *pipeline_state);
extern void process_pipeline(int *pipeline_state, int file_noclobber, dataset_parameters *dsm_dp);
extern int commands_in_pipeline(void);
extern void abort_pipeline(void);
extern pipeline_command *create_pipeline_command_integrate(int expose, int exposure_type, int exposure_parameter, int buffer, char *filename_frame, char *filename_thumb1, char *filename_thumb2);
extern pipeline_command *create_pipeline_command_readout(int destination_buffer, int do_dezinger, int do_correction, int write_buffer, char *filename_frame, char *filename_thumb1, char *filename_thumb2, SingleFrameValues *framevaluesp, GoniostatValues *goniostatvaluesp, segment_parameters *dspp, frame_header user_header, int thumbnail_type_1, int thumbnail_x_1, int thumbnail_y_1, int thumbnail_type_2, int thumbnail_x_2, int thumbnail_y_2);
extern pipeline_command *create_pipeline_command_dezinger(int destination_buffer, int do_correction, int write_buffer, char *filename_frame, char *filename_thumb1, char *filename_thumb2);
extern pipeline_command *create_pipeline_command_writefile(int write_buffer, char *filename_frame, char *filename_thumb1, char *filename_thumb2, SingleFrameValues *framevaluesp, GoniostatValues *goniostatvaluesp, frame_header user_header, int thumbnail_type_1, int thumbnail_x_1, int thumbnail_y_1, int thumbnail_type_2, int thumbnail_x_2, int thumbnail_y_2);
extern void destroy_pipeline_command(pipeline_command *command);
extern int queue_pipeline_command(int *pipeline_state, pipeline_command *command);

extern int task_queued_or_exec(int status, int task);
extern int any_error(int status);
extern int task_error(int status, int task);
extern int task_started(int status, int task);
extern int tasklist_finished(int status, int tasklist);
extern int task_finished(int status, int task);
void print_ring_buffer_usage(void);

#endif /* pipeline_h */
