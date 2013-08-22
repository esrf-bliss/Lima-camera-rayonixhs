#ifndef goniostat_h
#define goniostat_h

#include <stdint.h>

#include "configuration.h"

#define CENTER_MODE_MANUAL	0
#define CENTER_MODE_AUTO	1

#define MAX_GONIOSTATS		1
#define MAX_AXES		32
#define MAX_MOTOR_GROUPS	6
#define MAX_USER_POSITIONS	4
#define MAX_NAME_LENGTH 	32
#define GONIOSTAT_FILENAME_LENGTH	1024

#define GONIOSTAT_FAILURE  0
#define GONIOSTAT_SUCCESS  1
#define GONIOSTAT_UNKNOWN  2
#define GONIOSTAT_TIMEOUT  3

#define UNIT_NONE		0
#define UNIT_REVOLUTION		1
#define UNIT_DEGREE		2
#define UNIT_ARCMINUTE		3
#define UNIT_ARCSECOND		4
#define UNIT_METER		5
#define UNIT_CENTIMETER		6
#define UNIT_MILLIMETER		7
#define UNIT_MICRON		8
#define UNIT_NANOMETER		9
#define UNIT_ANGSTROM		10
#define UNIT_PICOMETER		11
#define UNIT_FEMTOMETER		12
#define UNIT_EV			13
#define UNIT_KEV		14
#define UNIT_DAY		15
#define UNIT_HOUR		16
#define UNIT_MINUTE		17
#define UNIT_SECOND		18
#define UNIT_MILLISECOND	19
#define UNIT_MICROSECOND	20
#define UNIT_NANOSECOND		21
#define UNIT_PICOSECOND		22
#define UNIT_FEMTOSECOND	23

#define MOTOR_GROUP_GONIOSTAT		0
#define MOTOR_GROUP_CRYSTAL		1
#define MOTOR_GROUP_BEAM		2
#define MOTOR_GROUP_TABLE		3
#define MOTOR_GROUP_SAMPLE_CHANGER	4

#define CANONICAL_OMEGA			1
#define CANONICAL_CHI			2
#define CANONICAL_KAPPS			3
#define CANONICAL_PHI			4
#define CANONICAL_GAMMA			5
#define CANONICAL_DELTA			6
#define CANONICAL_THETA			7
#define CANONICAL_THETA_2		8
#define CANONICAL_DISTANCE		9
#define CANONICAL_DISTANCE_2		10
#define CANONICAL_CRYSTAL_X		11
#define CANONICAL_CRYSTAL_Y		12
#define CANONICAL_CRYSTAL_Z		13
#define CANONICAL_ENERGY		14
#define CANONICAL_WAVELENGTH		15
#define CANONICAL_SHUTTER		16
#define CANONICAL_SAFETY_SHUTTER	17
#define CANONICAL_SLIT1_HOR		18
#define CANONICAL_SLIT1_VER		19
#define CANONICAL_SLIT2_HOR		20
#define CANONICAL_SLIT2_VER		21
#define CANONICAL_SLIT3_HOR		22
#define CANONICAL_SLIT3_VER		23
#define CANONICAL_TABLE_TRANS_HOR	24
#define CANONICAL_TABLE_TRANS_VER	25
#define CANONICAL_TABLE_ROT_HOR		26
#define CANONICAL_TABLE_ROT_VER		27
#define CANONICAL_CAROUSEL_SAMPLE	28
#define CANONICAL_CAROUSEL		29

#define DRIVE_TO_HOME1	1
#define DRIVE_TO_HOME2	2
#define DRIVE_TO_LIMIT1	3
#define DRIVE_TO_LIMIT2	4
#define DRIVE_TO_MIN	5
#define DRIVE_TO_MAX	6
#define DRIVE_DOWN	7
#define DRIVE_UP	8

#define GONIOSTAT_SC_INIT_MODE_ALL		0
#define GONIOSTAT_SC_INIT_MODE_SERVER_GROUP	1
#define GONIOSTAT_SC_INIT_MODE_CAROUSEL_GROUP	2
#define GONIOSTAT_SC_INIT_MODE_PHI_GROUP	3
#define GONIOSTAT_SC_INIT_MODE_CRYSTAL_GROUP	4
#define GONIOSTAT_SC_INIT_MODE_BARCODE_GROUP	5
#define GONIOSTAT_SC_INIT_MODE_EASYMOUNT_GROUP	6
#define GONIOSTAT_SC_INIT_MODE_CRYO		7

typedef enum {
   GONIOSTAT_SC_ERROR_UNKNOWN=-1,
   GONIOSTAT_SC_ERROR_NONE,
   GONIOSTAT_SC_ERROR_NOCAP,
   GONIOSTAT_SC_ERROR_NOVIAL,
   GONIOSTAT_SC_ERROR_NOEMPTY,
   GONIOSTAT_SC_ERROR_NOPINLENGTH,
   GONIOSTAT_SC_ERROR_CAP,
   GONIOSTAT_SC_ERROR_VIAL,
   GONIOSTAT_SC_ERROR_EMPTY,
   GONIOSTAT_SC_ERROR_GIVE_PHASE1_NOTEMPTY,
   GONIOSTAT_SC_ERROR_TAKE_PHASE4_NOTEMPTY,
   GONIOSTAT_SC_ERROR_READ_PHASE1_NOTEMPTY,
   GONIOSTAT_SC_ERROR_READ_PHASE4_NOTEMPTY,
   GONIOSTAT_SC_ERROR_LOAD_PHASE1_NOTEMPTY,
   GONIOSTAT_SC_ERROR_LOAD_PHASE2_NOCAP,
   GONIOSTAT_SC_ERROR_LOAD_PHASE2_NOVIAL,
   GONIOSTAT_SC_ERROR_LOAD_PHASE2_PINLEN,
   GONIOSTAT_SC_ERROR_LOAD_PHASE3_CAP,
   GONIOSTAT_SC_ERROR_LOAD_PHASE3_NOVIAL,
   GONIOSTAT_SC_ERROR_LOAD_PHASE4_NOTEMPTY,
   GONIOSTAT_SC_ERROR_UNLOAD_PHASE1_NOTEMPTY,
   GONIOSTAT_SC_ERROR_UNLOAD_PHASE2_CAP,
   GONIOSTAT_SC_ERROR_UNLOAD_PHASE2_NOVIAL,
   GONIOSTAT_SC_ERROR_UNLOAD_PHASE3_NOCAP,
   GONIOSTAT_SC_ERROR_UNLOAD_PHASE3_NOVIAL,
   GONIOSTAT_SC_ERROR_UNLOAD_PHASE4_NOTEMPTY
} GoniostatSCError;

typedef enum {
	EXPOSURE_MODE_TIME,
	EXPOSURE_MODE_DOSE
} ExposureMode;

typedef enum _GoniostatOption {
   GONIOSTAT_CAN_MEASURE_INTENSITY,
   GONIOSTAT_INTENSITY,
   GONIOSTAT_INTENSITY_RANGE,
   GONIOSTAT_INTENSITY_MAXIMUM,
   GONIOSTAT_DOSE_TO_TIME,
   GONIOSTAT_TIME_TO_DOSE,
   GONIOSTAT_CAN_TIME_CURRENT_SCAN,
   GONIOSTAT_CAN_TIME_DARK,
   GONIOSTAT_TIME_REMAINING,
   GONIOSTAT_EXPOSURE_SEQUENCE_STATUS,
   GONIOSTAT_SHUTTER_IS_AUTOMATIC,
   GONIOSTAT_SHUTTER_HAS_MANUAL_MODE,
   GONIOSTAT_SHUTTER_IN_MANUAL_MODE,
   GONIOSTAT_SHUTTER_MANUAL_IS_OPEN,
   GONIOSTAT_ERROR_STATUS,
   GONIOSTAT_ERROR_MESSAGE,
   GONIOSTAT_HAS_SAMPLE_CHANGER,
   GONIOSTAT_HAS_EASYMOUNT,
   GONIOSTAT_SAMPLE_CHANGER_MAXIMUM_SAMPLE_NUMBER,
   GONIOSTAT_SAMPLE_CHANGER_INITIALIZED,
   GONIOSTAT_SAMPLE_CHANGER_BUSY,
   GONIOSTAT_SAMPLE_CHANGER_ERROR_STATUS,
   GONIOSTAT_SAMPLE_CHANGER_POSITION,
   GONIOSTAT_SAMPLE_CHANGER_AT_OPERATING_TEMPERATURE,
   GONIOSTAT_SAMPLE_CHANGER_SAMPLE_MOUNTED,
   GONIOSTAT_SAMPLE_CHANGER_SAMPLE_CODE_RECENT,
   GONIOSTAT_SAMPLE_CHANGER_SAMPLE_CODE_MOUNTED,
   GONIOSTAT_SAMPLE_CHANGER_SAMPLE_CODE_STATUS,
   GONIOSTAT_SAMPLE_CHANGER_SAMPLE_ANGLE,
   GONIOSTAT_SAMPLE_CHANGER_BACKGROUND_IMAGE_OK,
   GONIOSTAT_SAMPLE_CHANGER_CAROUSEL_LOAD_POSITION,
   GONIOSTAT_SIMULATE_BEAM,
   GONIOSTAT_CRYSTAL_BACKGROUND,
   GONIOSTAT_CRYSTAL_ILLUMINATION,
   GONIOSTAT_BACKGROUND_ILLUMINATION,
   GONIOSTAT_AXIS_DEADBAND,
   GONIOSTAT_SCAN_SAMPLE_FREQUENCY,
   GONIOSTAT_CRYSTAL_ANNEAL_DURATION

} GoniostatOption;

typedef enum _GoniostatCommand {
   GONIOSTAT_COMMAND_CLEAR_COMMAND,
   GONIOSTAT_COMMAND_RAW_COMMAND,
   GONIOSTAT_COMMAND_QUERY_COMMAND,
   GONIOSTAT_COMMAND_NULL_COMMAND,
   GONIOSTAT_COMMAND_INITIALIZE_CONTROLLER,
   GONIOSTAT_COMMAND_OPEN_SHUTTER,
   GONIOSTAT_COMMAND_CLOSE_SHUTTER,
   GONIOSTAT_COMMAND_START_EXPOSURE_SEQUENCE,
   GONIOSTAT_COMMAND_ENABLE_CHAMBER_SWITCHING,
   GONIOSTAT_COMMAND_ENABLE_SERIAL_OUTPUT,
   GONIOSTAT_COMMAND_ENABLE_MANUAL_SHUTTER,
   GONIOSTAT_COMMAND_ENABLE_HV,
   GONIOSTAT_COMMAND_ENABLE_BEAM,
   GONIOSTAT_COMMAND_MOVE_AXIS_CONTINUOUS_SLOW,
   GONIOSTAT_COMMAND_MOVE_AXIS_CONTINUOUS,
   GONIOSTAT_COMMAND_STOP_AXIS,
   GONIOSTAT_COMMAND_ABORT_AXIS,
   GONIOSTAT_COMMAND_STOP_ALL_AXES,
   GONIOSTAT_COMMAND_ABORT_ALL_AXES,
   GONIOSTAT_COMMAND_HOME_AXIS,
   GONIOSTAT_COMMAND_HOME_ALL_AXES,
   GONIOSTAT_COMMAND_SCAN_AXIS,
   GONIOSTAT_COMMAND_STOP_SCAN_AXIS,
   GONIOSTAT_COMMAND_GET_SCAN,
   GONIOSTAT_COMMAND_SET_HEARTBEAT,
   GONIOSTAT_COMMAND_SET_ADC_AVERAGE,
   GONIOSTAT_COMMAND_SET_RC_UPDATE,
   GONIOSTAT_COMMAND_ENABLE_RC,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_PINLENGTH,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_PERMIT_ERROR_LEVEL,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_MAGNET_ON,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_INITIALIZE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_LOAD_SAMPLE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_UNLOAD_SAMPLE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_CHANGE_SAMPLE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_GIVE_SAMPLE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_TAKE_SAMPLE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_READ_SAMPLE_CODE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_CHECK_RANGE,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_ABORT,
   GONIOSTAT_COMMAND_SAMPLE_CHANGER_ANNEAL,
   GONIOSTAT_COMMAND_SET_MANUAL_MODE,
   GONIOSTAT_COMMAND_ENABLE_LOC_12V,
   GONIOSTAT_COMMAND_ENABLE_CRYSTAL_BACKGROUND,
   GONIOSTAT_COMMAND_ENABLE_CRYSTAL_ILLUMINATION,
   GONIOSTAT_COMMAND_ENABLE_CRYSTAL_BACKGROUND_ILLUMINATION,
   GONIOSTAT_COMMAND_ENABLE_INTENSITY_OUTPUT,
   GONIOSTAT_COMMAND_SET_RC_POSITION_DEFAULT,
   GONIOSTAT_COMMAND_SET_RC_POSITION_OTHER
} GoniostatCommand;


typedef enum _GoniostatType {
   GoniostatNone,
   GoniostatUnknown,
   GoniostatVirtual,
   GoniostatMMX, GoniostatMMX0, GoniostatMMX1, GoniostatMMX2,
   GoniostatMar, GoniostatMarSCSI,
   GoniostatMar345, GoniostatMar345V1, GoniostatMar345V2,
   GoniostatMarNet, GoniostatMarNetV1, GoniostatMarNetV2,
   GoniostatMarDTB,
   GoniostatSPEC,
   GoniostatEPICS,
   GoniostatTACO,
   GoniostatACE,
   GoniostatGRACE,
   GoniostatRemote,
   GoniostatSoftware
   } GoniostatType;

typedef struct _axis_parameters {
   double current;
   double previous;
   double next;
   double deadband;
   double user_positions[MAX_USER_POSITIONS];
   double min;
   double max;
   double home1;
   double home2;
   double limit1;
   double limit2;
   double speed;
   double speed2;
   double speed_min;
   double speed_max;
   double speed_factor;
   double com_delay;
   double acceleration;
   double reference_speed1;
   double reference_speed2;
   double reference_acceleration;
   double reference_timeout;
   double continuous_move_acceleration_factor;
   double continuous_move_speed;
   double offset;
   double exposure_current;
   double exposure_min;
   double exposure_max;
   double exposure_speed;
   double exposure_speed_min;
   double exposure_speed_max;
   double exposure_speed_factor;
   double exposure_com_delay;
   double scan_current;
   double scan_min;
   double scan_max;
   double scan_speed;
   double scan_speed_min;
   double scan_speed_max;
   double scan_speed_factor;
   double scan_com_delay;
   double anti_backlash_size;
   double anti_backlash_speed;
   double steps_per_drive_rev;
   double drive_rev_per_axis_rev;
   double pulses_per_deg;
   double divide;
   double run_current;
   double hold_current;
   int    synchronized;
   int    direction;
   int    has_user_positions[MAX_USER_POSITIONS];
   int    configurable;
   int    present;
   int    toggle;
   int    move_capable;
   int    exposure_capable;
   int    scan_capable;
   int    osc_capable;
   int    forgetful;
   int    expose;
   int    scan;
   int    oscillate;
   int    motor_control;
   int    motor_disconnected;
   int    automation_enabled;
   int    continuous_move_enabled;
   int    initialization_capable;
   int    initialization_enabled;
   int    easy_init_enabled;
   int    easy_scan_enabled;
   int    easy_set_enabled;
   int    easy_drive_enabled;
   int    external_control;
   int    external_encoder;
   int    secondary_hardware_control;
   int    pulses_per_step;
   int    has_rc_control;
   int    rc_position_parameter_default;
   int    rc_position_parameter_other;
   int    has_ok_flag;
   int    has_home_switch1;
   int    has_home_switch2;
   int    has_limit_switch1;
   int    has_limit_switch2;
   int    default_home_switch;
   int    home_switch;
   int    do_home;
   int    do_move;
   int    do_scan;
   int    do_expose;
   int    id;
   int    canonical_id;
   int    independent_programming;
   int    exposure_stop_id;
   int    unit;
   int    motor_group;
   char   device_name[GONIOSTAT_FILENAME_LENGTH];
   char   display_name[32];
   char   internal_name[32];
   char   unit_name[16];
   double (*transform_steps_to_units)(int mode, double steps);
   double (*transform_units_to_steps)(int mode, double units);
} axis_parameters;

typedef struct _GoniostatValues { GoniostatType	goniostat_type;
   char			goniostat_device[GONIOSTAT_FILENAME_LENGTH];
   char			goniostat_logical_name[GONIOSTAT_FILENAME_LENGTH];
   int			goniostat_port;
   char			goniostat_type_name[GONIOSTAT_FILENAME_LENGTH];
   char			parameter_file_name[GONIOSTAT_FILENAME_LENGTH];
   char			external_command_name[GONIOSTAT_FILENAME_LENGTH];
   char			carousel_changer_command_name[GONIOSTAT_FILENAME_LENGTH];
   int			external_server_type;
   int			int_parameter[64];
   int			reserved;
   char    		motor_group_name[MAX_MOTOR_GROUPS][MAX_NAME_LENGTH];
   char    		user_position_name[MAX_USER_POSITIONS][MAX_NAME_LENGTH];
   //axis_parameters	motor[MAX_AXES-1];
   axis_parameters	motor[MAX_AXES];
   //axis_parameters	shutter;
   double		omega_theta_min;
   double		omega_theta_max;
   int			n_detectors;
   int			send_commands;
   int			goniostat_initialized;
   int			last_static_variable;
   volatile int			communication_command_busy_pid;
   volatile int			communication_command_busy;
   volatile int			communication_write_busy;
   volatile int			communication_read_busy;
   volatile char                 scratch_area[4096];
} GoniostatValues;

typedef struct {
   double	position;
   int		adc1;
   int		adc2;
} GoniostatScanDataRecord;

typedef union {
   int				nrecords;
   GoniostatScanDataRecord	data;
} GoniostatScanData;

//extern GoniostatValues *TheGoniostatP;
extern axis_parameters *the_axes[];


/*----------------------------------------------------------------------------*/

/* A function for each function to be performed on or by a goniostat */
typedef  struct _goniostat_functions {
   GoniostatType (*goniostat_type)(void);
   int (*find_goniostat)(GoniostatType type, char *device, int port, int number);
   int (*init_goniostat)(char * config_dir, char * log_dir, char * device, int port);
   int (*init_data_goniostat)(GoniostatValues *goniostat_values);
   int (*get_data_goniostat)(GoniostatValues *cg);
   int (*set_data_goniostat)(GoniostatValues *cg);
   int (*get_option_goniostat)(int option, void *argument);
   int (*set_option_goniostat)(int option, void *argument);
   int (*command_goniostat)(int option, void *argument);
   char *(*print_goniostat)(void);
   void (*load_goniostat)(void);
   int (*query_goniostat)(int);
   void (*set_positions)(int all);
   int (*query_positions)(void);
   void (*load_speeds)(void);
   void (*query_speeds)(void);
   int (*query_movings)(void);
   int (*query_limit_statuses)(void);
   void (*load_oscillations)(void);
   void (*query_oscillations)(void);
   void (*load_ok_flags)(void);
   int (*query_ok_flags)(void);
   int (*move_positions_conditional)(void);
   int (*move_positions)(void);
   int (*start_oscillations)(void);
   int (*stop_oscillations)(void);
   int (*restore_positions)(void);
   int (*open_goniostat_shutter)(void);
   int (*close_goniostat_shutter)(void);
   int (*query_goniostat_shutter)(void);
   void (*wait_goniostat)(void);
   int (*abort_goniostat)(void);
   int (*close_goniostat)(void);
   int (*validate_positions)(GoniostatValues *gvp, char *buffer, int buffer_size);
   int (*validate_positions_conditional)(GoniostatValues *gvp, char *buffer, int buffer_size);
   char *(*printf_goniostat)(char *format, ...);
} goniostat_functions;


/* A pointer for each function to be performed on or by a goniostat */
extern GoniostatType (*goniostat_type)(void);
extern int (*find_goniostat)(GoniostatType type, char *device, int port, int number);
extern int init_goniostat(char * config_dir, char * log_dir, char * device, int port);
extern int init_data_goniostat(GoniostatValues *goniostat_values);
extern int (*get_data_goniostat)(GoniostatValues *cg);
extern int (*set_data_goniostat)(GoniostatValues *cg);
extern int get_option_goniostat(int option, void *argument);
extern int (*set_option_goniostat)(int option, void *argument);
extern int command_goniostat(int option, void *argument);
extern char *(*print_goniostat)(void);
extern void (*load_goniostat)(void);
extern int query_goniostat(int);
extern void set_positions(int all);
extern int query_positions(void);
extern void (*load_speeds)(void);
extern void (*query_speeds)(void);
extern int (*query_movings)(void);
extern int (*query_limit_statuses)(void);
extern void (*load_oscillations)(void);
extern void (*query_oscillations)(void);
extern void (*load_ok_flags)(void);
extern int (*query_ok_flags)(void);
extern int move_positions_conditional(void);
extern int move_positions(void);
extern int (*start_oscillations)(void);
extern int (*stop_oscillations)(void);
extern int (*restore_positions)(void);
extern int (*open_goniostat_shutter)(void);
extern int (*close_goniostat_shutter)(void);
extern int (*query_goniostat_shutter)(void);
extern void (*wait_goniostat)(void);
extern int (*abort_goniostat)(void);
extern int (*close_goniostat)(void);
extern int (*validate_positions)(GoniostatValues *gvp, char *buffer, int buffer_size);
extern int (*validate_positions_conditional)(GoniostatValues *gvp, char *buffer, int buffer_size);
extern char *(*printf_goniostat)(char *format, ...);


/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


/* The universal function for initializing the goniostat functions */
extern int init_goniostat_functions(
#if NeedFunctionPrototypes
GoniostatType type
#endif
);

extern GoniostatValues *get_goniostat_value_structure(
#if NeedFunctionPrototypes
void
#endif
);

extern axis_parameters **GetTheGoniostatAxes(void);

extern void goniostat_find_configuration_file(GoniostatValues *gv, char *root_dir);

extern void copy_goniostat_values(GoniostatValues *out, GoniostatValues *in);
extern int compare_goniostat_values(GoniostatValues *gv0, GoniostatValues *gv1);

extern void setup_axis_array_pointers( GoniostatValues *agp, axis_parameters **axis_array);
extern void goniostat_set_move_flag(GoniostatValues *GVp, int group, int set);
extern void goniostat_sync_next_positions(GoniostatValues *GVp);
extern void goniostat_set_near_home_positions(GoniostatValues *GVp, int group);
extern void goniostat_set_standard_next_positions(GoniostatValues *GVp, int position, int group);
extern void goniostat_copy_next_positions(GoniostatValues *GVOutp, GoniostatValues *GVInp);
extern void goniostat_copy_current_positions(GoniostatValues *GVOutp, GoniostatValues *GVInp);

extern double pulses_per_deg(
#if NeedFunctionPrototypes
axis_parameters *axis
#endif
);

extern int test_will_move_positions(GoniostatValues *gvp, char *buffer, int buffer_size);
extern int test_will_move_positions_conditional(GoniostatValues *gvp, char *buffer, int buffer_size);
extern int test_movable_positions_conditional(GoniostatValues *gv, char *buffer, int buffer_size);
extern int test_movable_positions(GoniostatValues *gv, char *buffer, int buffer_size);
extern int validate_next_positions_conditional(GoniostatValues *gv, char *buffer, int buffer_size);
extern int validate_next_positions(GoniostatValues *gv, char *buffer, int buffer_size);
extern int goniostat_position_decimal_places(axis_parameters *axis);
extern axis_parameters *find_axis_by_display_name(const char *name, GoniostatValues *GVp, int case_sensitive);
extern axis_parameters *find_axis_by_internal_name(const char *name, GoniostatValues *GVp, int case_sensitive);
extern axis_parameters *find_axis_by_name(const char *name, GoniostatValues *GVp, int case_sensitive);
extern axis_parameters *axisp_from_GVoffset(GoniostatValues *GVp, intptr_t offset);
extern intptr_t GVoffset_from_axisp(GoniostatValues *GVp, axis_parameters *axisp);
extern ConfigRecord *GetGoniostatConfigurationList(void);

extern double drive_motor_to(const char *motor_name, double position, char *error_buffer, int buflen);
extern double drive_motor_by(const char *motor_name, double position, char *error_buffer, int buflen);

extern int dtb_read_param_values(int nparams, int *params, int *values);

#endif	/* goniostat_h */
