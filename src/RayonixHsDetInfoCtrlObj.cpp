#include <cstdlib>

#include "RayonixHsDetInfoCtrlObj.h"
#include "RayonixHsCamera.h"

using namespace lima;
using namespace lima::RayonixHs;

DetInfoCtrlObj::DetInfoCtrlObj(Camera *cam)
	: m_cam(cam) {
	
	DEB_CONSTRUCTOR();
}

DetInfoCtrlObj::~DetInfoCtrlObj() {
        DEB_DESTRUCTOR();
}

void DetInfoCtrlObj::getMaxImageSize(Size& max_image_size) {
        DEB_MEMBER_FUNCT();    
	m_cam->getMaxImageSize(max_image_size);
}

void DetInfoCtrlObj::getDetectorImageSize(Size& det_image_size) {
        DEB_MEMBER_FUNCT();    
	getMaxImageSize(det_image_size);
}

void DetInfoCtrlObj::getDefImageType(ImageType& def_image_type) {
        DEB_MEMBER_FUNCT();    
	m_cam->getImageType(def_image_type);
}

void DetInfoCtrlObj::getCurrImageType(ImageType& curr_image_type) {
        DEB_MEMBER_FUNCT();    
	m_cam->getImageType(curr_image_type);
}

void DetInfoCtrlObj::setCurrImageType(ImageType curr_image_type) {
        DEB_MEMBER_FUNCT();    
	m_cam->setImageType(curr_image_type);
}

void DetInfoCtrlObj::getPixelSize(double& x_size, double& y_size) {
        DEB_MEMBER_FUNCT();    
	m_cam->getPixelSize(x_size, y_size);
}

void DetInfoCtrlObj::getDetectorType(std::string& det_type) {
        DEB_MEMBER_FUNCT();    
	m_cam->getDetectorType(det_type);
}

void DetInfoCtrlObj::getDetectorModel(std::string& det_model) {
        DEB_MEMBER_FUNCT();    
	m_cam->getDetectorModel(det_model);
}

void DetInfoCtrlObj::registerMaxImageSizeCallback(HwMaxImageSizeCallback& cb) {
        DEB_MEMBER_FUNCT();    
	m_cam->registerMaxImageSizeCallback(cb);
}

void DetInfoCtrlObj::unregisterMaxImageSizeCallback(HwMaxImageSizeCallback& cb) {
        DEB_MEMBER_FUNCT();    
	m_cam->unregisterMaxImageSizeCallback(cb);
}

