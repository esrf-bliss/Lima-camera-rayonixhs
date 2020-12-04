//###########################################################################
//// This file is part of LImA, a Library for Image Acquisition
////
//// Copyright (C) : 2009-2014
//// European Synchrotron Radiation Facility
//// BP 220, Grenoble 38043
//// FRANCE
////
//// This is free software; you can redistribute it and/or modify
//// it under the terms of the GNU General Public License as published by
//// the Free Software Foundation; either version 3 of the License, or
//// (at your option) any later version.
////
//// This software is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU General Public License for more details.
////
//// You should have received a copy of the GNU General Public License
//// along with this program; if not, see <http://www.gnu.org/licenses/>.
////###########################################################################

#include "RayonixHsCamera.h"

using namespace lima;
using namespace lima::RayonixHs;


// Home made std::bind for C
#define RAYONIXHS_FRAMESTATUS_CALLBACK0(name) \
static void name(void *cbk) { \
   reinterpret_cast<FrameStatusCb *>(cbk)->name(); \
}

#define RAYONIXHS_FRAMESTATUS_CALLBACK1(name, t1) \
static void name(void *cbk, t1 p1) { \
   reinterpret_cast<FrameStatusCb *>(cbk)->name(p1); \
}

#define RAYONIXHS_FRAMESTATUS_CALLBACK2(name, t1, t2) \
static void name(void *cbk, t1 p1, t2 p2) { \
   reinterpret_cast<FrameStatusCb *>(cbk)->name(p1, p2); \
}

#define RAYONIXHS_FRAMESTATUS_CALLBACK3(name, t1, t2, t3) \
static void name(void *cbk, t1 p1, t2 p2, t3 p3) { \
   reinterpret_cast<FrameStatusCb *>(cbk)->name(p1, p2, p3); \
}

#define RAYONIXHS_FRAMESTATUS_CALLBACK4(name, t1, t2, t3, t4) \
static void name(void *cbk, t1 p1, t2 p2, t3 p3, t4 p4) { \
   reinterpret_cast<FrameStatusCb *>(cbk)->name(p1, p2, p3, p4); \
}

#define RAYONIXHS_FRAMESTATUS_CALLBACK5(name, t1, t2, t3, t4, t5) \
static void name(void *cbk, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5) { \
   reinterpret_cast<FrameStatusCb *>(cbk)->name(p1, p2, p3, p4, p5); \
}

RAYONIXHS_FRAMESTATUS_CALLBACK0(SequenceStarted)
RAYONIXHS_FRAMESTATUS_CALLBACK0(SequenceEnded)
RAYONIXHS_FRAMESTATUS_CALLBACK1(ExposureStarted, int)
RAYONIXHS_FRAMESTATUS_CALLBACK1(ExposureEnded, int)
RAYONIXHS_FRAMESTATUS_CALLBACK1(ReadoutStarted, int)
RAYONIXHS_FRAMESTATUS_CALLBACK1(ReadoutEnded, int)
RAYONIXHS_FRAMESTATUS_CALLBACK1(BackgroundFrameReady, const Craydl_RxFrame_t)
RAYONIXHS_FRAMESTATUS_CALLBACK2(RawFrameReady, int, const Craydl_RxFrame_t)
RAYONIXHS_FRAMESTATUS_CALLBACK2(FrameReady, int, const Craydl_RxFrame_t)
RAYONIXHS_FRAMESTATUS_CALLBACK1(FrameAborted, int)
RAYONIXHS_FRAMESTATUS_CALLBACK1(FrameCompleted, int)
RAYONIXHS_FRAMESTATUS_CALLBACK4(FrameError, int, const Craydl_RxFrame_t, int, const char*)


//---------------------------
// @brief  Ctor
//---------------------------
Camera::Camera(std::string config_path) :
    m_rx_detector(Craydl_RxDetector_Ctor(config_path.c_str())),
    m_status(DETECTOR_STATUS_IDLE),
    m_acquiring(false),
    m_cooler(true),
    m_vac_valve(false),
    m_image_type(Bpp16)
{
	DEB_CONSTRUCTOR();

	init();

        m_frame_status_cb = new FrameStatusCb(this, m_acquiring);

        struct Craydl_FrameCallback_t cbk;
        cbk.SequenceStarted = SequenceStarted;
        cbk.SequenceEnded = SequenceEnded;
        cbk.ExposureStarted = ExposureStarted;
        cbk.ExposureEnded = ExposureEnded;
        cbk.ReadoutStarted = ReadoutStarted;
        cbk.ReadoutEnded = ReadoutEnded;
        cbk.BackgroundFrameReady = BackgroundFrameReady;
        cbk.RawFrameReady = RawFrameReady;
        cbk.FrameReady = FrameReady;
        cbk.FrameAborted = FrameAborted;
        cbk.FrameCompleted = FrameCompleted;
        cbk.FrameError = FrameError;
        cbk.user_data = m_frame_status_cb;

	// create callback obj and register only once here
	// Do not trust comment /opt/rayonix/include/craydl/RxDetector.h:2974
	// EndAcquisition() does not unregister any callback, so it is permanently added.
	
	m_frame_cb_connection = Craydl_RxDetector_RegisterFrameCallback(m_rx_detector, cbk);
	//if (m_frame_cb_connection.connected())
	// this return false, don't know how to test if the callback is registered.
	//      THROW_HW_ERROR(Error) << "RegisterFrameCallback() failed";


	//m_frame_status_cb->registerCallbackAcqComplete(&lima::RayonixHs::Camera::acquisitionComplete);
	//m_frame_status_cb->registerCallbackAcqComplete(&acquisitionComplete);
}

//---------------------------
// @brief  Initialize method
//---------------------------
void Camera::init() {
	DEB_MEMBER_FUNCT();	

	setStatus(DETECTOR_STATUS_FAULT, true);
	//Open camera
	if (Craydl_RxDetector_Open(m_rx_detector)) {
		m_max_image_size = Size(0, 0);
		THROW_HW_ERROR(Error) << "Fatal error opening camera";
	}

	char *model, *serial, *version, *junk;
	if (Craydl_RxDetector_GetDetectorID(m_rx_detector, model, serial))
		THROW_HW_ERROR(Error) << "Cannot get camera ID";
	if (Craydl_RxDetector_GetDetectorFirmwareID(m_rx_detector, junk, version))
		THROW_HW_ERROR(Error) << "Cannot get camera firmware ID";

	DEB_ALWAYS() << "Found RayonixHs model " << model
		     << "  - serial   # " << serial
		     << "  - firmware # " << version;

	free(model);
        free(serial);
        free(version);
        free(junk);

	//Get unbinned frame size from camera
	Craydl_DetectorFormat_t detector_format = Craydl_DetectorFormat_Ctor();
	if (Craydl_RxDetector_GetDetectorFormat(m_rx_detector, detector_format)) {
		THROW_HW_ERROR(Error) << "Cannot get camera format";
	}

	int fast = Cray_DetectorFormat_n_pixels_fast(detector_format);
	int slow = Cray_DetectorFormat_n_pixels_slow(detector_format);

	m_max_image_size = Size(fast, slow);

	m_exp_time = 1.0;
	m_lat_time = 0.001;
	m_int_time = m_exp_time + m_lat_time;

	m_nb_frames = 1;
	// default frame mode is SINGLE, FAST_TRANFSER is not
	m_frame_mode = SINGLE;
	m_frame_trig_signal_type = OPTO;
	m_sequ_gate_signal_type = OPTO;

	setStatus(DETECTOR_STATUS_IDLE, true);
}

//---------------------------
// @brief  Dtor
//---------------------------
Camera::~Camera() {
	DEB_DESTRUCTOR();

	if (Craydl_RxDetector_EndAcquisition(m_rx_detector, true))
		DEB_ERROR() << "Cannot end acquisition";

	if (Craydl_RxDetector_Close(m_rx_detector))
		DEB_ERROR() << "Cannot close camera";

	Craydl_RxDetector_Dctor(m_rx_detector);
	delete m_frame_status_cb;
}

//---------------------------
// @brief  return the hw buffer
//---------------------------
HwBufferCtrlObj* Camera::getBufferCtrlObj() {
	DEB_MEMBER_FUNCT();
	return &m_buffer_ctrl_obj;
}

//---------------------------
// @brief  return the detector type
//---------------------------
void Camera::getDetectorType(std::string &type) {
	DEB_MEMBER_FUNCT();
	type = "RayonixHs";
}

//---------------------------
// @brief  return the current number of acquired (corrected) images
//---------------------------
int Camera::getNbAcquiredFrames() {
	DEB_MEMBER_FUNCT();
	return m_frame_status_cb->frameCountCorrected();
}

//---------------------------
// @brief  return the detector model
//---------------------------
void Camera::getDetectorModel(std::string &model) {
	DEB_MEMBER_FUNCT();
	char *model_buf, *junk_buf;
	if (Craydl_RxDetector_GetDetectorID(m_rx_detector, model_buf, junk_buf))
		DEB_ERROR() << "Cannot read the detector model";

        model = model_buf;
	free(model_buf);
	free(junk_buf);
}

//---------------------------
// @brief  return the image type
//---------------------------
void Camera::getImageType(ImageType &img_type) {
	DEB_MEMBER_FUNCT();
	img_type = m_image_type;
}

//---------------------------
// @brief set the image type
//---------------------------
void Camera::setImageType(ImageType img_type) {
	DEB_MEMBER_FUNCT();
        THROW_HW_ERROR(InvalidValue) << "Image type is not supported: "
                                     << DEB_VAR1(img_type);
}


//---------------------------
// @brief  check if the trigger mode is valid
// valid modes depend on the frame mode
//---------------------------
bool Camera::checkTrigMode(TrigMode mode) {
	DEB_MEMBER_FUNCT();
	bool valid_mode;

	switch (mode) {
	case IntTrig:
	case IntTrigMult:
	case ExtTrigSingle:
	case ExtTrigMult:
	case ExtGate:
	        valid_mode = true;
		break;
	case ExtTrigReadout:
	        // Only in FAST_TRANSER mode
	        valid_mode = (m_frame_mode == FAST_TRANSFER);
		break;
	default:
		valid_mode = false;
	}
	return valid_mode;
}

//---------------------------
// @brief  set the frame mode SINGLE or FAST_TRANSFER
//---------------------------
void Camera::setFrameMode(FrameMode mode) {
	DEB_MEMBER_FUNCT();

	// RayonixHs is switched to FAST_TRANSFER frame mode by setting exposure time to 0
	// then interval time sets the exposure duration, and latency is 1ms (transfer time)
	if (mode != m_frame_mode) {
		double exp_time;
		if (mode == SINGLE) exp_time = m_exp_time;
		else // FAST_TRANSFER
			exp_time = 0;

		if (Craydl_RxDetector_SetExposureTime(m_rx_detector, exp_time))
			THROW_HW_ERROR(Error) << "Failed  setting a new exposure time";


	}
	m_frame_mode = mode;
}

//---------------------------
// @brief  return the frame mode
//---------------------------
void Camera::getFrameMode(FrameMode &mode) {
	DEB_MEMBER_FUNCT();
	mode = m_frame_mode;
}

//---------------------------
// @brief  return the trigger mode
//---------------------------
void Camera::getTrigMode(TrigMode &mode) {
	DEB_MEMBER_FUNCT();
	mode = m_trig_mode;
}

//---------------------------
// @brief  set the trigger mode
//---------------------------
void Camera::setTrigMode(TrigMode mode) {
	DEB_MEMBER_FUNCT();
	m_trig_mode = mode;
}
//---------------------------
// @brief  return the pixel size in meter x and y
//---------------------------
void Camera::getPixelSize(double &x, double &y) {
	DEB_MEMBER_FUNCT();
	Craydl_RxDetector_GetPixelSize(m_rx_detector, x, y);
}

//---------------------------
// @brief return the maximum image size
//---------------------------
void Camera::getMaxImageSize(Size& max_image_size) {
	DEB_MEMBER_FUNCT();
	max_image_size = m_max_image_size;
}

//---------------------------
// @brief  set the number of frames for acquistion
//---------------------------
void Camera::setNbFrames(int nb_frames) {
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(nb_frames);
	if (nb_frames < 0)
		THROW_HW_ERROR(InvalidValue) << "Invalid nb of frames";

	m_nb_frames = nb_frames;
}

//---------------------------
// @brief  return the number of frames for acquisition
//---------------------------
void Camera::getNbFrames(int& nb_frames) {
	DEB_MEMBER_FUNCT();
	nb_frames = m_nb_frames;
}

//---------------------------
// @brief  set the new exposure time in second
//---------------------------
void Camera::setExpTime(double exp_time) {
	DEB_MEMBER_FUNCT();
	if (exp_time < 0)
		THROW_HW_ERROR(InvalidValue) << "Invalid exposure time";
	if (m_frame_mode == SINGLE) {
		if (Craydl_RxDetector_SetExposureTime(m_rx_detector, exp_time))
			THROW_HW_FATAL(Error) << "Failed setting exposure!";
		m_exp_time = exp_time;
	}
	else { // FAST_TRANSFER
		if (Craydl_RxDetector_SetIntervalTime(m_rx_detector, exp_time))
			THROW_HW_FATAL(Error) << "Failed setting interval time for exposure in FAST_TRANSFER mode";
		m_int_time = exp_time;
	}
}

//---------------------------
// @brief  return the exposure time in second
//---------------------------
void Camera::getExpTime(double& exp_time) {
	DEB_MEMBER_FUNCT();

	if (m_frame_mode == SINGLE) {
		m_exp_time = Craydl_RxDetector_GetExposureTime(m_rx_detector);
		exp_time = m_exp_time;
	}
	else { // FAST_TRANSFER
		m_int_time = Craydl_RxDetector_GetIntervalTime(m_rx_detector);
		exp_time = m_int_time;
	}
}

//---------------------------
// @brief  set the latency (interval) time in second
//---------------------------
void Camera::setLatTime(double lat_time) {
	DEB_MEMBER_FUNCT();

	if (lat_time < 0)
		THROW_HW_ERROR(InvalidValue) << "Invalid latency time";

	// Ok, RayonixHs manages an interval time not a latency:
	// in SINGLE frame mode latency = interval - exposure
	// in FAST_TRANSFER latency = 1ms and interval is the exposure (exposure must be 0 )
	if (m_frame_mode == SINGLE){
		if (Craydl_RxDetector_SetIntervalTime(m_rx_detector, lat_time+m_exp_time))
			THROW_HW_FATAL(Error) << "Cannot set latency time";

	}
	else {
		// FAST_TRANSFER: latency is fixed, 1ms of frame transfer
		DEB_WARNING() << "Cannot set latency in FAST_TRANSFER frame mode: fixed to 1ms!";
	}
	m_lat_time = lat_time;
}

//---------------------------
// @brief  return the latency (interval) time in second
//---------------------------
void Camera::getLatTime(double& lat_time) {
	DEB_MEMBER_FUNCT();

	if (m_frame_mode == SINGLE){
		lat_time = m_lat_time;
	}
	else { // FAST_TRANSFER: latency is fixed, 1ms of frame transfer
		lat_time = 1e-3;
	}
	//m_lat_time = m_rx_detector->IntervalTime();
	lat_time = m_lat_time;
}

//---------------------------
// @brief  set the binning factors
//---------------------------
void Camera::setBin(const Bin& bin) {
	DEB_MEMBER_FUNCT();

	if (Craydl_RxDetector_SetBinning(m_rx_detector, bin.getX(), bin.getY()))
		THROW_HW_ERROR(Error) << "Cannot set a new binning!";
}

//---------------------------
// @brief  return the binning factors
//---------------------------
void Camera::getBin(Bin& bin) {
	DEB_MEMBER_FUNCT();

	int binFast, binSlow;
	if (Craydl_RxDetector_GetBinning(m_rx_detector, binFast, binSlow)) {
		THROW_HW_ERROR(Error) << "Cannot read binning!";
		return;
	}
	bin = Bin(binFast, binSlow);
}

//---------------------------
// @brief  check if the binning factors are valid
// if invalid return the current binning factors
//---------------------------
void Camera::checkBin(Bin& bin) {
	DEB_MEMBER_FUNCT();

	if (!Craydl_RxDetector_CheckBinning(m_rx_detector, bin.getX(), bin.getY())) {
		DEB_TRACE() << "Invalid binning.  Setting bin to current detector binning.";
		getBin(bin);
	}
}

//---------------------------
// @brief  do nothing, not supported
//---------------------------
void Camera::setFrameDim(const FrameDim& frame_dim) {
	DEB_MEMBER_FUNCT();

	//Rayonix detector library handles this automatically
}

//---------------------------
// @brief  return the frame dimension (size x,y and pixel depth and sign)
//---------------------------
void Camera::getFrameDim(FrameDim& frame_dim) {
	DEB_MEMBER_FUNCT();

	int fast, slow, depth;
	Craydl_RxDetector_GetFrameSize(m_rx_detector, fast, slow, depth);
	frame_dim.setSize(Size(fast, slow));
	frame_dim.setImageType(Bpp16);
}

//---------------------------
// @brief  stop the running acq. and reinitialize the detector
//---------------------------
void Camera::reset() {
	DEB_MEMBER_FUNCT();

	stopAcq();
	init();
}

//---------------------------
// @brief  return detector acquisition status
// from IDLE to ACQUISITION or FAULT
//---------------------------
void Camera::getStatus(DetectorStatus &status) {
	DEB_MEMBER_FUNCT();

	status = m_status;
}

//---------------------------
// @brief  private: set the new acquisition status
//---------------------------
void Camera::setStatus(DetectorStatus status,bool force)
{
	DEB_MEMBER_FUNCT();

	if(force || m_status != DETECTOR_STATUS_FAULT)
		m_status = status;
}

//---------------------------
// @brief  prepare the new acquisition
//---------------------------
void Camera::prepareAcq() {
	DEB_MEMBER_FUNCT();

	// 0 means first frame id equal 0 (InternalFrameID)
	if (Craydl_RxDetector_SetupAcquisitionSequence(m_rx_detector, m_nb_frames, 0))
		THROW_HW_ERROR(Error) << "SetupAcquisitionSequence() failed!";

	Craydl_FrameTriggerType_t rx_frame_trig_type;
	Craydl_DigitalIOSignalType_t rx_trig_signal_type;
	Craydl_SequenceGate_t rx_sequence_gate;
	int trigger;

	switch (m_trig_mode) {
	case IntTrig:
		rx_frame_trig_type	 = FrameTriggerTypeNone;
		rx_sequence_gate	 = SequenceGateModeNone;
		rx_trig_signal_type 	 = DigitalIOSignalTypeNone;
		trigger = 0;
		break;
	case IntTrigMult:
		rx_frame_trig_type	 = FrameTriggerTypeFrame;
		rx_sequence_gate	 = SequenceGateModeNone;
		rx_trig_signal_type      = DigitalIOSignalTypeSoftware;
		trigger = 0;
		break;

	case ExtTrigSingle:
		rx_frame_trig_type	 = FrameTriggerTypeNone;
		rx_sequence_gate	 = SequenceGateModeStart;
		rx_trig_signal_type      = (Craydl_DigitalIOSignalType_t) m_sequ_gate_signal_type;
		trigger = 1; // the Gate input
		break;

	case ExtTrigMult:
		rx_frame_trig_type	 = FrameTriggerTypeFrame;
		rx_sequence_gate	 = SequenceGateModeNone;
		rx_trig_signal_type      = (Craydl_DigitalIOSignalType_t) m_frame_trig_signal_type;
		trigger = 0; // Frame input
		break;

	case ExtGate:
		rx_frame_trig_type	 = FrameTriggerTypeBulb;
		rx_sequence_gate	 = SequenceGateModeNone;
		rx_trig_signal_type      = (Craydl_DigitalIOSignalType_t) m_frame_trig_signal_type;
		trigger = 0; // Frame input
		break;

	case ExtTrigReadout:
	        // only in FAST_TRANSFER frame mode
	        rx_frame_trig_type	 = FrameTriggerTypeFrame;
		rx_sequence_gate	 = SequenceGateModeNone;
		rx_trig_signal_type      = (Craydl_DigitalIOSignalType_t) m_frame_trig_signal_type;
		trigger = 0; // Frame input
break;

	}
	// apply trigger mode (soft, trig, gate ...)
	Craydl_RxDetector_SetFrameTriggerMode(m_rx_detector, rx_frame_trig_type);
	Craydl_RxDetector_SetSequenceGate(m_rx_detector, rx_sequence_gate);
	// then set trig signal type and input (trig is input 0 and gate is input 1)
	if (trigger==1) {
		if (Craydl_RxDetector_SetSequenceGateSignalType(m_rx_detector, rx_trig_signal_type))
			THROW_HW_FATAL(Error) << "SetSequenceGateSignalType() failed";
	}
	else {
		if (Craydl_RxDetector_SetFrameTriggerSignalType(m_rx_detector, rx_trig_signal_type))
			THROW_HW_FATAL(Error) << "SetFrameTriggerSignalType() failed";
	}


	// Clear here the mapped queue, sometimes Rx can send frames in an arbitrary order
	// so we use a queue mechanism, BUT if an acquisition
	// is stopped before end it can remain some frames in the queue
	// We experienced this problem when Rx has not enough memory to work
	// (Lima used 70% of RAM), in that case some processing tasks become slow !!
	m_pending_frames.clear();
	m_expected_frame_nb = 0;
	// acq will be started in the first call of startAcq()
	if (m_trig_mode == IntTrigMult) m_int_trig_mult_started = false;

	// reset the callbacks frame counters
	m_frame_status_cb->resetFrameCounts();
}

//---------------------------
// @brief  start the new acquisition
//---------------------------
void Camera::startAcq() {
	DEB_MEMBER_FUNCT();

	m_buffer_ctrl_obj.getBuffer().setStartTimestamp(Timestamp::now());

	if (m_trig_mode == IntTrigMult && !m_int_trig_mult_started) {
	        // Release the bulb if still High otherwise acq 'll start immediately
	        if (Craydl_RxDetector_Bulb(m_rx_detector))
		        Craydl_RxDetector_ReleaseBulb(m_rx_detector);
		if (Craydl_RxDetector_StartAcquisition(m_rx_detector))
			THROW_HW_ERROR(Error) << "Cannot start the acquisition in IntTrigMult mode";
		m_int_trig_mult_started = true;
	}
	if (m_trig_mode == IntTrigMult) {
		if (Craydl_RxDetector_PulseBulb(m_rx_detector, 0.001))
			THROW_HW_ERROR(Error) << "PulsBulb() failed!";
	}
	else {
		if (Craydl_RxDetector_StartAcquisition(m_rx_detector))
			THROW_HW_ERROR(Error) << "StartAcquisition() failed!";
	}
	setStatus(DETECTOR_STATUS_INTEGRATING);
}

//---------------------------
// @brief  stop the acquisition
//---------------------------
void Camera::stopAcq() {
	DEB_MEMBER_FUNCT();
	if (Craydl_RxDetector_EndAcquisition(m_rx_detector, true))
		DEB_ERROR() << "Camera::stopAcq: Error stopping acquisition!";

	setStatus(DETECTOR_STATUS_IDLE);
}



//---------------------------
// @brief  callback function for each new frame
// called by FrameStatusCB.FrameReady()
//---------------------------
void Camera::frameReady(const Craydl_RxFrame_t pFrame) {

	DEB_MEMBER_FUNCT();
	int frameID = Craydl_RxFrame_InternalFrameID(pFrame);

	StdBufferCbMgr& buffer_mgr = m_buffer_ctrl_obj.getBuffer();
	void *ptr = buffer_mgr.getFrameBufferPtr(frameID);
	FrameDim frame_dim(Craydl_RxFrame_getNFast(pFrame), Craydl_RxFrame_getNSlow(pFrame), Bpp16);
	memcpy(ptr, Craydl_RxFrame_getBufferAddress(pFrame), frame_dim.getMemSize());


	HwFrameInfoType frame_info;
	frame_info.acq_frame_nb = frameID;
	DEB_ALWAYS() << "got frame " << DEB_VAR1(frameID);

	AutoMutex aLock(m_mutex);
	if(m_expected_frame_nb == frameID){
		bool continueAcq = buffer_mgr.newFrameReady(frame_info);
		++m_expected_frame_nb;

		for(std::map<int,HwFrameInfoType>::iterator i = m_pending_frames.begin();
		    continueAcq && i != m_pending_frames.end();m_pending_frames.erase(i++)){
			if(i->first == m_expected_frame_nb) {
				++m_expected_frame_nb;
				continueAcq = buffer_mgr.newFrameReady(i->second);
			}
			else
				break;
		}
	}
	else
		m_pending_frames[frameID] = frame_info;

}

//---------------------------
// @brief  return the frame trigger (input1) signal type
//---------------------------
void Camera::getFrameTriggerSignalType(SignalType & signal_type) {
	DEB_MEMBER_FUNCT();
	signal_type = m_frame_trig_signal_type;
}

//---------------------------
// @brief  set the frame trigger (input1) signal type
// @param  signal_type SOFT type is not allowed
//---------------------------
void Camera::setFrameTriggerSignalType(SignalType signal_type) {
	DEB_MEMBER_FUNCT();
	if (signal_type == SOFTWARE)
		THROW_HW_ERROR(InvalidValue) << "Signal Type SOFT is reserved"
					     << "Please use setTrigMode(IntTrigMult) instead";
	m_frame_trig_signal_type = signal_type;
}

//---------------------------
// @brief return the sequence gate (input2) signal type
//---------------------------
void Camera::getSequenceGateSignalType(SignalType & signal_type) {
	DEB_MEMBER_FUNCT();
	signal_type = m_sequ_gate_signal_type;
}

//---------------------------
// @brief  set the sequence gate (input2) signal type
// @param  signal_type SOFT type is not allowed
//---------------------------
void Camera::setSequenceGateSignalType(SignalType signal_type) {
	DEB_MEMBER_FUNCT();
	if (signal_type == SOFTWARE)
		THROW_HW_ERROR(InvalidValue) << "Signal Type SOFT is reserved"
					     << "Please use setTrigMode(IntTrigMult) instead";
	m_sequ_gate_signal_type = signal_type;
}

//---------------------------
// @brief set the output channel signal type
// @param[in] output CHANNEL_1 or CHANNEL_2
// @param[in] signal_type see SignalType enum
//---------------------------
void Camera::setOutputSignalType(OutputChannel output, SignalType signal_type) {
	DEB_MEMBER_FUNCT();

	Craydl_DigitalIOSignalType_t sig_type = (Craydl_DigitalIOSignalType_t)signal_type;

	if(Craydl_RxDetector_SetDigitalOutputSignalType(m_rx_detector, (int) output, sig_type))
		THROW_HW_ERROR(Error) << "Cannot set output signal type";
}
//---------------------------
// @brief return the output signl type on selected channel
// @param[in] output CHANNEL_1 or CHANNEL_2
// @param[out] signal_type
//---------------------------
void Camera::getOutputSignalType(OutputChannel output, SignalType &signal_type) {
	DEB_MEMBER_FUNCT();

	Craydl_DigitalIOSignalType_t sig_type;
	sig_type = Craydl_RxDetector_GetDigitalOutputSignalType(m_rx_detector, (int)output);
	signal_type = (SignalType)sig_type;
}

//---------------------------
// @brief set the output ID on the selected channel
// @param[in] output CHANNEL_1 or CHANNEL_2
// @param[in] signal_id see SignalID enum for list
//---------------------------
void Camera::setOutputSignalID(OutputChannel output, SignalID signal_id) {
	DEB_MEMBER_FUNCT();

	Craydl_DigitalIOSignalID_t sig_id = (Craydl_DigitalIOSignalID_t)signal_id;

	if(Craydl_RxDetector_SetDigitalOutputSignalID(m_rx_detector, (int) output, sig_id))
		THROW_HW_ERROR(Error) << "Cannot set output signal ID";
}
//---------------------------
// @brief return the output ID on selected channel
// @param[in] output CHANNEL_1 or CHANNEL_2
// @param[out] signal_id see SignalID enum for list
//---------------------------
void Camera::getOutputSignalID(OutputChannel output, SignalID &signal_id) {
	DEB_MEMBER_FUNCT();

	Craydl_DigitalIOSignalID_t sig_id;
	sig_id = Craydl_RxDetector_GetDigitalOutputSignalID(m_rx_detector, (int)output);
	signal_id = (SignalID)sig_id;
}

//---------------------------
// @brief set the shutter opening delay in seconds
//---------------------------
void Camera::setShutterOpenDelay(double delay) {
	DEB_MEMBER_FUNCT();

	if (Craydl_RxDetector_SetShutterOpenDelay(m_rx_detector, delay))
		THROW_HW_ERROR(Error) << "Cannot set shutter open delay";
}

//---------------------------
// @brief return the shutter opening delay in seconds
//---------------------------
void Camera::getShutterOpenDelay(double &delay) {
	DEB_MEMBER_FUNCT();

	delay = Craydl_RxDetector_GetShutterOpenDelay(m_rx_detector);
}

//---------------------------
// @brief set the shutter closing delay in seconds
//---------------------------
void Camera::setShutterCloseDelay(double delay) {
	DEB_MEMBER_FUNCT();

	if (Craydl_RxDetector_SetShutterCloseDelay(m_rx_detector, delay))
		THROW_HW_ERROR(Error) << "Cannot set shutter close delay";
}

//---------------------------
// @brief return the shutter opening delay in seconds
//---------------------------
void Camera::getShutterCloseDelay(double &delay) {
	DEB_MEMBER_FUNCT();

	delay = Craydl_RxDetector_GetShutterCloseDelay(m_rx_detector);
}

//---------------------------
// @brief set manually the shutter open or close
// @param[in] open true = open, false = close
//---------------------------
void Camera::setShutter(bool open) {
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(open);

	if (Craydl_RxDetector_CommandShutter(m_rx_detector, open))
		THROW_HW_ERROR(Error) << "Cannot set manual shutter to :"
				      << DEB_VAR1(open);
}

//---------------------------
// @brief return the shutter status
// @param[out] open true or false
//---------------------------
void Camera::getShutter(bool &open) {
	DEB_MEMBER_FUNCT();

	open = Craydl_RxDetector_Shutter(m_rx_detector);
}

//---------------------------
// @brief enable/disable the electronic shutter
// @param[in] enable true or false
//---------------------------
void Camera::setElectronicShutterEnabled(bool enable) {
	DEB_MEMBER_FUNCT();

	if (Craydl_RxDetector_EnableElectronicShutter(m_rx_detector, enable))
		THROW_HW_ERROR(Error) << "Cannot enable electronic shutter";
}

//---------------------------
// @brief return if electronic shutter is enable or disable
//---------------------------
void Camera::getElectronicShutterEnabled(bool &enable) {
	DEB_MEMBER_FUNCT();

	enable = Craydl_RxDetector_ElectronicShutterEnabled(m_rx_detector);
}

//---------------------------
// @brief return the cooler temperature set point
// @param[out] temperature in degre Celcius
//---------------------------
void Camera::getCoolerTemperatureSetpoint(double &temperature) {
	DEB_MEMBER_FUNCT();

	temperature = Craydl_RxDetector_SensorTemperatureSetpoint(m_rx_detector);
}

//---------------------------
// @brief set the cooler temperature set point
// @param[in] temperature in degree Celcius
//---------------------------
void Camera::setCoolerTemperatureSetpoint(double temperature) {
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(temperature);

	if (Craydl_RxDetector_SetSensorTemperatureSetpoint(m_rx_detector, temperature))
		THROW_HW_ERROR(Error) << "Cannot set cooler temperature setpoint!";
}

//---------------------------
// @brief return the sensor temperature set point
// @param[out] temperature in degree Celcius
//---------------------------
void Camera::getSensorTemperatureSetpoint(double &temperature) {
	DEB_MEMBER_FUNCT();

	temperature = Craydl_RxDetector_SensorTemperatureSetpoint(m_rx_detector);
}

//---------------------------
// @brief set the sensor temperature set point
// @param[in] temperature in degree Celcius
//---------------------------
void Camera::setSensorTemperatureSetpoint(double temperature) {
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(temperature);

	if (Craydl_RxDetector_SetSensorTemperatureSetpoint(m_rx_detector, temperature))
		THROW_HW_ERROR(Error) << "Cannot set sensor temperature setpoint!";
}

//---------------------------
// @brief return the sensor temperature (average)
// @param[out] temperature in degree Celcius
//---------------------------
void Camera::getSensorTemperature(double &temperature) {
	DEB_MEMBER_FUNCT();

	temperature = Craydl_RxDetector_SensorTemperatureAve(m_rx_detector);
}


//---------------------------
// @brief start or stop the cooling system
// @param[in] start true = start, false = stop
//---------------------------
void Camera::setCooler(bool start) {
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(start);

	if (Craydl_RxDetector_CommandCoolers(m_rx_detector, start))
		THROW_HW_ERROR(Error) << "Cannot set cooler to : "
				      << DEB_VAR1(start);
	m_cooler = start;
}

//---------------------------
// @brief return if the cooling system is running or not
// @param[out] started true = started, false = stopped
//---------------------------
void Camera::getCooler(bool& started)
{
	DEB_MEMBER_FUNCT();

	m_cooler = Craydl_RxDetector_SupportedStatusFlagValue(m_rx_detector, StatusFlagCoolersEnabled);
	started = m_cooler;

}

//---------------------------
// @brief close or open the vacuum valve
// @param[in] open true = open, false = close
//---------------------------
void Camera::setVacuumValve(bool open) {
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(open);

	if (Craydl_RxDetector_CommandVacuumValve(m_rx_detector, open))
		THROW_HW_ERROR(Error) << "Cannot set vacuum valve to : "
				      << DEB_VAR1(open);
	m_vac_valve = open;
}

//---------------------------
// @brief close or open the vacuum valve
// @param[in] opened true = open, false = close
//---------------------------
void Camera::getVacuumValve(bool& opened)
{
	DEB_MEMBER_FUNCT();

	m_vac_valve = Craydl_RxDetector_SupportedStatusFlagValue(m_rx_detector, StatusFlagVacuumValveEnabled);
	opened = m_vac_valve;
}

//---------------------------
// @brief return if the detector needs a new background
// @param[out] needed: true = yes, false = no
//---------------------------
void Camera::getNewBackgroundNeeded(bool& needed)
{
	DEB_MEMBER_FUNCT();

	needed  = Craydl_RxDetector_NewBackgroundNeeded(m_rx_detector);
}


//---------------------------
// @brief acquire (a) new background frame(s)
// @param[in] block: true = blocking cmd, false = none-blocking cmd
//---------------------------
void Camera::acquireNewBackground(bool block, int n_background)
{
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR2(block,n_background);

        if (m_status == DETECTOR_STATUS_INTEGRATING) {
		THROW_HW_ERROR(Error) << "Cannot set a new background while the detector is running. "
                                      << "Please stop the acquisition before !!";
        }

	if (Craydl_RxDetector_AcquireNewBackground(m_rx_detector, block, n_background))
		THROW_HW_ERROR(Error) << "Cannot take a new background :"
				      << DEB_VAR2(block, n_background);
}

//---------------------------
// @brief return the readout mode
// @param[out] mode:
//---------------------------
void Camera::getReadoutMode(ReadoutMode& mode)
{
	DEB_MEMBER_FUNCT();

	mode = (ReadoutMode) Craydl_RxDetector_GetReadoutMode(m_rx_detector);
}

//---------------------------
// @brief set the readout mode
// @param[in] mode:
//---------------------------
void Camera::setReadoutMode(ReadoutMode mode)
{
	DEB_MEMBER_FUNCT();

        if (m_status == DETECTOR_STATUS_INTEGRATING) {
		THROW_HW_ERROR(Error) << "Cannot change the readout mode while the detector is running. "
                                      << "Please stop the acquisition before !!";
        }
	if (Craydl_RxDetector_SetReadoutMode(m_rx_detector, (Craydl_ReadoutMode_t) mode))
	        THROW_HW_ERROR(Error) << "Cannot set the readout mode :"
				      << DEB_VAR1(mode);
        // In High Dynamic Range, the image type Bpp32
        if (mode == READOUT_MODE_HDR32) m_image_type = Bpp32;
        else m_image_type = Bpp16;
	// Update CtImage about image size changes
	Size image_size;
	getMaxImageSize(image_size);
	maxImageSizeChanged(image_size,m_image_type);
}
