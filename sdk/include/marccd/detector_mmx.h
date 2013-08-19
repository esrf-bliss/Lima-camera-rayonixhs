#ifndef detector_mmx_h
#define detector_mmx_h

#include "detector.h"

#define DETECTOR_MMX_NFAST	2048
#define DETECTOR_MMX_NSLOW	2048
#define DETECTOR_MMX_IMAGESIZE    (DETECTOR_MMX_NFAST * DETECTOR_MMX_NFAST)
#define DETECTOR_MMX_BUFFER_SIZE	2048

/* Commands defined on PC Detector Server  - see pccom.h */
#define  RQ_NOP   "0"
#define  RQ_INT   "1"
#define  RQ_READ  "2"
#define  RQ_BIN   "3"

#define  RQ_AOI   "4"
#define  RQ_TEST  "5"
#define  RESET    "6"
/* extension for network commands to PC env */
#define  RQ_KILL  "7"
#define  RQ_STAT  "8"


/* Commands application->detector */
#define DETECTOR_MMX_COMMAND_KEY	    "mmxcom"
#define DETECTOR_MMX_NO_ARGUMENT            0
#define DETECTOR_MMX_START_INTEGRATION      RQ_INT
#define DETECTOR_MMX_START_READOUT_BINNED   RQ_BIN
#define DETECTOR_MMX_START_READOUT_AOI      RQ_AOI
#define DETECTOR_MMX_START_READOUT_NORMAL   RQ_READ
#define DETECTOR_MMX_ABORT_RESET            RESET
#define DETECTOR_MMX_NULL_COMMUNICATION     RQ_NOP
#define DETECTOR_MMX_KILL_CONNECTION        RQ_KILL
#define DETECTOR_MMX_QUERY_STATUS           RQ_STAT

/* Commands detector->application*/
#define DETECTOR_MMX_OVERFLOW_DETECTED      101
#define DETECTOR_MMX_READOUT_STARTED        102
#define DETECTOR_MMX_INTEGRATION_STARTED    103
#define DETECTOR_MMX_CLEAR_STARTED          104

#define DETCOM_RESPOGOOD		"ack"
#define DETCOM_RESPOBAD			"huh"
#define DETCOM_REPLYGOOD		"ok!"
#define DETCOM_REPLYBAD 		"nfg"


/* A Function for each type of detector */
extern detector_functions *get_detector_mmx(void);


#endif /* detector_mmx_h */
