#ifndef detector_marMosaic_h
#define detector_marMosaic_h

#include "detector.h"
#include "ccd_chips.h"

/* This will depend on how many readouts there are and/or how many are in use */
#define DETECTOR_MAR0_NFASTDETECTORS 	1
#define DETECTOR_MAR0_NSLOWDETECTORS 	1
#define DETECTOR_MAR0_NDETECTORS 	(DETECTOR_MAR0_NSLOWDETECTORS*DETECTOR_MAR0_NFASTDETECTORS)

#define DETECTOR_MAR0_READSIZE		8192
#define DETECTOR_MAR0_DMA_BUFFER_SIZE	8192


/* A Function for each type of detector */
//extern detector_functions *get_detector_marMosaic(void);
extern detector_functions *get_detector_marMosaic(void);
void get_driver_version_marMosaic(char *driver_version);


#endif /* detector_marMosaic_h */
