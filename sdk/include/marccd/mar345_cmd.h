/***********************************************************************
 * 
 * mar345: marcmd.h
 *
 * Copyright by:	Dr. Claudio Klein
 * 			X-ray Research GmbH, Hamburg
 *
 * Version: 	1.0 
 * Date:	16/01/1997
 *
 ***********************************************************************/
#define	MDC_COM_IDLE  	   0
#define	MDC_COM_STARTUP	   1
#define	MDC_COM_INIT	   2
#define	MDC_COM_ERASE	   3
#define MDC_COM_STOP	   4
#define MDC_COM_ABORT	   5
#define MDC_COM_DISTANCE   6
#define	MDC_COM_PHI	   7
#define	MDC_COM_DSET	   8
#define	MDC_COM_PSET	   9
#define	MDC_COM_SHUT	  10
#define	MDC_COM_SCAN  	  11
#define	MDC_COM_COLL	  12
#define	MDC_COM_ABORTPHI  13
#define	MDC_COM_ABORTDIST 14
#define	MDC_COM_OMOVE     15
#define	MDC_COM_OSET      16
#define	MDC_COM_LOCK      17
#define	MDC_COM_RESET	  18
#define	MDC_COM_RESTART   19
#define	MDC_COM_MODE   	  20
#define	MDC_COM_LISTEN 	  21
#define	MDC_COM_QUIT   	  22

/*
 *      Operation codes for the initialize command.
 *	Keeps track about initialization phase.
 */

#define INITOP_ABORT    0
#define INITOP_RESET    1
#define INITOP_SHUTTER  2
#define INITOP_LOADTAB  3
#define INITOP_DISTANCE 4
#define INITOP_SELFTEST 5
#define INITOP_PARAM    6

/*
 *      Operation codes for the data collection command.
 *	Keeps track about data collection phase.
 */

#define DCOP_IDLE       0
#define DCOP_EXPOSE     1
#define DCOP_SCAN       2
#define DCOP_ERASE      3
#define DCOP_DISTANCE   4
#define DCOP_PHI        5
#define DCOP_WAIT       6
#define DCOP_MODE	7

/*
 *      Operation codes for the recovery procedure
 */

#define RECOVER_SHUTTER			1
#define RECOVER_LOCK   			2
#define RECOVER_EXPO  			3
#define RECOVER_EXPO_RESET		4
#define RECOVER_EXPO_LOCK		5
#define RECOVER_EXPO_ERASE		6
#define RECOVER_EXPO_ERASE_LOCK		7
#define RECOVER_EXPO_EXPOSE		8
#define RECOVER_EXPO_MOVE_PHI_BACK  	9
#define RECOVER_EXPO_MOVE_PHI_FORWARD 	10
#define RECOVER_SHUTTER_OPEN		11

/*
 *      Operation codes for the shutter command.
 *	Keeps track about shutter status.
 */

#define SHUTTER_IS_CLOSED       1
#define SHUTTER_IS_OPEN         0

/*
 *      Operation codes for the scanner activity.
 */

#define MAR_CONTROL_IDLE        0
#define MAR_CONTROL_ACTIVE      1

/*
 *      The following parameters are used as
 *      descriptors for functions.
 */

#define MAR_START_DC            1
#define MAR_CHECK_PHI           2
#define MAR_CHECK_DIST          3
#define MAR_MOVE_PHI            4
#define MAR_MOVE_DIST           5
#define MAR_READ_STATUS         6
#define MAR_SCAN_START          7
#define MAR_SCAN_READ           8
#define MAR_SCAN_XFORM          9
#define MAR_RECOVER             10
#define MAR_CHANGE_MODE		11
#define MAR_ERASE      		12
#define MAR_PROGRESS            98
#define MAR_TIMER               99

