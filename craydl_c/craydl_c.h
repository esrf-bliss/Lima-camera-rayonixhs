#pragma once

#if !defined(CRAYDL_C_H)

#if !defined(__cplusplus)
#include <stdbool.h>
#endif

extern "C" {

typedef void* Craydl_RxReturnStatus_t;
typedef void* Craydl_RxDetector_t;
typedef void const* Craydl_RxFrame_t;
typedef void* Craydl_CallbackConnection_t;
typedef void* Craydl_DetectorFormat_t;

struct Craydl_FrameCallback_t
{
    void (* SequenceStarted)(void *user_data);
    void (* SequenceEnded)(void *user_data);
    void (* ExposureStarted)(void *user_data, int frame_number);
    void (* ExposureEnded)(void *user_data, int frame_number);
    void (* ReadoutStarted)(void *user_data, int frame_number);
    void (* ReadoutEnded)(void *user_data, int frame_number);
    void (* BackgroundFrameReady)(void *user_data, const Craydl_RxFrame_t frame_p);
    void (* RawFrameReady)(void *user_data, int frame_number, const Craydl_RxFrame_t frame_p);
    void (* FrameReady)(void *user_data, int frame_number, const Craydl_RxFrame_t frame_p);
    void (* FrameAborted)(void *user_data, int frame_number);
    void (* FrameCompleted)(void *user_data, int frame_number);
    void (* FrameError)(void *user_data, int frame_number, const Craydl_RxFrame_t frame_p, int error_code, const char* error_string);

    void *user_data;
};

// Readout Mode - affects gain, noise, speed and bit-depth
enum Craydl_ReadoutMode_t {ReadoutModeUnknown, ReadoutModeStandard, ReadoutModeHighGain, ReadoutModeLowNoise, ReadoutModeHDR, ReadoutModeTurbo, ReadoutModeHDR16};

// Triggering mode
enum Craydl_FrameTriggerType_t {FrameTriggerTypeUnknown, FrameTriggerTypeNone, FrameTriggerTypeFrame, FrameTriggerTypeBulb};

// Gating type
enum Craydl_SequenceGate_t {SequenceGateModeUnknown, SequenceGateModeNone, SequenceGateModeStart, SequenceGateModeGate};

// Trigger Signal Type
enum Craydl_DigitalIOSignalType_t {DigitalIOSignalTypeUnknown, DigitalIOSignalTypeNone,  DigitalIOSignalTypeExtended, DigitalIOSignalTypeOpto,  DigitalIOSignalTypeOptoInverted,  DigitalIOSignalTypeCMOS, DigitalIOSignalTypeCMOSPullDown,  DigitalIOSignalTypeCMOSPullUp,  DigitalIOSignalTypeCMOSPullDownInverted,  DigitalIOSignalTypeCMOSPullUpInverted,  DigitalIOSignalTypeSoftware}; 

enum Craydl_DigitalIOSignalID_t {DigitalIOSignalIDUnknown, DigitalIOSignalIDNone,  DigitalIOSignalIDExtended, DigitalIOSignalIDShutter, DigitalIOSignalIDIntegrate, DigitalIOSignalIDFrame, DigitalIOSignalIDLine, DigitalIOSignalIDShutterOpening, DigitalIOSignalIDShutterClosing, DigitalIOSignalIDShutterActive, DigitalIOSignalIDTrigger1RiseWait, DigitalIOSignalIDTrigger1RiseACK, DigitalIOSignalIDTrigger1FallWait, DigitalIOSignalIDTrigger1FallACK, DigitalIOSignalIDTrigger2RiseWait, DigitalIOSignalIDTrigger2RiseACK, DigitalIOSignalIDInputFrame, DigitalIOSignalIDInputGate};

// Status flags
enum Craydl_StatusFlag_t {StatusFlagUnknown, StatusFlagNone, StatusFlagVacuumControllerAlive, StatusFlagVacuumControllerAlarm, StatusFlagLinePressureSensorAlive, StatusFlagChamberPressureSensorAlive,
   StatusFlagVacuumPressureAlarm, StatusFlagVacuumControllerCommunicating, StatusFlagVacuumPumpAlive,  StatusFlagVacuumPumpRunning, StatusFlagVacuumPumpIgnored, StatusFlagVacuumPumpAlarm, StatusFlagVacuumValveAlive,
   StatusFlagVacuumValveEnabled, StatusFlagVacuumValveOpen, StatusFlagVacuumAllIgnored, StatusFlagVacuumValveAlarm, StatusFlagCoolersEnabled, StatusFlagCoolersOKToRun, StatusFlagCoolersRunning,
   StatusFlagDetectorIntegrating, StatusFlagMasterAlarm, StatusFlagPowerDistributionAlarm, StatusFlagPowerSupplyAlarm, StatusFlagVacuumSystemAlarm, StatusFlagVoltagesAlarm, StatusFlagOSMasterAlarm,
   StatusFlagOSMultipleFrames, StatusFlagOSTimestampEnabled, StatusFlagOSClearing, StatusFlagOSSequenceBusy, StatusFlagOSShutterOpening, StatusFlagOSShutterOpen, StatusFlagOSShutterClosing, StatusFlagOSGateArmed,
   StatusFlagOSGate, StatusFlagOSTriggerRiseArmed, StatusFlagOSTriggerRise, StatusFlagOSTriggerFallArmed, StatusFlagOSTriggerFall, StatusFlagOSTrigger, StatusFlagOSIntegrating, StatusFlagOSExitingInversion,
   StatusFlagOSReadout, StatusFlagOSTransfer, StatusFlagOSActive
};


//RxDetector
Craydl_RxDetector_t  Craydl_RxDetector_Ctor(const char* config_path);
void Craydl_RxDetector_Dctor(Craydl_RxDetector_t det);

bool Craydl_RxDetector_Open(Craydl_RxDetector_t det);
bool Craydl_RxDetector_GetDetectorID(Craydl_RxDetector_t det, char** name, char** serial_number);
bool Craydl_RxDetector_GetDetectorFirmwareID(Craydl_RxDetector_t det, char** name, char** version);
bool Craydl_RxDetector_GetDetectorFormat(Craydl_RxDetector_t det, Craydl_DetectorFormat_t df);

bool Craydl_RxDetector_SetupAcquisitionSequence(Craydl_RxDetector_t det, int n_frames, int start_frame_number);
bool Craydl_RxDetector_SetFrameTriggerMode(Craydl_RxDetector_t det, Craydl_FrameTriggerType_t mode);
bool Craydl_RxDetector_SetSequenceGate(Craydl_RxDetector_t det, Craydl_SequenceGate_t gate);
bool Craydl_RxDetector_SetSequenceGateSignalType(Craydl_RxDetector_t det, Craydl_DigitalIOSignalType_t type);
bool Craydl_RxDetector_SetFrameTriggerSignalType(Craydl_RxDetector_t det, Craydl_DigitalIOSignalType_t type);

bool Craydl_RxDetector_Bulb(Craydl_RxDetector_t det);
bool Craydl_RxDetector_ReleaseBulb(Craydl_RxDetector_t det);
bool Craydl_RxDetector_PulseBulb(Craydl_RxDetector_t det, double time);
bool Craydl_RxDetector_StartAcquisition(Craydl_RxDetector_t det);
bool Craydl_RxDetector_EndAcquisition(Craydl_RxDetector_t det, bool abort);
bool Craydl_RxDetector_Close(Craydl_RxDetector_t det);

bool Craydl_RxDetector_SetExposureTime(Craydl_RxDetector_t det, double expo_time);
double Craydl_RxDetector_GetExposureTime(Craydl_RxDetector_t det);

bool Craydl_RxDetector_SetIntervalTime(Craydl_RxDetector_t det, double expo_time);
double Craydl_RxDetector_GetIntervalTime(Craydl_RxDetector_t det);

bool Craydl_RxDetector_SetBinning(Craydl_RxDetector_t det, int fast_binning, int slow_binning);
bool Craydl_RxDetector_GetBinning(Craydl_RxDetector_t det, int& fast_binning, int& slow_binning);
bool Craydl_RxDetector_CheckBinning(Craydl_RxDetector_t det, int fast_binning, int slow_binning);

bool Craydl_RxDetector_SetShutterOpenDelay(Craydl_RxDetector_t det, double delay);
double Craydl_RxDetector_GetShutterOpenDelay(Craydl_RxDetector_t det);
bool Craydl_RxDetector_SetShutterCloseDelay(Craydl_RxDetector_t det, double delay);
double Craydl_RxDetector_GetShutterCloseDelay(Craydl_RxDetector_t det);

bool Craydl_RxDetector_CommandShutter(Craydl_RxDetector_t det, bool open);
bool Craydl_RxDetector_OpenShutter(Craydl_RxDetector_t det);
bool Craydl_RxDetector_CloseShutter(Craydl_RxDetector_t det);
bool Craydl_RxDetector_Shutter(Craydl_RxDetector_t det);

bool Craydl_RxDetector_EnableElectronicShutter(Craydl_RxDetector_t det, bool enable);
bool Craydl_RxDetector_ElectronicShutterEnabled(Craydl_RxDetector_t det);

bool Craydl_RxDetector_SetSensorTemperatureSetpoint(Craydl_RxDetector_t det, double temperature);
double Craydl_RxDetector_SensorTemperatureSetpoint(Craydl_RxDetector_t det);
double Craydl_RxDetector_SensorTemperatureAve(Craydl_RxDetector_t det);

bool Craydl_RxDetector_CommandCoolers(Craydl_RxDetector_t det, bool enable);
bool Craydl_RxDetector_CommandVacuumValve(Craydl_RxDetector_t det, bool enable);

bool Craydl_RxDetector_SupportedStatusFlagValue(Craydl_RxDetector_t det, Craydl_StatusFlag_t key);

int Craydl_RxDetector_GetFrameSize(Craydl_RxDetector_t det, int& fast_pixels, int& slow_pixels, int& pixel_depth);
bool Craydl_RxDetector_GetPixelSize(Craydl_RxDetector_t det, double& fast_pixels, double& slow_pixels);

Craydl_DigitalIOSignalType_t Craydl_RxDetector_GetDigitalOutputSignalType(Craydl_RxDetector_t det, int line);
bool Craydl_RxDetector_SetDigitalOutputSignalType(Craydl_RxDetector_t det, int line, Craydl_DigitalIOSignalType_t type);

Craydl_DigitalIOSignalID_t Craydl_RxDetector_GetDigitalOutputSignalID(Craydl_RxDetector_t det, int line);
bool Craydl_RxDetector_SetDigitalOutputSignalID(Craydl_RxDetector_t det, int line, Craydl_DigitalIOSignalID_t type);

bool Craydl_RxDetector_NewBackgroundNeeded(Craydl_RxDetector_t det);
bool Craydl_RxDetector_AcquireNewBackground(Craydl_RxDetector_t det, bool block, int n_backgrounds);

bool Craydl_RxDetector_SetReadoutMode(Craydl_RxDetector_t det, Craydl_ReadoutMode_t mode);
Craydl_ReadoutMode_t Craydl_RxDetector_GetReadoutMode(Craydl_RxDetector_t det);

Craydl_CallbackConnection_t Craydl_RxDetector_RegisterFrameCallback(Craydl_RxDetector_t det, struct Craydl_FrameCallback_t cbk);

//rxFrame
int Craydl_RxFrame_InternalFrameID(const Craydl_RxFrame_t frame_p);
int Craydl_RxFrame_getNFast(const Craydl_RxFrame_t frame_p);
int Craydl_RxFrame_getNSlow(const Craydl_RxFrame_t frame_p);
void * Craydl_RxFrame_getBufferAddress(const Craydl_RxFrame_t frame_p);

//DetectorFormat
Craydl_DetectorFormat_t Craydl_DetectorFormat_Ctor();
void Craydl_DetectorFormat_Dctor();
int Cray_DetectorFormat_n_pixels_fast(Craydl_DetectorFormat_t df);
int Cray_DetectorFormat_n_pixels_slow(Craydl_DetectorFormat_t df);

}

#endif //!defined(CRAYDL_C_H)
