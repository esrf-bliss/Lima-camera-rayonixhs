#ifndef detector_nwu0P_h
#define detector_nwu0P_h

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_nwu0(void);
static int find_detector_nwu0( DetectorType type, char *device, int port, int number);
static int init_detector_nwu0( char * root_dir, char * device, int  port);
static int integrate_detector_nwu0(int integration_time, int exposure_time);
static int read_detector_nwu0(void *framep);
static int abort_detector_nwu0(void);
static int reset_detector_nwu0(void);
static int close_detector_nwu0(void);
static int query_detector_nwu0(void);
static int set_option_detector_nwu0(int option, void *argument);
static int get_option_detector_nwu0(int option, void *argument);
static char * print_detector_nwu0(void);
static int null_detector_nwu0(void);
static int kill_detector_nwu0(void);
static int raw_detector_nwu0(const char *);
static int command_detector_nwu0(int command, ...);

#endif /* detector_nwu0P_h */
