#include <string.h>

#include "craydl/craydl.h"
#include "craydl_c.h"

using namespace craydl;


//RxDetector

Craydl_RxDetector_t Craydl_RxDetector_Ctor(const char* config_path)
{
    return reinterpret_cast<void*>(RxDetector::create(config_path));
}

void Craydl_RxDetector_Dctor(Craydl_RxDetector_t det)
{
    delete reinterpret_cast<RxDetector *>(det);
}

bool Craydl_RxDetector_Open(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->Open().IsError();
}

bool Craydl_RxDetector_GetDetectorID(Craydl_RxDetector_t det, char** name, char** serial_number)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);

    std::string tmp_name, tmp_serial_number;
    bool res = self->GetDetectorID(tmp_name, tmp_serial_number).IsError();

    *name = strdup(tmp_name.c_str());
    *serial_number = strdup(tmp_serial_number.c_str());

    return res;
}

bool Craydl_RxDetector_GetDetectorFormat(Craydl_RxDetector_t det, Craydl_DetectorFormat_t df)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);

    std::string tmp_name, tmp_serial_number;
    return self->GetDetectorFormat(*reinterpret_cast<DetectorFormat *>(df)).IsError();
}

bool Craydl_RxDetector_GetDetectorFirmwareID(Craydl_RxDetector_t det, char** name, char** version)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);

    std::string tmp_name, tmp_version;
    bool res = self->GetDetectorFirmwareID(tmp_name, tmp_version).IsError();

    *name = strdup(tmp_name.c_str());
    *version = strdup(tmp_version.c_str());

    return res;
}

bool Craydl_RxDetector_SetupAcquisitionSequence(Craydl_RxDetector_t det, int n_frames, int start_frame_number)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetupAcquisitionSequence(n_frames, start_frame_number).IsError();
}

bool Craydl_RxDetector_SetFrameTriggerMode(Craydl_RxDetector_t det, Craydl_FrameTriggerType_t mode)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetFrameTriggerMode(FrameTriggerType((FrameTriggerType_t)mode)).IsError();
}

bool Craydl_RxDetector_SetSequenceGate(Craydl_RxDetector_t det, Craydl_SequenceGate_t gate)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetSequenceGate(SequenceGateMode((SequenceGate_t)gate)).IsError();
}

bool Craydl_RxDetector_SetSequenceGateSignalType(Craydl_RxDetector_t det, Craydl_DigitalIOSignalType_t type)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetSequenceGateSignalType(DigitalIOSignalType((DigitalIOSignalType_t) type)).IsError();
}

bool Craydl_RxDetector_SetFrameTriggerSignalType(Craydl_RxDetector_t det, Craydl_DigitalIOSignalType_t type)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetFrameTriggerSignalType(DigitalIOSignalType((DigitalIOSignalType_t) type)).IsError();
}

bool Craydl_RxDetector_Bulb(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->Bulb();
}

bool Craydl_RxDetector_ReleaseBulb(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->ReleaseBulb().IsError();
}

bool Craydl_RxDetector_PulseBulb(Craydl_RxDetector_t det, double time)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->PulseBulb(time).IsError();
}

bool Craydl_RxDetector_StartAcquisition(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->StartAcquisition(craydl::FrameAcquisitionTypeLight).IsError();
}

bool Craydl_RxDetector_EndAcquisition(Craydl_RxDetector_t det, bool abort)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->EndAcquisition(abort).IsError();
}

bool Craydl_RxDetector_Close(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->Close().IsError();
}

bool Craydl_RxDetector_SetExposureTime(Craydl_RxDetector_t det, double expo_time)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetExposureTime(expo_time).IsError();
}

double Craydl_RxDetector_GetExposureTime(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->ExposureTime();
}

bool Craydl_RxDetector_SetIntervalTime(Craydl_RxDetector_t det, double expo_time)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetIntervalTime(expo_time).IsError();
}

double Craydl_RxDetector_GetIntervalTime(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->IntervalTime();
}

bool Craydl_RxDetector_SetBinning(Craydl_RxDetector_t det, int fast_binning, int slow_binning)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetBinning(fast_binning, slow_binning).IsError();
}

bool Craydl_RxDetector_GetBinning(Craydl_RxDetector_t det, int& fast_binning, int& slow_binning)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->GetBinning(fast_binning, slow_binning).IsError();
}

bool Craydl_RxDetector_CheckBinning(Craydl_RxDetector_t det, int fast_binning, int slow_binning)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->CheckBinning(fast_binning, slow_binning);
}

bool Craydl_RxDetector_SetShutterOpenDelay(Craydl_RxDetector_t det, double delay)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetShutterOpenDelay(delay).IsError();
}

double Craydl_RxDetector_GetShutterOpenDelay(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->ShutterOpenDelay();
}

bool Craydl_RxDetector_SetShutterCloseDelay(Craydl_RxDetector_t det, double delay)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetShutterCloseDelay(delay).IsError();
}

double Craydl_RxDetector_GetShutterCloseDelay(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->ShutterCloseDelay();
}

bool Craydl_RxDetector_CommandShutter(Craydl_RxDetector_t det, bool open)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->CommandShutter(open).IsError();
}

bool Craydl_RxDetector_OpenShutter(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->OpenShutter().IsError();
}

bool Craydl_RxDetector_CloseShutter(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->CloseShutter().IsError();
}

bool Craydl_RxDetector_Shutter(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->Shutter();
}

bool Craydl_RxDetector_EnableElectronicShutter(Craydl_RxDetector_t det, bool enable)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->EnableElectronicShutter(enable).IsError();
}

bool Craydl_RxDetector_ElectronicShutterEnabled(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->ElectronicShutterEnabled();
}

bool Craydl_RxDetector_SetSensorTemperatureSetpoint(Craydl_RxDetector_t det, double temperature)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetSensorTemperatureSetpoint(temperature).IsError();
}

double Craydl_RxDetector_SensorTemperatureSetpoint(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SensorTemperatureSetpoint();
}

double Craydl_RxDetector_SensorTemperatureAve(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SensorTemperatureAve();
}

bool Craydl_RxDetector_CommandCoolers(Craydl_RxDetector_t det, bool enable)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->CommandCoolers(enable).IsError();
}

bool Craydl_RxDetector_CommandVacuumValve(Craydl_RxDetector_t det, bool enable)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->CommandVacuumValve(enable).IsError();
}

bool Craydl_RxDetector_SupportedStatusFlagValue(Craydl_RxDetector_t det, Craydl_StatusFlag_t key)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SupportedStatusFlagValue((craydl::StatusFlag_t) key);
}

int Craydl_RxDetector_GetFrameSize(Craydl_RxDetector_t det, int& fast_pixels, int& slow_pixels, int& pixel_depth)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->GetFrameSize(fast_pixels, slow_pixels, pixel_depth);
}

bool Craydl_RxDetector_GetPixelSize(Craydl_RxDetector_t det, double& fast_pixels, double& slow_pixels)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->GetPixelSize(fast_pixels, slow_pixels).IsError();
}

Craydl_DigitalIOSignalType_t Craydl_RxDetector_GetDigitalOutputSignalType(Craydl_RxDetector_t det, int line)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return (Craydl_DigitalIOSignalType_t) self->GetDigitalOutputSignalType(line).key();
}

bool Craydl_RxDetector_SetDigitalOutputSignalType(Craydl_RxDetector_t det, int line, Craydl_DigitalIOSignalType_t type)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetDigitalOutputSignalType(line, craydl::DigitalIOSignalType((DigitalIOSignalType_t) type)).IsError();
}

Craydl_DigitalIOSignalID_t Craydl_RxDetector_GetDigitalOutputSignalID(Craydl_RxDetector_t det, int line)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return (Craydl_DigitalIOSignalID_t) self->GetDigitalOutputSignalID(line).key();
}

bool Craydl_RxDetector_SetDigitalOutputSignalID(Craydl_RxDetector_t det, int line, Craydl_DigitalIOSignalID_t type)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetDigitalOutputSignalID(line, craydl::DigitalIOSignalID((DigitalIOSignalID_t) type)).IsError();
}

bool Craydl_RxDetector_NewBackgroundNeeded(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->NewBackgroundNeeded();
}

bool Craydl_RxDetector_AcquireNewBackground(Craydl_RxDetector_t det, bool block, int n_backgrounds)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->AcquireNewBackground(block, n_backgrounds).IsError();
}

bool Craydl_RxDetector_SetReadoutMode(Craydl_RxDetector_t det, Craydl_ReadoutMode_t mode)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return self->SetReadoutMode(craydl::ReadoutMode((ReadoutMode_t) mode)).IsError();
}

Craydl_ReadoutMode_t Craydl_RxDetector_GetReadoutMode(Craydl_RxDetector_t det)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);
    return (Craydl_ReadoutMode_t) self->GetReadoutMode().key();
}

class FrameStatusCbkStub : public virtual craydl::VirtualFrameCallback
{
    public:
        FrameStatusCbkStub(struct Craydl_FrameCallback_t cbk) : m_cbk(cbk) {}

        void SequenceStarted() { m_cbk.SequenceStarted(m_cbk.user_data); }
        void SequenceEnded() { m_cbk.SequenceStarted(m_cbk.user_data); }	
	void ExposureStarted(int frame_number) { m_cbk.ExposureStarted(m_cbk.user_data, frame_number); }
	void ExposureEnded(int frame_number) { m_cbk.ExposureEnded(m_cbk.user_data, frame_number); }
	void ReadoutStarted(int frame_number) { m_cbk.ReadoutStarted(m_cbk.user_data, frame_number); }
	void ReadoutEnded(int frame_number) { m_cbk.ReadoutEnded(m_cbk.user_data, frame_number); }

        void RawFrameReady(int frame_number, const craydl::RxFrame *rx_frame) {
            m_cbk.RawFrameReady(m_cbk.user_data, frame_number, static_cast<const Craydl_RxFrame_t>(rx_frame));
        }

        void BackgroundFrameReady(const craydl::RxFrame *rx_frame) {
            m_cbk.BackgroundFrameReady(m_cbk.user_data, reinterpret_cast<const Craydl_RxFrame_t>(rx_frame));
        }

        void FrameReady(int frame_number, const craydl::RxFrame *rx_frame) {
            m_cbk.FrameReady(m_cbk.user_data, frame_number, reinterpret_cast<const Craydl_RxFrame_t>(rx_frame));
        }

        void FrameAborted(int frame_number) { m_cbk.FrameAborted(m_cbk.user_data, frame_number); }
	void FrameCompleted(int frame_number) { m_cbk.FrameCompleted(m_cbk.user_data, frame_number); }

        void FrameError(int frame_number, const craydl::RxFrame* rx_frame, int error_code, const std::string& error_string) {
            m_cbk.FrameError(m_cbk.user_data, frame_number, reinterpret_cast<const Craydl_RxFrame_t>(rx_frame), error_code, error_string.c_str());
        }

    private:
    	struct Craydl_FrameCallback_t m_cbk;
};


Craydl_CallbackConnection_t Craydl_RxDetector_RegisterFrameCallback(Craydl_RxDetector_t det, struct Craydl_FrameCallback_t cbk)
{
    RxDetector *self = reinterpret_cast<RxDetector *>(det);

    FrameStatusCbkStub* stub = new FrameStatusCbkStub(cbk);

    self->RegisterFrameCallback(stub);
}


//DetectorFormat
Craydl_DetectorFormat_t Craydl_DetectorFormat_Ctor()
{
    return reinterpret_cast<Craydl_DetectorFormat_t>(new DetectorFormat);
}

void Craydl_DetectorFormat_Dctor(Craydl_DetectorFormat_t df)
{
    delete reinterpret_cast<DetectorFormat *>(df);
}

int Cray_DetectorFormat_n_pixels_fast(Craydl_DetectorFormat_t df)
{
    DetectorFormat *self = reinterpret_cast<DetectorFormat *>(df);
    return self->n_pixels_fast();
}

int Cray_DetectorFormat_n_pixels_slow(Craydl_DetectorFormat_t df)
{
    DetectorFormat *self = reinterpret_cast<DetectorFormat *>(df);
    return self->n_pixels_slow();
}

// RxFrame

int Craydl_RxFrame_InternalFrameID(const Craydl_RxFrame_t frame_p)
{
    RxFrame const * self = reinterpret_cast<RxFrame const *>(frame_p);
    return self->InternalFrameID();
}

int Craydl_RxFrame_getNFast(const Craydl_RxFrame_t frame_p)
{
    RxFrame const * self = reinterpret_cast<RxFrame const *>(frame_p);
    return self->getNFast();
}

int Craydl_RxFrame_getNSlow(const Craydl_RxFrame_t frame_p)
{
    RxFrame const * self = reinterpret_cast<RxFrame const *>(frame_p);
    return self->getNSlow();
}


void * Craydl_RxFrame_getBufferAddress(const Craydl_RxFrame_t frame_p)
{
    RxFrame const * self = reinterpret_cast<RxFrame const *>(frame_p);
    return self->getBufferAddress();
}

