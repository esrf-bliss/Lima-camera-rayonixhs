#ifndef detector_none_h
#define detector_none_h

#include "detector.h"

#define DETECTOR_NONE_NFAST	0
#define DETECTOR_NONE_NSLOW	0
#define DETECTOR_NONE_IMAGESIZE    (DETECTOR_NONE_NFAST * DETECTOR_NONE_NFAST)
#define DETECTOR_NONE_BUFFER_SIZE	2048


/* A Function for each type of detector */
extern detector_functions *get_detector_none(void);
static void get_driver_version_none(char *driver_version);

#endif /* detector_none_h */
