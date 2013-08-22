#ifndef goniostat_mardtbP_h
#define goniostat_mardtbP_h

#include "types.h"

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
#define CMD_SET_OPTION		20
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

#define CMD_MODE_STATUS_TYPE	1
#define    STATUS_TYPE_BINARY	0
#define    STATUS_TYPE_ASCII	1

#define CMD_MODE_OUTPUT_ENABLE	2
#define    OUTPUT_CONSOLE	0x1
#define    OUTPUT_SERIAL	0x2
#define    OUTPUT_SPY_SERIAL	0x4
#define    OUTPUT_SPY_NETWORK	0x8

/***********************************************************************
 ***********************************************************************/
#define 	DTB_NPARAMS	10


/***********************************************************************
 * From: 
 * dtb.h for BASECON
 *
 * Copyright by:        Dr. Claudio Klein
 *                      X-ray Research GmbH, Hamburg
 *
 * Version:     1.0
 * Date:        09/04/2001
 *
 ***********************************************************************/
/*
 * DTB commands
 */
#define DTB_QUERY       0		/* Don't really know what this should be! MB */
#define DTB_NULL        0		/* DTB: stepper commands 1-99 */

#define DTB_SHELL       100		/* DTB: other commands  100-xxx */
#define DTB_SHUTTER     101
#define DTB_ADC         102
#define DTB_SET         103
#define DTB_DIO         104
#define DTB_COLLECT	105
#define DTB_SCAN   	106
#define DTB_CSC         107

/* defined in esd docs as USERP_MAX */
#define DTB_MAX_USER_PARAMETER		254
#define DTB_USERP_SPARE			DTB_MAX_USER_PARAMETER

#define DTB_SYSP_OFFSET			DTB_MAX_USER_PARAMETER
#define DTB_SYSP(x)			(DTB_SYSP_OFFSET+(x))

#define DTB_STATP_OFFSET		512
#define DTB_STATP(x)			(DTB_STATP_OFFSET+(x))

/* MAX_STATIC_PARAMETER determined by testing 6/17/04 mb (APPL v4.05) */
#define DTB_MAX_STATIC_PARAMETER	195
/* MAX_SYSTEM_PARAMETER determined by testing 6/17/04 mb (APPL v4.05) */
#define DTB_MAX_SYSTEM_PARAMETER	100
#define DTB_SYSP_SPARE			DTB_MAX_SYSTEM_PARAMETER


/* DTB_STEPPER arguments */
#define DTB_ARG_ABORT		0
#define DTB_ARG_STOP		1
#define DTB_ARG_ABSOLUTE	2

#define DTB_ARG_DOSEMODE	1
#define DTB_ARG_TIMEMODE	2

#define DTB_ARG_VELOCITY	5
#define DTB_ARG_RELATIVE	6
#define DTB_ARG_INIT       	7

/* Remote Control parameters  (RC) */

#define DTB_PARAM_RC_BUTTON_MASK	19
#define DTB_PARAM_RC_BUTTON_BOOT_MASK	69
#define DTB_PARAM_RC_BUTTON_ALL_ENABLE	70

#define DTB_RC_BUTTON_MASK_CRYO		(1 << 0)
#define DTB_RC_BUTTON_MASK_BEAMSTOP	(1 << 1)
#define DTB_RC_BUTTON_MASK_THETA	(1 << 2)
#define DTB_RC_BUTTON_MASK_DISTANCE	(1 << 3)
#define DTB_RC_BUTTON_MASK_CHI		(1 << 4)
#define DTB_RC_BUTTON_MASK_UNUSED5	(1 << 5)
#define DTB_RC_BUTTON_MASK_UNUSED6	(1 << 6)
#define DTB_RC_BUTTON_MASK_UNUSED7	(1 << 7)
#define DTB_RC_BUTTON_MASK_X_MINUS	(1 << 8)
#define DTB_RC_BUTTON_MASK_Y_MINUS	(1 << 9)
#define DTB_RC_BUTTON_MASK_Z_MINUS	(1 << 10)
#define DTB_RC_BUTTON_MASK_X_PLUS	(1 << 11)
#define DTB_RC_BUTTON_MASK_Y_PLUS	(1 << 12)
#define DTB_RC_BUTTON_MASK_Z_PLUS	(1 << 13)
#define DTB_RC_BUTTON_MASK_PHI_X	(1 << 14)
#define DTB_RC_BUTTON_MASK_PHI_Y	(1 << 15)
#define DTB_RC_BUTTON_MASK_CAR_MINUS	(1 << 16)
#define DTB_RC_BUTTON_MASK_INIT_ALL	(1 << 17)
#define DTB_RC_BUTTON_MASK_INIT_CAR	(1 << 18)
#define DTB_RC_BUTTON_MASK_CAR_PLUS	(1 << 19)
#define DTB_RC_BUTTON_MASK_MAGNET	(1 << 20)
#define DTB_RC_BUTTON_MASK_UNLOAD	(1 << 21)
#define DTB_RC_BUTTON_MASK_GIVE_TAKE	(1 << 22)
#define DTB_RC_BUTTON_MASK_FOOTSWITCH	(1 << 23)
#define DTB_RC_BUTTON_MASK_ALL	        (0xffffffff)	
#define DTB_RC_BUTTON_MASK_AUTOMATIC	(DTB_RC_BUTTON_MASK_ALL & ~(DTB_RC_BUTTON_MASK_CRYO | DTB_RC_BUTTON_MASK_MAGNET))
#define DTB_RC_BUTTON_MASK_MANUAL 	(DTB_RC_BUTTON_MASK_ALL & ~(DTB_RC_BUTTON_MASK_CRYO))

#define DTB_CSC_MAX_SAMPLE		19

/* CSC Commands - Argument to DTB_CSC */
#define DTB_ARG_CSC_ABORT		0
#define DTB_ARG_CSC_INIT		1
#define DTB_ARG_CSC_LOAD		2
#define DTB_ARG_CSC_UNLOAD		3
#define DTB_ARG_CSC_CHANGE		4
#define DTB_ARG_CSC_GIVE		5
#define DTB_ARG_CSC_TAKE		6
#define DTB_ARG_CSC_READ_CODE		7
#define DTB_ARG_CSC_CARPOS		8
#define DTB_ARG_CSC_ANNEAL		9

#define DTB_ARG_CSC_LOAD_COMPLETE	0
#define DTB_ARG_CSC_LOAD_QUICK		1

#define DTB_ARG_CSC_PINLENGTH_BARCODE	-1
#define DTB_ARG_CSC_PINLENGTH_DEFAULT	-18
#define DTB_ARG_CSC_PINLENGTH_14	14
#define DTB_ARG_CSC_PINLENGTH_16	16
#define DTB_ARG_CSC_PINLENGTH_18	18
#define DTB_ARG_CSC_PINLENGTH_21	21
#define DTB_ARG_CSC_PINLENGTH_24	24

#define DTB_ARG_CSC_IGNORE_CAP_NO	0
#define DTB_ARG_CSC_IGNORE_CAP_YES	1

#define DTB_ARG_CSC_IGNORE_BCR_NONE	0
#define DTB_ARG_CSC_IGNORE_BCR_SOME	1
#define DTB_ARG_CSC_IGNORE_BCR_ALL	2

#define DTB_ARG_CSC_V35_CHECKCAP_IGNORE	0
#define DTB_ARG_CSC_V35_CHECKCAP_MONITOR	1

#define DTB_ARG_CSC_V35_SAMPLE_CODE_IGNORE		0
#define DTB_ARG_CSC_V35_SAMPLE_CODE_EXPECTED	1

#define DTB_ARG_CSC_READ_ONE		0
#define DTB_ARG_CSC_READ_FIRST		1
#define DTB_ARG_CSC_READ_NEXT		2
#define DTB_ARG_CSC_READ_LAST		3


/* DTB_STEPPER INITIALIZE arguments: */
#define DTB_ARG_MOVE_MIN	17
#define DTB_ARG_MOVE_MAX	18
#define DTB_ARG_HOME_POS_FALL	19
#define DTB_ARG_HOME_NEG_RISE	20
#define DTB_ARG_HOME_NEG_FALL	21
#define DTB_ARG_HOME_POS_RISE	22
#define DTB_ARG_HOME_CUR	35

/* ADC arguments */
#define DTB_ARG_ADC1		1
#define DTB_ARG_ADC2		2

/* Exposure arguments */
#define DTB_ARG_DOSE 	 	1
#define DTB_ARG_TIME 	 	2

/* Shutter arguments */
#define DTB_ARG_CLOSE		0
#define DTB_ARG_OPEN 	 	1

/* SET arguments */
#define DTB_ARG_READ 	 	0
#define DTB_ARG_WRITE        	1
#define DTB_ARG_SETDEF      	(-1)

/* Stepper status */
#define DTB_STEPPER_IST      	0
#define DTB_STEPPER_SOLL     	1
#define DTB_STEPPER_STATUS   	2

/* DTB_DIO_BITS : */
#define DTB_DIO_BIT_BEAM_OPEN	1
#define DTB_DIO_BIT_BEAM_CLOSE	2
#define DTB_DIO_BIT_BEAM_INREF	3
#define DTB_DIO_BIT_PHI_INREF	4
#define DTB_DIO_BIT_EXT_12V	5
#define DTB_DIO_BIT_LOC_12V	6
#define DTB_DIO_BIT_BEAM_ON	7
#define DTB_DIO_BIT_BEAM_EXTERN	8
#define DTB_DIO_BIT_IO_DATA7	9
#define DTB_DIO_BIT_IO_DATA6	10
#define DTB_DIO_BIT_IO_DATA5	11
#define DTB_DIO_BIT_IO_DATA4	12
#define DTB_DIO_BIT_IO_DATA3	13
#define DTB_DIO_BIT_IO_DATA2	14
#define DTB_DIO_BIT_IO_DATA1	15
#define DTB_DIO_BIT_IO_DATA0	16
#define DTB_DIO_BIT_AD2_300PA	17
#define DTB_DIO_BIT_AD1_300PA	18
#define DTB_DIO_BIT_RESERVE1	19
#define DTB_DIO_BIT_RESERVE2	20
#define DTB_DIO_BIT_RESERVE3	21
#define DTB_DIO_BIT_HV_ON	22
#define DTB_DIO_BIT_DOUT_OK	23
#define DTB_DIO_BIT_DOUT_ENABLE	24
#define DTB_DIO_BIT_OUT_DATA7	25
#define DTB_DIO_BIT_OUT_DATA6	26
#define DTB_DIO_BIT_OUT_DATA5	27
#define DTB_DIO_BIT_OUT_DATA4	28
#define DTB_DIO_BIT_OUT_DATA3	29
#define DTB_DIO_BIT_OUT_DATA2	30
#define DTB_DIO_BIT_OUT_DATA1	31
#define DTB_DIO_BIT_OUT_DATA0	32

#define DTB_PARAM_READ		0
#define DTB_PARAM_WRITE		1
#define DTB_PARAM_DEFAULT	-1

/* From ESD documentation for v3.2 */
/*
!------------------------------------------------------------------
!------- user para: userp() (1...USERP_MAX=254) (r/w with setparam)
!                                 no
*/
#define FLASH_WRITE_CYCLES         0
#define STEPLOC_POS_1              1
#define STEPLOC_POS_2              2
#define STEPLOC_POS_3              3
#define STEPLOC_POS_4              4
#define STEPLOC_POS_5              5
#define STEPLOC_POS_6              6
#define CYCLE_TIME_STATE           7
#define ADC_AVERAGE                8
#define ADC_NOTFREQ                9	// store notch freq value [value=1/2*1/T...]
                                        // NO Default
#define BEAM_REF_DELAY            10	// Ref.Sw. sign:edge detect; value:delay[ms]
#define PHI_REF_DELAY             11	// Ref.Sw. sign:edge detect; value:delay[ms]
#define DUAL_MOVE_DELAY           12	// wait between 1st and 2nd move [ms]
#define PDO_EVENT_TIMER           13	// cycle activate PDO  obj. 0x180x,5
#define PDO_EVENT_TIMER_SCAN      14	// SCAN: cycle act.[value+1ms]
				        // 13,14 >0:value+1 ms, 0:on pos. change;
					// default gear-> 1/4 step
					// (min_gear or 1/64 step (mask lower 2 bit))]
#define STEPPERSTART_TOUT         15	// Wait (timeout) for stepper_start
#define CAN_HEARTBEAT_TOUT        16	// Timeout Heartbeat der CAN-M.
#define CAN_PDO_RX_TOUT           17	// Timeout PDO_RX der CAN-M.
#define RC_UPDATE_TIME            18	// Update cycle time RemoteControl-LCD (ADC_n values)
#define RC_TAST_ENABLE            19	// RemoteControl TAST-Filter 0xXXXXXX00..0xXXXXXX1F;
					// high=enable
					// dec. 1:cryo;2:adjust;4:theta;8:distance;16:CHI  enable 
#define RC_CAN_MODULE_NO          20	// RemoteControl CAN-Module_No
#define BASEC_CAN_MODULE_NO1      21	// Basecon CAN-Module_No
#define RC_THETA_POS_1            22	// RemoteC. Pos
#define RC_THETA_POS_2            23	// RemoteC. Pos
#define RC_THETA_ACC              24	// RemoteC. acc
#define RC_THETA_VEL              25	// RemoteC. velocity
#define RC_THETA_CHAN             26	// RemoteC. channel
#define RC_DIST_POS_1             27	// RemoteC. Pos
#define RC_DIST_POS_2             28	// RemoteC. Pos
#define RC_DIST_ACC               29	// RemoteC. acc
#define RC_DIST_VEL               30	// RemoteC. velocity
#define RC_DIST_CHAN              31	// RemoteC. channel
#define RC_CHI_POS_1              32	// RemoteC. Pos
#define RC_CHI_POS_2              33	// RemoteC. Pos
#define RC_CHI_ACC                34	// RemoteC. acc
#define RC_CHI_VEL                35	// RemoteC. velocity
#define RC_CHI_CHAN               36	// RemoteC. channel
#define RC_CRYO_POS_1             37	// RemoteC. Pos
#define RC_CRYO_POS_2             38	// RemoteC. Pos
#define RC_CRYO_ACC               39	// RemoteC. acc
#define RC_CRYO_VEL               40	// RemoteC. velocity
#define RC_CRYO_CHAN              41	// RemoteC. channel
#define RC_CH1_GAIN               42	// RemoteC. Adjust Gain   Ch 1
#define RC_CH1_OFFSET             43	// RemoteC. Adjust Offset Ch 1
#define RC_CH1_TOLERANZ           44	// RemoteC. Adjust Error  Ch 1
#define RC_CH2_GAIN               45	// RemoteC. Adjust Gain   Ch 2
#define RC_CH2_OFFSET             46	// RemoteC. Adjust Offset Ch 2
#define RC_CH2_TOLERANZ           47	// RemoteC. Adjust Error  Ch 2

#define RC_BEAMSTOP_POS_1         51	// RemoteC. Pos
#define RC_BEAMSTOP_POS_2         52	// RemoteC. Pos
#define RC_BEAMSTOP_ACC           53	// RemoteC. acc
#define RC_BEAMSTOP_VEL           54	// RemoteC. velocity
#define RC_BEAMSTOP_CHAN          55	// RemoteC. channel

#define SHUTTER_OPEN_TOUT         57
#define SHUTTER_CLOSE_TOUT        58

#define SHUTTER_OPEN_DELAY        67	// unit: 250us
#define SHUTTER_CLOSE_DELAY       68	// unit: 250us

#define CONTROLLER_NO             95	// NO Default
#define SCANNER_NO                96	// NO Default

#define EXPOSURE_NO               98	// NO Default

#define ERR_CNT_INTERN           100	// task_intern (Cmd 0)... STEP_NO (Cmd 32)
					// 100...132
#define ERR_CNT_SHELL            200	// task_shell (Cmd 100)...task_max(TASKSTMAX)
					// 200...220
/*
#define ADC_NOTFREQ                9
#define BEAM_REF_DELAY            10
#define PHI_REF_DELAY             11
#define DUAL_MOVE_DELAY           12
#define PDO_EVENT_TIMER           13
#define PDO_EVENT_TIMER_SCAN      14
#define STEPPERSTART_TOUT         15
#define CAN_HEARTBEAT_TOUT        16
         
#define SHUTTER_OPEN_TOUT         57
#define SHUTTER_CLOSE_TOUT        58

#define SHUTTER_OPEN_DELAY        67
#define SHUTTER_CLOSE_DELAY       68

#define CONTROLLER_NO             95
#define SCANNER_NO                96

#define EXPOSURE_NO               98

#define ERR_CNT_INTERN           100
#define ERR_CNT_SHELL            200
  */



typedef struct _dtb_cmd { 
         CHAR8    id	[4];
         INT32    par	[DTB_NPARAMS];
         CHAR8    str	[128];
} DTB_CMD;

typedef struct _dtb_msg {
        CHAR8    id	[4];
        CHAR8    str	[80];
} DTB_MSG;


/*
 * SCANCON status block definition.
 */
typedef struct _stepper {		/* 2+2+4+4 = 12 bytes per stepper */
	UINT16 opmode;	
	UINT16 state;
	INT32	pos;
	INT32	speed;
} STEPPER;

typedef struct _csc {		/* 1+1+2 = 4 bytes per csc */
	UINT8 carousel_pos_loaded_from;	
	UINT8 pin_length;
	UINT16 status;
} CSC;

#define  CSC_HARDWARE_CONFIG0	 (1 << 0)
#define  CSC_HARDWARE_CONFIG1	 (1 << 1)
#define  CSC_HARDWARE_CONFIG2	 (1 << 2)
#define  CSC_HARDWARE_CONFIG3	 (1 << 3)

typedef struct _dtb_stb_msg {
	UINT8	task;
	UINT8	class;
	UINT16	number;
} DTB_STB_MSG;

#define DTB_STB_MAX_STEPPERS_LOCAL	6
#define DTB_STB_MAX_STEPPERS_CAN_ORIG	22
#define DTB_STB_MAX_STEPPERS_CAN_V35	22
#define DTB_STB_MAX_STEPPERS_CAN_V40X	22
#define DTB_STB_MAX_STEPPERS_CAN_V4X	20
/* MAX_STEPPERS_CAN must be the largest of the different version of MAX_STEPPERS_CAN_XXX - used to dimension arrays */
#define DTB_STB_MAX_STEPPERS_CAN		DTB_STB_MAX_STEPPERS_CAN_ORIG
#define DTB_STB_MAX_T1S			2
#define DTB_STB_MAX_ERRORS		10
#define DTB_STB_N_PARAM_VALUES		8

#define DTB_STB_MAX_ADCS		2

#define DTB_STB_MAX_TASKS_ORIG		52
#define DTB_STB_MAX_TASKS_V35		42
#define DTB_STB_MAX_TASKS_V40X		44 /* 0-32,100-110 */
#define DTB_STB_MAX_TASKS_V4X		44 /* There is a hole - 0-30, 2 unused, 100-110 */
/* MAX_TASKS must be the largest of the different version of MAX_TASKS_VXX - used to dimension arrays */
#define DTB_STB_MAX_TASKS		DTB_STB_MAX_TASKS_ORIG
#define DTB_STB_BARCODE_SIZE_V35	8
#define DTB_STB_BARCODE_SIZE_V4X	16
/* BARCODE_SIZE must be the largest of the different version of BARCODE_SIZE_VXX - used to dimension arrays */
#define DTB_STB_BARCODE_SIZE		DTB_STB_BARCODE_SIZE_V4X
#define DTB_STB_SPARE_WORDS_ORIG	5
#define DTB_STB_SPARE_WORDS_V4X		10

/* The carousel position from which the carousel may be unloaded and loaded */
#define DTB_CAROUSEL_LOAD_POSITION	4.0

typedef struct _dtb_stb_any {
	STEPPER 	stepper_local[DTB_STB_MAX_STEPPERS_LOCAL];	/*  6 x 12  =  72 (lw =   1- 18) */
        UINT32		reserved0[12];					/* 12 * 4   =  48 (lw =  19- 30) */
	STEPPER 	stepper_can[DTB_STB_MAX_STEPPERS_CAN];		/* 22 * 12  = 264 (lw =  31- 96) */
	UINT32   	dio;						/*  1 * 4   =   4 (lw =  97- 97) */
	UINT32   	t1[DTB_STB_MAX_T1S];				/*  2 * 4   =   8 (lw =  98- 99) */
        DTB_STB_MSG   	errors[DTB_STB_MAX_ERRORS];			/* 10 * 4   =  40 (lw = 100-109) */
	UINT16   	task[DTB_STB_MAX_TASKS];			/* 52 * 2   = 104 (lw = 110-135) */
	UINT32  	adc[DTB_STB_MAX_ADCS];				/*  2 * 4   =   8 (lw = 136-137) */
	UINT32		timestamp;					/*  1 * 4   =   4 (lw = 138-138) */
	UINT32		cpu_load;					/*  1 * 4   =   4 (lw = 139-139) */
        UINT32		reserved1[1];					/*  1 * 4   =   4 (lw = 140-140) */
} DTB_STB_ANY;

typedef struct _dtb_stb_v4x {
	STEPPER 	stepper_local[DTB_STB_MAX_STEPPERS_LOCAL];	/*  6 x 12  =  72 (lw =   1- 18) */
	INT32		param_value[DTB_STB_N_PARAM_VALUES];		/*  8 * 4   =  32 (lw =  19- 26) */
        UINT32		reserved0[3];					/*  3 * 4   =  12 (lw =  27- 29) */
	CSC		csc;						/*  1 * 4   =   4 (lw =  30- 30) */
	STEPPER 	stepper_can[DTB_STB_MAX_STEPPERS_CAN_V4X];	/* 20 * 12  = 240 (lw =  31- 90) */
	char	   	barcode_mounted[DTB_STB_BARCODE_SIZE_V4X];	/* 16 * 1   =   4 (lw =  91- 94) */
	UINT32   	gray_count;					/*  1 * 4   =   4 (lw =  95- 95) */
	UINT32   	reserved1;					/*  1 * 4   =   4 (lw =  96- 96) */
	UINT32   	dio;						/*  1 * 4   =   4 (lw =  97- 97) */
	UINT32   	t1[DTB_STB_MAX_T1S];				/*  2 * 4   =   8 (lw =  98- 99) */
        DTB_STB_MSG   	errors[DTB_STB_MAX_ERRORS];			/* 10 * 4   =  40 (lw = 100-109) */
	UINT16   	task[DTB_STB_MAX_TASKS_V4X];			/* 42 * 2   =  88 (lw = 110-130) */
	char	   	barcode_recent[DTB_STB_BARCODE_SIZE_V4X];	/* 16 * 1   =   4 (lw = 132-135) */
	UINT32  	adc[DTB_STB_MAX_ADCS];				/*  2 * 4   =   8 (lw = 136-137) */
	UINT32		timestamp;					/*  1 * 4   =   4 (lw = 138-138) */
	UINT32		cpu_load;					/*  1 * 4   =   4 (lw = 139-139) */
	char	   	barcode_status[2];				/*  2 * 1   =  0.5(lw = 140-   )! */
	UINT16		barcode_angle;					/*  1 * 2   =  0.5(lw =    -140)! */
} DTB_STB_V4X;

typedef struct _dtb_stb_v40x {
	STEPPER 	stepper_local[DTB_STB_MAX_STEPPERS_LOCAL];	/*  6 x 12  =  72 (lw =   1- 18) */
	INT32		param_value[DTB_STB_N_PARAM_VALUES];		/*  8 * 4   =  32 (lw =  19- 26) */
        UINT32		reserved0[3];					/*  3 * 4   =  12 (lw =  27- 29) */
	CSC		csc;						/*  1 * 4   =   4 (lw =  30- 30) */
	STEPPER 	stepper_can[DTB_STB_MAX_STEPPERS_CAN_V40X];		/* 22 * 12  = 264 (lw =  31- 96) */
	UINT32   	dio;						/*  1 * 4   =   4 (lw =  97- 97) */
	UINT32   	t1[DTB_STB_MAX_T1S];				/*  2 * 4   =   8 (lw =  98- 99) */
        DTB_STB_MSG   	errors[DTB_STB_MAX_ERRORS];			/* 10 * 4   =  40 (lw = 100-109) */
	UINT16   	task[DTB_STB_MAX_TASKS_V40X];			/* 44 * 2   =  88 (lw = 110-131) */
	char	   	barcode[DTB_STB_BARCODE_SIZE_V4X];		/* 16 * 1   =   4 (lw = 132-135) */
	UINT32  	adc[DTB_STB_MAX_ADCS];				/*  2 * 4   =   8 (lw = 136-137) */
	UINT32		timestamp;					/*  1 * 4   =   4 (lw = 138-138) */
	UINT32		cpu_load;					/*  1 * 4   =   4 (lw = 139-139) */
	char	   	barcode_status[2];				/*  2 * 1   =  0.5(lw = 140-   )! */
	UINT16		barcode_angle;					/*  1 * 2   =  0.5(lw =    -140)! */
} DTB_STB_V40X;

typedef struct _dtb_stb_v35 {
	STEPPER 	stepper_local[DTB_STB_MAX_STEPPERS_LOCAL];	/*  */
	UINT32		reserved0[12];
	STEPPER 	stepper_can[DTB_STB_MAX_STEPPERS_CAN_V35];	/*   */
	UINT32   	dio;				/* 385-388 Digital IO                   */
	UINT32   	t1[DTB_STB_MAX_T1S];		/* 389-396                              */
        DTB_STB_MSG   	errors[DTB_STB_MAX_ERRORS];	/* 396-336: Error message buffer        */
	UINT16   	task[DTB_STB_MAX_TASKS_V35];	/* 336-   : 42*16-bit task bits  ?	*/
	char	   	barcode[DTB_STB_BARCODE_SIZE_V35];	/*        : 2 32 bits for barcode       */
	UINT16	   	barcode_status;			/*        : 1 16 bit word for reader status */
	UINT16   	spare[DTB_STB_SPARE_WORDS_ORIG];	/*        : Leftovers                   */
	UINT32  	adc[DTB_STB_MAX_ADCS];
	UINT32		timestamp;
	UINT32		cpu_load;
	UINT32		barcode_info;
} DTB_STB_V35;

typedef struct _dtb_stb_orig {
	STEPPER 	stepper_local[DTB_STB_MAX_STEPPERS_LOCAL];	/*  */
	UINT32		reserved0[12];
	STEPPER 	stepper_can[DTB_STB_MAX_STEPPERS_CAN_ORIG];	/*   */
	UINT32   	dio;				/* 385-388 Digital IO                   */
	UINT32   	t1[DTB_STB_MAX_T1S];		/* 389-396                              */
        DTB_STB_MSG   	errors[DTB_STB_MAX_ERRORS];	/* 396-336: Error message buffer        */
	UINT16   	task[DTB_STB_MAX_TASKS_ORIG];	/* 336-   : 42*16-bit task bits  ?	*/
	UINT32  	adc[DTB_STB_MAX_ADCS];
	UINT32		timestamp;
	UINT32		cpu_load;
	UINT32		reserved1;
} DTB_STB_ORIG;

typedef union _dtb_stb {
   DTB_STB_ANY		dtb_any;
   DTB_STB_ORIG		dtb_orig;
   DTB_STB_V35		dtb_v35;
   DTB_STB_V40X		dtb_v40x;
   DTB_STB_V4X		dtb_v4x;
} DTB_STB;

typedef struct _dtb_dat {	/* Data structure */
	INT32		pos1;
	INT32		adc1;
	INT32		pos2;
	INT32		adc2;
} DTB_DAT;

#define DTB_DATA_SIZE	2460

typedef struct _can_status  {		/* Statusword of CAN stepper */
	CHAR8 		warning;
	CHAR8		switch1;
	CHAR8		quickstop;
	CHAR8		voltage;
	CHAR8		fault;
	CHAR8		operation;
	CHAR8		switch2;
	CHAR8		ready;
	CHAR8		maxendswitch;
	CHAR8		minendswitch;
	CHAR8		homerro;
	CHAR8		homeattarget;
	CHAR8		limit_active;
	CHAR8		target;
	CHAR8		remote;
	CHAR8		refswitch;
} CAN_STATUS;

typedef struct _dtb_dio {
	CHAR8	shutter_open;
	CHAR8	shutter_close;
	CHAR8	shutter_timeout;
	CHAR8	phi_reference;
	CHAR8	extern_12v_enable;
	CHAR8	local_12v_enable;
	CHAR8	shutter_on;
	CHAR8	shutter_extern;
	CHAR8	io_data7;
	CHAR8	lcd_24v_enable;
	CHAR8	fan_enable;
	CHAR8	trigger_lcd;
	CHAR8	shutter_extern_closed;
	CHAR8	adc2;
	CHAR8	adc1;
	CHAR8	hv_on;
	CHAR8	data_ok;
	CHAR8	data_enable;
	CHAR8	xtal_light;
	CHAR8	back_light;
	CHAR8	back_enabled;
} STB_DIO;

extern DTB_CMD          dtb_cmd;
extern DTB_MSG          dtb_msg;
extern DTB_STB          dtb_stb;
extern STB_DIO		dio;


/* A local function for each function to be performed on or by a goniostat */

/* Semi-private methods */
static GoniostatType goniostat_type_P(void);
static int find_goniostat_P(GoniostatType type, char *device, int port, int number);
static int init_goniostat_P(char * config_dir, char * log_dir, char * device, int port);
static int init_data_goniostat_P(GoniostatValues *goniostat_values);
static int get_data_goniostat_P(GoniostatValues *cg);
static int set_data_goniostat_P(GoniostatValues *cg);
static int get_option_goniostat_P(int option, void *argument);
static int set_option_goniostat_P(int option, void *argument);
static int command_goniostat_P(int option, void *argument);
static char *print_goniostat_P(void);
static void load_goniostat_P(void);
static int query_goniostat_P(int);
static void set_positions_P(int all);
static int query_positions_P(void);
static void load_speeds_P(void);
static void query_speeds_P(void);
static int query_movings_P(void);
static int query_limit_statuses_P(void);
static void load_oscillations_P(void);
static void query_oscillations_P(void);
static void load_ok_flags_P(void);
static int query_ok_flags_P(void);
static int move_positions_conditional_P(void);
static int move_positions_P(void);
static int start_oscillations_P(void);
static int stop_oscillations_P(void);
static int restore_positions_P(void);
static int open_goniostat_shutter_P(void);
static int close_goniostat_shutter_P(void);
static int query_goniostat_shutter_P(void);
static void wait_goniostat_P(void);
static int abort_goniostat_P(void);
static int close_goniostat_P(void);
static int validate_positions_P(GoniostatValues *gvp, char *buffer, int buffer_size);
static int validate_positions_conditional_P(GoniostatValues *gvp, char *buffer, int buffer_size);
static char *printf_goniostat_P(char * format, ...);



/* Truly private methods */

static void set_position(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static double query_position(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static void load_speed(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static double query_speed(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int query_moving(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int query_limit_status(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static void load_oscillation(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static double query_oscillation(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int load_ok_flag(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int query_ok_flag(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int move_position(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int start_oscillation(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int init_gon_cont (
#if NeedFunctionPrototypes
void
#endif
);

static int close_gon_cont (
#if NeedFunctionPrototypes
void
#endif
);


#if defined(_SVID_SOURCE) && !defined(_BSD_COMPAT) && !defined(_BSD_SIGNALS)
#if defined(_SGI_SOURCE)
static void gon_cont_timeout();
#else
static int gon_cont_timeout(
#if NeedFunctionPrototypes
void
#endif
);
#endif
#elif defined(_BSD_SOURCE) || defined(_BSD_COMPAT) || defined(_BSD_SIGNALS)
static void gon_cont_timeout(
#if NeedFunctionPrototypes
void
#endif
);
#else
static void gon_cont_timeout();
#endif

#endif /* goniostat_mardtbP_h */
