
#include "craydl.h"

#include "RayonixHsCamera.h"

using namespace lima;
using namespace lima::RayonixHs;

//TODO: Frame callback?!?!

Camera::Camera()
	: m_rx_detector(new craydl::RxDetector()),
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
	
	status = m_rx_detector->Open();
	if (status.IsError()) {
		DEB_ERROR() << "Camera::init: Error opening camera!";
		m_max_image_size = Size(0, 0);
		return;
	}

	m_detector_status = DETECTOR_STATUS_IDLE;

	int fast, slow, depth;
	m_rx_detector->GetFrameSize(fast, slow, depth);
	m_max_image_size = Size(fast, slow);

	m_exp_time = 0;
	m_lat_time = 0;
	m_nb_frames = 0;
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

SoftBufferCtrlObj* Camera::getBufferCtrlObj() {
        DEB_MEMBER_FUNCT();
	return (SoftBufferCtrlObj *)m_buffer_ctrl_obj;
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
	switch (mode) {
		case IntTrig:
		case ExtTrigSingle:
		case ExtTrigMult:
		case ExtGate:
			return true;
		default:
			return false;
	}
}

void Camera::getPixelSize(double &x, double &y) {
        DEB_MEMBER_FUNCT();
//TODO: Fix when library has pixel size method
	x = y = -1.;
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

	m_exp_time = exp_time;
}

void Camera::getExpTime(double& exp_time) {
        DEB_MEMBER_FUNCT();
	exp_time = m_exp_time;
}

void Camera::setLatTime(double lat_time) {
        DEB_MEMBER_FUNCT();
	if (lat_time < 0)
		throw LIMA_HW_EXC(InvalidValue, "Invalid latency time");

	DEB_TRACE() << "Camera::setLatTime: Latency time unsupported on this camera.";

	//m_lat_time = lat_time;
}

void Camera::getLatTime(double& lat_time) {
        DEB_MEMBER_FUNCT();
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
	m_frame_dim = frame_dim;
}

void Camera::getFrameDim(FrameDim& frame_dim) {
        DEB_MEMBER_FUNCT();
	frame_dim = m_frame_dim;
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
	if (m_rx_detector->SetupAcquisitionSequence(m_nb_frames, static_cast<craydl::VirtualFrameCallback *> (m_frame_status_cb), 1).IsError()) {
		DEB_ERROR() << "Camera::prepareAcq: Error setting up acquisition sequence!";
	}
}

void Camera::startAcq() {
        DEB_MEMBER_FUNCT();

//TODO: Other frame types?
	if (m_rx_detector->StartAcquisition(craydl::ACQUIRE_LIGHT).IsError())
		DEB_ERROR() << "Camera::startAcq: Error starting acquisition!";
}

void Camera::stopAcq() {
        DEB_MEMBER_FUNCT();
	if (m_rx_detector->EndAcquisition(true).IsError())
		DEB_ERROR() << "Camera::stopAcq: Error stopping acquisition!";
}

void Camera::getTrigMode(TrigMode &mode) {
        DEB_MEMBER_FUNCT();
//TODO: Trig mode functionality to do
	mode = IntTrig;
}

void Camera::setTrigMode(TrigMode mode) {
        DEB_MEMBER_FUNCT();
//TODO: Trig mode functionality to do
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
	// TODO: Add ROI functionality
}

void Camera::getRoi(Roi& roi) {
        DEB_MEMBER_FUNCT();
	// TODO: Add ROI functionality
}

void Camera::checkRoi(Roi& roi) {
        DEB_MEMBER_FUNCT();
	// TODO: Add ROI functionality
}

//void Camera::acquisitionComplete() {
//   m_acquiring = false;
//}
