#ifndef detector_si500P_h
#define detector_si500P_h

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_si500(void);
static int find_detector_si500( DetectorType type, char *device, int port, int number);
static int init_detector_si500( char * root_dir, char * device, int  port);
static int integrate_detector_si500(int integration_time, int exposure_time);
static int read_detector_si500(void *framep);
static int abort_detector_si500(void);
static int reset_detector_si500(void);
static int close_detector_si500(void);
static int query_detector_si500(void);
static int set_option_detector_si500(int option, void *argument);
static int get_option_detector_si500(int option, void *argument);
static char * print_detector_si500(void);
static int null_detector_si500(void);
static int kill_detector_si500(void);
static int raw_detector_si500(const char *);
static int command_detector_si500(int command, ...);


#endif /* detector_si500P_h */
