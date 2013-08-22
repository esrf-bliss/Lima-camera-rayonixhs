#ifndef REMOTE_MODE_EMULATOR_H
#define REMOTE_MODE_EMULATOR_H

/*! \file RemoteModeEmulator.cpp

 \brief emulator of marccd remote mode for controlling Rayonix HS detectors

 */
#include "craydl.h"

#include "ConfigFile.h"

#include <boost/date_time.hpp>

#include <iostream> 
#include <iomanip> 
#include <memory> 
#include <vector> 
#include <typeinfo> 
#include <getopt.h>
#include <signal.h>
#include <stdarg.h>


//! \namespace craydl::marccd encapsulates symbols from the marccd libraries
namespace marccd {
   extern "C" {
//#include "application.h"
//#include "frame.h"
//#include "foreign_frame.h"
//#include "frame_math.h"
#include "slave_esrfds.h"
#include "task_macros.h"
#include "image.h"
      typedef enum {
	 READOUT_MODE_HIGH_SPEED,
	 READOUT_MODE_LOW_NOISE
      } readout_modes;
   }
}
#include "task_macros.h"


using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::map;

// All craydl classes, functions, etc, reside in the craydl namespace
namespace craydl {

class RemoteModeEmulator;

class IntegrateStatusCB : public VirtualKeyedStateChangeCallback
{
   public:
      IntegrateStatusCB(RemoteModeEmulator* rmep) : remote_mode_emulator_p_(rmep) {}
      ~IntegrateStatusCB() {}
      void StatusChanged() {RxLog(LOG_INFO) << "Status Changed!" << endl;}
      void StatusChanged(const std::string& name, const std::string& value) {RxLog(LOG_INFO) << "Status " << name << " changed to " << value << endl;}
      void StatusParameterChanged(const StatusParameter_t key, const std::string& value);
      void ParameterChanged() {RxLog(LOG_INFO) << "Parameter Changed!" << endl;}
      void ParameterChanged(const std::string& name, const std::string& value) {RxLog(LOG_INFO) << "Parameter " << name << " changed to " << value << endl;}

   private:
      RemoteModeEmulator* remote_mode_emulator_p_;
};

class AcquisitionCB : public VirtualFrameCallback
{
   public:
      AcquisitionCB(RxDetector& detector, RemoteModeEmulator* rmep = NULL) :
	detector_(detector),
	remote_mode_emulator_p_(rmep),
	series_(false),
	write_raw_frame_(false),
	write_corrected_frame_(false),
	frame_number_width_(4),
	filename_(""),
	filename_root_(""),
	raw_filename_root_(""),
	roi_(0,0,0,0),
        first_frame_(0) {}
      ~AcquisitionCB() {}
      void SequenceStarted();
      void SequenceEnded();
      void ExposureStarted(int frame_number) {}
      void ExposureEnded(int frame_number) {}
      void ReadoutStarted(int frame_number) {}
      void ReadoutEnded(int frame_number) {}
      void BackgroundFrameReady(RxFrame *frame_p);
      void RawFrameReady(int frame_number, RxFrame *frame_p);
      void FrameReady(int frame_number, RxFrame *frame_p);
      void FrameAborted(int frame_number) {RxLog(LOG_WARNING) << "CB: Frame " << frame_number << " aborted." << endl;}
      void FrameCompleted(int frame_number) {RxLog(LOG_DEBUG) << "CB: Frame " << frame_number << " completed." << endl;}
      void FrameError(int frame_number, const int error_code, const std::string& error_string) {RxLog(LOG_ERROR) << "CB: Frame " << frame_number << " reported error " << error_code << ":" << error_string << endl;}

      void set_series(const bool series) {
	 this->series_ = series;
      }

      void set_write_raw_frame(const bool doit = true) {
	 this->write_raw_frame_ = doit;
      }

      void set_write_corrected_frame(const bool doit = true) {
	 this->write_corrected_frame_ = doit;
      }

      void set_filename(const string &filename) {
	 filename_ = filename;
	 filename_root_.clear();
	 filename_suffix_.clear();
      }
      void set_raw_filename(const string &filename) {
	 raw_filename_ = filename;
	 raw_filename_root_.clear();
	 raw_filename_suffix_.clear();
      }
      void set_filename_generator(const std::string& raw_root, const std::string& root, int width, const std::string& suffix) {
	 set_filename("");
	 //filename_.clear();
	 raw_filename_root_ = raw_root;
	 filename_root_ = root;
	 filename_suffix_ = suffix;
	 frame_number_width_ = width;
      }
      void set_filename_generator(const std::string& root, int width, const std::string& suffix) {
	 set_filename("");
	 //filename_.clear();
	 raw_filename_root_.clear();
	 filename_root_ = root;
	 filename_suffix_ = suffix;
	 frame_number_width_ = width;
      }

      void set_default_meta_data(const ExperimentMetaData &meta_data)
      {
	 default_meta_data_ = meta_data;
      }

      void set_default_meta_data_increment(const ExperimentMetaData &meta_data)
      {
	 default_meta_data_increment_ = meta_data;
      }

      string get_background_filename() {
	 if (!filename_root_.empty()) {
	    std::ostringstream oss;
	    oss << std::setfill('_') << std::setw(frame_number_width_) << "back";
	    return filename_root_ + oss.str() + filename_suffix_;
	 }
	 else if (!filename_.empty()) {
	    return filename_;
	 }
	 return string("");
      }

      string get_raw_filename() {
	 return filename_;
      }

      string get_corrected_filename() {
	 return filename_;
      }

      string get_raw_filename(int frame_number) {
	 if (!raw_filename_root_.empty()) {
	    std::ostringstream oss;
	    oss << std::setfill('0') << std::setw(frame_number_width_) << frame_number;
	    return raw_filename_root_ + oss.str() + filename_suffix_;
	 }
	 else if (!raw_filename_.empty()) {
	    return raw_filename_;
	 }
	 return string("");
      }

      string get_corrected_filename(int frame_number) {
	 if (!filename_root_.empty()) {
	    std::ostringstream oss;
	    oss << std::setfill('0') << std::setw(frame_number_width_) << frame_number;
	    return filename_root_ + oss.str() + filename_suffix_;
	 }
	 else if (!filename_.empty()) {
	    return filename_;
	 }
	 return string("");
      }

      void set_destination_frame(RxFrame** frame_p) {
	 if (frame_p) {
	    destination_frame_pp_ = frame_p;
	 }
      }

      void set_first_frame(int first_frame) {
	 first_frame_ = first_frame;
      }


   private:
      RxDetector& detector_;
      RemoteModeEmulator* remote_mode_emulator_p_;
      bool series_;
      bool write_raw_frame_;
      bool write_corrected_frame_;
      int frame_number_width_;
      string filename_;
      string filename_root_;
      string filename_suffix_;
      string raw_filename_;
      string raw_filename_root_;
      string raw_filename_suffix_;
      Rect<int> roi_;
      int first_frame_;
      RxFrame** destination_frame_pp_;
      ExperimentMetaData default_meta_data_;
      ExperimentMetaData default_meta_data_increment_;

};

// Advance declaration
class RemoteCommandExecutor;

typedef bool (RemoteCommandExecutor::*RCPMethod) (const std::string&);

// Class to parse incoming command and execute code for that commmand
class RemoteCommandExecutor
{
   public:
      RemoteCommandExecutor(RxDetector &detector, RemoteModeEmulator& rmep, int& server_state);
      ~RemoteCommandExecutor();
      bool GetAndExecuteCommand();
      bool ParseAndExecuteCommand(const string &command);
      bool ParseRawCommand(const string &full_command, std::string& command, std::string& argument);
      bool null(const std::string& argument);
      bool get_size(const std::string& argument);
      bool get_size_bkg(const std::string& argument);
      bool set_size(const std::string& argument);
      bool get_readout_mode(const std::string& argument);
      bool set_readout_mode(const std::string& argument);
      bool get_bin(const std::string& argument);
      bool set_bin(const std::string& argument);
      bool get_stability(const std::string& argument);
      bool set_stability(const std::string& argument);
      bool get_frameshift(const std::string& argument);
      bool set_frameshift(const std::string& argument);
      bool get_preset(const std::string& argument);
      bool set_preset(const std::string& argument);
      bool get_roi(const std::string& argument);
      bool set_roi(const std::string& argument);
      bool get_thumbnail1(const std::string& argument);
      bool get_thumbnail2(const std::string& argument);
      bool set_thumbnail1(const std::string& argument);
      bool set_thumbnail2(const std::string& argument);
      bool shutter(const std::string& argument);
      bool start(const std::string& argument);
      bool start_bottomhalf();
      bool start_series_timed(const std::string& argument);
      bool start_series_triggered(const std::string& argument);
      bool readout(const std::string& argument);
      bool dezinger(const std::string& argument);
      bool dezinger_bottomhalf(RxFrame** frame_p);
      bool correct(const std::string& argument);
      bool correct_bottomhalf(RxFrame** frame_p);
      bool writefile(const std::string& argument);
      bool writefile_bottomhalf(RxFrame** frame_p, const std::string& filename);
      bool writethumbnail(const std::string& argument);
      bool header(const std::string& argument);
      bool abort(const std::string& argument);
      bool get_mode(const std::string& argument);
      bool get_state(const std::string& argument);
      bool is_state(const std::string& argument);
      bool end_automation(const std::string& argument);
      bool reboot(const std::string& argument);
      bool help(const std::string& argument);
   private:
      ReadoutMode_t DetectorReadoutMode(int server_readout_mode);
      int ServerReadoutMode(ReadoutMode_t detector_readout_mode);
   private:
      RxDetector &detector_;
      RemoteModeEmulator &remote_mode_emulator_;
      int &ServerState_;
      map<const string, RCPMethod> CommandMethod_;

      //RemoteEmulatorAcquistionCB frame_cb_;

};

class RemoteModeEmulator
{
   friend class RemoteCommandExecutor;
   friend class IntegrateStatusCB;
   friend class AcquisitionCB;
   public:
      RemoteModeEmulator(RxDetector &detector, const std::string& config_file = string(""));
      ~RemoteModeEmulator();

      void Start();

      bool Started();

      void End(bool force = false);

      void Listen(bool block = false);

      bool Listening();

      void StopListening();

      bool ClientConnected();

      string ConfigurationFilename() {return configFilename_;}

      int ServerState() { return ServerState_; }
      void SetServerState(int state)
      {
	 ServerState_ = state;
	 RxLog(LOG_DEBUG) << " RemoteCommandEmulator::SetServerState: ServerState_ is now " << boost::format("0x%06x") % ServerState_ << endl;
      }
      int SendState(int state)
      {
	 int result;
	 RxLog(LOG_INFO) << " RemoteCommandEmulator::SendState:  sending state " << boost::format("0x%06x") % state << endl;
	 {
	    boost::mutex::scoped_lock acq_lock(serverSendMutex_);
	    result = marccd::esrf_dserver_is_state (state);
	    serverSendCondition_.notify_all();
	 }
	 RxLog(LOG_VERBOSE) << " RemoteCommandEmulator::SendState:  SENT state " << boost::format("0x%06x") % state << endl;
	 return result;
      }

      //Send data to dserver over the socket
      int SendFromServer(const char *command, ...)
      {
	va_list   args;
	int result;

	va_start(args, command);
	result = marccd::esrf_dserver_send (command, args);
	va_end(args);

	RxLog(LOG_DEBUG) << " RemoteCommandEmulator::SendFromServer: " << command << args << endl;

	return result;
      }

   RxFrame* RawFrameP() { return frame_buffer_raw_p_; }
   RxFrame** RawFramePP() { return &frame_buffer_raw_p_; }

   RxFrame* CorrectedFrameP() { return frame_buffer_corrected_p_; }
   RxFrame** CorrectedFramePP() { return &frame_buffer_corrected_p_; }

   RxFrame* BackgroundFrameP() { return frame_buffer_background_p_; }
   RxFrame** BackgroundFramePP() { return &frame_buffer_background_p_; }

   RxFrame* ScratchFrameP() { return frame_buffer_scratch_p_; }
   RxFrame** ScratchFramePP() { return &frame_buffer_scratch_p_; }

   void SetRawFrame(RxFrame* const frame_p)
   {
      if (frame_buffer_raw_p_) {
	 delete frame_buffer_raw_p_;
      }
      frame_buffer_raw_p_ = frame_p;
      return ;
   }

   void SetCorrectedFrame(RxFrame* const frame_p)
   {
      if (frame_buffer_corrected_p_) {
	 delete frame_buffer_corrected_p_;
      }
      frame_buffer_corrected_p_ = frame_p;
      return ;
   }

   void SetBackgroundFrame(RxFrame* const frame_p)
   {
      if (frame_buffer_background_p_) {
	 delete frame_buffer_background_p_;
      }
      frame_buffer_background_p_ = frame_p;
      marccd::esrf_dserver_is_size_bkg(frame_buffer_background_p_->getNFast(), frame_buffer_background_p_->getNSlow());
      return ;
   }

   void SetScratchFrame(RxFrame* const frame_p)
   {
      if (frame_buffer_scratch_p_) {
	 delete frame_buffer_scratch_p_;
      }
      frame_buffer_scratch_p_ = frame_p;
      return ;
   }

   void SetFrame(RxFrame* storage_frame_p, RxFrame* const frame_p)
   {
      if (storage_frame_p) {
	 delete storage_frame_p;
      }
      storage_frame_p = frame_p;
      return ;
   }


   ExperimentMetaData base_frame_meta_data_;

   private:
      void OpenConfigurationFile(const std::string& config_file = string(""));
      void OpenLogFile(const std::string& filename = string(""));


      ConfigFile* configFile_;
      string configFilename_;

      RxDetector& detector_;
      
      bool started_;
      bool listening_;
      boost::thread listen_thread_;

      int ServerState_;
      int ServerErrorCondition_;

      /* thumbnail parameters */
      int ThumbnailType1_;
      int ThumbnailX1_;
      int ThumbnailY1_;
      int ThumbnailType2_;
      int ThumbnailX2_;
      int ThumbnailY2_;

      RemoteCommandExecutor* CommandExecutor_;
      //IntegrateStatusCB integrate_status_cb;
      IntegrateStatusCB* integrate_status_cb_p_;
      AcquisitionCB* AcqCB_p_;
      boost::mutex  serverSendMutex_;
      boost::condition_variable serverSendCondition_;
      boost::mutex  acquisitionStatusMutex_;
      boost::condition_variable acquisitionStatusCondition_;
      RxFrame* frame_buffer_raw_p_;
      RxFrame* frame_buffer_background_p_;
      RxFrame* frame_buffer_scratch_p_;
      RxFrame* frame_buffer_corrected_p_;
};

}

#endif // REMOTE_MODE_EMULATOR_H
