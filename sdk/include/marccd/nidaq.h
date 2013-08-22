/*
 * Copyright (C) National Instruments 1993.
 * Function prototype file for Microsoft C programs using
 * NI-DAQ DOS 4.4
 * nidaq.h
 */

/**** START OF BLUM MODIFICATIONS *********/

/* DOS test added 1/94 - M.B. */
#ifndef DOS
#define far
#endif

/* BIT definitions added 1/94 - M.B. */
#define  BIT0	0x0001 
#define  BIT1	0x0002 
#define  BIT2	0x0004 
#define  BIT3	0x0008
#define  BIT4	0x0010 
#define  BIT5	0x0020
#define  BIT6	0x0040
#define  BIT7	0x0080
#define  BIT8	0x0100
#define  BIT9	0x0200
#define  BIT10	0x0400
#define  BIT11	0x0800
#define  BIT12	0x1000
#define  BIT13	0x2000
#define  BIT14	0x4000
#define  BIT15	0x8000

/* new functions added 1/94 - M.B. */
extern int far set_nidaq_board(int board, int address);
extern int far REG_Level_Get_Addr (int board, int registerIndex, void **registerAddr);

/****** END OF BLUM MODIFICATIONS *********/

extern int far A2000_Calibrate (int slot, int saveNewValues, int calMethod, int channel, double extRefVoltage);
extern int far A2000_Config (int slot, int sampClkSrc, int sampClkDrv, int dither);
extern int far A2150_Calibrate (int slot, int ref0, int ref1);
extern int far AI_Check (int slot, int far *status, int far *value);
extern int far AI_Clear (int slot);
extern int far AI_Configure (int slot, int chan, int inputMode, int inputRange, int polarity, int driveAIS);
extern int far AI_Mux_Config (int slot, int numMuxBrds);
extern int far AI_Read (int slot, int chan, int gain, int far *value);
extern int far AI_Setup (int slot, int chan, int gain);
extern int far AI_VRead (int slot, int chan, int gain, double far *volts);
extern int far AI_VScale (int slot, int chan, int gain, double gainAdjust, double offset, int reading, double far *voltage);
extern int far Align_DMA_Buffer (int slot, int resource, int far buffer[], unsigned int cnt, unsigned long bufSize, unsigned int far *alignIndex);
extern int far AO_Calibrate (int slot, int operation, int EEPROMloc);
extern int far AO_Configure (int slot, int chan, int outputPolarity, int intOrExtRef, double refVoltage, int updateMode);
extern int far AO_Update (int slot);
extern int far AO_VScale (int slot, int chan, double voltage, int far *value);
extern int far AO_VWrite (int slot, int chan, double voltage);
extern int far AO_Write (int slot, int chan, int value);
extern int far Config_Alarm_Deadband (int slot, int mode, char *chanStr, double trigLvl, double deadbandWidth, int handle, int alarmOnMsg, int alarmOffMsg, unsigned long callbackAddr);
extern int far Config_ATrig_Event_Message (int slot, int mode, char *chanStr, double trigLvl, double winSize, int trigSlope, long skipCnt, unsigned long preTrigScans, unsigned long postTrigScans, int handle, int msg, unsigned long callBackAddr);
extern int far Config_DAQ_Event_Message (int slot, int mode, char *chanStr, int DAQEvent, unsigned long val0, unsigned long val1, long skipCnt, unsigned long preTrigScans, unsigned long postTrigScans, int handle, int msg, unsigned long callbackAddr);
extern int far CTR_Config (int slot, int ctr, int edgeMode, int gateMode, int outType, int outPolarity);
extern int far CTR_EvCount (int slot, int ctr, int timebase, int cont);
extern int far CTR_EvRead (int slot, int ctr, int far *overflow, unsigned int far *counts);
extern int far CTR_FOUT_Config (int slot, int FOUT, int mode, int timebase, int division);
extern int far CTR_Period (int slot, int ctr, int timebase);
extern int far CTR_Pulse (int slot, int ctr, int timebase, unsigned int delay, unsigned int pulseWidth);
extern int far CTR_Rate (double freq, double duty, int far *timebase, unsigned int far *period1, unsigned int far *period2);
extern int far CTR_Reset (int slot, int ctr, int outState);
extern int far CTR_Restart (int slot, int ctr);
extern int far CTR_Simul_Op (int slot, int numCtrs, int far ctrList[], int mode);
extern int far CTR_Square (int slot, int ctr, int timebase, unsigned int period1, unsigned int period2);
extern int far CTR_State (int slot, int ctr, int far *outState);
extern int far CTR_Stop (int slot, int ctr);
extern int far DAQ_Check (int slot, int far *status, unsigned int far *retrieved);
extern int far DAQ_Clear (int slot);
extern int far DAQ_Config (int slot, int startTrig, int extConv);
extern int far DAQ_DB_Config (int slot, int dbMode);
extern int far DAQ_DB_HalfReady (int slot, int far *halfReady, int far *status);
extern int far DAQ_DB_StrTransfer (int slot, char far buffer[], unsigned int far *ptsTfr, int far *status);
extern int far DAQ_DB_Transfer (int slot, int far hbuffer[], unsigned int far *ptsTfr, int far *status);
extern int far DAQ_Monitor (int slot, int chan, int seq, unsigned int monitorCnt, int far monitorBuf[], unsigned int far *newestIndex, int far *status);
extern int far DAQ_Op (int slot, int chan, int gain, int far buffer[], unsigned int cnt, double sampleRate);
extern int far DAQ_Rate (double rate, int units, int far *timebase, unsigned int far *sampleInt);
extern int far DAQ_Start (int slot, int chan, int gain, int far buffer[], unsigned int cnt, int timebase, unsigned int sampInt);
extern int far DAQ_StopTrigger_Config (int slot, int preTrig, unsigned long preTrigCnt);
extern int far DAQ_to_Disk (int slot, int chan, int gain, char far fileName[], unsigned long cnt, double sampleRate, int concat);
extern int far DAQ_Trigger_Config (int slot, int preTrig, unsigned int preTrigCnt);
extern int far DAQ_VScale (int slot, int chan, int gain, double gainAdjust, double offset, int count, int far reading[], double far voltage[]);
extern int far DIG_Block_Check (int slot, int grp, unsigned int far *remaining);
extern int far DIG_Block_Clear (int slot, int grp);
extern int far DIG_Block_In (int slot, int grp, int far buffer[], unsigned int cnt);
extern int far DIG_Block_Out (int slot, int grp, int far buffer[], unsigned int cnt);
extern int far DIG_Block_PG_Config (int slot, int grp, int PGmode, int reqSource, int timebase, unsigned int interval, int externalGate);
extern int far DIG_DB_Config (int slot, int grp, int DBMode, int oldDataStop, int partialTransfer);
extern int far DIG_DB_HalfReady (int slot, int grp, int far *halfReady);
extern int far DIG_DB_StrTransfer (int slot, int grp, char far halfBuffer[], unsigned int ptsTfr);
extern int far DIG_DB_Transfer (int slot, int grp, int far halfBuffer[], unsigned int ptsTfr);
extern int far DIG_Grp_Config (int slot, int grp, int grpsize, int port, int dir);
extern int far DIG_Grp_Mode (int slot, int grp, int sigType, int edge, int reqpol, int ackpol, int settleTime);
extern int far DIG_Grp_Status (int slot, int grp, int far *status);
extern int far DIG_In_Grp (int slot, int grp, int far *grp_pat);
extern int far DIG_In_Line (int slot, int port, int line, int far *status);
extern int far DIG_In_Port (int slot, int port, int far *pattern);
extern int far DIG_Line_Config (int slot, int port, int line, int dir);
extern int far DIG_Out_Grp (int slot, int grp, int grp_pat);
extern int far DIG_Out_Line (int slot, int port, int line, int status);
extern int far DIG_Out_Port (int slot, int port, int pattern);
extern int far DIG_Prt_Config (int slot, int port, int latch_mode, int dir);
extern int far DIG_Prt_Status (int slot, int port, int far *status);
extern int far DIG_SCAN_Setup (int slot, int grp, int numPorts, int far portList[], int dir);
extern int far DSP2200_Calibrate (int slot, int mode, int ADCref);
extern int far DSP2200_Config (int slot, int aitranslate, int aotranslate, int demux);
extern int far Get_DA_Brds_Info (int slot, int far *brdCode, int far *baseAddr, int far *irq1Lvl, int far *irq2Lvl, int far *irqTrigMode, int far *dma1Lvl, int far *dma2Lvl, int far *daqMode);
extern int far Get_DAQ_Event (unsigned long timeOut, int *handle, int *msg, int *wParam, long *lParam);
extern int far Get_NI_DAQ_Version (long far * version);
extern int far ICTR_Read (int slot, int counter, unsigned int far *count);
extern int far ICTR_Reset (int slot, int counter, int state);
extern int far ICTR_Setup (int slot, int counter, int mode, unsigned int cnt, int binBCD);
extern int far Init_DA_Brds (int slot, int far *brdCode);
extern int far Lab_ISCAN_Check (int slot, int far *status, unsigned int far *retrieved, int far finalScanOrder[]);
extern int far Lab_ISCAN_Op (int slot, int numChans, int gain, int far buffer[], unsigned int cnt, double sampleRate, double scanRate, int far finalScanOrder[]);
extern int far Lab_ISCAN_Start (int slot, int numChans, int gain, int far buffer[], unsigned int cnt, int timebase, unsigned int sampleInt, unsigned int scanInt);
extern int far Lab_ISCAN_to_Disk (int slot, int numChans, int gain, char far fileName[], unsigned long cnt, double sampleRate, double scanRate, int concat);
extern int far LPM16_Calibrate (int slot);
extern int far MAI_Arm (int slot, int onOff);
extern int far MAI_Clear (int slot);
extern int far MAI_Coupling (int slot, int numChans, int far coupling[]);
extern int far MAI_Read (int slot, int far reading[]);
extern int far MAI_Scale (int slot, unsigned long numScans, int far values[], double far volts[]);
extern int far MAI_Setup (int slot, int numChans, int far chanList[], int far gainList[], unsigned int muxInterval, int timebase, int muxMode);
extern int far Master_Slave_Config (int slot, int numSlaves, int far saveList[]);
extern int far MDAQ_Check (int slot, int fullCheck, int far *acqDone, unsigned long far *framesDone, unsigned long far *scansDone);
extern int far MDAQ_Clear (int slot);
extern int far MDAQ_Get (int slot, int scansOrFrames, int getOrTap, unsigned long numToGet, unsigned long startFrame, unsigned long startScan, long timeout, int far getBuffer[], unsigned long far *numGotten, unsigned long far *lastFrame, unsigned long far *lastScan, int far *acqDone);
extern int far MDAQ_ScanRate (int slot, unsigned int interval, int timebase);
extern int far MDAQ_Setup (int slot, unsigned long bufferSize, int scansOrFrames, unsigned long preTrigScans, unsigned long postTrigScans, int far acqBuffer[]);
extern int far MDAQ_Start (int slot, unsigned long numTriggers);
extern int far MDAQ_Stop (int slot);
extern int far MDAQ_StrGet (int slot, int scansOrFrames, int getOrTap, unsigned long numToGet, unsigned long startFrame, unsigned long startScan, long timeout, char far getBuffer[], unsigned long far *numGotten, unsigned long far *lastFrame, unsigned long far *lastScan, int far *acqDone);
extern int far MDAQ_Trig_Delay (int slot, unsigned int postTrigDelay, int timebase);
extern int far MDAQ_Trig_Select (int slot, int dTrigMode, int dEdge, int aTrigMode, int aSlope, int aLevel, int aTrigChan);
extern int far MIO_Calibrate (int slot, int calOP, int saveNewCal, int EEPROMloc, int CalRefChan, int DAC0Chan, int DAC1Chan, double calRefVolts, int refLoc);
extern int far MIO_Config (int slot, int dither, int useAMUX);
extern int far NI_DAQ_Mem_Alloc(int far *handle, int elementSize, long numElements, int memType, int memSource);
extern int far NI_DAQ_Mem_Attributes(int handle, int far *elementSize, long far *numElements, int far *lockCnt, int far *memType, int far *memSource);
extern int far NI_DAQ_Mem_Copy(int handle, void far *buffer, long startIndex, long numEl, int CopyToNIDAQ_Mem);
extern int far NI_DAQ_Mem_Free(int handle);
extern int far NI_DAQ_Mem_Lock(int handle, long far *address);
extern int far NI_DAQ_Mem_Unlock(int handle);
extern int far Peek_DAQ_Event (unsigned long timeOut, int *handle, int *msg, int *wParam, long *lParam);
extern int far REG_Level_Read (int slot, int registerIndex, unsigned long *registerValue);
extern int far REG_Level_Write (int slot, int registerIndex, unsigned long bitsAffected, unsigned long bitSettings, unsigned long *registerValue);
extern int far RTSI_Clear (int slot);
extern int far RTSI_Clock (int slot, int connect, int dir);
extern int far RTSI_Conn (int slot, int brdSignal, int busLine, int dir);
extern int far RTSI_DisConn (int slot, int brdSignal, int busLine);
extern int far SCAN_Demux (int far buffer[], unsigned int cnt, int numChans, int muxMode);
extern int far SCAN_Op (int slot, int numChans, int far chans[], int far gains[], int far buffer[], unsigned int cnt, double sampleRate, double scanRate);
extern int far SCAN_Setup (int slot, int num_chans, int far chans[], int far gains[]);
extern int far SCAN_Start (int slot, int far buffer[], unsigned int cnt, int tb1, unsigned int si1, int tb2, unsigned int si2);
extern int far SCAN_to_Disk (int slot, int numChans, int far chans[], int far gains[], char far fileName[], unsigned long cnt, double sampleRate, double scanRate, int concat);
extern int far SCXI_Calibrate_Setup (int chassisID, int module, int calOp);
extern int far SCXI_Change_Chan (int chassisID, int module, int chan);
extern int far SCXI_Get_Chassis_Info (int chassisID, int far *type, int far *address, int far *commMode, int far *commPath, int far *numSlots);
extern int far SCXI_Get_Module_Info (int chassisID, int slot, long far *type, int far *opMode, int far *DAQboard);
extern int far SCXI_Get_State (int chassisID, int module, int port, int channel, long *data);
extern int far SCXI_Get_Status (int chassisID, int module, int wait, long *data);
extern int far SCXI_Load_Config (int chassisID);
extern int far SCXI_MuxCtr_Setup (int slot, int enable, int scanDiv, unsigned int muxCtrVal);
extern int far SCXI_Reset (int chassisID, int moduleSlot);
extern int far SCXI_SCAN_Setup (int chassisID, int numModules, int far modules[], int far numChans[], int far startChans[], int DAQboard, int modeFlag);
extern int far SCXI_Set_Config (int chassisID, int type, int address, int commMode, int slotOrCOMM, int numSlots, long far moduleTypes[], int far opModes[], int far DAQboards[]);
extern int far SCXI_Set_Module_Gain (int chassisID, int module, int gain);
extern int far SCXI_Set_State (int chassisID, int module, int port, int channel, long data);
extern int far SCXI_Single_Chan_Setup (int chassisID, int module,int chan, int DAQboard);
extern int far SCXI_Track_Hold_Control (int chassisID, int module, int state, int DAQboard);
extern int far SCXI_Track_Hold_Setup (int chassisID, int module, int mode, int source, int send, int holdCnt, int DAQboard);
extern int far Set_DAQ_Mode (int slot, int mode);
extern int far Timeout_Config (int slot, long numTicks);
extern int far Trigger_Window_Config(int slot, int mode, unsigned int windowSize);
extern int far WFM_Chan_Control (int slot, int channel, int operation);
extern int far WFM_Check (int slot, int channel, int far *status, unsigned long far *pointsDone, unsigned long far *itersDone);
extern int far WFM_ClockRate (int slot, int group, int whichClock, int timebase, unsigned long updateInterval, int mode);
extern int far WFM_DB_Config (int slot, int numChans, int far chanVect[], int DBMode, int oldDataStop, int partialTransfer);
extern int far WFM_DB_HalfReady (int slot, int numChans, int far chanVect[], int far *halfReady);
extern int far WFM_DB_StrTransfer (int slot, int numChans, int far chanVect[], char far strBuffer[], unsigned long count);
extern int far WFM_DB_Transfer (int slot, int numChans, int far chanVect[], int far buffer[], unsigned long count);
extern int far WFM_from_Disk (int slot, int numChans, int far chanVect[], char far fileName[], unsigned long startPts, unsigned long endPts, unsigned long iterations, double rate);
extern int far WFM_Group_Control (int slot, int group, int operation);
extern int far WFM_Group_Setup (int slot, int numChans, int far chanVect[], int group);
extern int far WFM_Load (int slot, int numChans, int far chanVect[], int far buffer[], unsigned long count, unsigned long iterations, int mode);
extern int far WFM_Op (int slot, int numChans, int far chanVect[], int far buffer[], unsigned long count, unsigned long iterations, double rate);
extern int far WFM_Rate (double rate, int unit, int far *timebase, unsigned long far *updateInterval);
extern int far WFM_Scale (int slot, int chan, unsigned long count, double gain, double far voltArray[], int far binArray[]);


extern int far AI_Config (int slot, int singOrDiff, int range, int uniOrBi);
extern int far AI_Scale (int slot, int gain, int value, double far *voltage);
extern int far AO_Config (int slot, int chan, int outputPolarity, double refVoltage, int updateMode);
extern int far CTR_Clock (int slot, int mode, int timebase, int division);
extern int far CTR_Simul_Stop (int slot, int ctr1, int ctr2, int ctr5);
extern int far DAQ_Scale (int slot, int gain, unsigned int cnt, int far rawData[], double far scaledData[]);
extern int far Get_A2000_Info (int slot, int far *baseAddr, int far *intLvl, int far *intTrig, int far *dmaLvl, int far *daqMode);
extern int far Get_DIO24_Info (int slot, int far *baseAddr, int far *intLvl);
extern int far Get_DIO32F_Info (int slot, int far *baseAddr, int far *int1Lvl, int far *int2Lvl, int far *dma1Lvl, int far *dma2Lvl);
extern int far Get_LabBrd_Info (int slot, int far *baseAddr, int far *intLvl, int far *dmaLvl, int far *daqMode);
extern int far Get_MIO16_Info (int slot, int far *baseAddr, int far *subType, int far *intLvl, int far *dma1Lvl, int far *dmaLvl, int far *daqMode);
extern int far Lab_SCAN_Check (int slot, int far *status, unsigned int far *retrieved, int far finalScanOrder[]);
extern int far Lab_SCAN_Op (int slot, int numChans, int gain, int far buffer[], unsigned int cnt, double sampleRate, int far finalScanOrder[]);
extern int far Lab_SCAN_to_Disk (int slot, int numChans, int gain, char far fileName[], unsigned long cnt, double sampleRate, int concat);
extern int far Lab_SCAN_Start (int slot, int numChans, int gain, int far buffer[], unsigned int cnt, int timebase, unsigned int sampleInt);
extern int far MDAQ_Ext_Setup (int slot, unsigned long bufferSize, int scansOrFrames, unsigned long preTrigScans, unsigned long postTrigScans, unsigned long extMemAddr);
extern int far MIO16_F5_Calibrate (int slot, int calOP, int saveNewCal, int EEPROMloc, int CalRefChan, int DAC0Chan, int DAC1Chan, double calRefVolts, int refLoc);
extern int far MIO16_F5_Config (int slot, int dither);
extern int far WFM_UpdateRate (int slot, int group, int timebase,  unsigned long updateInterval, int mode);
extern int far WF_Check (int slot, int chan, int far *status, unsigned int far *itersDone, unsigned int far *nextPoint);
extern int far WF_Clear (int slot);
extern int far WF_DB_Config (int slot, int chan, int DBmode, int oldDataStop);
extern int far WF_DB_StrTransfer (int slot, int chan, char far buffer[], unsigned int cnt);
extern int far WF_DB_Transfer (int slot, int chan, int far buffer[], unsigned int cnt);
extern int far WF_from_Disk (int slot, int chan, char far fileName[], unsigned int iters, double rate, unsigned long startPt, unsigned long endPt);
extern int far WF_Load (int slot, int chan, int far buffer[], unsigned int cnt, unsigned int iterations);
extern int far WF_Op (int slot, int chan, int far buf0[], int far buf1[], unsigned int cnt0, unsigned int cnt1, unsigned int iters0, unsigned int iters1, double rate);
extern int far WF_Pause (int slot);
extern int far WF_Rate (double rate, int units, int far *timebase, unsigned int far *updateInt);
extern int far WF_Resume (int slot);
extern int far WF_Scale (int slot, int chan, unsigned int cnt, double gain, double far realArray[], int far intArray[]);
extern int far WF_Start (int slot, int timebase, unsigned int updateInt);


/**************************************************************************
*                                                                         *
*  Board codes returned by NI-DAQ's Init_DA_Brds and Get_DA_Brds_Info     *
*  functions.                                                             *
*                                                                         *
***************************************************************************/

#define  AT_MIO_16L_9            0
#define  AT_MIO_16L_15           1
#define  AT_MIO_16L_25           2
#define  AT_MIO_16H_9            4
#define  AT_MIO_16H_15           5
#define  AT_MIO_16H_25           6
#define  AT_DIO_24               7
#define  AT_DIO_32               8
#define  LAB_PC                  9
#define  EISA_A2000              10
#define  AT_MIO_16F_5            11
#define  PC_DIO_96               12
#define  PC_LPM_16               13
#define  PC_TIO_10               14
#define  AT_AO_6or10             15
#define  AT_A2150S               16
#define  DSP_2200_64k            17    /* 64k words */ 
#define  DSP_2200_nk             18    /* >=128k words */ 
#define  AT_MIO_16X              19
#define  AT_MIO_64F_5            20
#define  AT_MIO_16DL_9           21
#define  AT_MIO_16DL_25          22
#define  AT_MIO_16DH_9           23
#define  AT_MIO_16DH_25          24
#define  AT_AO_10                26
#define  AT_A2150C               27
#define  LAB_PC_PLUS             28
