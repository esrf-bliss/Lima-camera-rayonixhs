#ifndef detector_mmxP_h
#define detector_mmxP_h

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_mmx(void);
static int find_detector_mmx( DetectorType type, char *device, int port, int number);
static int init_detector_mmx( char * root_dir, char * device, int  port);
static int integrate_detector_mmx(int integration_time, int exposure_time);
static int read_detector_mmx(void *framep);
static int abort_detector_mmx(void);
static int reset_detector_mmx(void);
static int close_detector_mmx(void);
static int query_detector_mmx(void);
static int set_option_detector_mmx(int option, void *argument);
static int get_option_detector_mmx(int option, void *argument);
static char * print_detector_mmx(void);
static int null_detector_mmx(void);
static int kill_detector_mmx(void);
static int raw_detector_mmx(const char *);

#endif /* detector_mmxP_h */
