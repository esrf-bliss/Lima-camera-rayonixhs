/***********************************************************************
 *
 * mar345: mar_command.h
 *
 * Copyright by:        Dr. Claudio Klein
 *                      X-ray Research GmbH, Hamburg
 *
 * Version:     1.0
 * Date:        28/01/1997
 *
 ***********************************************************************/

/*
 *	Definitions for the mar controller hardware commands.
 */
#define	CMD_NULL     		0
#define	CMD_MOVE_DIST		1
#define	CMD_MOVE_PHI 		2
#define	CMD_MOVE_OMEGA 		3
#define	CMD_MOVE_CHI   		4
#define	CMD_MOVE_THETA		5
#define CMD_ABORT               6
#define CMD_COLLECT             7
#define CMD_SHUTTER             8
#define	CMD_CHANGE_MODE		9
#define	CMD_SCAN		10
#define	CMD_ERASE		11
#define CMD_RESET		12
#define	CMD_SET      		13
#define	CMD_TEST 		14
#define	CMD_LOADFILE 		15
#define	CMD_LISTEN		16
#define	CMD_QUIT  		17
#define	CMD_ION_CHAMBER		18
#define CMD_QUERY_STATUS	19	
#define MAX_CMD			20	

#define	CMD_MODE_MOVE_REL	0
#define	CMD_MODE_MOVE_ABS	1
#define	CMD_MODE_MIN     	2
#define	CMD_MODE_MAX     	3
#define	CMD_MODE_SET     	4

#define	CMD_MODE_CLOSE		0
#define	CMD_MODE_OPEN 		1

#define	CMD_MODE_DISABLE	0
#define	CMD_MODE_ENABLE 	1

#define	CMD_MODE_DOSE		0
#define	CMD_MODE_TIME		1
