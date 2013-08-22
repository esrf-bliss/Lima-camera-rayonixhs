#ifndef dataset_h
#define dataset_h

#include "frame.h"
#include "detector.h"
#include "goniostat.h"
#include "parameters.h"
#include "collect_frame.h"

#define MAXEXPOSECHARS 6
#define MAXFRAMECHARS  4

#define AXIS_REPEAT		-7
#define AXIS_ANY		-6
#define AXIS_DUMMY		-5
#define AXIS_SKIP		-4
#define AXIS_NONE		-3
#define AXIS_STILL		-2
#define AXIS_STOP		-1
#define AXIS_THETA		0
#define AXIS_OMEGA		1
#define AXIS_CHI		2
#define AXIS_KAPPA		3
#define AXIS_PHI		4
#define AXIS_GAMMA		5
#define AXIS_DELTA		6
#define AXIS_XTAL_TO_DETECTOR	7
#define AXIS_THETA2		8
#define AXIS_XTAL_TO_DETECTOR2	9
#define AXIS_WAVELENGTH		10

#define MOTION_STILL		1
#define MOTION_SCAN		2
#define MOTION_OSCILLATE	3
#define MOTION_DARK		4

#define AXIS_FIELD_WIDTH_STATIC	12
#define AXIS_FIELD_WIDTH_ACTIVE	7
#define TIME_FIELD_WIDTH	7

#if 0

typedef struct _experiment_data  {
   char experiment[32];
   char operator[32];
   char date[32];
} experiment_data;

typedef struct _crystal_data  {
  char sample[32];
  long spacegroup;
  long pointgroup;
  char spindle[8]; 
  char beam[8]; 
} crystal_data;

typedef struct _source_data  {
  long type;
  long power;
  long voltage;
  long current;
  long optics;
  long wavelength;
  long dispersion;
  long size_x;
  long crossfire_x;
  long size_y;
  long crossfire_y;
} source_data;

typedef struct _detector_data  {
   long type;
   long nfast;
   long fastbinning;
   long fastorigin;
   long nslow;
   long sloworigin;
   long orientation;
} detector_data;

typedef struct _goniostat_position_data  {
   long ndetectors;
   long detector_distance[MAX_DETECTORS];
   long detector_2theta[MAX_DETECTORS];
   long omega;
   long chi;
   long phi;
   long delta;
   long gamma;
   long naxes;
   long axis_position[MAXAXES];
   void *axis_pointer[MAXAXES];
} goniostat_position_data;

typedef struct _storage_data  {
   long disk_files;
   char disk_directory[64];
   long tape_files;
   char tape_device[64];
   long tape_archive;
   char archive_device[64];
} storage_data;

typedef struct _exposure_data {
  long exposure_mode;
  long exposure_parameter; /* May be time, or dose, or ? */
  long detector_binning;
  long active_axis;
  long angular_width;
  long shutter;
} exposure_data;

typedef struct _runsegment_data  {
  long active_axis;
  long angular_width;
  long frame1;
  long frameN;
  goniostat_position_data    goniostat;
  exposure_data exposure;
} runsegment_data;

typedef struct _collection_data {
   experiment_data   experiment;
   crystal_data      crystal;
   source_data       source;
   detector_data     detector[MAX_DETECTORS];
   goniostat_position_data    goniostat;
   storage_data      storage;
   runsegment_data   runsegment[MAXSEGMENTS];
} collection_data;

#endif

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int frame_ok( data_frame *framep, data_frame *reference_framep); 

extern void setup_frame_header_from_sfv(data_frame *framep, SingleFrameValues *sfvp, GoniostatValues *gp);

extern void setup_frame_header_from_dataset_parameters( data_frame *fp, dataset_parameters *dspp, segment_parameters *segpp, GoniostatValues *gp);

extern int dataset_centering_first_crystal_sanity_check( dataset_parameters *dspp, char *error_buffer, int buflen);

extern int dataset_sanity_check( dataset_parameters *dspp, GoniostatValues *gp, int maxerrors, char *error_buffer, int buflen);

extern void setup_position(GoniostatValues *LocalGoniostatP, dataset_parameters *dspp, segment_parameters *segpp);

extern void setup_oscillation(GoniostatValues *LocalGoniostatP, segment_parameters *segpp);

extern void setup_single_frame_values(SingleFrameValues *lsfvp, dataset_parameters *dspp, segment_parameters *segpp);


extern int sanity_check_from_sfv( SingleFrameValues *lsfvp, GoniostatValues *gp, int maxerrors, char *error_buffer, int buflen);

extern void setup_position_from_sfv(GoniostatValues *LocalGoniostatP, SingleFrameValues *lsfvp);

extern void setup_oscillation_from_sfv(GoniostatValues *LocalGoniostatP, SingleFrameValues *lsfvp);

extern void init_dataset_parameter_axis_definitions(dataset_parameters *dp, GoniostatValues *gv);
extern int find_axis_index_by_name(char *name, char **name_list, int n_names);
extern int find_axis_index_by_name_in_GVoffset_list(char *name, intptr_t *axis_GVoffset_list, int n_axes, GoniostatValues *gv);
extern int find_axis_index_by_GVoffset(intptr_t GVoffset, intptr_t *axis_GVoffset_list, int n_axes);

extern void dataset_time_to_completion( double *seconds_to_go, double *seconds_total);

extern void *create_shared_framevalues( void);
extern int set_data_collection_protocol_active(int active);
extern int data_collection_protocol_active(void);
extern int set_data_collection_routine_active(int active);
extern int data_collection_routine_active(void);


#endif /* dataset_h */
