#ifndef detector_noneP_h
#define detector_noneP_h

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_none(void);
static int find_detector_none( DetectorType type, char *device, int port, int number);
static int init_detector_none( char * root_dir, char * device, int  port);
static int integrate_detector_none(int integration_time, int exposure_time);
static int read_detector_none(void *frame_structure);
static int abort_detector_none(void);
static int reset_detector_none(void);
static int close_detector_none(void);
static int query_detector_none(void);
static int set_option_detector_none(int option, void *argument);
static int get_option_detector_none(int option, void *argument);
static char * print_detector_none(void);
static int null_detector_none(void);
static int kill_detector_none(void);
static int raw_detector_none(const char *);
static int command_detector_none(int command, ...);


#endif /* detector_noneP_h */
