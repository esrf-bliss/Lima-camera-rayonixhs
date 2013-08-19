#ifndef detector_rayonixP_h
#define detector_rayonixP_h

/* Driver file - needed for ioctl definitions and others... */
#include "drivers/si3097cs/si3097cs.h"
#include "drivers/si3097cs/si3097cs_ioctl.h"

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_rayonix(void);
static int find_detector_rayonix( DetectorType type, char *device, int port, int number);
static int init_detector_rayonix( char * root_dir, char * device, int  port);
static int integrate_detector_rayonix(int integration_time, int exposure_time);
static int read_detector_rayonix(void *framep);
static int abort_detector_rayonix(void);
static int reset_detector_rayonix(void);
static int close_detector_rayonix(void);
static int query_detector_rayonix(void);
static int set_option_detector_rayonix(int option, void *argument);
static int get_option_detector_rayonix(int option, void *argument);
static char * print_detector_rayonix(void);
static int null_detector_rayonix(void);
static int kill_detector_rayonix(void);
static int raw_detector_rayonix(const char *);
static int command_detector_rayonix(int command, ...);


#endif /* detector_rayonixP_h */
