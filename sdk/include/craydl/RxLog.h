#ifndef RX_LOG_H
#define RX_LOG_H

/*! \file RxLog.h
 
  \brief Logging utility for the craydl System
  
 */

#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <set>

#include <boost/date_time.hpp>
#include <boost/date_time/time_facet.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

#include "RxUtils.h"

namespace craydl {

//using namespace boost::gregorian;

extern std::ostream dev_null;

typedef boost::posix_time::ptime timestamp_t;

#define RxLog(severity)	Log(severity)()

//! \brief  Logging Levels
enum LogLevel {LOG_TIMING, LOG_SYSTEM, LOG_FATAL, LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_VERBOSE, LOG_DEBUG, LOG_TRACE};

inline LogLevel& operator++(LogLevel& ll, int) // postfix ++
{
   if (ll == LOG_TRACE) return ll = LOG_TRACE; // truncate
   int temp = ll; //convert to an int
   return ll = static_cast<LogLevel>(++temp);
}

inline LogLevel& operator--(LogLevel& ll, int) // postfix --
{
   if (ll == LOG_SYSTEM) return ll = LOG_SYSTEM; // truncate
   int temp = ll; //convert to an int
   return ll = static_cast<LogLevel>(--temp);
}

inline LogLevel& operator+=(LogLevel& ll, int rhs) // +=
{
     int temp = ll; //convert to an int
     temp += rhs;
     if (temp <= LOG_SYSTEM) return ll = LOG_SYSTEM;
     if (temp >= LOG_TRACE) return ll = LOG_TRACE;
     return ll = static_cast<LogLevel>(temp);
}

inline LogLevel& operator-=(LogLevel& ll, int rhs) // -=
{
     int temp = ll; //convert to an int
     temp -= rhs;
     if (temp <= LOG_SYSTEM) return ll = LOG_SYSTEM;
     if (temp >= LOG_TRACE) return ll = LOG_TRACE;
     return ll = static_cast<LogLevel>(temp);
}

/*! \class Log
 * \brief The logging class
 *
 * The client needs to do these things:
 * - If desired, set logging level (default is LOG_WARNING)
 *   \code Log::ReportingLevel() = LOG_DEBUG; \endcode
 * - or level can also be set with a string)
 *   \code Log::ReportingLevel(string("DEBUG")); \endcode
 * - Log as needed using RxLog(level) macro or direct call.
 *   \code RxLog(LOG_DEBUG) << "This is a bug!" << std::endl; \endcode
 *   or
 *   \code Log(LOG_DEBUG)() << "This is a bug!" << std::endl; \endcode
 * - If logging to file, it is necesary to specifically pass a filename to Log
 *   \code Log::File(filename); \endcode
 */

template <class T>
class LogTemplate
{
   public:
      LogTemplate(LogLevel messageLevel = LOG_WARNING){LogTemplate<T>::messageLevel_ = messageLevel;}
      virtual ~LogTemplate();
      //! \brief The () operator implements the logging stream \code Log(LOG_WARNING)() << "a message" << std::endl; \endcode
      virtual std::ostringstream& operator()();
      static LogLevel& ReportingLevel(const std::string& level = std::string(""));
      static bool& ShowThread();

   private:
      LogTemplate(const LogTemplate&);
      LogTemplate& operator =(const LogTemplate&);
      static std::string ToString(LogLevel level);
      static LogLevel FromString(std::string level_string);
      std::string NowTime();

   protected:
      LogLevel messageLevel_;

   private:
      std::ostringstream message_;
      //boost::mutex messageMutex_;
      static bool showThread_;
};


template <class T>
LogTemplate<T>::~LogTemplate()
{
   if ( (messageLevel_ <= LogTemplate<T>::ReportingLevel() && messageLevel_ != LOG_TIMING) 
     || ((LogTemplate<T>::ReportingLevel() == LOG_TIMING) && (messageLevel_ <= LOG_WARNING ||  messageLevel_ == LOG_TIMING))) {
      //fprintf(stderr, "%s", message_.str().c_str());
      //fflush(stderr);
      T::Output(message_.str());
   }
}

template <class T>
std::ostringstream& LogTemplate<T>::operator()()
{
   //Build must be atomic - but why? message is instantiated for each object
   //boost::mutex::scoped_lock lock(messageMutex_);
   if (ShowThread()) this->message_ << boost::this_thread::get_id() << " ";
   //}
   //this->message_ << NowTime();
   //this->message_ << " [" << std::left << std::setw(8) << ToString(this->messageLevel_) << "] ";
   //this->message_ << " <m:" << std::left << std::setw(8) << craydl::RxMemory() << "> ";
   this->message_ << NowTime() << ","<< "[" << std::left << std::setw(8) << ToString(this->messageLevel_) << "]," << "<m:" << std::left << std::setw(8) << craydl::RxMemory() << ">,";
   return this->message_;
}

template <class T>
std::string LogTemplate<T>::ToString(LogLevel level)
{
   switch(level) {
      case LOG_TRACE:
	 return "TRACE";
	 break;
      case LOG_DEBUG:
	 return "DEBUG";
	 break;
      case LOG_VERBOSE:
	 return "VERBOSE";
	 break;
      case LOG_INFO:
	 return "INFO";
	 break;
      case LOG_WARNING:
	 return "WARNING";
	 break;
      case LOG_ERROR:
	 return "ERROR";
	 break;
      case LOG_FATAL:
	 return "FATAL";
	 break;
      case LOG_SYSTEM:
	 return "SYSTEM";
	 break;
      case LOG_TIMING:
	 return "TIMING";
	 break;
      default:
	 return "UNKOWN";
	 break;
   }
}

template <class T>
LogLevel LogTemplate<T>::FromString(std::string level_string)
{
   int level;
   for (level = LOG_TRACE; level >= LOG_SYSTEM; level--) {
      if (level_string == LogTemplate<T>::ToString((LogLevel)level)) break;
   }

   return (LogLevel)level;
}

template <class T>
LogLevel& LogTemplate<T>::ReportingLevel(const std::string& level)
{
   static LogLevel reportingLevel_ = LOG_WARNING;
   if (!level.empty()) {
      // Set level before reporting
      reportingLevel_ = LogTemplate<T>::FromString(level);
   }
   // If reporting level is DEBUG or higher, then print a thread id on each line
   if (reportingLevel_ >= LOG_DEBUG) ShowThread() = true;
   return reportingLevel_;
}

template <class T>
bool& LogTemplate<T>::ShowThread()
{
   return showThread_;
}


template <class T>
std::string LogTemplate<T>::NowTime()
{
   bool high_resolution_time = true;
   std::ostringstream oss;
   boost::local_time::local_time_facet* output_facet = new boost::local_time::local_time_facet();
   oss.imbue(std::locale(std::locale::classic(), output_facet));

   boost::posix_time::ptime call_time;
   if (high_resolution_time) {
      call_time = boost::posix_time::microsec_clock::local_time();
      output_facet->format("%Y-%m-$d %H:%M::%F");
   }
   else {
      call_time = boost::posix_time::second_clock::local_time();
      output_facet->format("%Y-%m-$d %H:%M::%S");
   }

   //oss.str("");
   //oss << to_iso_extended_string(call_time);
   oss << call_time;
   return oss.str();
}

class OutputLogToFile
{
   public:
      static FILE*& Stream();
      static void Output(const std::string& msg);
      static void File(std::string filename);
      static std::string Filename();
      static std::string Filename(const std::string* filename = NULL);
   public:
      //static boost::mutex fileMutex_;
};

inline FILE*& OutputLogToFile::Stream()
{
   static FILE* pStream = stderr;
   return pStream;
}
   
inline void OutputLogToFile::Output(const std::string& msg)
{             
   //boost::mutex::scoped_lock lock(OutputLogToFile::fileMutex_);
   FILE* pStream = Stream();
   if (!pStream)
      return;
   //OutputLogToFile::fileMutex_.lock();
   fprintf(pStream, "%s", msg.c_str());
   fflush(pStream);
   //OutputLogToFile::fileMutex_.lock();
   fprintf(stderr, "%s", index(msg.c_str(), '['));
   fflush(stderr);
}          

inline std::string OutputLogToFile::Filename(const std::string* filename)
{
   static std::string filename_;
   if (!filename) return filename_;
   filename_ = *filename;
   try {
      //Canonical must wait for boost v3
      //filename_ = boost::filesystem::canonical(filename_).string();
      filename_ = boost::filesystem::absolute(filename_).string();
   }
   catch (...) {
      filename_ = boost::filesystem::absolute(filename_).string();
   }

   return filename_;
}

inline void OutputLogToFile::File(std::string filename)
{
   //boost::mutex::scoped_lock lock(OutputLogToFile::fileMutex_);
   static FILE *f = NULL;
   if (f) fclose(f);
   f = fopen(filename.c_str(), "a");
   if  (f) {
      boost::filesystem::path p = boost::filesystem::absolute(filename);
      Filename(&p.string());
   }
   else {
      std::string empty("");
      Filename(&empty);
   }
   Stream() = f;
}
class Log : public LogTemplate<OutputLogToFile>
{
   public:
      Log(LogLevel messageLevel = LOG_WARNING){LogTemplate<OutputLogToFile>::messageLevel_ = messageLevel;}
      static FILE*& Stream() { return OutputLogToFile::Stream();}
      static void File(std::string filename) { OutputLogToFile::File(filename);}
      //static void File(std::string filename) { static FILE *f = NULL; if (f) fclose(f); f = fopen(filename.c_str(), "a"); Stream() = f; }
      static std::string Filename(const std::string* filename = NULL) { return OutputLogToFile::Filename(filename);}
};



class ScopedTimerLog
{
   public:
      ScopedTimerLog(std::string message, LogLevel log_level = LOG_TIMING);
      ~ScopedTimerLog();

      void LapTime(std::string message = std::string(""));

      void ElapsedTime(std::string message = std::string(""));

   private:
      std::string message_;
      LogLevel log_level_;
      timestamp_t uninitialized_time_;
      timestamp_t start_time_;
      timestamp_t lap_start_time_;
};

inline ScopedTimerLog::ScopedTimerLog(std::string message, LogLevel log_level) : message_(message), log_level_(log_level)
{
   start_time_ = boost::posix_time::microsec_clock::local_time();
}

inline ScopedTimerLog::~ScopedTimerLog()
{
   timestamp_t end_time = boost::posix_time::microsec_clock::local_time();
   if (lap_start_time_ != uninitialized_time_) {
      RxLog(log_level_) << message_ << " LASTLAP TIME " << end_time - lap_start_time_ <<  std::endl;
   }
   RxLog(log_level_) << message_ << " ELAPSED TIME " << end_time - start_time_ <<  std::endl;
}

inline void ScopedTimerLog::LapTime(std::string message)
{
   timestamp_t lap_start_time = boost::posix_time::microsec_clock::local_time();
   if (lap_start_time_ == uninitialized_time_) {
      lap_start_time_ = start_time_;
   }
   RxLog(log_level_) << message_ << " " << message << " " << lap_start_time - lap_start_time_ <<  std::endl;
   lap_start_time_ = lap_start_time;
}

inline void ScopedTimerLog::ElapsedTime(std::string message)
{
   timestamp_t end_time = boost::posix_time::microsec_clock::local_time();
   RxLog(log_level_) << message_ << " " << message << " " << end_time - start_time_ <<  std::endl;
}

typedef boost::posix_time::ptime RxTimestamp_t;
typedef boost::posix_time::time_duration RxTimeDuration_t;

class TimingLogger
{
   public:
      TimingLogger();
      ~TimingLogger();
      
      void RecordTimestamp(unsigned int index, const std::string& label, const RxTimestamp_t &timestamp, std::map<std::string,std::vector<RxTimestamp_t> >& timestamp_map);

      void RecordCycleTimestamp(unsigned int index, const std::string label, RxTimestamp_t timestamp);

      void RecordTimestamp(unsigned int index, const std::string label, RxTimestamp_t timestamp);

      void RecordElapsedTime(unsigned int index, const std::string label, RxTimeDuration_t time_usec);

   private:

      void PrintAllTimesLabels();

      void PrintAllTimesRecord(int record);

      void PrintAllTimes();

      void PrintCycleTimeLabels();

      void PrintCycleTimeRecord(int record);

      void PrintAllCycleTimes();

      void PrintElapsedTimeLabels();

      void PrintElapsedTimeRecord(int record);

      void PrintAllElapsedTimes();

      void CheckFull(int index);

      std::set<std::string> labels_;
      std::map<std::string,std::vector<RxTimestamp_t> > timestamps_;
      std::map<std::string,std::vector<RxTimestamp_t> > cycle_timestamps_;
      std::map<std::string,std::vector<RxTimeDuration_t> > elapsed_times_;
      int base_;
      bool active_;
      boost::recursive_mutex recordMutex_;
};

const size_t MaxLogSize = 1000;

inline TimingLogger::TimingLogger() :
   base_(0),
   active_(true)
{
}

inline TimingLogger::~TimingLogger()
{
   RxLog(LOG_TRACE) << "~TimingLogger()" << std::endl;

   //PrintAllTimestamps();
   //PrintAllElapsedTimes();
   //PrintAllCycleTimes();
   PrintAllTimes();

   // Wait for all threads to be done with Mutex before destroying
   //boost::recursive_mutex::scoped_lock lock(recordMutex_);
   //boost::recursive_mutex::scoped_lock unlock(recordMutex_);

}

inline void TimingLogger::CheckFull(int index)
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!labels_.empty()) {
      if (timestamps_[*labels_.begin()].size() >= MaxLogSize 
       || cycle_timestamps_[*labels_.begin()].size() >= MaxLogSize 
       || elapsed_times_[*labels_.begin()].size() >= MaxLogSize) {
	 PrintAllTimes();
	 //std::set<std::string> labels_;
	 for (std::set<std::string>::iterator label = labels_.begin(); label != labels_.end(); ++label) {
	    timestamps_[*label].clear();
	    cycle_timestamps_[*label].clear();
	    elapsed_times_[*label].clear();
	 }
	 base_ = index;
	 // For now, the resetting base method is dangerous because later calls to Record.. may have index lower than base
	 active_ = false;
      }
   }
}

inline void TimingLogger::RecordTimestamp(unsigned int index, const std::string& label, const RxTimestamp_t &timestamp, std::map<std::string,std::vector<RxTimestamp_t> >& timestamp_map)
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   RxLog(LOG_TRACE) << "RecordTimestamp(" << index << ", " << label << ", " << timestamp << ")" << std::endl;
   CheckFull(index);
   int record = index-base_;
   if (record < 0) return;
   labels_.insert(label);
   if ((size_t)record+1 > timestamp_map[label].size()) timestamp_map[label].resize(record+1);
   timestamp_map[label][record] = timestamp;

   RxLog(LOG_TRACE) << "RecordTimestamp(" << index << ", " << label << ", " << timestamp << "): " << timestamp_map[label][record] << std::endl;

}

inline void TimingLogger::RecordCycleTimestamp(unsigned int index, const std::string label, RxTimestamp_t timestamp)
{
   RecordTimestamp(index, label, timestamp, cycle_timestamps_);
}

inline void TimingLogger::RecordTimestamp(unsigned int index, const std::string label, RxTimestamp_t timestamp)
{
   RecordTimestamp(index, label, timestamp, timestamps_);
}

inline void TimingLogger::RecordElapsedTime(unsigned int index, const std::string label, RxTimeDuration_t time_usec)
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   RxLog(LOG_TRACE) << "RecordElapsedTime(" << index << ", " << label << ", " << time_usec << ")" << std::endl;
   CheckFull(index);
   int record = index-base_;
   if (record < 0) return;
   labels_.insert(label);
   if ((size_t)record+1 > elapsed_times_[label].size()) elapsed_times_[label].resize(record+1);
   elapsed_times_[label][record] = time_usec;

   RxLog(LOG_TRACE) << "RecordElapsedTime(" << index << ", " << label << ", " << time_usec << "): " << elapsed_times_[label][record] << std::endl;
}

inline void TimingLogger::PrintAllTimesLabels()
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   std::ostringstream temp;
   temp << "TIMING(complete summary),Frame";
   for (std::map<std::string,std::vector<RxTimestamp_t> >::const_iterator ti = cycle_timestamps_.begin(); ti != cycle_timestamps_.end(); ++ti) {
      temp << "," << ti->first;
   }
   for (std::map<std::string,std::vector<RxTimeDuration_t> >::const_iterator ti = elapsed_times_.begin(); ti != elapsed_times_.end(); ++ti) {
      temp << "," << ti->first;
   }
   for (std::map<std::string,std::vector<RxTimestamp_t> >::const_iterator ti = timestamps_.begin(); ti != timestamps_.end(); ++ti) {
      temp << "," << ti->first;
   }
   RxLog(LOG_TIMING) << temp.str() << std::endl;
}

inline void TimingLogger::PrintAllTimesRecord(int record)
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   std::ostringstream temp;
   temp << "TIMING(complete summary)," << record+base_;
   for (std::map<std::string,std::vector<RxTimestamp_t> >::const_iterator ti = cycle_timestamps_.begin(); ti != cycle_timestamps_.end(); ++ti) {
      if (record != 0) {
	 if (ti->second.size() > (size_t)record) {
	    temp << "," << (ti->second[record]-ti->second[record-1]).total_microseconds()/1.0E6;
	 }
	 else {
	    temp << ",";
	 }
      }
      else {
	 temp << ",";
      }
   }
   for (std::map<std::string,std::vector<RxTimeDuration_t> >::const_iterator ti = elapsed_times_.begin(); ti != elapsed_times_.end(); ++ti) {
      if (ti->second.size() > (size_t)record) {
	 temp << "," << ti->second[record].total_microseconds()/1.0E6;
      }
      else {
	 temp << ",";
      }
   }
   for (std::map<std::string,std::vector<RxTimestamp_t> >::const_iterator ti = timestamps_.begin(); ti != timestamps_.end(); ++ti) {
      if (ti->second.size() > (size_t)record) {
	 temp << "," << ti->second[record];
      }
      else {
	 temp << ",";
      }
   }
   RxLog(LOG_TIMING) << temp.str() << std::endl;
}

inline void TimingLogger::PrintAllTimes()
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   int n_times = 0;
   if (!elapsed_times_.empty()) {
      n_times = elapsed_times_.begin()->second.size();
   }
   if (!timestamps_.empty()) {
      n_times = std::max(n_times,(int)timestamps_.begin()->second.size());
   }
   if (!cycle_timestamps_.empty()) {
      n_times = std::max(n_times,(int)cycle_timestamps_.begin()->second.size());
   }
   RxLog(LOG_DEBUG) << "There are " << n_times << " TimeLog records to print" << std::endl;
   if (n_times > 0) {
      PrintAllTimesLabels();
      for (int record = 0; record < n_times; ++record) {
	 PrintAllTimesRecord(record);
      }
   }
}

inline void TimingLogger::PrintCycleTimeLabels()
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   std::ostringstream temp;
   temp << "TIMING(cycle summary),Frame";
   for (std::map<std::string,std::vector<RxTimestamp_t> >::const_iterator ti = cycle_timestamps_.begin(); ti != cycle_timestamps_.end(); ++ti) {
      temp << "," << ti->first;
   }
   RxLog(LOG_TIMING) << temp.str() << std::endl;
}

inline void TimingLogger::PrintCycleTimeRecord(int record)
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   std::ostringstream temp;
   temp << "TIMING(cycle summary)," << record+base_;
   for (std::map<std::string,std::vector<RxTimestamp_t> >::const_iterator ti = cycle_timestamps_.begin(); ti != cycle_timestamps_.end(); ++ti) {
      if (record != 0) {
	 temp << "," << (ti->second[record]-ti->second[record-1]).total_microseconds()/1.0E6;
      }
      else {
	 temp << ",";
      }
   }
   RxLog(LOG_TIMING) << temp.str() << std::endl;
}

inline void TimingLogger::PrintAllCycleTimes()
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   int n_times = cycle_timestamps_.begin()->second.size();
   if (n_times > 1) {
      PrintCycleTimeLabels();
      for (int record = 1; record < n_times; ++record) {
	 PrintCycleTimeRecord(record);
      }
   }
}

inline void TimingLogger::PrintElapsedTimeLabels()
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   std::ostringstream temp;
   temp << "TIMING(summary),Frame";
   for (std::map<std::string,std::vector<RxTimeDuration_t> >::const_iterator ti = elapsed_times_.begin(); ti != elapsed_times_.end(); ++ti) {
      temp << "," << ti->first;
   }
   RxLog(LOG_TIMING) << temp.str() << std::endl;
}
inline void TimingLogger::PrintElapsedTimeRecord(int record)
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   std::ostringstream temp;
   temp << "TIMING(summary)," << record+base_;
   for (std::map<std::string,std::vector<RxTimeDuration_t> >::const_iterator ti = elapsed_times_.begin(); ti != elapsed_times_.end(); ++ti) {
      temp << "," << ti->second[record].total_microseconds()/1.0E6;
   }
   RxLog(LOG_TIMING) << temp.str() << std::endl;
}

inline void TimingLogger::PrintAllElapsedTimes()
{
   boost::recursive_mutex::scoped_lock lock(recordMutex_);
   if (!active_) return;
   int n_times = elapsed_times_.begin()->second.size();
   if (n_times > 0) {
      PrintElapsedTimeLabels();
      for (int record = 0; record < n_times; ++record) {
	 PrintElapsedTimeRecord(record);
      }
   }
}

template <class T>
bool LogTemplate<T>::showThread_ = false;
template 
bool LogTemplate<OutputLogToFile>::showThread_;

} // namespace craydl

#endif	// RX_LOG_H
