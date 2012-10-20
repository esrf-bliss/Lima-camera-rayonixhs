//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2011
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
#ifndef RAYONIXHSBUFFERCTRLOBJ_H
#define RAYONIXHSBUFFERCTRLOBJ_H

#include "HwBufferCtrlObj.h"
#include "HwBufferMgr.h"

namespace lima {
namespace RayonixHs {

class Camera;
class SyncCtrlObj;
class Interface;

class BufferCtrlObj: public HwBufferCtrlObj, public HwFrameCallbackGen {
      friend class Interface;
      
      DEB_CLASS_NAMESPC(DebModCamera,"BufferCtrlObj","RayonixHs");

   public:
      BufferCtrlObj(Camera *cam);
      
      void setFrameDim(const FrameDim& frame_dim);
      void getFrameDim(FrameDim& frame_dim);
      
      void setNbBuffers(int nb_buffers);
      void getNbBuffers(int& nb_buffers);
      
      void setNbConcatFrames(int nb_concat_frames);
      void getNbConcatFrames(int& nb_concat_frames);
      
      void getMaxNbBuffers(int& max_nb_buffers);
      
      void* getBufferPtr(int,int);
      
      void* getFramePtr(int);
      
      void getStartTimestamp(Timestamp&);
      
      void getFrameInfo(int acq_frame_nb, HwFrameInfoType& info);
      
      void registerFrameCallback(HwFrameCallback &frame_cb);
      void unregisterFrameCallback(HwFrameCallback &frame_cb);

      void frameReady(HwFrameInfoType &info) { newFrameReady(info); }

   private:
      SyncCtrlObj* m_sync;
      bool m_exposing;
      Camera *m_cam;
      
      HwFrameCallback *m_callback;
};

} //namespace RayonixHs
} //namespace lima

#endif
