//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2014
// European Synchrotron Radiation Facility
// BP 220, Grenoble 38043
// FRANCE
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//###########################################################################
#ifndef RAYONIXHS_H
#define RAYONIXHS_H

//#include <ostream>

#include "Debug.h"
#include "HwMaxImageSizeCallback.h"
#include "HwInterface.h"
#include "HwBufferMgr.h"
#include "SizeUtils.h"

#include "craydl.h"
#include "FrameStatusCb.h"
#include "RayonixHsSyncCtrlObj.h"

namespace lima {
namespace RayonixHs {

enum DetectorStatus {
   DETECTOR_STATUS_IDLE,
   DETECTOR_STATUS_INTEGRATING,
   DETECTOR_STATUS_READOUT,
   DETECTOR_STATUS_LATENCY,
   DETECTOR_STATUS_CONFIG,
   DETECTOR_STATUS_FAULT
};

 enum FrameMode {
   SINGLE,
   FAST_TRANSFER
 };

 enum TriggerSignalType {
   UNKNOWN, 
   NONE,  
   EXTENDED, 
   OPTO,  
   OPTO_INVERTED,  
   CMOS, 
   CMOS_PULLDOWN,  
   CMOS_PULLUP,  
   CMOS_PULLDOWN_INVERTED,  
   CMOS_PULLUP_INVERTED,  
   SOFTWARE   
};


class Camera : public HwMaxImageSizeCallbackGen {
   DEB_CLASS_NAMESPC(DebModCamera, "Camera", "RayonixHs");
   friend class Interface;
   friend class FrameStatusCb;

	public:
		Camera();
		~Camera();

		void getDetectorModel(std::string &model);
		void getDetectorType(std::string &model);
		
		void getStatus(DetectorStatus &status);

		void getMaxImageSize(Size& max_image_size);
	        void getPixelSize(double &x, double &y);

		void reset();

		void prepareAcq();
		void startAcq();
		void stopAcq();

		void getTrigMode(TrigMode &mode);
		void setTrigMode(TrigMode mode);
		bool checkTrigMode(TrigMode mode);

		void getImageType(ImageType &type);
		void setImageType(ImageType type);

		void setNbFrames(int nb_frames);
		void getNbFrames(int& nb_frames);
		int getNbAcquiredFrames();

		void setExpTime(double exp_time);
		void getExpTime(double& exp_time);

		void setLatTime(double lat_time);
		void getLatTime(double& lat_time);

		void setBin(const Bin& bin);
		void getBin(Bin& bin);
		void checkBin(Bin& bin);

		void setRoi(const Roi& roi);
		void getRoi(Roi& roi);
		void checkRoi(const Roi& set_roi, Roi &hw_roi);

		void setFrameDim(const FrameDim& frame_dim);
		void getFrameDim(FrameDim& frame_dim);

		HwBufferCtrlObj* getBufferCtrlObj();

		// Specific Rayonix interface for configuration
		void setFrameMode(FrameMode mode);
		void getFrameMode(FrameMode &mode);
		void setTriggerSignalType(TriggerSignalType signal_type);
		void getTriggerSignalType(TriggerSignalType &signal_type);

	private:
		void init();
		void setStatus(DetectorStatus status, bool force=false);

		SoftBufferCtrlObj m_buffer_ctrl_obj;
		
		FrameDim m_frame_dim;

		double m_exp_time;
		double m_lat_time;
		double m_int_time;

		int m_nb_frames;
		TrigMode m_trig_mode;
		Size m_max_image_size;

		DetectorStatus m_status;

		FrameStatusCb *m_frame_status_cb;
		Mutex m_mutex;
		std::map<int,HwFrameInfoType> m_pending_frames;
		int m_expected_frame_nb;

		craydl::RxDetector *m_rx_detector;
		FrameMode m_frame_mode;
		TriggerSignalType m_trig_signal_type;

		volatile bool m_int_trig_mult_started;
		volatile bool m_acquiring;

		void frameReady(const craydl::RxFrame *pFrame);
};


//LIBRAYONIXHS_API std::ostream& operator <<(std::ostream& os, Camera& simu);

} //namespace rayonixhs
} // namespace lima

#endif // RAYONIXHS_H
