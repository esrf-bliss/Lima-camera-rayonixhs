#ifndef detector_nwu0_h
#define detector_nwu0_h

#include "detector.h"

#define DETECTOR_NWU0_NFAST	512
#define DETECTOR_NWU0_NSLOW	512
#define DETECTOR_NWU0_IMAGESIZE    (DETECTOR_NWU0_NFAST * DETECTOR_NWU0_NFAST)
#define DETECTOR_NWU0_BUFFER_SIZE	2048

/* Commands defined on PC Detector Server  - see pccom.h */
#define  RQ_NOP   "0"		/* No operation */
#define  RQ_INT   "1"		/* Integrate */
#define  RQ_READ  "2"		/* Read data from server */
#define  RQ_BIN   "3"		/* Read binned data from server */

#define  RQ_AOI   "4"		/* Read area of interest data from server */
#define  RQ_TEST  "5"		/* Read Test patter */
#define  RESET    "6"		
/* extension for network commands to PC env */
#define  RQ_KILL  "7"		/* Kill server program */
#define  RQ_STAT  "8"		/* Query status of detector */


/* Commands application->detector */
#define DETECTOR_NWU0_COMMAND_KEY	    "mmxcom"
#define DETECTOR_NWU0_NO_ARGUMENT            0
#define DETECTOR_NWU0_START_INTEGRATION      RQ_INT
#define DETECTOR_NWU0_START_READOUT_BINNED   RQ_BIN
#define DETECTOR_NWU0_START_READOUT_AOI      RQ_AOI
#define DETECTOR_NWU0_START_READOUT_NORMAL   RQ_READ
#define DETECTOR_NWU0_ABORT_RESET            RESET
#define DETECTOR_NWU0_NULL_COMMUNICATION     RQ_NOP
#define DETECTOR_NWU0_KILL_CONNECTION        RQ_KILL
#define DETECTOR_NWU0_QUERY_STATUS           RQ_STAT
#define DETECTOR_NWU0_COLLECT_CORRECTION     9

/* Commands detector->application*/
#define DETECTOR_NWU0_OVERFLOW_DETECTED      101
#define DETECTOR_NWU0_READOUT_STARTED        102
#define DETECTOR_NWU0_INTEGRATION_STARTED    103
#define DETECTOR_NWU0_CLEAR_STARTED          104

#define DETCOM_RESPOGOOD		"ack"
#define DETCOM_RESPOBAD			"huh"
#define DETCOM_REPLYGOOD		"ok!"
#define DETCOM_REPLYBAD 		"nfg"


/* A Function for each type of detector */
extern detector_functions *get_detector_nwu0(void);


#endif /* detector_nwu0_h */
