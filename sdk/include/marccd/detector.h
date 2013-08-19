#ifndef detector_h
#define detector_h

#include "frame.h"
#include "geometry.h"

#include "drivers/marMosaic/G3.h"
#include "drivers/si3097cs/G4.h"

#define MAX_DETECTOR_TYPES	12

#define MAX_DETECTORS		2

#define MAX_ALLOWABLE_BINNINGS	16

#define MAX_READOUT_CHANNELS	64

#define MAX_SERIAL_OVERSCAN	256
#define MAX_PARALLEL_OVERSCAN	0

/* defined conditions */
#define DETECTOR_SUCCESS	0
#define DETECTOR_NOT_READY	1
#define DETECTOR_BUSY		2
/* error conditions */
#define DETECTOR_FAILURE	-1
#define DETECTOR_STATUS_UNKNOWN	-2

#define DETECTOR_SPECIAL_VERSION_NONE			0x0
#define DETECTOR_SPECIAL_VERSION_MMX_EMULATOR0		0x1
#define DETECTOR_SPECIAL_VERSION_MMX_PROTOTYPE0		0x2

/* Communication status */
#define DETECTOR_COMMUNICATION_STATUS_UNKNOWN	1
#define DETECTOR_COMMUNICATION_STATUS_UP	2
#define DETECTOR_COMMUNICATION_STATUS_DOWN	3

#define CHANNEL_MAJOR_ORDER	1
#define SENSOR_MAJOR_ORDER	2
#define SI_ORDER		SENSOR_MAJOR_ORDER
#define MARCCD_ORDER_ORDER	CHANNEL_MAJOR_ORDER

typedef enum {
   READOUT_MODE_HIGH_SPEED,
   READOUT_MODE_LOW_NOISE
} readout_modes;

#if 1
typedef enum {
      DETECTOR_BINNING_DEFAULT = -1,
      DETECTOR_BINNING_AUTO = 0,
      DETECTOR_BINNING_UNBINNED,
      DETECTOR_BINNING_BINNED2X2,
      DETECTOR_BINNING_BINNED3X3,
      DETECTOR_BINNING_BINNED4X4,
      DETECTOR_BINNING_BINNED5X5,
      DETECTOR_BINNING_BINNED6X6,
      DETECTOR_BINNING_BINNED7X7,
      DETECTOR_BINNING_BINNED8X8
   } DetectorMode;
#endif

/* Commands to set/get_options */
typedef enum {
   DETECTOR_NULL_OPTION,
   DETECTOR_TYPE,
   DETECTOR_CONTROLLER_TYPE,
   DETECTOR_CAMERA_TYPE,
   DETECTOR_SENSOR_TYPE,
   DETECTOR_SERIAL_NUMBER,
   DETECTOR_HARDWARE_CONFIGURATION,
   DETECTOR_FIRMWARE_FILE_CONFIGURATION,
   DETECTOR_FIRMWARE_FILE_PARTNUMBER,
   DETECTOR_FIRMWARE_FILE_REVNUMBER,
   DETECTOR_FIRMWARE_FILE_CHECKSUM,
   DETECTOR_SOFTWARE_CONFIGURATION,
   DETECTOR_SOFTWARE_PARTNUMBER,
   DETECTOR_SOFTWARE_REVNUMBER,
   DETECTOR_SOFTWARE_CHECKSUM,
   DETECTOR_CORRECTIONFILE_SUFFIX_RAW,
   DETECTOR_CORRECTIONFILE_SUFFIX_CORRECTED,
   DETECTOR_CONFIGURATIONFILE_BASENAME,
   DETECTOR_CONFIGURATIONFILE,
   DETECTOR_CORRECTIONFILE_BASENAME,
   DETECTOR_CORRECTIONFILE,
   DETECTOR_MICROCODEFILE_BASENAME,
   DETECTOR_MICROCODEFILE,
   DETECTOR_HOUSEKEEPING_PROCESSOR_VERSION,
   DETECTOR_INTEGRATION_START_TIME,
   DETECTOR_INTEGRATION_END_TIME,
   DETECTOR_INTEGRATE_TIME,
   DETECTOR_EXPOSURE_START_TIME,
   DETECTOR_EXPOSURE_END_TIME,
   DETECTOR_EXPOSURE_TIME,
   DETECTOR_READOUT_START_TIME,
   DETECTOR_READOUT_END_TIME,
   DETECTOR_READOUT_TIME,
   DETECTOR_INTEGRATE_WILL_BLOCK,
   DETECTOR_NEEDS_BIAS_FRAME,
   DETECTOR_NEEDS_DARK_FRAME,
   DETECTOR_MAXFRAMESIZE,
   DETECTOR_FRAMESIZE_PRERAW,
   DETECTOR_FRAMESIZE_RAW,
   DETECTOR_FRAMESIZE_CORRECTED,
   DETECTOR_PIXELSIZEX,
   DETECTOR_PIXELSIZEY,
   DETECTOR_ALLOWABLE_BINNINGS,
   DETECTOR_ALLOWABLE_PIXELSIZES,
   DETECTOR_ALLOWABLE_RESOLUTIONS,
   DETECTOR_UPDATE,
   DETECTOR_COOLER_SETPOINT,
   DETECTOR_TEMPERATURE_SETPOINT,
   DETECTOR_PORT_CONFIGURATION,
   DETECTOR_SENSOR_TEMPERATURE,
   DETECTOR_SENSOR_TEMPERATURES,
   DETECTOR_SYSTEM_TEMPERATURES,
   DETECTOR_CHAMBER_PRESSURE,
   DETECTOR_LINE_PRESSURE,
   DETECTOR_SYSTEM_PRESSURES,
   DETECTOR_SYSTEM_VOLTAGES,
   DETECTOR_OVERSCAN_FAST,
   DETECTOR_OVERSCAN_SLOW,
   DETECTOR_PIXEL_NOISE,
   DETECTOR_HARDWARE_FORMAT_PARAMETERS,
   DETECTOR_DEFAULT_FRAME_FORMAT_PARAMETERS,
   DETECTOR_READOUT_FORMAT_PARAMETERS,
   DETECTOR_FRAME_FORMAT_PARAMETERS,
   DETECTOR_SYSTEM_PARAMETERS,
   DETECTOR_STATUS,
   DETECTOR_EXTENDED_STATUS,
   DETECTOR_COMMUNICATION_STATUS,
   DETECTOR_TESTPATTERN,
   DETECTOR_READOUT_SPEED_PARAMETER,
   DETECTOR_READOUT_RATE,
   DETECTOR_EXPECTED_READOUT_TIME,
   DETECTOR_ACTIVE_READOUTS,
   DETECTOR_HARDWARE_RELATIVE_GAINS,
   DETECTOR_ACTIVE_RELATIVE_GAINS,
   DETECTOR_NGAIN_SETTINGS,
   DETECTOR_GAIN_SETTINGS,
   DETECTOR_GAIN_SETTING,
   DETECTOR_CCD_ATTENUATION,
   DETECTOR_ANALOG_ATTENUATION,
   DETECTOR_SPEED_SETTING,
   DETECTOR_DEFAULT_RESOLUTION_SETTING,
   DETECTOR_RESOLUTION_SETTING,
   DETECTOR_SHUTTER_IS_AUTOMATIC,
   DETECTOR_COOLER_OFFSET,
   DETECTOR_TEMPERATURE_OFFSET,
   DETECTOR_PIXEL_DEPTH,
   DETECTOR_PIXEL_BITS,
   DETECTOR_SERIAL_CONFIGURATION,
   DETECTOR_NUMBER_OF_READOUTS,
   DETECTOR_NUMBER_OF_READOUTS_PER_SENSOR_IN_FIRMWARE_CONFIGURATION,
   DETECTOR_MEAN,
   DETECTOR_RMS,
   DETECTOR_ANALOG_ADC_OFFSETS,
   DETECTOR_RELATIVE_PREAMP_GAINS,
   DETECTOR_ANALOG_PREAMP_OFFSETS,
   DETECTOR_DIGITAL_ADC_OFFSETS,
   DETECTOR_DIGITAL_PREAMP_OFFSETS,
   DETECTOR_PARALLEL_SHIFT_DELAY,
   DETECTOR_SHUTTER_CLOSE_DELAY,
   DETECTOR_COOLER_STATUS,
   DETECTOR_BASELINE,
   DETECTOR_SATURATION_LEVEL,
   DETECTOR_BADPIXEL_FLAG,
   DETECTOR_ERROR_STATUS,
   DETECTOR_SHUTTER_STATUS,
   DETECTOR_INTEGRATION_STATUS,
   DETECTOR_READOUT_STATUS,
   DETECTOR_AUX_INTERRUPT_STATUS,
   DETECTOR_SOFTWARE_READ_TRIGGER_STATUS,
   DETECTOR_TRIGGER_EXTERNALLY,
   DETECTOR_TRIGGER_TTL_IN,
   DETECTOR_TRIGGER_TTL_OUT,
   DETECTOR_TIME_REMAINING,
   DETECTOR_READ_TIME_REMAINING,
   DETECTOR_STATUS_BLOCK_ADDRESS,
   DETECTOR_INTEGRATION_TIMER_DONE,
   DETECTOR_READ_BUFFER_ONLY,
   DETECTOR_CAN_DO_FRAMESHIFT,
   DETECTOR_FRAMESHIFT_LINES,
   DETECTOR_TRIGGER_IN_PULLUP,
   DETECTOR_TRIGGER2_IN_PULLUP,
   DETECTOR_QUERY_SYSTEM_STATUS,
   DETECTOR_QUERY_SENSOR_STATUS,
   DETECTOR_QUERY_ADC_STATUS,
   DETECTOR_QUERY_SYSTEM_CONFIGURATION,
   DETECTOR_QUERY_SENSOR_CONFIGURATION,
   DETECTOR_QUERY_SYSTEM_FORMAT,
   DETECTOR_QUERY_SYSTEM_READOUT,
   DETECTOR_QUERY_SENSOR_READOUT,
   DETECTOR_SET_SYSTEM_CONFIGURATION,
   DETECTOR_SET_SENSOR_CONFIGURATION,
   DETECTOR_SET_SYSTEM_FORMAT,
   DETECTOR_SET_SYSTEM_READOUT,
   DETECTOR_SET_SENSOR_READOUT,
   DETECTOR_SENSOR_SELECT,
   DETECTOR_PRESET,
   DETECTOR_PRESET_NAMES,
   DETECTOR_REGION_OF_INTEREST,
   DETECTOR_REGION_OF_INTEREST_CORR
} DetectorOption;

extern char **DetectorOptionStrings;


/* Possible commands to command_detector */
typedef enum {
   COLLECT_REALTIME_CORRECTION_DATA,
   DETECTOR_COMMAND_OPEN_SHUTTER,
   DETECTOR_COMMAND_CLOSE_SHUTTER,
   DETECTOR_COMMAND_ENABLE_COOLING,
   DETECTOR_COMMAND_DISABLE_COOLING,
   DETECTOR_COMMAND_VACUUM_VALVE_ENABLE,
   DETECTOR_COMMAND_VACUUM_VALVE_DISABLE,
   DETECTOR_COMMAND_VACUUM_VALVE_OPEN,
   DETECTOR_COMMAND_VACUUM_VALVE_CLOSE,
   DETECTOR_COMMAND_VACUUM_PUMP_IGNORE,
   DETECTOR_COMMAND_TEMP_SENSOR_IGNORE,
   DETECTOR_COMMAND_ENABLE_HEATING,
   DETECTOR_COMMAND_DISABLE_HEATING,
   DETECTOR_COMMAND_REBOOT_CONTROLLER,
   DETECTOR_COMMAND_ABORT_INTEGRATION,
   DETECTOR_COMMAND_TEST_TIMER_AND_TRIGGER_READ,
   DETECTOR_COMMAND_REWIND_DETECTOR_BUFFER,
   DETECTOR_COMMAND_READ_DETECTOR_BUFFER,
   DETECTOR_COMMAND_QUERY_FIRMWARE,
   DETECTOR_COMMAND_STORE_FIRMWARE,
   DETECTOR_COMMAND_DUMP_PARAMETERS,
   DETECTOR_COMMAND_STORE_DEFAULTS,
   DETECTOR_COMMAND_STORE_READOUT_MODE,
   DETECTOR_COMMAND_STORE_FORMAT_MODE,
   DETECTOR_COMMAND_RESTORE_DEFAULTS,
   DETECTOR_COMMAND_RESTORE_READOUT_MODE,
   DETECTOR_COMMAND_RESTORE_FORMAT_MODE,
   DETECTOR_COMMAND_DELETE_READOUT_MODE,
   DETECTOR_COMMAND_DELETE_FORMAT_MODE,
   DETECTOR_COMMAND_LOG_STATUS
} DetectorCommand;

typedef enum {
   DETECTOR_SPEED_AUTO, DETECTOR_SPEED_VERY_LOW, DETECTOR_SPEED_LOW, DETECTOR_SPEED_MEDIUM, DETECTOR_SPEED_HIGH, DETECTOR_SPEED_VERY_HIGH
   } DetectorSpeed;
typedef enum {
   DETECTOR_GAIN_AUTO, DETECTOR_GAIN_VERY_LOW, DETECTOR_GAIN_LOW, DETECTOR_GAIN_MEDIUM, DETECTOR_GAIN_HIGH, DETECTOR_GAIN_VERY_HIGH
   } DetectorGain;

#define SI900S_RABBIT_VACUUM_PUMP_PRESENT		(1 << 0)
#define SI900S_RABBIT_VACUUM_PUMP_RUNNING		(1 << 1)
#define SI900S_RABBIT_VACUUM_SENSOR_PRESENT_CHAMBER	(1 << 2)
#define SI900S_RABBIT_VACUUM_PURGED_CHAMBER		(1 << 3)
#define SI900S_RABBIT_COOLER_ENABLED			(1 << 4)
#define SI900S_RABBIT_COOLER_COMMANDED_ON		(1 << 5)
#define SI900S_RABBIT_COOLER_ON1			(1 << 6)
#define SI900S_RABBIT_COOLER_ON2			(1 << 7)
#define SI900S_RABBIT_VACUUM_SENSOR_PRESENT_LINE	(1 << 8)
#define SI900S_RABBIT_VACUUM_PURGED_LINE		(1 << 9)
#define SI900S_RABBIT_VACUUM_VALVE_ENABLED		(1 << 10)
#define SI900S_RABBIT_VACUUM_PURGE_MODE_ON		(1 << 11)
#define SI900S_RABBIT_VACUUM_VALVE_OPEN			(1 << 12)
#define SI900S_RABBIT_TEMPERATURE_SENSOR_PRESENT_CASE	(1 << 13)
#define SI900S_RABBIT_OVERTEMPERATURE_CASE		(1 << 14)
#define SI900S_RABBIT_CASE_OVERRIDE			(1 << 15)
#define SI900S_RABBIT_PUMP_OVERRIDE			(1 << 16)
#define SI900S_RABBIT_PUMP_TYPE_PFEIFFER		(1 << 17)
#define SI900S_RABBIT_PUMP_TYPE_VARIAN			(1 << 18)
#define SI900S_RABBIT_SPARE5				(1 << 19)
#define SI900S_RABBIT_SPARE4				(1 << 20)
#define SI900S_RABBIT_SPARE3				(1 << 21)
#define SI900S_RABBIT_SPARE2				(1 << 22)
#define SI900S_RABBIT_SPARE1				(1 << 23)

#define SI1100S_HKS_FLAG_ENABLE_FW_HEAT		(1 << 0)
#define SI1100S_HKS_FLAG_ENABLE_CB_HEAT		(1 << 1)
#define SI1100S_HKS_FLAG_COOLER_ENABLED		(1 << 2)
#define SI1100S_HKS_FLAG_BP_TEMP_PRESENT	(1 << 3)
#define SI1100S_HKS_FLAG_BP_OVERRIDE		(1 << 4)
#define SI1100S_HKS_FLAG_BP_OVERTEMP		(1 << 5)
#define SI1100S_HKS_FLAG_CRC_MISMATCH		(1 << 14)
#define SI1100S_HKS_FLAG_ALARM			(1 << 15)

#define SI1100S_PS_FLAG_CAMERA_ON		(1 << 0)
#define SI1100S_PS_FLAG_COOLER_ENABLE		(1 << 1)
#define SI1100S_PS_FLAG_AC_ON			(1 << 2)
#define SI1100S_PS_FLAG_CRYO_RUNNING		(1 << 3)
#define SI1100S_PS_FLAG_HEAT_AMPS_OK		(1 << 4)
#define SI1100S_PS_FLAG_HEAT_ON			(1 << 5)
#define SI1100S_PS_FLAG_AUX_V_ON		(1 << 6)
#define SI1100S_PS_FLAG_UNUSED0			(1 << 7)
#define SI1100S_PS_FLAG_UNUSED1			(1 << 8)
#define SI1100S_PS_FLAG_UNUSED2			(1 << 9)
#define SI1100S_PS_FLAG_UNUSED3			(1 << 10)
#define SI1100S_PS_FLAG_SWITCHER		(1 << 11)
#define SI1100S_PS_FLAG_CRC_RECORDED		(1 << 12)
#define SI1100S_PS_FLAG_CRC_MISMATCH		(1 << 13)
#define SI1100S_PS_FLAG_AC_MISMATCH		(1 << 14)
#define SI1100S_PS_FLAG_ALARM			(1 << 15)

typedef enum _DetectorType {
   DetectorNone, DetectorUnknown, DetectorVirtual,
   DetectorMMX , DetectorMMX0, DetectorMMX1, DetectorMMX2,
   DetectorNWU0, DetectorNWU1,
   DetectorSI500,
   DetectorMarCCD,DetectorMarMosaic,
   DetectorRayonix,
   DetectorMarIP, DetectorMar180, DetectorMar300,  DetectorMar345, DetectorMar345V1, DetectorMar345V2
   } DetectorType;

typedef enum _ReadoutType {
   ReadoutNormal, ReadoutBinned, ReadoutAOI
   } ReadoutType;

struct _detector_format_parameters {
/*for hardware_format:
   serial and parallel_length are the number of unbinned pixels on CCD chip.
   serial and parallel_origin are unused "warm-up" pixels on the chip.
   binning is the maximum possible binning for the chip.
   pixelsize is the actual pixel size for the chip.
for frame_format:
   serial and parallel_length are the image dimensions in binned pixels.
   serial and parallel_origin are not yet used?
   binning is the binning to use for the image.
   pixelsize is adjusted for image binning.
for readout_format:
   serial and parallel_length are the number of binned pixels to readout per channel.
   serial and parallel_origin are the number of unbinned pixels to skip due to unused "warm-up" pixels and binning alignment.
   binning is the binning to use for the readout.
   pixelsize is adjusted for image binning, as in frame_format.*/
   int    pixel_depth;
   int    serial_configuration, serial_prescan, serial_origin, serial_length, serial_binning, serial_postscan, serial_pixelsize;
   //prescan and postscan would be extra (non-image) pixels read out before/after image pixels
   //a serial_configuration of "1" means the 2nd serial register (e.g. the "bottom one") is to read out in the opposite direction of the primary one.
   //Note: a serial/parallel_phase of "1" in the configuration file means the registers are read out in the opposite direction of usual.
   int    serial_underscan, serial_overscan;
   //serial_overscan are extra pixels read out _after_ image pixels (used for baseline stabilization)
   //underscan would be extra pixels read out _before_ image pixels (this value is not used)
   int    serial_rawlength; //includes image pixels, pre-scan pixels (unused) and post-scan pixels (for baseline stabilization).
   int    parallel_configuration, parallel_prescan, parallel_origin, parallel_length, parallel_binning, parallel_postscan, parallel_pixelsize;
   int    parallel_underscan, parallel_overscan;  //unused
   int    parallel_rawlength; //includes image pixels, pre-scan pixels (unused) and post-scan pixels
   int    nports_per_sensor, readout_pattern;
   int    nsensors_fast, nsensors_slow, nsensors_enabled;
   int    row_enable_flags[MAX_SENSOR_ROWS];
   int    orientation_code;
   int    array_orientation_code;
   };

typedef struct {
   /* Structure defintion */
   int type;

   int		correction_time;
   double	correction_distance;
} nwu0_specific_structure;

typedef struct {
	int speed_parameter;
	int binning;
	int gain;
	int ccd_attenuation;
	int analog_attenuation;
	} speed_bin_gain_group;

typedef struct  {
   /* Structure definition */
   int type;

   /* Configuration parameters */
   int hardware_configuration;
   int serial_number;
   int software_configuration;
   int firmware_id;
   int firmware_revision;
   int firmware_checksum;

   /* System paremeters */
   int temperature_offset;
   int temperature_setpoint;
   int parallel_shift_delay;
   int parallel_configuration;
   int parallel_phasing;
   int parallel_split;
   int parallel_size;
   int serial_configuration;
   int serial_phasing;
   int serial_split;
   int serial_size;
   int analog0_offset;
   int analog1_offset;
   int analog2_offset;
   int analog3_offset;
   int DSI_sample_time;
   int gain;
   int number_of_ports;
   int shutter_close_delay;
   int spare1, spare2;
   int amplifier_gainA, amplifier_gainB, amplifier_gainC, amplifier_gainD;
   int amplifier_biasA, amplifier_biasB, amplifier_biasC, amplifier_biasD;
   int amplifier_bias0, amplifier_bias1, amplifier_bias2, amplifier_bias3;
   int desired_bias;
   int saturation_level;
   int badpixel_flag;

   /* Format parameters */
   int    serial_origin, serial_length, serial_binning, serial_postscan; 
   int    parallel_origin, parallel_length, parallel_binning, parallel_postscan; 
   int    pixel_depth; 
   int    ports_in_use; 
   int    shift_lines;
   int    command_on_trigger;

   /* Exposure time */
   int exposure_time;

   /* Status variables */
   int CCD_temperature;
   int chamber_pressure;
   int loaded_exposure_time;
   int controller_integrating;
   int shutter_status;
   int cooler_status;
   int error_status;
   int aux_interrupt_status;

   /* Misc program stuff */
#define MAX_GAIN_OPTIONS	5
   int ngain_selections;
   speed_bin_gain_group gain_selection[MAX_GAIN_OPTIONS];

   double gain_corrections[MAX_SENSORS][MAX_CHANNELS_PER_SENSOR];

} marCCD_specific_structure;

typedef struct  {
   /* Structure definition */
   int type;

   /* Configuration parameters */
   int hardware_configuration;
   int serial_number;
   int dspcode_file_configuration;
   int dspcode_file_id;
   int dspcode_file_revision;
   int dspcode_file_checksum;
   int firmware_configuration;
   int firmware_id;
   int firmware_revision;
   int firmware_checksum;

   /* System paremeters */
   int temperature_offset;
   int temperature_setpoint;
   int cooler_offset;
   int cooler_setpoint;
   int parallel_shift_delay;
   int parallel_configuration;
   int parallel_phasing;
   int parallel_split;
   int parallel_size;
   int serial_configuration;
   int serial_phasing;
   int serial_split;
   int serial_size;
   int analog0_offset;
   int analog1_offset;
   int analog2_offset;
   int analog3_offset;
   int DSI_sample_time;
   int gain;
   int number_of_ports;
   int shutter_close_delay;
   int spare1, spare2;
   int amplifier_gainA, amplifier_gainB, amplifier_gainC, amplifier_gainD;
   int amplifier_biasA, amplifier_biasB, amplifier_biasC, amplifier_biasD;
   int amplifier_bias0, amplifier_bias1, amplifier_bias2, amplifier_bias3;
   int desired_bias;
   int saturation_level;
   int badpixel_flag;

   /* Exposure time */
   int exposure_time;

   /* Status variables */
   int CCD_temperature;
   int chamber_pressure;
   int loaded_exposure_time;
   int controller_integrating;
   int shutter_status;
   int cooler_status;
   int error_status;
   int aux_interrupt_status;

   /* Misc program stuff */
#define MAX_GAIN_OPTIONS	5
   int ngain_selections;
   speed_bin_gain_group gain_selection[MAX_GAIN_OPTIONS];

   double gain_corrections[MAX_SENSORS][MAX_CHANNELS_PER_SENSOR];

   CameraParameters	camera_parameters;

} marMosaic_specific_structure;

typedef struct  {
   /* Structure definition */
   int type;

   /* Configuration parameters */
   int hardware_configuration;
   int serial_number;
   int dspcode_file_configuration;
   int dspcode_file_id;
   int dspcode_file_revision;
   int dspcode_file_checksum;
   int firmware_configuration;
   int firmware_id;
   int firmware_revision;
   int firmware_checksum;

   /* System paremeters */
   int temperature_offset;
   int temperature_setpoint;
   int cooler_offset;
   int cooler_setpoint;
   int parallel_shift_delay;
   int parallel_configuration;
   int parallel_phasing;
   int parallel_split;
   int parallel_size;
   int serial_configuration;
   int serial_phasing;
   int serial_split;
   int serial_size;
   int analog0_offset;
   int analog1_offset;
   int analog2_offset;
   int analog3_offset;
   int DSI_sample_time;
   int gain;
   int number_of_ports;
   int shutter_close_delay;
   int spare1, spare2;
   int amplifier_gainA, amplifier_gainB, amplifier_gainC, amplifier_gainD;
   int amplifier_biasA, amplifier_biasB, amplifier_biasC, amplifier_biasD;
   int amplifier_bias0, amplifier_bias1, amplifier_bias2, amplifier_bias3;
   int desired_bias;
   int saturation_level;
   int badpixel_flag;

   /* Exposure time */
   int exposure_time;

   /* Status variables */
   int CCD_temperature;
   int chamber_pressure;
   int loaded_exposure_time;
   int controller_integrating;
   int shutter_status;
   int cooler_status;
   int error_status;
   int aux_interrupt_status;

   /* Misc program stuff */
#define MAX_GAIN_OPTIONS	5
   int ngain_selections;
   speed_bin_gain_group gain_selection[MAX_GAIN_OPTIONS];

   double gain_corrections[MAX_SENSORS][MAX_CHANNELS_PER_SENSOR];

   SICameraParameters	camera_parameters;

} rayonix_specific_structure;

typedef struct  {
   /* Structure definition */
   int type;

   /* Configuration parameters */
   int serial_number;
   int resolution;
   int readout_pattern;
   int sensors_fast;
   int sensors_slow;

} none_specific_structure;



typedef union {
   rayonix_specific_structure rayonix;
   marMosaic_specific_structure marMosaic;
   marCCD_specific_structure marCCD;
   nwu0_specific_structure nwu0;
   none_specific_structure none;
} detector_specific_union;



typedef struct _DetectorValues {
   DetectorType    detector_type;
   int    detector_initialized;
   char   detector_device[256];
   int    detector_port;
   int    detector_special_version;
   int    device_fd;
   int    auxillary_device_type;
   char   auxillary_device_name[256];
   int    auxillary_device_fd;
   int    detector_com_status;
   char   detector_config_directory[256];
   char   configurationfile_basename[256];
   char   correctionfile_basename[256];
   char   microcodefile_basename[256];
   int    controller_type;
   int    camera_type;
   int    sensor_type;
   int    nfast;
   int    nslow;
   int    bytes_per_pixel;
   int    binned;
   int    binning_fast;
   int    binning_slow;
   int    aoi;
   int    aoi_fast;
   int    aoi_slow;
   int    test_pattern;
   int    correction_time;
   int    readout_rate;
   int    expose_on_external_trigger;
   int    read_on_external_trigger;
   int	  software_trigger_status;
   int    send_signal_after_integration_start;
   double    correction_distance;
   int    allowable_binnings[MAX_ALLOWABLE_BINNINGS];

   /* Option Flags */
   int IntegrateWillBlock;
   int TimeExposureInGoniostat;
   int ReadBufferOnlyFlag;

   /* State flags */
   void *external_status_block;  /* address to copy next four variables to */
   int DetectorIsIntegrating;
   int DetectorExposureTimeRemaining;
   int DetectorIsDoingDMA;
   int DetectorReadTimeRemaining;

   int DetectorNewFrameInPhysicalBuffer;
   int DetectorIsTimingIntegration;
   int GoniostatIsTimingIntegration;

   /* Image format */
   struct _detector_format_parameters hardware_frame_format;
   struct _detector_format_parameters default_frame_format;
   struct _detector_format_parameters frame_format;
   struct _detector_format_parameters readout_format;
   detector_specific_union detector_specific;
   struct RectCartInt region_of_interest; //Rectangle containing region of interest (raw coords)
   struct RectCartInt region_of_interest_corr; //Rectangle containing region of interest (corrected coords)
   struct PointCartInt roi_within_pre_raw; //Location of region of interest within the read-out pre-raw frame
} DetectorValues;


/*----------------------------------------------------------------------------*/


/* A function for each function to be performed on or by a detector */
typedef  struct _detector_functions {
   DetectorType (*detector_type)(void);
   int (*find_detector)( DetectorType type, char *device, int port, int number);
   int (*init_detector)( char * root_dir, char * device, int  port);
   int (*integrate_detector)(int integration_time, int exposure_time);
   int (*read_detector)(void *framep);
   int (*abort_detector)(void);
   int (*reset_detector)(void);
   int (*close_detector)(void);
   int (*query_detector)(void);
   int (*set_option_detector)(int option, void *argument);
   int (*get_option_detector)(int option, void *argument);
   char * (*print_detector)(void);
   int (*null_detector)(void);
   int (*kill_detector)(void);
   int (*raw_detector)(const char *);
   int (*command_detector)(int command, ...);
   void (*get_driver_version)(char *driver_version);
} detector_functions;


/* A pointer for each function to be performed on or by a detector */
extern DetectorType (*detector_type)(void);
extern int (*find_detector)(DetectorType type, char *device, int port, int number);
extern int (*init_detector)(char * root_dir, char * device, int  port);
extern int (*integrate_detector)(int integration_time, int exposure_time);
extern int (*read_detector)(void *framep);
extern int (*abort_detector)(void);
extern int (*reset_detector)(void);
extern int (*close_detector)(void);
extern int (*query_detector)(void);
extern int (*set_option_detector)(int option, void *argument);
extern int (*get_option_detector)(int option, void *argument);
extern char * (*print_detector)(void);
extern int (*null_detector)(void);
extern int (*kill_detector)(void);
extern int (*raw_detector)(const char *);
extern int (*command_detector)(int command, ...);
extern void (*get_driver_version)(char *driver_version);


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


/* The universal function for initializing the detector functions */
extern int init_detector_functions(
#if NeedFunctionPrototypes
DetectorType type
#endif
);

extern DetectorValues *get_detector_value_structure(
#if NeedFunctionPrototypes
void
#endif
);

extern void print_frame_format(char *label, struct _detector_format_parameters *formatp);

extern int convert_readoutpattern_to_phasing(int readout_pattern, int serial_configuration, int parallel_configuration, int *serial_splitp, int *serial_phasingp, int *parallel_splitp, int *parallel_phasingp, int *true_number_of_portsp, int *port_selectp);

extern int convert_phasing_to_readoutpattern(int serial_configuration, int parallel_configuration, int serial_split, int serial_phasing, int parallel_split, int parallel_phasing, int *number_of_ports, int *readout_pattern);

extern int convert_readoutformat_to_frameformat( struct _detector_format_parameters *hardware_format, struct _detector_format_parameters *readout_format, struct _detector_format_parameters *frame_format);

int convert_frameformat_to_readoutformat(struct _detector_format_parameters *hardware_format, struct _detector_format_parameters *frame_format, struct _detector_format_parameters *readout_format);

extern void guess_and_set_overscan_in_readout_format (struct _detector_format_parameters *hardware_formatp, struct _detector_format_parameters *readout_formatp);

extern int set_binning_in_readout_format (int binning, struct _detector_format_parameters *hardware_formatp, struct _detector_format_parameters *readout_formatp);

extern int set_binning_in_frame_format (int binning, struct _detector_format_parameters *hardware_formatp, struct _detector_format_parameters *frame_formatp);

extern int setup_detector_mode(data_frame *the_correction_table, int detector_binning, int stabilize_baseline, double baseline_stabilization_target, int do_frameshift, int shift_size, struct RectCartInt *ROI, char *error_buffer, int error_buffer_size);

extern int calculate_overscan_from_stability(double stability);

extern double calculate_stability_from_overscan(void);

extern int count_ports_per_sensor(int readout_pattern);

extern int calculate_offsets_of_muxed_readouts_in_full_readout_list(int verbose, int original_order, int mux_pattern, int *muxed_offset_list, int *n_active_channels, int n_channels_per_sensor, int n_sensors_fast, int n_sensors_slow, int parallel_configuration, int serial_configuration, int hardware_mux_pattern, int array_orientation);

extern int push_muxed_list_into_readout_channel_list(int verbose, int original_order, int mux_pattern, int *muxed_list, int *muxed_offset_list, int *n_active_channels, int n_channels_per_sensor, int *sensor_list, int n_sensors_fast, int n_sensors_slow, int parallel_configuration, int serial_configuration, int hardware_mux_pattern, int array_orientation);

extern int pull_muxed_list_from_readout_channel_list(int verbose, int original_order, int mux_pattern, int *muxed_list, int *muxed_offset_list, int *n_active_channels, int n_channels_per_sensor, int *sensor_list, int n_sensors_fast, int n_sensors_slow, int parallel_configuration, int serial_configuration, int hardware_mux_pattern, int array_orientation);

extern int image_format_readout_pattern(int readout_pattern, int parallel_configuration, int serial_configuration, int to_image);

extern int integer_orientation_code(const char *string);

extern int check_for_new_correction_file(const char *old_filename, char *error_buffer, int buflen);

extern int process_baseline_stabilization(data_frame *raw_framep, data_frame *preraw_framep);

//Added for region of interest...
int demirror_region_of_interest(data_frame *raw_roi_frame, data_frame *preraw_frame);
int pixels_in_binned_frame(int nfast_or_nslow_hardware, int binning);
int get_serial_pixels_from_detector_values(DetectorValues *Dp);
int ctbl_matches_roi(data_frame *ctbl, struct RectCartInt ROI);
struct _detector_format_parameters guess_frameformat_from_detector_values(void);

int change_readout_mode(int new_mode); //changes to high_speed/low_noise
int get_readout_mode(); //returns high_speed/low_noise
int switch_calib_tables_for_readout_mode(int new_mode);

#endif /* detector_h */
