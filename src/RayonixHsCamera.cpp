
#include "craydl.h"
#include "RayonixHsCamera.h"

using namespace lima;
using namespace lima::RayonixHs;

Camera::Camera()
	: m_rx_detector(new craydl::RxDetector("./RxDetector.conf")),
	  m_acquiring(false) {
        
	DEB_CONSTRUCTOR();

	init();

	m_frame_status_cb = new FrameStatusCb(this, m_acquiring);
	//m_frame_status_cb->registerCallbackAcqComplete(&lima::RayonixHs::Camera::acquisitionComplete);
	//m_frame_status_cb->registerCallbackAcqComplete(&acquisitionComplete);
}

void Camera::init() {
        DEB_MEMBER_FUNCT();
	craydl::RxReturnStatus status;
	
	//Open camera
	status = m_rx_detector->Open();
	if (status.IsError()) {
		DEB_ERROR() << "Camera::init: Error opening camera!";
		m_max_image_size = Size(0, 0);
		return;
	}

	m_detector_status = DETECTOR_STATUS_IDLE;
	
	//Get unbinned frame size from camera
	craydl::DetectorFormat detector_format;
	if (m_rx_detector->GetDetectorFormat(detector_format).IsError()) {
		DEB_ERROR() << "Camera::init: Error getting camera format!";
		return;
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
}

void Camera::reset() {
        DEB_MEMBER_FUNCT();
	stopAcq();
	init();
}

HwInterface::StatusType::Basic Camera::getStatus() {
        DEB_MEMBER_FUNCT();
	switch (m_detector_status) {
		case DETECTOR_STATUS_IDLE:
			return HwInterface::StatusType::Ready;
		case DETECTOR_STATUS_INTEGRATING:
			return HwInterface::StatusType::Exposure;
		default:
			throw LIMA_HW_EXC(Error, "Invalid status");
	}
}

void Camera::prepareAcq() {
        DEB_MEMBER_FUNCT();
   if (m_rx_detector->SetAcquisitionUserCB(static_cast<craydl::VirtualFrameCallback *> (m_frame_status_cb)).IsError()) {
      DEB_ERROR() << "Camera::prepareAcq: Error setting frame callback!";
   }
   // 0 means first frame id equal 0 (InternalFrameID)
   if (m_rx_detector->SetupAcquisitionSequence(m_nb_frames, 0).IsError()) 
     DEB_ERROR() << "Camera::prepareAcq: Error setting up acquisition sequence!";

   craydl::FrameTriggerType_t rx_frame_trig_type;
   craydl::TriggerSignalType_t rx_trig_signal_type;
   craydl::SequenceGate_t rx_sequence_gate;
   craydl::TriggerDirection_t rx_trig_direction;
   int trigger;

   switch (m_trig_mode) {
   case IntTrig:
     rx_frame_trig_type  = craydl::FrameTriggerTypeNone;
     rx_trig_signal_type = craydl::TriggerSignalTypeNone;
     rx_sequence_gate    = craydl::SequenceGateModeNone;
     rx_trig_direction = craydl::TriggerDirectionInput;
     trigger = 0;
     break;
   case IntTrigMult:
     rx_frame_trig_type  = craydl::FrameTriggerTypeFrame;
     rx_trig_signal_type = craydl::TriggerSignalTypeSoftware;
     rx_sequence_gate    = craydl::SequenceGateModeNone;
     rx_trig_direction = craydl::TriggerDirectionInput;
     trigger = 0;
     if (m_rx_detector->StartAcquisition(craydl::FrameAcquisitionTypeLight).IsError())
       DEB_ERROR() << "Camera::prepareAcq: Error preparing acquisition in IntTrigMult mode!";
     break;

   case ExtTrigSingle:
     rx_frame_trig_type  = craydl::FrameTriggerTypeNone;
     rx_trig_signal_type = (craydl::TriggerSignalType_t)m_trig_signal_type;
     rx_sequence_gate    = craydl::SequenceGateModeStart;
     rx_trig_direction = craydl::TriggerDirectionInput;
     trigger = 1; // the Gate input
     break;

   case ExtTrigMult:
     rx_frame_trig_type  = craydl::FrameTriggerTypeFrame;
     rx_trig_signal_type =  (craydl::TriggerSignalType_t)m_trig_signal_type;
     rx_sequence_gate    = craydl::SequenceGateModeNone;
     rx_trig_direction = craydl::TriggerDirectionInput;
     trigger = 0; // Frame input
     break;

   case ExtGate:
     break;

   case ExtTrigReadout:
     break;

   }

   m_rx_detector->SetFrameTriggerMode(craydl::FrameTriggerType(rx_frame_trig_type));
   m_rx_detector->SetTriggerSignalType(trigger, rx_trig_direction, craydl::TriggerSignalType(rx_trig_signal_type));
   m_rx_detector->SetSequenceGate(craydl::SequenceGateMode(rx_sequence_gate));


   m_expected_frame_nb = 0;
}

void Camera::getTriggerSignalType(TriggerSignalType & signal_type) {
  DEB_MEMBER_FUNCT();
  signal_type = m_trig_signal_type;
}

void Camera::setTriggerSignalType(TriggerSignalType signal_type) {
  DEB_MEMBER_FUNCT();
  if (signal_type == SOFTWARE)
    throw LIMA_HW_EXC(InvalidValue, "Signal Type SOFT is reserved, please use setTrigMode(IntTrig[Mult]) instead !");
  m_trig_signal_type = signal_type;
}

void Camera::startAcq() {
        DEB_MEMBER_FUNCT();

	//TODO: Other frame types?
	m_frame_status_cb->resetFrameCounts();

	m_buffer_ctrl_obj.getBuffer().setStartTimestamp(Timestamp::now());

	if (m_trig_mode == IntTrigMult) {
	  // in this mode startAcq() must  be called for each frame
	  if (m_rx_detector->StartExposure(craydl::FrameAcquisitionTypeLight).IsError())
	    DEB_ERROR() << "Camera::startAcq: Error starting acquisition!";
	}
	else {
	  if (m_rx_detector->StartAcquisition(craydl::FrameAcquisitionTypeLight).IsError())
	    DEB_ERROR() << "Camera::startAcq: Error starting acquisition!";
	}
}

void Camera::stopAcq() {
        DEB_MEMBER_FUNCT();
	if (m_rx_detector->EndAcquisition(true).IsError())
		DEB_ERROR() << "Camera::stopAcq: Error stopping acquisition!";
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
  
   StdBufferCbMgr& buffer_mgr = m_buffer_ctrl_obj.getBuffer();
   void *ptr = buffer_mgr.getFrameBufferPtr(pFrame->InternalFrameID());
   FrameDim frame_dim(pFrame->getNFast(), pFrame->getNSlow(), Bpp16);
   memcpy(ptr,pFrame->getBufferAddress(),frame_dim.getMemSize());

   
   HwFrameInfoType frame_info;
   frame_info.acq_frame_nb = pFrame->InternalFrameID();

   AutoMutex aLock(m_mutex);
   if(m_expected_frame_nb == pFrame->InternalFrameID())
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
     m_pending_frames[pFrame->InternalFrameID()] = frame_info;
   
}
