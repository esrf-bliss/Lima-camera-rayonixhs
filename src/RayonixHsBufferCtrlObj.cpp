#include "HwFrameInfo.h"

#include "RayonixHsBufferCtrlObj.h"
#include "RayonixHsSyncCtrlObj.h"
#include "RayonixHsCamera.h"

using namespace lima;
using namespace lima::RayonixHs;

BufferCtrlObj::BufferCtrlObj(Camera *cam)
   : m_buffer_cb_mgr(m_buffer_alloc_mgr),
     m_buffer_ctrl_mgr(m_buffer_cb_mgr),
     m_exposing(false),
     m_cam(cam) {

   DEB_CONSTRUCTOR();
}

/** @brief method to set the frame dimension.
 */
void BufferCtrlObj::setFrameDim(const FrameDim& frame_dim)
{
   m_cam->setFrameDim(frame_dim);
}

/** @brief get the frame dimension
 */
void BufferCtrlObj::getFrameDim(FrameDim& frame_dim)
{
  m_cam->getFrameDim(frame_dim);
}

/** @brief set the number of buffer for memory allocation
 */
void BufferCtrlObj::setNbBuffers(int nb_buffers)
{
   //Rayonix detector library handles this automatically
}

/** @brief this should return the number of buffer allocated
 */
void BufferCtrlObj::getNbBuffers(int& nb_buffers)
{
   //Rayonix detector library handles this automatically and does not disclose
}

/** @brief this parameter set the number of frame concatenated in one buffer.
 */
void BufferCtrlObj::setNbConcatFrames(int nb_concat_frames)
{
  DEB_MEMBER_FUNCT();
  DEB_PARAM() << DEB_VAR1(nb_concat_frames);

  //Rayonix detector library always puts one and only one frame per buffer
  if(nb_concat_frames != 1)
    THROW_HW_ERROR(NotSupported) << "Not managed by this BufferCtrlObj";
}

void BufferCtrlObj::getNbConcatFrames(int& nb_concat_frames)
{
  //Rayonix detector library always puts one and only one frame per buffer
  DEB_MEMBER_FUNCT();
  nb_concat_frames = 1;
}

/** @brief this method should return the possible maximum 
 *  number of allocated frames.
 */
void BufferCtrlObj::getMaxNbBuffers(int& max_nb_buffers)
{
   //Rayonix detector library does not disclose
   DEB_MEMBER_FUNCT();
}

void* BufferCtrlObj::getBufferPtr(int,int)
{
  //Rayonix detector library does not keep track of which frames are in which buffers
  //(they are temporary ring buffers)
  DEB_MEMBER_FUNCT();
  return NULL;
}

void* BufferCtrlObj::getFramePtr(int)
{
  //Rayonix detector library does not keep track of which frames are in which buffers
  //(they are temporary ring buffers)
  DEB_MEMBER_FUNCT();
  return NULL;
}

void BufferCtrlObj::getStartTimestamp(Timestamp&)
{
  // not needed in your case
  DEB_MEMBER_FUNCT();
}

/** @brief get a frame from is acq_frame_nb
 */
void BufferCtrlObj::getFrameInfo(int acq_frame_nb, HwFrameInfoType& info)
{
  DEB_MEMBER_FUNCT();
  // in this method, you should send back the full frame info
  // or throw an exception if it's no more available
  // i.e:
  THROW_HW_ERROR(NotSupported) << "Frame info from frame number not implemented.";
}

/** @brief register frame callback.
    This method is called by the control layer.
    you should call HwFrameCallback::newFrameReady when a frame is acquired
*/
void BufferCtrlObj::registerFrameCallback(HwFrameCallback &frame_cb)
{
  // you should store this instance in this object
  //i.e:
  //m_callback = &frame_cb;
  DEB_MEMBER_FUNCT();
  m_buffer_ctrl_mgr.registerFrameCallback(frame_cb);
}

void BufferCtrlObj::unregisterFrameCallback(HwFrameCallback& frame_cb)
{
  DEB_MEMBER_FUNCT();
  m_buffer_ctrl_mgr.unregisterFrameCallback(frame_cb);
}

void BufferCtrlObj::frameReady(HwFrameInfoType &frame_info) {
  //DEB_MEMBER_FUNCT();
   //m_callback->newFrameReady(frame_info);
   m_buffer_cb_mgr.newFrameReady(frame_info);
}

#if 0
void BufferCtrlObj::prepareAcq() {
   DEB_MEMBER_FUNCT();

   m_cam->prepareAcq();
}

void BufferCtrlObj::startAcq() {
   DEB_MEMBER_FUNCT();

   m_cam->startAcq();
}
#endif
