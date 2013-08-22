#ifndef detector_mmx1P_h
#define detector_mmx1P_h

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_mmx1(void);
static int find_detector_mmx1( DetectorType type, char *device, int port, int number);
static int init_detector_mmx1( char * root_dir, char * device, int  port);
static int integrate_detector_mmx1(int integration_time, int exposure_time);
static int read_detector_mmx1(void *framep);
static int abort_detector_mmx1(void);
static int reset_detector_mmx1(void);
static int close_detector_mmx1(void);
static int query_detector_mmx1(void);
static int set_option_detector_mmx1(int option, void *argument);
static int get_option_detector_mmx1(int option, void *argument);
static char * print_detector_mmx1(void);
static int null_detector_mmx1(void);
static int kill_detector_mmx1(void);
static int raw_detector_mmx1(const char *);


#endif /* detector_mmx1P_h */
