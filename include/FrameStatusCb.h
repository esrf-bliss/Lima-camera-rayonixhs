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
#ifndef FRAMESTATUSCB_H
#define FRAMESTATUSCB_H

#include "craydl_c.h"
#include "lima/Debug.h"

namespace lima {
namespace RayonixHs {

class Camera;

class FrameStatusCb {
  DEB_CLASS_NAMESPC(DebModCamera, "Camera", "RayonixHs");
    public:
        FrameStatusCb(Camera *cam, volatile bool &acquiring);

        ~FrameStatusCb();

        void RawFrameReady(int frame_number, Craydl_RxFrame_t rx_frame);

        void BackgroundFrameReady(const Craydl_RxFrame_t rx_frame);

        void FrameReady(int frame_number, const Craydl_RxFrame_t rx_frame);

        void FrameAborted(int frame_number);

        void FrameError(int frame_number, const Craydl_RxFrame_t rx_frame, int error_code, const std::string& error_string);

        void SequenceStarted();

        void SequenceEnded();
	
	void ExposureStarted(int);
	void ExposureEnded(int);
	void ReadoutStarted(int);
	void ReadoutEnded(int);
	void FrameCompleted(int);

	void resetFrameCounts();

	int frameCountRaw() const;
	int frameCountBackground() const;
	int frameCountCorrected() const;
	
    private:
    	Craydl_FrameCallback_t m_cbk;

    	Camera *m_cam;
    	volatile int m_RawFramesRcvd;
	volatile int m_BgFramesRcvd;
	volatile int m_CorrFramesRcvd;
	
	volatile bool &m_acquiring;
};

} //namespace RayonxHs
} //namespace lima

#endif //FRAMESTATUSCB_H
