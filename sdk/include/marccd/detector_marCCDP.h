#ifndef detector_marCCDP_h
#define detector_marCCDP_h

/* Driver file - needed for ioctl definitions and others... */
#include "drivers/marCCD/marCCD.h"
#include "drivers/marCCD/marCCD_ioctl.h"

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_marCCD(void);
static int find_detector_marCCD( DetectorType type, char *device, int port, int number);
static int init_detector_marCCD( char * root_dir, char * device, int  port);
static int integrate_detector_marCCD(int integration_time, int exposure_time);
static int read_detector_marCCD(void *framep);
static int abort_detector_marCCD(void);
static int reset_detector_marCCD(void);
static int close_detector_marCCD(void);
static int query_detector_marCCD(void);
static int set_option_detector_marCCD(int option, void *argument);
static int get_option_detector_marCCD(int option, void *argument);
static char * print_detector_marCCD(void);
static int null_detector_marCCD(void);
static int kill_detector_marCCD(void);
static int raw_detector_marCCD(const char *);
static int command_detector_marCCD(int command, ...);


#endif /* detector_marCCDP_h */
