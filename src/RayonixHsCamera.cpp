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
#include "craydl.h"
#include "RayonixHsCamera.h"

using namespace lima;
using namespace lima::RayonixHs;

Camera::Camera()
	: m_rx_detector(new craydl::RxDetector("./RxDetector.conf")),
	  m_status(DETECTOR_STATUS_IDLE),
	  m_acquiring(false)
{
        
	DEB_CONSTRUCTOR();

	init();

	m_frame_status_cb = new FrameStatusCb(this, m_acquiring);
	//m_frame_status_cb->registerCallbackAcqComplete(&lima::RayonixHs::Camera::acquisitionComplete);
	//m_frame_status_cb->registerCallbackAcqComplete(&acquisitionComplete);
}

void Camera::init() {
        DEB_MEMBER_FUNCT();
	craydl::RxReturnStatus status;
	
	setStatus(DETECTOR_STATUS_FAULT, true);
	//Open camera
	status = m_rx_detector->Open();
	if (status.IsError()) {
	       m_max_image_size = Size(0, 0);
	       THROW_HW_ERROR(Error) << "Camera::init: Error opening camera!";
	}

	//Get unbinned frame size from camera
	craydl::DetectorFormat detector_format;
	if (m_rx_detector->GetDetectorFormat(detector_format).IsError()) {                	  
		THROW_HW_ERROR(Error) << "Camera::init: Error getting camera format!";
	}
	int fast, slow;
	fast = detector_format.n_pixels_fast();
	slow = detector_format.n_pixels_slow();

	m_max_image_size = Size(fast, slow);
	
	m_exp_time = 1.0;
	m_lat_time = 0.001;
	m_int_time = m_exp_time + m_lat_time;

	m_nb_frames = 1;
	// default frame mode is SINGLE, FAST_TRANFSER is not
	m_frame_mode = SINGLE;
	m_trig_signal_type = OPTO;

	setStatus(DETECTOR_STATUS_IDLE, true);
}

Camera::~Camera() {
        DEB_DESTRUCTOR();

	if (m_rx_detector->EndAcquisition(true).IsError())
		DEB_ERROR() << "Camera::~Camera: Error ending acquisition!";

	if (m_rx_detector->Close().IsError())
		DEB_ERROR() << "Camera::~Camera: Error closing camera!";

	delete m_rx_detector;
	delete m_frame_status_cb;
}

HwBufferCtrlObj* Camera::getBufferCtrlObj() {
        DEB_MEMBER_FUNCT();
	return &m_buffer_ctrl_obj;
}

void Camera::getDetectorType(std::string &type) {
        DEB_MEMBER_FUNCT();
	type = "RayonixHs";
}

void Camera::getImageType(ImageType &img_type) {
        DEB_MEMBER_FUNCT();
	img_type = Bpp16;
}

void Camera::setImageType(ImageType img_type) {
        DEB_MEMBER_FUNCT();
	switch (img_type) {
		case Bpp16:
			break;
		default:
			throw LIMA_HW_EXC(InvalidValue,"This image type is not supported.");
	}
}


bool Camera::checkTrigMode(TrigMode mode) {
        DEB_MEMBER_FUNCT();
	bool valid_mode;

	switch (mode) {
	case IntTrig:
	case IntTrigMult:
	case ExtTrigSingle:
	case ExtTrigMult:
	case ExtGate:
	case ExtTrigReadout:
	  valid_mode = true;
	  break;
	default:
	  valid_mode = false;
	}
	return valid_mode;
}

void Camera::setFrameMode(FrameMode mode) {
  DEB_MEMBER_FUNCT();
  
  // RayonixHs is switched to FAST_TRANSFER frame mode by setting exposure time to 0 
  // then interval time sets the exposure duration, and latency is 1ms (transfer time)
  if (mode != m_frame_mode) {
    double exp_time;
    if (mode == SINGLE) exp_time = m_exp_time;
    else // FAST_TRANSFER
      exp_time = 0;

    if (m_rx_detector->SetExposureTime(exp_time).IsError()) {
      DEB_ERROR() << "Camera::setExpTime: Error setting exposure!";
      return;  
    }
    
  }
  m_frame_mode = mode;
}

void Camera::getFrameMode(FrameMode &mode) {
  DEB_MEMBER_FUNCT();
  mode = m_frame_mode;
}

void Camera::getTrigMode(TrigMode &mode) {
        DEB_MEMBER_FUNCT();
	mode = m_trig_mode;
}

void Camera::setTrigMode(TrigMode mode) {
        DEB_MEMBER_FUNCT();
	m_trig_mode = mode;
}
void Camera::getPixelSize(double &x, double &y) {
        DEB_MEMBER_FUNCT();
	m_rx_detector->GetPixelSize(x, y);
}

void Camera::getMaxImageSize(Size& max_image_size) {
        DEB_MEMBER_FUNCT();
	max_image_size = m_max_image_size;
}

void Camera::setNbFrames(int nb_frames) {
        DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(nb_frames);
	if (nb_frames < 0)
		throw LIMA_HW_EXC(InvalidValue, "Invalid nb of frames");

	m_nb_frames = nb_frames;
}

void Camera::getNbFrames(int& nb_frames) {
        DEB_MEMBER_FUNCT();
	nb_frames = m_nb_frames;
}

void Camera::setExpTime(double exp_time) {
        DEB_MEMBER_FUNCT();
	if (exp_time < 0)
		throw LIMA_HW_EXC(InvalidValue, "Invalid exposure time");
	if (m_frame_mode == SINGLE) {
	  if (m_rx_detector->SetExposureTime(exp_time).IsError()) {
	    DEB_ERROR() << "Camera::setExpTime: Error setting exposure!";
	    return;
	  }
	  m_exp_time = exp_time;
	}
	else { // FAST_TRANSFER
	  if (m_rx_detector->SetIntervalTime(exp_time).IsError()) {
	    DEB_ERROR() << "Camera::setLatTime: Error setting latency!";
	    return;
	  }
	  m_int_time = exp_time;
	}
}

void Camera::getExpTime(double& exp_time) {
        DEB_MEMBER_FUNCT();
	double real_exp_time;
	if (m_frame_mode == SINGLE) {
	  m_exp_time = m_rx_detector->ExposureTime();
	  exp_time = m_exp_time;
	}
	else { // FAST_TRANSFER
	  m_int_time = m_rx_detector->IntervalTime();
	  exp_time = m_int_time;
	}
}

void Camera::setLatTime(double lat_time) {
        DEB_MEMBER_FUNCT();
	if (lat_time < 0)
		throw LIMA_HW_EXC(InvalidValue, "Invalid latency time");

	// Ok, RayonixHs manages an interval time not a latency:
	// in SINGLE frame mode latency = interval - exposure
	// in FAST_TRANSFER latency = 1ms and interval is the exposure (exposure must be 0 )
	if (m_frame_mode == SINGLE) {
	  if (m_rx_detector->SetIntervalTime(lat_time+m_exp_time).IsError()) {
	    DEB_ERROR() << "Camera::setLatTime: Error setting latency!";
	    return;
	  }  
	}
	else {
	  // FAST_TRANSFER: latency is fixed, 1ms of frame transfer
	  throw LIMA_HW_EXC(InvalidValue, "Cannot set latency in FAST_TRANSFER frame mode!");
	}
	m_lat_time = lat_time;
}

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

void Camera::setBin(const Bin& bin) {
        DEB_MEMBER_FUNCT();
	if (m_rx_detector->SetBinning(bin.getX(), bin.getY()).IsError())
		DEB_ERROR() << "Camera::setBin: Error setting binning!";
}

void Camera::getBin(Bin& bin) {
        DEB_MEMBER_FUNCT();
	int binFast, binSlow;
	if (m_rx_detector->GetBinning(binFast, binSlow).IsError()) {
		DEB_ERROR() << "Camera::getBin: Error getting binning!";
		return;
	}
	bin = Bin(binFast, binSlow);
}

void Camera::checkBin(Bin& bin) {
        DEB_MEMBER_FUNCT();
	if (!m_rx_detector->CheckBinning(bin.getX(), bin.getY())) {
		DEB_TRACE() << "Camera::checkBin: Invalid binning.  Setting bin to current detector binning.";
		getBin(bin);
	}
}

void Camera::setFrameDim(const FrameDim& frame_dim) {
      DEB_MEMBER_FUNCT();
     //Rayonix detector library handles this automatically
}

void Camera::getFrameDim(FrameDim& frame_dim) {
        DEB_MEMBER_FUNCT();
	int fast, slow, depth;
	m_rx_detector->GetFrameSize(fast, slow, depth);
	frame_dim.setSize(Size(fast, slow));
	frame_dim.setImageType(Bpp16);
}

void Camera::reset() {
        DEB_MEMBER_FUNCT();
	stopAcq();
	init();
}

void Camera::getStatus(DetectorStatus &status) {
        DEB_MEMBER_FUNCT();

	status = m_status;
}

//-----------------------------------------------------
//
//-----------------------------------------------------
void Camera::setStatus(DetectorStatus status,bool force)
{
    DEB_MEMBER_FUNCT();
    if(force || m_status != DETECTOR_STATUS_FAULT)
        m_status = status;
}

void Camera::prepareAcq() {
        DEB_MEMBER_FUNCT();
   if (m_rx_detector->SetAcquisitionUserCB(static_cast<craydl::VirtualFrameCallback *> (m_frame_status_cb)).IsError()) {
     THROW_HW_ERROR(Error) << "Camera::prepareAcq: Error setting frame callback!";
   }
   // 0 means first frame id equal 0 (InternalFrameID)
   if (m_rx_detector->SetupAcquisitionSequence(m_nb_frames, 0).IsError()) 
     THROW_HW_ERROR(Error) << "Camera::prepareAcq: Error setting up acquisition sequence!";

   craydl::FrameTriggerType_t rx_frame_trig_type;
   craydl::DigitalIOSignalType_t rx_trig_signal_type;
   craydl::SequenceGate_t rx_sequence_gate;
   int trigger;

   switch (m_trig_mode) {
   case IntTrig:
     rx_frame_trig_type  = craydl::FrameTriggerTypeNone;
     rx_sequence_gate    = craydl::SequenceGateModeNone;
     rx_trig_signal_type = craydl::DigitalIOSignalTypeNone;
     trigger = 0;
     break;
   case IntTrigMult:
     rx_frame_trig_type  = craydl::FrameTriggerTypeFrame;
     rx_sequence_gate    = craydl::SequenceGateModeNone;
     rx_trig_signal_type = craydl::DigitalIOSignalTypeSoftware;
     trigger = 0;
     break;

   case ExtTrigSingle:
     rx_frame_trig_type  = craydl::FrameTriggerTypeNone;
     rx_sequence_gate    = craydl::SequenceGateModeStart;
     rx_trig_signal_type = (craydl::DigitalIOSignalType_t) m_trig_signal_type;
     trigger = 1; // the Gate input
     break;

   case ExtTrigMult:
     rx_frame_trig_type  = craydl::FrameTriggerTypeFrame;
     rx_sequence_gate    = craydl::SequenceGateModeNone;
     rx_trig_signal_type = (craydl::DigitalIOSignalType_t) m_trig_signal_type;
     trigger = 0; // Frame input
     break;

   case ExtGate:
     rx_frame_trig_type  = craydl::FrameTriggerTypeBulb;
     rx_sequence_gate    = craydl::SequenceGateModeNone;
     rx_trig_signal_type = (craydl::DigitalIOSignalType_t) m_trig_signal_type;
     trigger = 0; // Frame input
     break;

   case ExtTrigReadout:
     break;

   }
   // apply trigger mode (soft, trig, gate ...)
   m_rx_detector->SetFrameTriggerMode(craydl::FrameTriggerType(rx_frame_trig_type));
   m_rx_detector->SetSequenceGate(craydl::SequenceGateMode(rx_sequence_gate));
   // then set trig signal type and input (trig is input 0 and gate is input 1) 
   if (trigger==1) 
     m_rx_detector->SetSequenceGateSignalType(craydl::DigitalIOSignalType(rx_trig_signal_type));
   else
     m_rx_detector->SetFrameTriggerSignalType(craydl::DigitalIOSignalType(rx_trig_signal_type));


   m_expected_frame_nb = 0;
   // acq will be started in the first call of startAcq()
   if (m_trig_mode == IntTrigMult) m_int_trig_mult_started = false;

   // reset the callbacks frame counters
   m_frame_status_cb->resetFrameCounts();
}

void Camera::startAcq() {
        DEB_MEMBER_FUNCT();

	m_buffer_ctrl_obj.getBuffer().setStartTimestamp(Timestamp::now());

        if (m_trig_mode == IntTrigMult && !m_int_trig_mult_started) {
          if (m_rx_detector->StartAcquisition(craydl::FrameAcquisitionTypeLight).IsError())
	    THROW_HW_ERROR(Error) << "Camera::startAcq: Error preparing acquisition in IntTrigMult mode!";
	  m_int_trig_mult_started = true;
        }
	if (m_trig_mode == IntTrigMult) {
	  if (m_rx_detector->PulseBulb(0.001).IsError())
	    THROW_HW_ERROR(Error) << "Camera::startAcq: Error PulsBulb() acquisition!";
	}
	else {
	  if (m_rx_detector->StartAcquisition(craydl::FrameAcquisitionTypeLight).IsError())
	      THROW_HW_ERROR(Error) << "Camera::startAcq: Error starting acquisition!";
	}     
	setStatus(DETECTOR_STATUS_INTEGRATING);
}

void Camera::stopAcq() {
        DEB_MEMBER_FUNCT();
	if (m_rx_detector->EndAcquisition(true).IsError())
		DEB_ERROR() << "Camera::stopAcq: Error stopping acquisition!";
	setStatus(DETECTOR_STATUS_IDLE);
}

void Camera::getTriggerSignalType(TriggerSignalType & signal_type) {
  DEB_MEMBER_FUNCT();
  signal_type = m_trig_signal_type;
}

void Camera::setTriggerSignalType(TriggerSignalType signal_type) {
  DEB_MEMBER_FUNCT();
  if (signal_type == SOFTWARE)
    throw LIMA_HW_EXC(InvalidValue, "Signal Type SOFT is reserved, please use setTrigMode(IntTrigMult) instead !");
  m_trig_signal_type = signal_type;
}

int Camera::getNbAcquiredFrames() {
        DEB_MEMBER_FUNCT();
	return m_frame_status_cb->frameCountCorrected();
}

void Camera::getDetectorModel(std::string &model) {
        DEB_MEMBER_FUNCT();
	std::string junk;
	if (m_rx_detector->GetDetectorID(model, junk).IsError())
		DEB_ERROR() << "Camera::getDetectorModel: Error getting detector model.";
}

void Camera::setRoi(const Roi& roi) {
        DEB_MEMBER_FUNCT();
	//Rayonix HS cameras do software ROI so this is not implemented.
}

void Camera::getRoi(Roi& roi) {
        DEB_MEMBER_FUNCT();
	//Rayonix HS cameras do software ROI so this is not implemented.
	roi = Roi(Point(0, 0), m_max_image_size);
}

void Camera::checkRoi(const Roi& set_roi, Roi& hw_roi) {
       DEB_MEMBER_FUNCT();
       DEB_PARAM() << DEB_VAR1(set_roi);

       //Rayonix HS cameras do software ROI so this is not implemented.
       hw_roi = Roi(Point(0, 0), m_max_image_size); 

       DEB_RETURN() << DEB_VAR1(hw_roi);
}

void Camera::frameReady(const craydl::RxFrame *pFrame) {
  
   DEB_MEMBER_FUNCT();
   int frameID = pFrame->InternalFrameID();

   StdBufferCbMgr& buffer_mgr = m_buffer_ctrl_obj.getBuffer();
   void *ptr = buffer_mgr.getFrameBufferPtr(frameID);
   FrameDim frame_dim(pFrame->getNFast(), pFrame->getNSlow(), Bpp16);
   memcpy(ptr,pFrame->getBufferAddress(),frame_dim.getMemSize());

   
   HwFrameInfoType frame_info;
   frame_info.acq_frame_nb = frameID;
   DEB_TRACE() << "got frame " << DEB_VAR1(frameID);

   AutoMutex aLock(m_mutex);
   if(m_expected_frame_nb == frameID)
     {
       bool continueAcq = buffer_mgr.newFrameReady(frame_info);
       ++m_expected_frame_nb;

       for(std::map<int,HwFrameInfoType>::iterator i = m_pending_frames.begin();
	   continueAcq && i != m_pending_frames.end();m_pending_frames.erase(i++))
	 {
	   if(i->first == m_expected_frame_nb)
	     {
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
