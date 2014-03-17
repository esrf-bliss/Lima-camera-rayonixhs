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
#include "RayonixHsInterface.h"
#include "RayonixHsCamera.h"
#include "RayonixHsDetInfoCtrlObj.h"
#include "RayonixHsBinCtrlObj.h"
#include "RayonixHsSyncCtrlObj.h"

using namespace lima;
using namespace lima::RayonixHs;

Interface::Interface(Camera *cam)
	: m_cam(cam) {

	DEB_CONSTRUCTOR();

	m_det_info = new DetInfoCtrlObj(cam);
	m_buffer = cam->getBufferCtrlObj();
	m_sync = new SyncCtrlObj(cam);
	m_bin = new BinCtrlObj(cam);
}

Interface::~Interface() {
	DEB_DESTRUCTOR();

	delete m_det_info;
	delete m_sync;
	delete m_bin;
}

void Interface::getCapList(CapList &cap_list) const {
	cap_list.push_back(HwCap(m_sync));
	cap_list.push_back(HwCap(m_det_info));
	cap_list.push_back(HwCap(m_buffer));
	cap_list.push_back(HwCap(m_bin));
}

void Interface::reset(ResetLevel reset_level) {
	DEB_MEMBER_FUNCT();
	DEB_PARAM() << DEB_VAR1(reset_level);

	m_cam->stopAcq();
	if (reset_level == HardReset){
	  DEB_TRACE() << "Performing camera hard reset"; 
	  m_cam->reset();
	}
}

void Interface::prepareAcq() {
	DEB_MEMBER_FUNCT();
	m_cam->prepareAcq();
}

void Interface::startAcq() {
	DEB_MEMBER_FUNCT();
	m_cam->startAcq();
}

void Interface::stopAcq() {
	DEB_MEMBER_FUNCT();
	m_cam->stopAcq();
}

void Interface::getStatus(StatusType& status) {
        DEB_MEMBER_FUNCT();
	DetectorStatus det_status;
	
	m_cam->getStatus(det_status);

	switch (det_status) {
	case RayonixHs::DETECTOR_STATUS_INTEGRATING:
	  status.acq = AcqRunning;
	  status.det = DetExposure;
	  break;
	case DETECTOR_STATUS_IDLE:
	  status.acq = AcqReady;
	  status.det = DetIdle;
	  break;
	case DETECTOR_STATUS_READOUT:
	  status.acq = AcqRunning;
	  status.det = DetReadout;
	  break;
	case DETECTOR_STATUS_LATENCY:
	  status.det = DetLatency;
	  break;
	case DETECTOR_STATUS_CONFIG:
	  status.acq = AcqConfig;
	  break;
	default:
	  status.acq = AcqFault;
	  status.det = DetFault;
	  break;
  }
  DEB_RETURN() << DEB_VAR1(status);
}

int Interface::getNbAcquiredFrames() {
	DEB_MEMBER_FUNCT();

   int aNbAcquiredFrames = 0;
	if (m_cam)
		aNbAcquiredFrames = m_cam->getNbAcquiredFrames();

	DEB_RETURN() << DEB_VAR1(aNbAcquiredFrames);
	return aNbAcquiredFrames;
}

int Interface::getNbHwAcquiredFrames() {
        DEB_MEMBER_FUNCT();    
	return getNbAcquiredFrames();
}


void Interface::setFrameMode(FrameMode mode){
        DEB_MEMBER_FUNCT();    
	m_cam->setFrameMode(mode);
}

void Interface::getFrameMode(FrameMode &mode){
        DEB_MEMBER_FUNCT();    
	m_cam->getFrameMode(mode);
}

void Interface::setTriggerSignalType(TriggerSignalType signal_type){
        DEB_MEMBER_FUNCT();    
	m_cam->setTriggerSignalType(signal_type);
}

void Interface::getTriggerSignalType(TriggerSignalType &signal_type){

        DEB_MEMBER_FUNCT();    
	m_cam->getTriggerSignalType(signal_type);
}

