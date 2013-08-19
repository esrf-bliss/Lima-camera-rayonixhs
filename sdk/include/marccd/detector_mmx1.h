#ifndef detector_mmx1_h
#define detector_mmx1_h

#include "detector.h"

#define DETECTOR_MMX1_NFAST		2048
#define DETECTOR_MMX1_NSLOW		2048
#define DETECTOR_MMX1_IMAGESIZE 	(DETECTOR_MMX1_NFAST * DETECTOR_MMX1_NFAST)
#define DETECTOR_MMX1_NFASTDETECTORS 	2
#define DETECTOR_MMX1_NSLOWDETECTORS 	2
#define DETECTOR_MMX1_NDETECTORS 	(DETECTOR_MMX1_NSLOWDETECTORS*DETECTOR_MMX1_NFASTDETECTORS)
#define DETECTOR_MMX1_READSIZE		8192

#define DETECTOR_MMX1_RESET	0
#define DETECTOR_MMX1_REQ_INT	1
#define DETECTOR_MMX1_REQ_READ	2
#define DETECTOR_MMX1_REQ_BIN	3
#define DETECTOR_MMX1_REQ_AOI	4

#define DETECTOR_MMX1_NULL_ARGUMENT 0


/* A Function for each type of detector */
extern detector_functions *get_detector_mmx1(void);


#endif /* detector_mmx1_h */
