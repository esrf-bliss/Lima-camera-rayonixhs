#ifndef detector_marMosaicP_h
#define detector_marMosaicP_h

/* Driver file - needed for ioctl definitions and others... */
#include "drivers/marMosaic/marMosaic.h"
#include "drivers/marMosaic/marMosaic_ioctl.h"

/* A local function for each function to be performed on or by a detector */
static DetectorType detector_type_marMosaic(void);
static int find_detector_marMosaic( DetectorType type, char *device, int port, int number);
static int init_detector_marMosaic( char * root_dir, char * device, int  port);
static int integrate_detector_marMosaic(int integration_time, int exposure_time);
static int read_detector_marMosaic(void *framep);
static int abort_detector_marMosaic(void);
static int reset_detector_marMosaic(void);
static int close_detector_marMosaic(void);
static int query_detector_marMosaic(void);
static int set_option_detector_marMosaic(int option, void *argument);
static int get_option_detector_marMosaic(int option, void *argument);
static char * print_detector_marMosaic(void);
static int null_detector_marMosaic(void);
static int kill_detector_marMosaic(void);
static int raw_detector_marMosaic(const char *);
static int command_detector_marMosaic(int command, ...);


#endif /* detector_marMosaicP_h */
