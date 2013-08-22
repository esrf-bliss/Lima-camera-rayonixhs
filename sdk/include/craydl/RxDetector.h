#ifndef RX_DETECTOR_H
#define RX_DETECTOR_H

/*! \file RxDetector.h

 \brief declaration of the RxDetector Class

 */

#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <cmath>
#include <iterator>
#include <set>

#include <boost/thread.hpp>  
#include <boost/date_time.hpp>  
#include <boost/bind.hpp>
#include <boost/signals2.hpp>


#include "SIVCamDLLInterface.h"
#include "RxTransformation.h"
#include "RxFrame.h"

// Advance declarations
class CMainApp;

namespace craydl {

// Advance declarations
class Chameleon;
class ConfigFile;
class RxDetector;
class RxFrame;
class FrameMetaData;
class RxFrameCorrection;
class RxFrameCorrectionFilenameGenerator;
class SpectralFrameCB;
class ExperimentMetaData;
class VStatusFlag;

// Constants

//! Constants indicating severity of exception raised
const int RX_EXCEPTION_TYPE_NONE = 0;
const int RX_EXCEPTION_TYPE_WARNING = 1;
const int RX_EXCEPTION_TYPE_ERROR = 2;
const int RX_EXCEPTION_TYPE_FATAL = 3;

//! Constants indicating which exception raised
const int RX_EXCEPTION_NONE = 0;
const int RX_EXCEPTION_ERROR = 1;
const int RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED = 2;
const int RX_EXCEPTION_TIMEOUT = 3;
const int RX_EXCEPTION_UNUSABLE_POINTER = 4;
const int RX_EXCEPTION_COM_ERROR = 5;
const int RX_EXCEPTION_DMA_ACTIVE = 6;
const int RX_EXCEPTION_DMA_NOT_ACTIVE = 7;
const int RX_EXCEPTION_RETRIES_EXHAUSTED = 8;
const int RX_EXCEPTION_FILE_NOT_FOUND = 9;
const int RX_EXCEPTION_NO_DRIVERS_INSTALLED = 10;
const int RX_EXCEPTION_DMA_THREAD_FAILED = 11;
const int RX_EXCEPTION_DEINTERLACE_THREAD_FAILED = 12;
const int RX_EXCEPTION_MEMORY_ALLOCATION_FAILED = 13;
const int RX_EXCEPTION_INVALID_DEINTERLACE_MODE = 14;
const int RX_EXCEPTION_INVALID_PARAMETER_OFFSET = 15;
const int RX_EXCEPTION_INVALID_CAMERA_DB_INDEX = 16;
const int RX_EXCEPTION_MEDIA_TYPE_NOT_SELECTABLE = 17;
const int RX_EXCEPTION_MEDIA_TYPE_INVALID = 18;
const int RX_EXCEPTION_STRING_TOO_LONG = 19;
const int RX_EXCEPTION_NEGATIVE_RESPONSE = 20;
const int RX_EXCEPTION_FUNCTION_UNSUPPORTED = 21;
const int RX_EXCEPTION_UNSUPPORTED_RECORD_TYPE = 22;
const int RX_EXCEPTION_FRAMING_OVERRUN = 23;
const int RX_EXCEPTION_FILE_OPEN_ERROR = 24;
const int RX_EXCEPTION_MODE_INVALID = 25;
const int RX_EXCEPTION_NO_PLUGIN_FOUND = 26;
const int RX_EXCEPTION_DEVICE_ALREADY_OPEN = 27;
const int RX_EXCEPTION_DEVICE_NOT_OPEN = 28;
const int RX_EXCEPTION_OPEN_DEVICE_FAILED = 29;
const int RX_EXCEPTION_PARAMETER_NOT_VALID = 30;
const int RX_EXCEPTION_FRAME_CORRECTION_FAILED = 31;
const int RX_EXCEPTION_RESOURCE_ALLOCATION_FAILED = 32;
const int RX_EXCEPTION_FRAME_OBJECT_NOT_FOUND = 33;
const int RX_EXCEPTION_FRAME_DROPPED = 34;
const int RX_EXCEPTION_FRAME_CORRUPTED = 35;
const int RX_EXCEPTION_FRAME_INCOMPATIBLE = 36;

enum RxDataType
{
   TYPE_BOOL, TYPE_INT, TYPE_FLOAT, TYPE_STRING
};

enum RxFrameAcquisitionType
{
   ACQUIRE_DARK,
   ACQUIRE_LIGHT,
   ACQUIRE_BIAS,
   ACQUIRE_EXTERNAL_TRIGGER,
   ACQUIRE_TDI_EXTERNAL,
   ACQUIRE_TDI_INTERNAL,
   ACQUIRE_TEST,
   ACQUIRE_LINEARITY
};

enum ReadoutMode_t {RM_Unknown, RM_Standard, RM_HighGain, RM_LowNoise, RM_HDR};

enum SequenceMode_t{SM_SingleFrameTimed, SM_SingleFrameTriggered, SM_FrameTransferTimed, SM_FrameTransferTriggered, SM_Bulb };
enum SequenceGate_t {SG_None, SG_Start, SG_Gate};

#if 0
enum TriggerMode_t { TRIGGER_MODE_NONE, TRIGGER_MODE_TRANSFER, TRIGGER_MODE_TRANSFER_READ, TRIGGER_MODE_TRANSFER_INTEGRATE, TRIGGER_MODE_TRANSFER_INTEGRATE_READ, TRIGGER_MODE_INTEGRATE};
enum TriggerSignal_t { SIGNAL_NONE, SIGNAL_INPUT, SIGNAL_OUTPUT};
[ Trigger Type External Free Run ]
[ Trigger Type External Arbitrary Start ]

Trigger Mode = Trig. 1 Bulb Mode
Trigger 1 In Setup = Opto
Trigger 1 Out Setup = CMOS
Trigger 1 Out Selector = Trig. 1 Rise Wait
Trigger 2 In Setup = Opto
Trigger 2 Out Setup = CMOS
Trigger 2 Out Selector = Trig. 1 Fall Wait
#endif
enum TriggerType_t { TRIGGER_TYPE_UNKNOWN, TRIGGER_TYPE_NONE, TRIGGER_TYPE_EXTERNAL_FREE_RUN, TRIGGER_TYPE_EXTERNAL_ARBITRARY_START, TRIGGER_TYPE_INTERNAL_WITH_SHUTTER, TRIGGER_TYPE_CUSTOM_0, TRIGGER_TYPE_CUSTOM_1, TRIGGER_TYPE_CUSTOM_2 };

enum TriggerMode_t { TRIGGER_MODE_TRIGGER_1_BULB=1, TRIGGER_MODE_TRIGGER_1_FAST_BULB, TRIGGER_MODE_TRIGGER_2_FRAME_ON_TRIGGER_1};
enum TriggerSetupIn_t { TRIGGER_IN_SIGNAL_OPTO=1, TRIGGER_IN_SIGNAL_OPTO_INVERTED=2, TRIGGER_IN_SIGNAL_CMOS_PULLDOWN=4, TRIGGER_IN_SIGNAL_CMOS_PULLUP=5, TRIGGER_IN_SIGNAL_CMOS_PULLDOWN_INVERTED=6, TRIGGER_IN_SIGNAL_CMOS_PULLUP_INVERTED=7};
enum TriggerSetupOut_t { TRIGGER_OUT_SIGNAL_OPTO=0, TRIGGER_OUT_SIGNAL_CMOS=1};
enum TriggerSelectorOut_t { TRIGGER_OUT_SELECT_SHUTTER=0, TRIGGER_OUT_SELECT_INTEGRATE, TRIGGER_OUT_SELECT_FRAME, TRIGGER_OUT_SELECT_LINE, TRIGGER_OUT_SELECT_SHUTTER_OPENING, TRIGGER_OUT_SELECT_SHUTTER_CLOSING, TRIGGER_OUT_SELECT_ACTIVE, TRIGGER_OUT_SELECT_TRIGGER_1_RISE_WAIT, TRIGGER_OUT_SELECT_TRIGGER_1_RISE_ACK, TRIGGER_OUT_SELECT_TRIGGER_1_FALL_WAIT, TRIGGER_OUT_SELECT_TRIGGER_1_FALL_ACK, TRIGGER_OUT_SELECT_TRIGGER_2_RISE_WAIT, TRIGGER_OUT_SELECT_TRIGGER_2_RISE_ACK, TRIGGER_OUT_SELECT_TRIGGER_2_FALL_WAIT, TRIGGER_OUT_SELECT_TRIGGER_2_FALL_ACK}; 

enum TestPattern_t {
   TEST_PATTERN_NONE,
   TEST_PATTERN_SIMULATED_BIAS,
   TEST_PATTERN_PORT_ID,
   TEST_PATTERN_CONTINUOUS_RAMP,
   TEST_PATTERN_SERIAL_RAMP,
   TEST_PATTERN_PARALLEL_RAMP,
   TEST_PATTERN_WALKING_1,
   TEST_PATTERN_WALKING_0,
   TEST_PATTERN_DARK_SAMPLE,
   TEST_PATTERN_LIGHT_SAMPLE,
   TEST_PATTERN_MAX_VALUE_CONTROLLER,
   TEST_PATTERN_SIMULATED_BIAS_CONTROLLER,
   TEST_PATTERN_PORT_ID_CONTROLLER,
   TEST_PATTERN_CONTINUOUS_RAMP_CONTROLLER,
   TEST_PATTERN_SERIAL_RAMP_CONTROLLER,
   TEST_PATTERN_PARALLEL_RAMP_CONTROLLER,
   TEST_PATTERN_WALKING_1_CONTROLLER,
   TEST_PATTERN_WALKING_0_CONTROLLER,
   TEST_PATTERN_VIDEO
};

enum StatusParameter_t { NullParameter, None, SensorTemperatures, SensorTemperatureMin, SensorTemperatureMax, SensorTemperatureAve, CoolerTemperatures, CoolerTemperatureMin, CoolerTemperatureMax, CoolerTemperatureAve, AmbientTemperatures, PowerSupplyTemperatures, SystemTemperatures, CoolerPressures, ChamberPressure, LinePressure, VacuumControllerAlive, VacuumControllerAlarm, LinePressureSensorAlive, ChamberPressureSensorAlive, VacuumPressureAlarm, VacuumControllerCommunicating, VacuumPumpAlive, VacuumPumpRunning, VacuumPumpIgnored, VacuumPumpAlarm, VacuumValveAlive, VacuumValveEnabled, VacuumValveOpen, VacuumAllIgnored, VacuumValveAlarm, CoolerEnabled, CoolerOn, CoolerRunning, DetectorIntegrating, MasterAlarm, PowerDistributionAlarm, PowerSupplyAlarm, VacuumSystemAlarm, VoltagesAlarm };
   

typedef StatusParameter_t StatusFlag_t;

inline std::string VStatusParameterName(StatusParameter_t item)
{
   switch(item) {
   case NullParameter:
      return "None";
      break;
   case SensorTemperatureMin:
      return "SensorTemperatureMin";
      break;
   case SensorTemperatureMax:
      return "SensorTemperatureMax";
      break;
   case SensorTemperatureAve:
      return "SensorTemperatureAve";
      break;
   case SensorTemperatures:
      return "SensorTemperatures";
      break;
   case CoolerTemperatureMin:
      return "CoolerTemperatureMin";
      break;
   case CoolerTemperatureMax:
      return "CoolerTemperatureMax";
      break;
   case CoolerTemperatureAve:
      return "CoolerTemperatureAve";
      break;
   case CoolerTemperatures:
      return "CoolerTemperatures";
      break;
   case AmbientTemperatures:
      return "AmbientTemperatures";
      break;
   case PowerSupplyTemperatures:
      return "PowerSupplyTemperatures";
      break;
   case SystemTemperatures:
      return "SystemTemperatures";
      break;
   case CoolerPressures:
      return "CoolerPressures";
      break;
   case ChamberPressure:
      return "ChamberPressure";
      break;
   case LinePressure:
      return "LinePressure";
      break;
   case VacuumControllerAlive:
      return "VacuumControllerAlive";
      break;
   case VacuumControllerAlarm:
      return "VacuumControllerAlarm";
      break;
   case LinePressureSensorAlive:
      return "LinePressureSensorAlive";
      break;
   case ChamberPressureSensorAlive:
      return "ChamberPressureSensorAlive";
      break;
   case VacuumPressureAlarm:
      return "VacuumPressureAlarm";
      break;
   case VacuumControllerCommunicating:
      return "VacuumControllerCommunicating";
      break;
   case VacuumPumpAlive:
      return "VacuumPumpAlive";
      break;
   case VacuumPumpRunning:
      return "VacuumPumpRunning";
      break;
   case VacuumPumpIgnored:
      return "VacuumPumpIgnored";
      break;
   case VacuumPumpAlarm:
      return "VacuumPumpAlarm";
      break;
   case VacuumValveAlive:
      return "VacuumValveAlive";
      break;
   case VacuumValveEnabled:
      return "VacuumValveEnabled";
      break;
   case VacuumValveOpen:
      return "VacuumValveOpen";
      break;
   case VacuumAllIgnored:
      return "VacuumAllIgnored";
      break;
   case VacuumValveAlarm:
      return "VacuumValveAlarm";
      break;
   case CoolerEnabled:
      return "CoolerEnabled";
      break;
   case CoolerOn:
      return "CoolerOn";
      break;
   case CoolerRunning:
      return "CoolerRunning";
      break;
   case DetectorIntegrating:
      return "DetectorIntegrating";
      break;
   default:
      return "";
      break;
   }
}


template<class STATUSITEM> class VStatusMap;

class VStatusParameter
{
   friend class VStatusMap<VStatusParameter>;
   public:
      VStatusParameter() : display_name_(std::string("")), id_name_(std::string("")), value_(std::string("")), p_rxd_(NULL) {}
      virtual ~VStatusParameter() {}
      virtual std::string operator() () const = 0;
      virtual void setKey(StatusFlag_t key) { key_ = key; }
      virtual void setDisplayName(const std::string& display_name = std::string("")) { display_name_ = display_name; }
      virtual std::string setName(const std::string& name = std::string(""))
      {
	 if (!name.empty()) {
	    display_name_ = name;
	 }
	 else {
	    display_name_ = VStatusParameterName(key_);
	 }
	 id_name_ = display_name_;
	 return display_name_;
      }
      bool update()
      {
	 bool changed = false;
	 std::string new_value = (*this)();
	 if (value_ != new_value) {
	    value_ = new_value;
	    changed = true;
	 }
	 return changed;
      }

      bool monitorEnabled() const { return true; }

      std::string idName() const { return id_name_; }

      std::string displayName() const { return display_name_; }

      std::string value() const { return value_; }

      void setValue(const std::string& value)
      {
         value_ = value;
      }
      template<class DataType> void setValue(const DataType value)
      {
	 std::ostringstream oss;

	 oss << value;
	 setValue(oss.str());
	 return;
      }

      StatusParameter_t key() const {return key_;}


   //private:
      StatusParameter_t key_;
      std::string display_name_;
      std::string id_name_;
      std::string value_;
      RxDetector* p_rxd_;
};

class VStatusFlag
{
   friend class VStatusMap<VStatusFlag>;
   public:
      VStatusFlag(RxDetector &rxd, const std::string& container_name, const std::string& bit_name, const StatusFlag_t& key = NullParameter, const std::string& display_name = std::string(""), bool enable = true);
      VStatusFlag(RxDetector &rxd, bool (RxDetector::*method)(), const std::string& display_name, const StatusFlag_t& key = NullParameter, bool enable = true);
      ~VStatusFlag() {}
      virtual std::string operator() () const;

      StatusParameter_t key() const {return key_;}

      std::string idName() const { return id_name_; }

      std::string displayName() const { return display_name_; }

      std::string containerName() const { return container_name_; }

      std::string bitName() const { return bit_name_; }

      std::string value() const
      {
         return value_;
      }
      bool update()
      {
	 bool changed = false;
	 std::string new_value = (*this)();
	 if (value_ != new_value) {
	    value_ = new_value;
	    changed = true;
	 }
	 return changed;
      }
      bool monitorEnabled() const { return monitor_enabled_; }

      void disableMonitor() { enableMonitor(false); }
      void enableMonitor(bool enable = true) { monitor_enabled_ = enable; }

   private:
      virtual void setKey(StatusFlag_t key) { key_ = key; }
      virtual void setDisplayName(const std::string& display_name = std::string("")) { display_name_ = display_name; }
      virtual std::string setName(const std::string& name = std::string(""))
      {
	 id_name_ = name;
	 setDisplayName(id_name_);
	 return id_name_;
      }

   private:
      RxDetector& rxd_;
      bool (RxDetector::*special_method_)();
      StatusParameter_t key_;
      std::string id_name_;
      std::string display_name_;
      std::string bit_name_;
      std::string container_name_;
      std::string value_;
      bool monitor_enabled_;
};

template <class STATUSITEM>
class VStatusMap
{
   friend class RxDetector;
   public:
      VStatusMap(){};
      ~VStatusMap()
      {
	 for ( typename std::map<std::string, STATUSITEM*>::iterator vsi = name_map_.begin(); vsi != name_map_.end(); ++vsi) {
	    delete vsi->second;
	 }
      }

      // return true if added, otherwise false  (not used, so can be deleted by caller)
      bool add(STATUSITEM* parameter) {
	 typename std::map<const std::string, STATUSITEM*>::iterator vsfi = name_map_.find(parameter->idName());
	 STATUSITEM *my_parameter_p;
	 RxLog(LOG_TRACE) << "VStatusMap::add() - testing key " << parameter->key() << ": " << parameter->idName() << std::endl;
	 if (vsfi == name_map_.end()) {
	    // Not found, add it
	    RxLog(LOG_TRACE) << "VStatusMap::add() - adding key " << parameter->key() << ": " << parameter->idName() << std::endl;
	    name_map_[parameter->idName()] = parameter;
	    key_map_.insert(std::pair<StatusFlag_t, STATUSITEM*>(parameter->key(),parameter));
	    return true;
	 }
	 else {
	    // Flag already exists in list, use that instead, but update with any useful info from new parameter
	    my_parameter_p = vsfi->second;
	    if (my_parameter_p->key() == NullParameter) {
	       RxLog(LOG_TRACE) << "VStatusMap::add() - renaming key " << my_parameter_p->key() << ": " << my_parameter_p->displayName() << " to " << parameter->displayName() << std::endl;
	       // Set display name
	       my_parameter_p->setDisplayName(parameter->displayName()); 
	       // Set key
	       my_parameter_p->setKey(parameter->key()); 
	       // If this was a real key, then add it to key map
	       if (my_parameter_p->key() != NullParameter) key_map_.insert(std::pair<StatusFlag_t, STATUSITEM*>(my_parameter_p->key(),my_parameter_p));
	    }
	    RxLog(LOG_TRACE) << "VStatusMap::add() - using key " << my_parameter_p->key() << ": " << my_parameter_p->displayName() << std::endl;
	    return false;
	 }
      }


      std::string value (StatusParameter_t key) { if (key == NullParameter) return ""; return key_map_.find(key) == key_map_.end() ? "" :  key_map_.find(key)->second->value();}

      std::string name (StatusParameter_t key) { if (key == NullParameter) return ""; return key_map_.find(key) == key_map_.end() ? "" :  key_map_.find(key)->second->displayName();}

      //std::string setName(const std::string& key) { return theMap.find(key) == theMap.end() ? "" :  theMap[key]->setName();}

      //template<class DataType> void setValue(const std::string& key, const DataType value) { if (theMap.find(key) != theMap.end()) theMap[key]->setValue(value);}

      bool update(const std::string& name) { return name_map_.find(name) == name_map_.end() ? false :  name_map_[name]->update();}
      bool update(StatusFlag_t key) { if (key == NullParameter) return false; return key_map_.find(key) == key_map_.end() ? false :  key_map_.find(key)->second->update();}

      std::vector<STATUSITEM*> list()
      {
	 std::vector<STATUSITEM*> the_list;
	 for ( typename std::map<const std::string, STATUSITEM*>::iterator vsfi = name_map_.begin(); vsfi != name_map_.end(); ++vsfi) {
	    the_list.push_back(vsfi->second);
	 }
	 return the_list;
      }
      void updateAll()
      {
	 for ( typename std::map<const std::string, STATUSITEM*>::iterator vsfi = name_map_.begin(); vsfi != name_map_.end(); ++vsfi) {
	    vsfi->second->update();
	 }
      }
      STATUSITEM* find(StatusFlag_t key)
      {
	 if (key == NullParameter) return false;
	 return key_map_.find(key) == key_map_.end() ? NULL :  key_map_.find(key)->second;
      }

      void setAllNames();

   private:
      std::multimap<StatusFlag_t, STATUSITEM*> key_map_;
      std::map<std::string, STATUSITEM*> name_map_;
};

#if 0
template <> inline void VStatusMap<VStatusFlag>::setAllNames()
{
      RxLog(LOG_SYSTEM) << "VirtualStatusMap::setAllNames<VStatusFlag>() - called" << std::endl;
}
template <class VStatusParameter> inline void VStatusMap<VStatusParameter>::setAllNames()
{
   for ( typename std::map<std::string, VStatusParameter*>::iterator vsi = name_map_.begin(); vsi != name_map_.end(); ++vsi) {
      RxLog(LOG_SYSTEM) << "VirtualStatusMap::setAllNames() - calling setName() for " << vsi->second->idName() << std::endl;
      vsi->second->setName();
   }
}
#else
template <class STATUSITEM> inline void VStatusMap<STATUSITEM>::setAllNames()
{
   for ( typename std::map<std::string, STATUSITEM*>::iterator vsi = name_map_.begin(); vsi != name_map_.end(); ++vsi) {
      RxLog(LOG_DEBUG) << "VirtualStatusMap::setAllNames() - calling setName() for " << vsi->second->idName() << std::endl;
      vsi->second->setName();
   }
}
template inline void VStatusMap<VStatusParameter>::setAllNames();
template inline void VStatusMap<VStatusFlag>::setAllNames();
#endif

//! \private
//! For scaling an arbitrary data type by a double
template<class T> T ScaleValue(T value, double scaler);
//! \private
//! A specialization for strings
template<> std::string ScaleValue(std::string value, double scaler);


///////////////////////////////////////////////////////////////////////////////
// Callback Interface
// Generic reusable part for all callback objects
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//! \private
template <class CallbackType>
class CallbackInvoker
{
public:
    virtual ~CallbackInvoker() {}
    virtual void operator()(CallbackType* callback) const {};
};

//-----------------------------------------------------------------------------
//! \private
template <class CallbackType, class Binding>
class BoundCallbackInvoker : public CallbackInvoker<CallbackType>
{
public:
    BoundCallbackInvoker(const Binding& binding) : binding_(binding) {}
    void operator()(CallbackType* callback) const {binding_(callback);}

private:
    Binding binding_;
};

//-----------------------------------------------------------------------------
//! \private
template <class CallbackType>
class CallbackSlot
{
public:
    CallbackSlot(CallbackType* callback) : callback_(callback) {}
    void operator()(const CallbackInvoker<CallbackType>& invoker)
#define DOITINTHREAD 0
#if DOITINTHREAD
	{boost::thread(&invoker, this, callback_);}
#else
        {invoker(callback_);}
#endif

private:
    CallbackType* callback_;
};

//-----------------------------------------------------------------------------

typedef boost::signals2::connection CallbackConnection_t;
typedef boost::mutex Mutex_t;
typedef boost::condition_variable  ConditionVariable_t;

//! \private
template <class CallbackType>
class KeyedCallbackInterface
{

typedef typename boost::signals2::signal<void (const CallbackInvoker<CallbackType>&)> signal_t;
typedef std::map <std::string, signal_t *> signal_map_t;
typedef std::map <StatusParameter_t, signal_t *> status_item_signal_map_t;
typedef std::map <const VStatusFlag*, signal_t *> status_flag_signal_map_t;

public:
    KeyedCallbackInterface() {}
    ~KeyedCallbackInterface()
    {
      // Delete the signals
      for (typename signal_map_t::iterator smi = signal_map_.begin(); smi != signal_map_.end(); ++smi) {
	 delete smi->second;
      }
      for (typename status_item_signal_map_t::iterator smi = status_item_signal_map_.begin(); smi != status_item_signal_map_.end(); ++smi) {
	 delete smi->second;
      }
      for (typename status_flag_signal_map_t::iterator smi = status_flag_signal_map_.begin(); smi != status_flag_signal_map_.end(); ++smi) {
	 delete smi->second;
      }
    }

protected:
   CallbackConnection_t Connect_(const std::string& key, CallbackType* callback)
   {
      signal_t *a_signal;
      typename signal_map_t::iterator smi = signal_map_.find(key);

     RxLog(LOG_TRACE) << "Connect request for key: " << key << std::endl;

      if (smi != signal_map_.end()) {
	 RxLog(LOG_TRACE) << "Connect(): Old Signal found for key: " << key << std::endl;
	 // Retrieve an existing signal from the map
	 a_signal = smi->second;
      }
      else {
	 RxLog(LOG_TRACE) << "Connect(): NO Signal found for key: " << key << " Creating new signal." << std::endl;
	 // Create a new signal and put it in the map
	 a_signal = new signal_t();
	 signal_map_[key] = a_signal;
      }

      return a_signal->connect(CallbackSlot<CallbackType>(callback));
   }
   CallbackConnection_t Connect_(const StatusParameter_t& key, CallbackType* callback)
   {
      signal_t *a_signal;
      typename status_item_signal_map_t::iterator smi = status_item_signal_map_.find(key);

     RxLog(LOG_TRACE) << "Connect request for key: " << key << std::endl;

      if (smi != status_item_signal_map_.end()) {
	 RxLog(LOG_TRACE) << "Connect(): Old Signal found for key: " << key << std::endl;
	 // Retrieve an existing signal from the map
	 a_signal = smi->second;
      }
      else {
	 RxLog(LOG_TRACE) << "Connect(): NO Signal found for key: " << key << " Creating new signal." << std::endl;
	 // Create a new signal and put it in the map
	 a_signal = new signal_t();
	 status_item_signal_map_[key] = a_signal;
      }

      return a_signal->connect(CallbackSlot<CallbackType>(callback));
   }
   CallbackConnection_t Connect_(const VStatusFlag* key, CallbackType* callback)
   {
      signal_t *a_signal;
      typename status_flag_signal_map_t::iterator smi = status_flag_signal_map_.find(key);

     RxLog(LOG_TRACE) << "Connect request for key: " << key << std::endl;

      if (smi != status_flag_signal_map_.end()) {
	 RxLog(LOG_TRACE) << "Connect(): Old Signal found for key: " << key << std::endl;
	 // Retrieve an existing signal from the map
	 a_signal = smi->second;
      }
      else {
	 RxLog(LOG_TRACE) << "Connect(): NO Signal found for key: " << key << " Creating new signal." << std::endl;
	 // Create a new signal and put it in the map
	 a_signal = new signal_t();
	 status_flag_signal_map_[key] = a_signal;
      }

      return a_signal->connect(CallbackSlot<CallbackType>(callback));
   }
   CallbackConnection_t Connect_(CallbackType* callback)
   {
      return signal_.connect(CallbackSlot<CallbackType>(callback));
   }
   void Disconnect_(CallbackConnection_t conn) {conn.disconnect();}

   template <class Binding> void Signal(const std::string& key, const Binding& binding)
   {
      signal_t *a_signal;
      typename signal_map_t::iterator smi = signal_map_.find(key);

      if (smi != signal_map_.end()) {
	 RxLog(LOG_TRACE) << "Signal(): Signal found for key: " << key << " Calling Callback" << std::endl;
	 // Retrieve an existing signal from the map
	 a_signal = smi->second;
	 if (a_signal) {
	    (*a_signal)(BoundCallbackInvoker<CallbackType,Binding>(binding));
	 }
	 else {
	    RxLog(LOG_ERROR) << "Signal(): signal was NULL for key: " << key << std::endl;
	 }
      }
      else {
	 RxLog(LOG_TRACE) << "Signal(): NO Signal found for key: " << key << std::endl;
      }

   }
   template <class Binding> void Signal(const StatusParameter_t& key, const Binding& binding)
   {
      signal_t *a_signal;
      typename status_item_signal_map_t::iterator smi = status_item_signal_map_.find(key);

      if (smi != status_item_signal_map_.end()) {
	 RxLog(LOG_TRACE) << "Signal(): Signal found for key: " << key << " Calling Callback" << std::endl;
	 // Retrieve an existing signal from the map
	 a_signal = smi->second;
	 if (a_signal) {
	    (*a_signal)(BoundCallbackInvoker<CallbackType,Binding>(binding));
	 }
	 else {
	    RxLog(LOG_ERROR) << "Signal(): signal was NULL for key: " << key << std::endl;
	 }
      }
      else {
	 RxLog(LOG_TRACE) << "Signal(): NO Signal found for key: " << key << std::endl;
      }

   }
   template <class Binding> void Signal(const VStatusFlag* key, const Binding& binding)
   {
      signal_t *a_signal;
      typename status_flag_signal_map_t::iterator smi = status_flag_signal_map_.find(key);

      if (smi != status_flag_signal_map_.end()) {
	 RxLog(LOG_TRACE) << "Signal(): Signal found for key: " << key << " Calling Callback" << std::endl;
	 // Retrieve an existing signal from the map
	 a_signal = smi->second;
	 if (a_signal) {
	    (*a_signal)(BoundCallbackInvoker<CallbackType,Binding>(binding));
	 }
	 else {
	    RxLog(LOG_ERROR) << "Signal(): signal was NULL for key: " << key << std::endl;
	 }
      }
      else {
	 RxLog(LOG_TRACE) << "Signal(): NO Signal found for key: " << key << std::endl;
      }

   }
   template <class Binding> void Signal(const Binding& binding)
   {
      RxLog(LOG_TRACE) << "Signal(): Signal with no key, binding: " << &binding << std::endl;
      signal_(BoundCallbackInvoker<CallbackType,Binding>(binding));
   }
   CallbackConnection_t ConnectToSignal(signal_t sig, CallbackType* callback)
     {return sig.connect(CallbackSlot<CallbackType>(callback));}

private:
    signal_t signal_;
    signal_map_t signal_map_;
    status_item_signal_map_t status_item_signal_map_;
    status_flag_signal_map_t status_flag_signal_map_;
};


//
///////////////////////////////////////////////////////////////////////////////
// THIS PART SPECIFIC TO ONE SUBJECT
// to become part of RxDetectorClass...
///////////////////////////////////////////////////////////////////////////////

// to become part of RxDetectorClass...

//-----------------------------------------------------------------------------
//
//! \page  "Callback Interface"

//! \section  callbacks Callback Interface
//! Callbacks are implemented with callback objects
//! There are two different types, one for status and parameter changes
//! and one for frame acquistion status

//! \brief  a callback interface for receiving signals about changing status or parameter values
/*!
 * This class cannot be implemented - you must derive a new class from it.
 *
 * Status values are changed by the detector, never by the host
 * Parameter values are generally changed by the host, but may change by being read back from the detector
 * (eg, if a bad value from the host was not accepted by the detector)
 *
 * Note that it is only necessary to implement the methods that are needed. Methods left unimplemented in the
 * derived class will default to the empty virtual methods of the base class
 */
class VirtualKeyedStateChangeCallback
{
public:
   // pure virtual destructor mean that this is a virtual class that can only be used as a base for another derived class
   virtual ~VirtualKeyedStateChangeCallback() = 0;
   //! \brief  executes when any status changes
   virtual void StatusChanged() { RxLog(LOG_ERROR) << "StatusChanged() - virtual method called!" << std::endl; }
   //! \brief  executes when the named status changes
   virtual void StatusChanged(const std::string& name, const std::string& value) { RxLog(LOG_ERROR) << "StatusChanged(const std::string, const std::string) - virtual method called!" << std::endl; }
   virtual void StatusParameterChanged(const StatusParameter_t item, const std::string& value) { RxLog(LOG_ERROR) << "StatusParameterChanged(const StatusParameter_t item, const std::string) - virtual method called!" << std::endl; }
   virtual void StatusFlagChanged(const VStatusFlag* VSF_p) { RxLog(LOG_ERROR) << "StatusFlagChanged(const VStatusFlag* VSF_p) - virtual method called!" << std::endl; }
   //! \brief  executes when any parameter changes
   virtual void ParameterChanged() { RxLog(LOG_ERROR) << "ParameterChanged() - virtual method called!" << std::endl; }
   //! \brief  executes when the named parameter changes
   virtual void ParameterChanged(const std::string& name, const std::string& value) { RxLog(LOG_ERROR) << "ParameterChanged(const std::string, const std::string) - virtual method called!" << std::endl; }
};
// Requires implementation
inline VirtualKeyedStateChangeCallback::~VirtualKeyedStateChangeCallback() {}

//! \brief  a callback interface for receiving signals concerning frame acquisition status
/*!
 * This class cannot be implemented - you must derive a new class from it.
 *
 * The methods of this class allow the object to be notified about the progress of the acquistion of a data frame
 *
 * Note that it is only necessary to implement the methods that are needed. Methods left unimplemented in the
 * derived class will default to the empty virtual methods of the base class
 */
class VirtualFrameCallback
{
public:
   // pure virtual destructor mean that this is a virtual class that can only be used as a base for another derived class
   virtual ~VirtualFrameCallback() = 0;
   //! \brief  executes when acquisition sequence starts
   
   virtual void SequenceStarted() = 0;
   //! \brief  executes when acquisition sequence ends
   
   virtual void SequenceEnded() = 0;
   //! \brief  executes when exposure starts
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   virtual void ExposureStarted(int frame_number) = 0;
   //! \brief  executes when exposure ends
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   virtual void ExposureEnded(int frame_number) = 0;
   //! \brief  executes when readout starts
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   virtual void ReadoutStarted(int frame_number) = 0;
   //! \brief  executes when readout ends
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   virtual void ReadoutEnded(int frame_number) = 0;
   //! \brief  executes when raw frame data is ready for further processing after readout
   
   //! @param[in] frame_p
   //! The frame is a pointer to the background frame that will be used
   //! It is not necessary to copy it out, nor to process it in any way
   //! Note the contrast with the operation of the RawFrameReady and FrameReady() callbacks
   virtual void BackgroundFrameReady(RxFrame* frame_p) = 0;
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   //! @param[in] frame_p
   //! The frame is a pointer to the raw buffer that receives data from the detector.
   //! It is important that the callback routine finishes its access to the data before the buffer is reused by the detector.
   //! Note the contrast with the operation of the FrameReady() callback
   virtual void RawFrameReady(int frame_number, RxFrame* frame_p) = 0;
   //! \brief  executes when final (corrected) frame data is ready for access after readout, pass RxFrame to callback
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   //! @param[in] frame_p
   //! a pointer to an RxFrame object containing the corrected data frame.
   //! The frame is a new object created to be passed to this callback.  It will be deleted automatically when the callback returns
   //! Note the contrast with the operation of the RawFrameReady() callback
   
   virtual void FrameReady(int frame_number, RxFrame* frame_p) = 0;
   //! \brief  executes when frame is aborted
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   virtual void FrameAborted(int frame_number) = 0;
   //! \brief  executes when frame is completed - no more to be done for this frame!
   
   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   virtual void FrameCompleted(int frame_number) = 0;

   //! \brief  executes when an error is generated for a frame

   //! @param[in] frame_number
   //! The frame number, numbered beginning with start_frame_number parameter to SetupAcquisitionSequence()
   //! @param[in] error_code
   //! The code indicating the error
   //! @param[in] error_string
   //! A string describing the error
   virtual void FrameError(int frame_number, int error_code, const std::string& error_string) = 0;

};
// Requires implementation
inline VirtualFrameCallback::~VirtualFrameCallback() {};

//! A Frame acquisition callback class with multiple callbacks
class CVAcquisitionCBInterface
{
   public:
      virtual ~CVAcquisitionCBInterface() {}
      virtual void SeriesStartedCB() const {}
      virtual void SeriesProgressCB(double percent_done) const {}
      virtual void SeriesCompletedCB() const {}
      virtual void ExposureStartedCB(int frame_number) const {}
      virtual void ExposureProgressCB(int frame_number, double percent_done) {}
      virtual void ExposureCompletedCB(int frame_number) const {}
      virtual void ReadoutStartedCB(int frame_number, void *buffer_p) const {}
      virtual void ReadoutProgressCB(int frame_number, double percent_done) const {}
      virtual void ReadoutCompleted(int frame_number) const {}
      virtual void FrameReadyCB(int frame_number, void *buffer_p) const {}
};

namespace RxCB {
   class BackgroundAcquisitionCB;
   class AcquisitionCB;
}

//! \private
class RxDetectorParameter
{

   public:

      // Constructors/Destructors

      RxDetectorParameter() :
	 parameterScaler(1.0)
      {
         enumeratedTypeName.clear();
         enumeratedTypeValue.clear();
         UnsetImplemented();
      }
      RxDetectorParameter(const std::string& parameterName) :
	 parameterScaler(1.0)
      {
         enumeratedTypeName.clear();
         enumeratedTypeValue.clear();
         setName(parameterName);
         UnsetImplemented();
      }
      RxDetectorParameter(const std::string& parameterName, SpectralParameterRecord spectral_parameter_record)
      {
         enumeratedTypeName.clear();
         enumeratedTypeValue.clear();
         setName(parameterName);
         ImportSpectralParameter(spectral_parameter_record);
      }
      RxDetectorParameter(SpectralParameterRecord spectral_parameter_record)
      {
         enumeratedTypeName.clear();
         enumeratedTypeValue.clear();
         setName(spectral_parameter_record.getParameterName());
         ImportSpectralParameter(spectral_parameter_record);
      }
      ~RxDetectorParameter()
      {
      }

      //Operators
      bool operator== (const RxDetectorParameter &p) const
      {
	 return (
		  p.parameterName == parameterName
		  && p.parameterIndex == parameterIndex
		  && p.externalName == externalName
		  && p.unitName_ == unitName_
		  && p.parameterValue == parameterValue
		  && p.parameterScaler == parameterScaler
		  && p.minValue == minValue
		  && p.maxValue == maxValue
		  && p.valueStep == valueStep
		  && p.unitType_ == unitType_
		  && p.bitMask_ == bitMask_
		  && p.bitNames == bitNames
		  && p.bits == bits
		  && p.dataTypeName == dataTypeName
		  && enumeratedTypeName == enumeratedTypeName
		  && enumeratedTypeValue == enumeratedTypeValue
		  && p.implemented == implemented
	);
      }

      bool operator!= (const RxDetectorParameter &p) const
      {
	 return !(this->operator== (p));
      }

      // Public Getters
      std::string getName() const
      {
         return this->parameterName;
      }
      int getIndex() const
      {
         return this->parameterIndex;
      }
      std::string getExternalName() const
      {
         return this->externalName;
      }
      std::string unitName() const
      {
         return this->unitName_;
      }
      RxUnitType unitType() const
      {
         return this->unitType_;
      }
      //T getValue() const {stringstream ss; ss << this->parameterValue; ss >> this->typedValue; return this->typedValue;}
      std::string getValue() const
      {
	 return this->parameterValue;
      }
      std::string getValueWithUnit() const
      {
         std::ostringstream ss;
         ss << getValue();
         if (this->unitName_.length()) ss << " " << this->unitName_;
         return ss.str();
      }
      std::string getValueMin() const
      {
         return this->minValue;
      }
      std::string getValueMax() const
      {
         return this->maxValue;
      }
      std::string getValueStep() const
      {
         return this->valueStep;
      }
      std::string getDataTypeName() const
      {
         return this->dataTypeName;
      }
      bool IsImplemented()
      {
         return this->implemented;
      }
      std::string getFullDescription()
      {
         std::ostringstream fullDescription;
         fullDescription << getName() << ": " << getValueWithUnit() << " (" << getValueMin() << " <= \"" << getName() << "\" >= "
               << getValueMax() << " +/-" << getValueStep() << ")";
         return fullDescription.str();
      }

      bool isValidValue(std::string value)
      {
	 switch(unitType_) {
	 case UNIT_ENUMERATED:
	 case UNIT_ENUMERATED_SPARSE:
	    {
	       // Assume argument is display_name of pull_down and not actual value - check if it is in map
	       std::map<std::string, int>::const_iterator ei = enumeratedTypeValue.find(value);
	       if (ei == enumeratedTypeValue.end()) {
		  RxLog(LOG_ERROR) << "RxDetectorParameter::isValidValue(\"" << parameterName << "\", " << value << ") - Invalid parameter" << endl;
		  return false;
	       }
	       // Min,Max do not apply to pulldowns because limits are on index, but this is the value
	    }
	    break;
	 default:
	      // Need to add min and max tests here
	    break;
	 }

	 return true;
      }

      int bit(const std::string& name)
      {
	 if (this->bits.find(name) != this->bits.end()) {
	    return this->bits[name];
	 }
	 return -1;
      }
      std::string bitName(int bit)
      {
	 int nbits = sizeof(bitMask_)*8;
	 if (bitNames.size() == 0) bitNames.resize(nbits);
	 if (bit >= 0 && bit < nbits) {
	    return bitNames[bit];
	 }
	 return std::string("");
      }
      int bitMask()
      {
	 return bitMask_;
      }
      bool bitValue(const std::string& name)
      {
	 return bitValue(bit(name));
      }
      bool bitValue(int bit)
      {
	 int value;
	 if (bit >= 0 && bit < (int)sizeof(value)*8) {
	    std::stringstream ss;
	    // Convert value to int
	    ss.str(this->parameterValue);
	    ss >> value;
	    return (value & (1 << bit)) ? true : false;
	 }
	 return false;
      }

      // Public Setters - very limited
      void setName(const std::string& parameterName)
      {
         this->parameterName = parameterName;
         return;
      }
      void setValue(const std::string& parameterValue)
      {
	 this->parameterValue = parameterValue;
      }

      //! \brief  Updates parameter value from Spectral Value
      //
      //! Use for updating complete parameter - not for initial import!
      void updateFromSpectralValue(const std::string& spectral_value)
      {
         setValue(ConvertValueFromSpectral(spectral_value));
      }

      // Public exporters

      void ExportSpectralParameter(SpectralParameterRecord &spectral_parameter_record)
      {
         ExportSpectralParameterName(spectral_parameter_record);
         ExportSpectralParameterMetaData(spectral_parameter_record);
         ExportSpectralParameterData(spectral_parameter_record);
      }

   private:
      std::string parameterName;
      std::string externalName;
      int parameterIndex;
      std::string unitName_;
      std::string parameterValue;
      double parameterScaler;
      std::string minValue;
      std::string maxValue;
      std::string valueStep;
      RxUnitType unitType_;
      int bitMask_;
      std::vector<std::string> bitNames;
      std::map<std::string, int> bits;
      std::string dataTypeName;
      std::map<int, std::string> enumeratedTypeName;
      std::map<std::string, int> enumeratedTypeValue;
      bool implemented;

   private:
      void setIndex(int parameterIndex)
      {
         this->parameterIndex = parameterIndex;
         return;
      }
      void setExternalName(const std::string& externalName)
      {
         this->externalName = externalName;
         return;
      }
      void setUnitType(RxUnitType unitType)
      {
         this->unitType_ = unitType;
         return;
      }
      void setUnitName(const std::string& unitName)
      {
         this->unitName_ = unitName;
         return;
      }
      void setValueMin(const std::string& minValue)
      {
         this->minValue = minValue;
      }
      void setValueMax(const std::string& maxValue)
      {
         this->maxValue = maxValue;
      }
      void setValueStep(const std::string& step)
      {
         this->valueStep = step;
         return;
      }
      void resetBit(int bit)
      {
	 setBit(bit, false);
      }
      void setBit(int bit, bool on = true)
      {
	 // Convert current stored value to int
         std::stringstream ss;
	 int value;
         ss.str(this->parameterValue);
	 ss >> value;
	 if (bit >= 0 && bit < (int)sizeof(value)*8) {
	    if (on) {
	       // Set the bit
	       value |= (1 << bit);
	    }
	    else {
	       // Unset the bit
	       value &= ~(1 << bit);
	    }
	 }
	 // Convert back to string and store
	 ss.str("");
	 ss << value;
	 RxLog(LOG_TRACE) << getName() << ".setBit(" << bit << "," << on << ")  Old Value: " << parameterValue << " New Value: " << value << std::endl;
         this->parameterValue = ss.str();
      }
      void setDataTypeName(const std::string& dataTypeName)
      {
         this->dataTypeName = dataTypeName;
      }
      void setEnumeratedValuesMaps(const std::map<int, std::string> enumeratedMap)
      {
	 for (std::map<int, std::string>::const_iterator mi = enumeratedMap.begin(); mi != enumeratedMap.end(); ++mi) {
	    this->enumeratedTypeName[mi->first] = mi->second;
	    this->enumeratedTypeValue[mi->second] = mi->first;
	 }
      }
      void setBitMaskAndNames(std::string bitMask, std::string bitNames)
      {
	 switch(unitType_) {
	 default:
	    // Don't do anything if this is not a bit field
	    break;
	 case UNIT_BITFIELD:
	    {

	       std::vector<std::string> bitnames;

	       // make vector from CSV string 
	       SplitStringIntoTokens(bitNames, bitnames, ",");
	       RxLog(LOG_DEBUG) << getName() << ".setBitMaskandNames(" << bitMask << "," << bitNames << ") found " << bitnames.size() << " names" << std::endl;

	       // make int from string
	       from_string(bitMask, bitMask_);
	       RxLog(LOG_DEBUG) << getName() << ".setBitMaskandNames() bitmask is " << boost::format("0x%x") % bitMask_  << std::endl;

	       // Go through each bit from LSB to MSB and set its name
	       //std::map<int, std::string>::const_iterator ni = bitnames.begin();
	       std::vector<std::string>::const_iterator ni = bitnames.begin();
	       for (int bit = 0; bit < (int)sizeof(int)*8; ++bit) {
		  if (bitMask_ & (1 << bit)) {
		     // This bit has a name
		     if (ni != bitnames.end()) {
#if 1
			setBitName(bit,*ni);
#else 
			std::ostringstream oss;
			oss << *ni << "(BIT" << boost::format("%02.2d)") % bit;
			setBitName(bit,oss.str());
#endif
			++ni;
		     }
		     else {
			// Ran out of names, but this bit is used
			std::ostringstream oss;
			oss << "BIT" << boost::format("%02.2d") % bit;
			setBitName(bit,oss.str());
		     }
		  }
		  else {
		     // Not used, but if we have passed the end of the list, then stop
		     //if (ni == bitnames.end()) break;

		     if (ni != bitnames.end()) {
			// Not in the mask - just name it BITnn
			std::ostringstream oss;
			oss << "BIT" << boost::format("%02.2d") % bit;
			setBitName(bit,oss.str());
		     }
		     else {
			// Not in the mask, but also past the end of the name list - just name it XBITnn
			std::ostringstream oss;
			oss << "XBIT" << boost::format("%02.2d") % bit;
			setBitName(bit,oss.str());
		     }

		  }
	       }
	       
	       //for (std::map<int, std::string>::const_iterator mi = enumeratedMap.begin(); mi != enumeratedMap.end(); ++mi) {
		  //this->enumeratedTypeName[mi->first] = mi->second;
		  //this->enumeratedTypeValue[mi->second] = mi->first;
	       //}
	    }
	    break;
	 }
      }
      void resetBitValue(std::string& bitname)
      {
	 setBitValue(bitname, false);
      }
      void resetBitValue(int bit)
      {
	 setBitValue(bit, false);
      }
      void setBitValue(std::string& bitname, bool on = true)
      {
	 setBitValue(bit(bitname), on);
      }
      void setBitValue(int bit, bool on = true)
      {
	 // Convert current stored value to int
         std::stringstream ss;
	 int value;
         ss.str(this->parameterValue);
	 ss >> value;
	 if (bit >= 0 && bit < (int)sizeof(value)*8) {
	    if (on) {
	       // Set the bit
	       value |= (1 << bit);
	    }
	    else {
	       // Unset the bit
	       value &= ~(1 << bit);
	    }
	 }
	 // Convert back to string and store
	 ss.str("");
	 ss << value;
	 RxLog(LOG_TRACE) << getName() << ".setBit(" << bit << "," << on << ")  Old Value: " << parameterValue << " New Value: " << value << std::endl;
         this->parameterValue = ss.str();
      }
      void setBitName(int bit, std::string name)
      {
	 int nbits = sizeof(bitMask_)*8;
	 if (bitNames.size() == 0) bitNames.resize(nbits);
	 if (bit >= 0 && bit < nbits) {
	    bitNames[bit] = name;
	    // Check that it is unique
	    if (bits.find(name) == bits.end()) {
	       bits[name] = bit;
	    }
	    else {
	       // duplicate - reject
	       RxLog(LOG_WARNING) << "Parameter: " << parameterName << " Duplicate bit name: " << name << endl;
	    }
	 }
      }
      void setImplemented()
      {
         this->implemented = true;
         return;
      }
      void UnsetImplemented()
      {
         this->implemented = false;
         return;
      }

      /**
       * \brief Imports only the parameter name from the Spectral DLL form of a parameter record
       *
       * @param[in] spectral_parameter_record
       */
      void ImportSpectralParameterName(SpectralParameterRecord spectral_parameter_record)
      {
         setExternalName(spectral_parameter_record.getParameterName());
      }

      /**
       * \brief Imports data  from the Spectral DLL form of a parameter record
       *
       * This imports ONLY the parameter value
       *
       * @param[in] spectral_parameter_record
       */
      void ImportSpectralParameterData(SpectralParameterRecord spectral_parameter_record)
      {
         this->parameterScaler = spectral_parameter_record.getUnitDescriptor().getScaler();

         setValue(ConvertValueFromSpectral(spectral_parameter_record.getParameterValue()));
      }

      /**
       * \brief Imports meta-data  from the Spectral DLL form of a parameter record
       *
       * This imports all the extra data, but NOT the value itself nor the name
       *
       * @param[in] spectral_parameter_record
       */
      void ImportSpectralParameterMetaData(SpectralParameterRecord spectral_parameter_record)
      {
         this->parameterScaler = spectral_parameter_record.getUnitDescriptor().getScaler();

         setIndex(spectral_parameter_record.getParameterIndex());
         setValueMin(ConvertMetaValueFromSpectral(spectral_parameter_record.getParameterMinValue()));
         setValueMax(ConvertMetaValueFromSpectral(spectral_parameter_record.getParameterMaxValue()));
         setValueStep(ConvertMetaValueFromSpectral(spectral_parameter_record.getParameterStep(), 1));

         setUnitType(spectral_parameter_record.getUnitDescriptor().getUnitType());
         setUnitName(spectral_parameter_record.getUnitDescriptor().getUnitName());

         setEnumeratedValuesMaps(spectral_parameter_record.getParameterPulldownMap());

         setBitMaskAndNames(spectral_parameter_record.getBitMask(), spectral_parameter_record.getBitNames());

         //setDataTypeName(typeid(value).name());
         //setUnitType(spectral_parameter_record.getUnitType());
         //importSpectralUnitType(spectral_parameter_record.getUnitDescriptor().getUnitType());


         setImplemented();
      }

      //! \brief  Imports complete Parameter from Spectral DLL form
      void ImportSpectralParameter(SpectralParameterRecord spectral_parameter_record)
      {
         ImportSpectralParameterName(spectral_parameter_record);
         ImportSpectralParameterMetaData(spectral_parameter_record);
         ImportSpectralParameterData(spectral_parameter_record);
      }

      /**
       * \brief Exports only the parameter name to the Spectral DLL form of a parameter record
       *
       * @param[in] spectral_parameter_record
       */
      void ExportSpectralParameterName(SpectralParameterRecord &spectral_parameter_record)
      {
         // The external name becomes the Spectral Name
         spectral_parameter_record.setParameterName(getExternalName());
      }

      /**
       * \brief Exports data to the Spectral DLL form of a parameter record
       *
       * This exports ONLY the parameter value
       *
       * @param[in] spectral_parameter_record
       */
      void ExportSpectralParameterData(SpectralParameterRecord &spectral_parameter_record)
      {
         spectral_parameter_record.setParameterValue(ConvertValueToSpectral(getValue()));
      }

      /**
       * \brief Exports meta-data to the Spectral DLL form of a parameter record
       *
       * This exports all the extra data, but NOT the value itself nor the name
       *
       * @param[in] spectral_parameter_record
       */
      void ExportSpectralParameterMetaData(SpectralParameterRecord &spectral_parameter_record)
      {
         spectral_parameter_record.setParameterMinValue(ConvertMetaValueToSpectral(getValueMin()));
         spectral_parameter_record.setParameterMaxValue(ConvertMetaValueToSpectral(getValueMax()));
         spectral_parameter_record.setParameterStep(ConvertMetaValueToSpectral(getValueStep()));

         // This call needs rethink - it needs to set the unit_type - an integer - needs back map in UnitDesriptor name to integer.
         //spectral_parameter_record.setUnitName(ConvertMetaValueToSpectral(getUnitName()));
         // - call form set function - setUnitName(spectral_parameter_record.getUnitDescriptor().getUnitName());

         //setDataTypeName(typeid(value).name());
         //setUnitType(spectral_parameter_record.getUnitType());

      }

      std::string ConvertValueToSpectral(const std::string& parameterValue)
      {
	 switch(unitType_) {
	 case UNIT_ENUMERATED:
	 case UNIT_ENUMERATED_SPARSE:
	    {
	       // Assume argument is display_name of pull_down  and not actual value
	       std::string name = parameterValue;
	       std::map<std::string, int>::const_iterator ei = enumeratedTypeValue.find(name);
	       if (ei == enumeratedTypeValue.end()) {
		  // If name not found in list, then return string indicating 0
		  RxLog(LOG_ERROR) << "Parameter " << getName() << ": " << parameterValue << " is Invalid Value." << std::endl;
		  return std::string("0");
	       }
	       else {
		  // Convert int to string
		  std::ostringstream oss;
		  oss << ei->second;
		  // return string - this will be a string representation of an integer
		  return oss.str(); 
	       }
	    }
	    break;
	 default:
	    return ConvertMetaValueToSpectral(parameterValue);
	    break;
	 }
      }

      std::string ConvertMetaValueToSpectral(const std::string& parameterValue)
      {
	 if (this->parameterScaler != 0.0) {
	    return SetFloatStringFromString(parameterValue, 1.0 / this->parameterScaler);
	 }
	 else {
	    return SetFloatStringFromString(parameterValue);
	 }
      }

      std::string ConvertValueFromSpectral(const std::string& parameterValue, int default_integer = 0)
      {
	 switch(unitType_) {
	 case UNIT_ENUMERATED:
	 case UNIT_ENUMERATED_SPARSE:
	    {
	       // parameterValue is a Spectral pulldown index
	       int value = atoi(parameterValue.c_str());
	       // Find the corresponding name
	       std::map<int, std::string>::const_iterator ei = enumeratedTypeName.find(value);
	       if (ei == enumeratedTypeName.end()) {
		  std::ostringstream oss;
		  oss << unitType_;
		  return std::string("<Invalid Value> (") + oss.str() + std::string(")");
	       }
	       return ei->second;
	    }
	    break;
	 default:
	    return ConvertMetaValueFromSpectral(parameterValue, default_integer);
	    break;
	 }
      }

      std::string ConvertMetaValueFromSpectral(const std::string& parameterValue, int default_integer = 0)
      {
	 return SetFloatStringFromString(parameterValue, this->parameterScaler, default_integer);
      }


      //! \brief converts string to string representation of an integer
      /** If input is all whitespace, or not valid int, then conversion results in "0"
       *
       * @param[in] input
       * @return
       */

      std::string SetIntegerStringFromString(const std::string& input)
      {
         std::ostringstream ss;

         ss << atoi(input.c_str());

         return ss.str();
      }
      //! \brief converts string to string representation of a scaled real number
      /** If input is all whitespace, or not valid int, then conversion results in "0"
       *  Output will be scaled by scaleFactor.
       * @param[in] input
       * input string representing an integer or real number
       * @param[in] scaleFactor
       * Will scale input value by scaleFactor before converting to output string
       * @param[in] default_integer
       * If the original string is empty or malformed, then this value will be used (before scaling)
       * @return
       * returns a string representation of a real number
       */

      std::string SetFloatStringFromString(const std::string& input, double scaleFactor, int default_integer = 0)
      {
         std::ostringstream ss;

         if (input.length() == 0) {
            ss << scaleFactor * (double) default_integer;
         }
         else {
            ss << scaleFactor * atof(input.c_str());
         }

         return ss.str();
      }
      //! \brief converts string to string representation of a real number
      /** If input is all whitespace, or not valid int, then conversion results in "0"
       * @param[in] input
       * input string representing an integer or real number
       * @param[in] default_integer
       * If the original string is empty or malformed, then this value will be used
       * @return
       * returns a string representation of a real number
       */
      std::string SetFloatStringFromString(const std::string& input, int default_integer = 0)
      {
         return SetFloatStringFromString(input, 1.0, default_integer);
      }

};


//! \private
template<class BUFEL> bool CreateBuffers(bool initialize, size_t n_buffers, int n_fast, int n_slow, BUFEL*** buffer_list);

//! \private
template<class BUFEL> bool CreateBuffers(bool initialize, size_t n_buffers, int n_fast, int n_slow, std::vector<std::vector<BUFEL> >& buffer_list);

//! \private
template<class BUFEL> bool CreateBuffersFromVectors(bool initialize, std::vector<std::vector<BUFEL> > &buffer_vector, BUFEL*** buffer_list, int &n_pixels);

template<class BUFEL> void FreeBuffers(BUFEL** buffer_list);
template<class BUFEL> void FreeBuffers(std::vector<std::vector<BUFEL> >&buffer_list);

//! \private
template<class BUFEL> bool PrintBufferSection(int buffer, int from, int to, BUFEL** buffer_list);
template<class BUFEL> bool PrintBufferSection(int buffer, int from, int to, std::vector<std::vector<BUFEL> >& buffer_list);

// Letters are corner ports of 4 port chip, TopN, BottomN, and ALLN refer to multi-port serial register cameras
enum SerialRegisterInterlaceType_t {A, B, C, D, AB, AC, AD, BC, BD, CD, ABCD, TopN, BottomN, AllN};
enum SensorSerialRegisterInterlaceOrder_t {NoInterlace, SensorFast, SerialFast};
class InterlaceType {
   public:
      SerialRegisterInterlaceType_t serial_interlace;
      SensorSerialRegisterInterlaceOrder_t interlace_order;
      friend std::ostream& operator<< (std::ostream &out, InterlaceType &interlace_type);
};
 
// Overload ostream << operator for the InterlaceType Class
inline std::ostream& operator<< (std::ostream& out,  const InterlaceType& interlace_type)
{
   // Since operator<< is a friend of the InterlaceType class, we can access
   // InterlaceType's members directly.
   out << "(" << static_cast<int>(interlace_type.serial_interlace) << ", " << static_cast<int>(interlace_type.interlace_order) << ")";

   return out;
};

//Camera De-interlace	(type 9): (0="Software" but this option is not included on this camera), 1="Hardware", and 2=" Serial Register Hardware".
enum HardwareDeinterlaceType_t {NoDeinterlace, Hardware, SerialRegisterHardware};


//! Describes the format of the detector in terms of pixels, sensors and sensor sections
class FrameFormat;

//! Data are accessed with getters and thus this class is essentially read-only
//! Only RxDetector and FrameFormat can access data directly in this class
class DetectorFormat
{
   public:
      DetectorFormat() : 
      pixel_depth_(1),
      n_sensors_fast_(1),
      n_sensors_slow_(1),
      sensor_n_sections_fast_(1),
      sensor_n_sections_slow_(1),
      section_n_pixels_fast_(1),
      section_n_pixels_slow_(1)
      {
	 interlace_type_.serial_interlace = A;
	 interlace_type_.interlace_order = NoInterlace;
      }
      //! number of pixels in entire detector
      int n_pixels() const { return n_pixels_fast() * n_pixels_slow(); }
      //! depth of each pixel in bytes
      int depth() const { return pixel_depth_; }
      //! number of pixels in fast direction of detector
      int n_pixels_fast() const { return sensor_n_pixels_fast() * n_sensors_fast_; }
      //! number of pixels in slow direction of detector
      int n_pixels_slow() const { return sensor_n_pixels_slow() * n_sensors_slow_; }
      //! number of sensors in entire detector
      int n_sensors() const {return n_sensors_fast_ * n_sensors_slow_;}
      //! number of sensors in fast direction of detector
      int n_sensors_fast() const {return n_sensors_fast_;}
      //! number of sensors in slow direction of detector
      int n_sensors_slow() const {return n_sensors_slow_;}
      //! number of pixels in the fast direction in each section of a sensor
      int section_n_pixels_fast() const {return section_n_pixels_fast_;}
      //! number of pixels in the slow direction in each section of a sensor
      int section_n_pixels_slow() const {return section_n_pixels_slow_;}
      //! number of pixels in the fast direction of each sensor
      int sensor_n_pixels_fast() const { return section_n_pixels_fast_ * sensor_n_sections_fast_; };
      //! number of pixels in the slow direction of each sensor
      int sensor_n_pixels_slow() const { return section_n_pixels_slow_ * sensor_n_sections_slow_; };
      //! number of sections in the fast direction of each sensor
      int sensor_n_sections_fast() const {return sensor_n_sections_fast_;}
      //! number of sections in the slow direction of each sensor
      int sensor_n_sections_slow() const {return sensor_n_sections_slow_;}
      //! type of pixel interlace in frame (describes which corners where used to readout)
      InterlaceType interlace_type() const {return interlace_type_;}
      //! RxDetector may set the members in this class directly
      friend class RxDetector;
      //! FrameFormat may read members of this class directly
      friend class FrameFormat;
   private:
      int pixel_depth_;
      int n_sensors_fast_;
      int n_sensors_slow_;
      int sensor_n_sections_fast_;
      int sensor_n_sections_slow_;
      int section_n_pixels_fast_;
      int section_n_pixels_slow_;
      InterlaceType interlace_type_;
};

class FrameFormat
{
   public:
      FrameFormat() : 
      pixel_depth_(1),
      n_sensors_fast_(1),
      n_sensors_slow_(1),
      sensor_n_sections_fast_(1),
      sensor_n_sections_slow_(1),
      section_n_pixels_fast_(1),
      section_n_pixels_slow_(1)
      {
	 interlace_type_.serial_interlace = A;
	 interlace_type_.interlace_order = NoInterlace;
      }
      FrameFormat(const DetectorFormat detector_format, int fast_bin = 1, int slow_bin = 1, const HardwareDeinterlaceType_t deinterlace = NoDeinterlace)
      {
         int fast_binning = fast_bin;
         int slow_binning = slow_bin;
	 if (fast_binning <=0) fast_binning = 1;
	 if (slow_binning <=0) slow_binning = 1;
	 pixel_depth_ = detector_format.pixel_depth_;
	 n_sensors_fast_ = detector_format.n_sensors_fast_;
	 n_sensors_slow_ = detector_format.n_sensors_slow_;
	 sensor_n_sections_fast_ = detector_format.sensor_n_sections_fast_;
	 sensor_n_sections_slow_ = detector_format.sensor_n_sections_slow_;
	 section_n_pixels_fast_ = detector_format.section_n_pixels_fast_/fast_binning;
	 section_n_pixels_slow_ = detector_format.section_n_pixels_slow_/slow_binning;
	 switch (deinterlace) {
	    case NoDeinterlace:
	       interlace_type_ = detector_format.interlace_type_;
	       break;
	    case Hardware:
	       interlace_type_.serial_interlace = A;
	       interlace_type_.interlace_order = SensorFast;
	       break;
	    case SerialRegisterHardware:
	       switch(sensor_n_sections_slow_) {
		  default:
		  case 1:
		     interlace_type_.serial_interlace = A;
		     break;
		  case 2:
		     interlace_type_.serial_interlace = AC;
		     break;
	       }
	       interlace_type_.interlace_order = detector_format.interlace_type_.interlace_order;
	       break;
	 }
      }
      //! number of pixels in entire detector
      int n_pixels() const { return n_pixels_fast() * n_pixels_slow(); }
      //! depth of each pixel in bytes
      int depth() const { return pixel_depth_; }
      //! number of pixels in fast direction of detector
      int n_pixels_fast() const { return sensor_n_pixels_fast() * n_sensors_fast_; }
      //! number of pixels in slow direction of detector
      int n_pixels_slow() const { return sensor_n_pixels_slow() * n_sensors_slow_; }
      //! number of sensors in entire detector
      int n_sensors() {return n_sensors_fast_ * n_sensors_slow_;}
      //! number of sensors in fast direction of detector
      int n_sensors_fast() {return n_sensors_fast_;}
      //! number of sensors in slow direction of detector
      int n_sensors_slow() {return n_sensors_slow_;}
      //! number of pixels in the fast direction in each section of a sensor
      int section_n_pixels_fast() {return section_n_pixels_fast_;}
      //! number of pixels in the slow direction in each section of a sensor
      int section_n_pixels_slow() {return section_n_pixels_slow_;}
      //! number of pixels in the fast direction of each sensor
      int sensor_n_pixels_fast() const { return section_n_pixels_fast_ * sensor_n_sections_fast_; };
      //! number of pixels in the slow direction of each sensor
      int sensor_n_pixels_slow() const { return section_n_pixels_slow_ * sensor_n_sections_slow_; };
      //! number of sections in the fast direction of each sensor
      int sensor_n_sections_fast() {return sensor_n_sections_fast_;}
      //! number of sections in the slow direction of each sensor
      int sensor_n_sections_slow() {return sensor_n_sections_slow_;}
      //! type of pixel interlace in frame (describes which corners where used to readout)
      InterlaceType interlace_type() {return interlace_type_;}
   private:
      int pixel_depth_;
      int n_sensors_fast_;
      int n_sensors_slow_;
      int sensor_n_sections_fast_;
      int sensor_n_sections_slow_;
      int section_n_pixels_fast_;
      int section_n_pixels_slow_;
      InterlaceType interlace_type_;
};

class DataMap
{
   public:
      // pure virtual destructor mean that this is a virtual class that can only be used as a base for another derived class
      virtual ~DataMap() = 0;

      std::map<std::string, RxDetectorParameter> theMap;
      virtual RxDetectorParameter* createEntryFromCamera(RxDetector &camera, const std::string& parameter_name) = 0;
      virtual RxDetectorParameter updateEntryFromCamera(RxDetector &camera, const std::string& parameter_name) = 0;
      std::string getName(const std::string& name) { return theMap[name].getName();}
      std::string getValue(const std::string& name) { return theMap[name].getValue();}
      void setValue(const std::string& name, const std::string& value) { theMap[name].setValue(value);}
};
// Requires implementation
inline DataMap::~DataMap() {};

class StatusMap: public DataMap
{
   private:
      RxDetectorParameter* createEntryFromCamera(RxDetector &camera, const std::string& parameter_name);
      RxDetectorParameter updateEntryFromCamera(RxDetector &camera, const std::string& parameter_name);
};

class ParameterMap: public DataMap
{
   private:
      RxDetectorParameter* createEntryFromCamera(RxDetector &camera, const std::string& parameter_name);
      RxDetectorParameter updateEntryFromCamera(RxDetector &camera, const std::string& parameter_name);
};


//! \class RxReturnStatus
//! \brief  Object returned by most RxDetector methods
//!
//! Contins error code and methods for testing error code
//! and pulling out associated text error message

class RxReturnStatus
{
   public:

   // Constructors
   RxReturnStatus(int error_code = 0) {errorCode = error_code;}
   ~RxReturnStatus(){};

   // Public Methods
   int ErrorCode();
   void SetErrorCode(int error_code);
   bool IsImplemented();
   bool IsError();
   std::string ErrorText();

   private:
   int errorCode;

};

//! \class RxThreadGroup 
//! \brief a class for managing a group of threads

class RxThreadGroup
{
   public:

      void add_thread(boost::thread* thread)
      {
	 boost::mutex::scoped_lock lock(threadVectorMutex_);
	 threadVector_.insert(threadVector_.begin(), thread);
	 RxLog(LOG_TRACE) << "RxThreadGroup::add_thread() added a thread to " << this << ", now there are  " << threadVector_.size() << " threads" << std::endl;
      }

      int clean()
      {
	 int count = 0;
	 int n_threads = threadVector_.size();

	 boost::mutex::scoped_lock lock(threadVectorMutex_);
	 for (std::vector<boost::thread*>::iterator ti = threadVector_.begin(); ti != threadVector_.end(); ++ti) {
	    // Join if possible
	    boost::posix_time::time_duration wait_time = boost::posix_time::milliseconds(0);
	    (*ti)->timed_join(wait_time);
	    if ((*ti)->joinable()) {
	       // Still running, it was not done, so count it
	       count++;
	    }
	    else {
	       // It was done, so remove it
	       delete *ti;
	       *ti = NULL;
	    }
	 }
	 // Go through backwards because we might erase an element, which invalidates the iterator for elements after the erased element
	 for (std::vector<boost::thread*>::iterator ti = threadVector_.end(); ti != threadVector_.begin();) {
	    --ti;
	    if (!*ti) {
	       threadVector_.erase(ti);
	    }
	 }
	 RxLog(LOG_TRACE) << "RxThreadGroup::clean() cleaned up " << this << ". Removed " << n_threads - threadVector_.size() << " threads" << std::endl;
	 return count;
      }

      int join_all()
      {
	 int size;
	 boost::mutex::scoped_lock lock(threadVectorMutex_);
	 for (std::vector<boost::thread*>::iterator ti = threadVector_.begin(); ti != threadVector_.end(); ++ti) {
	    (*ti)->join();
	    delete *ti;
	 }
	 size = threadVector_.size();
	 threadVector_.clear();
	 return size;
      }

      int detach_all()
      {
	 int size;
	 boost::mutex::scoped_lock lock(threadVectorMutex_);
	 for (std::vector<boost::thread*>::iterator ti = threadVector_.begin(); ti != threadVector_.end(); ++ti) {
	    (*ti)->detach();
	    delete *ti;
	 }
	 size = threadVector_.size();
	 threadVector_.clear();
	 return size;
      }

      int interrupt_all()
      {
	 int size;
	 boost::mutex::scoped_lock lock(threadVectorMutex_);
	 for (std::vector<boost::thread*>::iterator ti = threadVector_.begin(); ti != threadVector_.end(); ++ti) {
	    (*ti)->interrupt();
	    (*ti)->detach();
	    delete *ti;
	 }
	 size = threadVector_.size();
	 threadVector_.clear();
	 return size;
      }

   private:
      std::vector<boost::thread*> threadVector_;
      boost::mutex threadVectorMutex_;
};

#if 1

class RxStatusLogState
{
   public:
      RxStatusLogState() : newData(false) {}
      ~RxStatusLogState() {}

   public:
      std::map<StatusParameter_t, std::string> statusValuesMap;
      std::map<StatusParameter_t, std::string> statusFlagsMap;
      std::map<std::string, std::string> statusUnkeyedFlagsMap;
      bool newData;
      Mutex_t values_mutex;
      ConditionVariable_t condition;
      Mutex_t condition_mutex;
};

//! \brief The callback that StatusLogger uses to get and report status values from a detector
/*! 
 * @param detector
 * a detector object
 *
 */
class RxStatusValueLoggerCallback : public VirtualKeyedStateChangeCallback
{
   public:
      RxStatusValueLoggerCallback(RxDetector &detector, RxStatusLogState &statusLogState);
      
      ~RxStatusValueLoggerCallback() {};

      void StatusChanged() {}
      void StatusChanged(const std::string& name, const std::string& value) {}
      void StatusParameterChanged(const StatusParameter_t key = NullParameter, const std::string& value = std::string(""));
      void ParameterChanged() {}
      void ParameterChanged(const std::string& name, const std::string& value) {}

   private:
      RxDetector& detector_;
      RxStatusLogState &statusLogState_;
      
};

//! \brief The callback that StatusLogger uses to get and report status flags from a detector
/*! 
 * @param detector
 * a detector object
 *
 */
class RxStatusFlagLoggerCallback : public VirtualKeyedStateChangeCallback
{
   public:
      RxStatusFlagLoggerCallback(RxDetector &detector, RxStatusLogState &statusLogState);
      
      ~RxStatusFlagLoggerCallback() {};

      void StatusChanged() {}
      void StatusChanged(const std::string& name, const std::string& value) {}
      void StatusParameterChanged(const StatusParameter_t key = NullParameter, const std::string& value = std::string(""));
      void StatusFlagChanged(const VStatusFlag* VSF_p);
      void ParameterChanged() {}
      void ParameterChanged(const std::string& name, const std::string& value) {}

   private:
      RxDetector& detector_;
      RxStatusLogState &statusLogState_;
      
};

//! \brief Creates a thread for logging detector status and manages status logging
/*! 
 * @param detector
 * a detector object
 *
 */
class RxStatusLogger
{
   public:
      RxStatusLogger(RxDetector &detector);
      ~RxStatusLogger();

      void SetUpdateIntervalMinimum(double seconds) {if (seconds >= 1.0) UpdateIntervalMinimum_ = boost::posix_time::seconds(seconds);}
      //void SetUpdateIntervalMinimum(RxTimeDuration_t interval) {UpdateIntervalMinimum_ = interval;}
      void SetUpdateIntervalMaximum(double seconds) {if (seconds >= 1.0) UpdateIntervalMaximum_ = boost::posix_time::seconds(seconds);}
      //void SetUpdateIntervalMaximum(RxTimeDuration_t interval) {UpdateIntervalMaximum_ = interval;}
      void Enable(bool enable = true) {enabled_ = enable;}


   private:
      void Initialize();
      void InitializeStatusValueItem(const StatusParameter_t key, const std::string& value = std::string("???"));
      void InitializeStatusFlagItem(const StatusParameter_t key, const std::string& value = std::string("?"));
      void LogUpdater();
      void LogTitles();
      void LogStatus();
      void Start();
      void Terminate();

   private:
      RxDetector& detector_;
      bool enabled_;
      bool terminate_;
      RxTimeDuration_t UpdateIntervalMinimum_;
      RxTimeDuration_t UpdateIntervalMaximum_;
      //RxTimestamp_t LastLogTimestamp_;
      boost::system_time LastLogTimestamp_;
      RxStatusValueLoggerCallback* ValueLoggingCallback_p_;
      RxStatusFlagLoggerCallback* FlagLoggingCallback_p_;
      boost::thread *StatusLoggerThread_p_;
      RxStatusLogState StatusLogState_;
      std::vector<CallbackConnection_t> status_callbacks;
      
};
#endif


//! \class RxDetector 
//! \brief implementation of the RxVDetector interface
/*! This class implements a real detector.
 */

//class RxDetector: public RxVDetector, public KeyedCallbackInterface<VirtualKeyedStateChangeCallback>, public KeyedCallbackInterface<VirtualFrameCallback>
class RxDetector: public KeyedCallbackInterface<VirtualKeyedStateChangeCallback>, public KeyedCallbackInterface<VirtualFrameCallback>
{

      friend class SpectralFrameCB;
      friend class ParameterMap;
      friend class StatusMap;
      friend class RxStatusLogger;

   // Constructors
   public:
      RxDetector(const std::string& config_file = std::string(""));
      ~RxDetector();
   private:
      //RxDetector(RxDetector const&){}	// copy constructor is private - no copies!
      // cppcheck-suppress *
      RxDetector& operator=(RxDetector const& rhs){/* This is broken too - but don't really need it */return *this;}  // assignment operator is private

   public:
      // Public Methods

      //! \brief Opens a Detector device and synchronizes internal data with detector data.
      RxReturnStatus Open(const std::string& device_name = std::string(""));

      //! \brief Closes a Detector device.
      //! Close will call EndAcquisition() to cleanup buffers and callbacs before returning
      RxReturnStatus Close();

      RxReturnStatus SetReadoutMode(const std::string& mode_string);
      RxReturnStatus SetReadoutMode(ReadoutMode_t mode);
      ReadoutMode_t ReadoutMode();

      //
      // The Status Getters
      //
   private:
      RxReturnStatus InitializeVirtualStatusObjects();
      bool VPMFlag(const std::string& bitname);
      bool VPMFlag(int bitmask);

   public:
      bool CoolerEnabled();
      bool CoolerOn();
      bool CoolerRunning();
      bool DetectorIntegrating();

      //! \brief Returns the current being drawn by the cooler
      //
      //! @return
      //! Current, in Amps, being drawn by the cooler
      double CoolerCurrent();

      //! \brief Returns the minimum sensor temperature
      //
      //! @return
      //! temperature of the coolest sensor in degrees Celsius
      double SensorTemperatureMin();

      //! \brief Returns the maximum sensor temperature
      //
      //! @return
      //! temperature of the warmest sensor in degrees Celsius
      double SensorTemperatureMax();

      //! \brief Returns the average sensor temperature
      //
      //! @return
      //! average temperature of the sensors in degrees Celsius
      double SensorTemperatureAve();

      //! \brief Returns the temperatures of all the sensors
      //
      //! @param[out] temperatures_C
      //! a vector containing the temperatures of each of the sensors in degrees Celsius
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SensorTemperatures(std::vector<double>& temperatures_C);

      double SensorTemperature(int Sensor);

      RxReturnStatus SensorTemperature(int Sensor, double& temperature_C);

      //! \brief Returns the minimum cold-head temperature
      //
      //! @return
      //! temperature of the coolest cold-head in degrees Celsius
      double CoolerTemperatureMin();

      //! \brief Returns the maximum cold-head temperature
      //
      //! @return
      //! temperature of the warmest cold-head in degrees Celsius
      double CoolerTemperatureMax();

      //! \brief Returns the average cold-head temperature
      //
      //! @return
      //! average temperature of the cold-heads in degrees Celsius
      double CoolerTemperatureAve();

      //! \brief Returns the temperatures of all the cold-heads
      //
      //! @param[out] temperatures_C
      //! a vector containing the temperatures of each of the cold-heads in degrees Celsius
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus CoolerTemperatures(std::vector<double>& temperatures_C);


      std::vector<std::string> ConfirmStatusNames(const std::vector<std::string> canonical_names, std::string* namescsv_p);

      std::vector<std::string> SensorTemperatureNames(std::string* namescsv_p = NULL);
      std::string SensorTemperatureName(int sensor);

      std::vector<std::string> CoolerTemperatureNames(std::string* namescsv_p = NULL);
      std::string CoolerTemperatureName(int sensor);

      std::vector<std::string> AmbientTemperatureNames(std::string* namescsv_p = NULL);
      std::vector<std::string> PowerSupplyTemperatureNames(std::string* namescsv_p = NULL);
      std::vector<std::string> SystemTemperatureNames(std::string* namescsv_p = NULL);
      std::vector<std::string> CoolerPressureNames(std::string* namescsv_p = NULL);

      RxReturnStatus AmbientTemperatures(std::vector<double>& temperatures_C);
      RxReturnStatus PowerSupplyTemperatures(std::vector<double>& temperatures_C);
      RxReturnStatus SystemTemperatures(std::vector<double>& temperatures_C);
      RxReturnStatus CoolerPressures(std::vector<double>& Pressures_Torr);

      //! \brief Returns the vacuum chamber pressure
      //
      //! @return
      //! pressure of the vacuum chamber in Torr
      double ChamberPressure();

      //! \brief Returns the vacuum line pressure
      //
      //! @return
      //! pressure of the vacuum line in Torr
      double LinePressure();


      //! \brief Updates the status values from the detector
      //
      //! UpdateStatus() sends a query to the detector and receives all the status parameters
      //! This results in significant I/O between host and detector
      //! This should normally be called when up-to-date information is needed, or in can
      //! be called regularly  with setStatusUpdateInterval()
      RxReturnStatus UpdateStatus();

      RxReturnStatus GetStatusItems(std::vector<StatusParameter_t> &status_item_list);

      std::string StatusName(StatusParameter_t item);

      template<class ReturnDataType> RxReturnStatus GetStatusValue(StatusParameter_t item, ReturnDataType &value);

      std::string StatusValueString(StatusParameter_t item);

      RxReturnStatus GetStatusNames(std::vector<std::string> &status_name_list);

      bool HasStatusParameter(const std::string& parameter_name);

      //! @return
      //! returns RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED
      RxReturnStatus GetRawStatusPulldownItem(const std::string& displayName, int PulldownIndex, std::string& PulldownValStr,
                                              std::string& PulldownName);
      //! @return
      //! returns RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED
      RxReturnStatus GetRawStatusBitField(const std::string& displayName, std::string& maskStr, std::string& display);

      //! \brief Gets the list of Names of Status items in the detector
      RxReturnStatus GetRawStatusNames(std::vector<std::string> &status_name_list);

      //! \brief Returns value of a status parameter in it's correct scale and units into a typed variable - caller must know what type to expect
      template<class ReturnDataType> RxReturnStatus GetRawStatusValue(const std::string& displayName, ReturnDataType &value, bool warn = true);

      RxReturnStatus GetRawStatusValue(const std::string& displayName, std::string& value, bool warn = true);

      //! \brief Returns value of a status parameter as a string
      std::string RawStatusValueString(const std::string& displayName);
      
      //! \brief Returns value and units of a status parameter as a string
      std::string RawStatusValueStringWithUnit(const std::string& displayName);

      bool RawStatusBit(const std::string& displayName, const std::string& bitname, bool warn = true);

   private:

      //! \brief Determine and return the interlace type from the camera parameters
      RxReturnStatus GetInterlaceType(InterlaceType& interlace_type);

      static RxReturnStatus ConvertInterlaceTypeToDeinterlaceCode(const InterlaceType& interlace_type, int& deinterlace_code);

      int BestNBuffers();

   public:

      //! \brief Get the parameters describing the format of the detector itself (!not the format of a frame)
      RxReturnStatus GetDetectorFormat(DetectorFormat& format);

      //! \brief Get the parameters describing the format of a data frame from the detector
      RxReturnStatus GetFrameFormat(FrameFormat& format);

      //! \brief Get the number of pixels in the fast and slow directions and depth of pixel in bytes
      //
      //! return value is number of pixel in frame
      int GetFrameSize(int &fast_pixels, int& slow_pixels, int& pixel_depth);

      //! \brief Get the number of pixels in a full image in the fast direction according to current parameters
      //
      //! @return
      //! returns length in fast direction;
      int FastLength();

      //! \brief Get the number of pixels in in a full image the slow direction according to current parameters
      //
      //! @return
      //! returns length in slow direction;
      int SlowLength();

      //! \brief returns a detector hardware model name and revision string
      RxReturnStatus GetDetectorID(std::string& name, std::string& serial_number);

      //! \brief returns a detector firmware name (partnumber) and version (revision)
      RxReturnStatus GetDetectorFirmwareID(std::string& name, std::string& version);

      //! \brief returns a vector containing all allowable binning combinations (a vector of vectors <fast_binning,slow_binning>)
      //
      //! @param[out] binning_list
      //! a vector containing vectors of binnings.  Each binning is a vector of length 2 containing binning in fast and slow directions
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus GetAllowedBinningList(std::vector<std::vector<int> >& binning_list);

      //! \brief Get the current binning setting
      //
      //! Gets both fast and slow binning, which may differ
      //! @param[out] fast_binning
      //! binning in fast direction
      //! @param[out] slow_binning
      //! binning in fast direction
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus GetBinning(int &fast_binning, int& slow_binning);
      std::pair<int,int> Binning();
      
      bool CheckBinning(int fast, int slow);

      RxReturnStatus GetPixelSize(double& pixelsize_fast, double& pixelsize_y);
      std::pair<double,double> PixelSize();

      int NSensors();

      //! \brief Gets the sensor temperature setpoint
      //
      //! @return
      //! the setpoint temperature of the sensor in degrees Celsius
      //! In a multi-sensor, the highest setpoint of all the sensors will be returned
      double SensorTemperatureSetpoint();

      //! \brief Sets the sensor temperature setpoint
      //
      //! @param[out] temperature_C
      //! the setpoint temperature of the sensor in degrees Celsius
      //! In a multi-sensor, the setpoints of all the sensors be set to this temperature
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SetSensorTemperatureSetpoint(double temperature_C);

      RxReturnStatus GetSensorTemperatureSetpoints(std::vector<double>& temperatures_C);
      RxReturnStatus SetSensorTemperatureSetpoints(const std::vector<double>& temperatures_C);

      //! \brief Gets the cold-head temperature setpoint
      //
      //! @return
      //! the setpoint temperature of the cold-head in degrees Celsius
      //! In a multi-cooler, the highest setpoint of all the cold-heads will be returned
      double CoolerTemperatureSetpoint();

      //! \brief Sets the cold head temperature setpoint
      //
      //! @param[out] temperature_C
      //! the setpoint temperature of the cold head in degrees Celsius
      //! In a multi-cooler system, the setpoints of all the coolers will be set to this temperature
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SetCoolerTemperatureSetpoint(double temperature_C);

      RxReturnStatus GetCoolerTemperatureSetpoints(std::vector<double>& temperatures_C);
      RxReturnStatus SetCoolerTemperatureSetpoints(const std::vector<double>& temperatures_C);

      //! \brief Returns the Shutter Open Delay
      //
      //! @return
      //! the Shutter Open Delay in seconds
      double ShutterOpenDelay();
      RxReturnStatus SetShutterOpenDelay(double time_sec);

      //! \brief Returns the Shutter Close Delay
      //
      //! @return
      //! the Shutter Close Delay in seconds
      double ShutterCloseDelay();
      RxReturnStatus SetShutterCloseDelay(double time_sec);

      TriggerType_t TriggerType();
      RxReturnStatus SetTriggerType(const TriggerType_t type);
      RxReturnStatus SetTriggerType(const std::string& name);

      TriggerMode_t TriggerMode();
      RxReturnStatus SetTriggerMode(const TriggerMode_t mode);

      TriggerSetupIn_t  TriggerSetupIn(int trigger_line);
      TriggerSetupOut_t  TriggerSetupOut(int trigger_line);
      TriggerSelectorOut_t TriggerSelectorOut(int trigger_line);

      RxReturnStatus SetTriggerSetupIn(int trigger_line, const TriggerSetupIn_t& signal);
      RxReturnStatus SetTriggerSetupOut(int trigger_line, const TriggerSetupOut_t& signal);
      RxReturnStatus SetTriggerSelectorOut(int trigger_line, const TriggerSelectorOut_t& signal);


      //! \brief Gets the maximum latency for responding to triggers
      //
      //! Unless a Trigger Latency is set using SetTriggerLatency, then the latency
      //  to respond to triggers is variable  (jitter).  This reports the maximum expected latency
      RxReturnStatus GetTriggerMaximumLatency(double& time_sec);

      //! \brief Gets the latency for responding to triggers
      //
      //! @return
      //! returns RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED
      RxReturnStatus GetTriggerLatency(double& time_sec);

      //! \brief Sets the latency for responding to triggers
      //
      //! @return
      //! returns RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED
      RxReturnStatus SetTriggerLatency(double time_sec);

   private:
      // Used to reset internal sequence mode after change to mpp or fast bulb
      RxReturnStatus SetSequenceMode();
      RxReturnStatus SetSequenceGate();
   public:
      SequenceMode_t SequenceMode();
      RxReturnStatus SetSequenceMode(SequenceMode_t mode);
      SequenceGate_t SequenceGate();
      RxReturnStatus SetSequenceGate(SequenceGate_t gate);
      bool MPPEnabled();
      RxReturnStatus DisableMPP();
      RxReturnStatus EnableMPP(bool enable = true);
      bool FastBulbEnabled();
      RxReturnStatus DisableFastBulb();
      RxReturnStatus EnableFastBulb(bool enable = true);

      //! \brief Returns the exposure time setting in seconds
      //
      //! @return
      //! the exposure time in seconds.  minimum resolution is 1ms. (0.001)
      double ExposureTime();

      //! \brief Sets the exposure time in seconds
      //
      //! @param[out] time_sec
      //! the exposure time in seconds.  minimum resolution is 1ms. (0.001)
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SetExposureTime(double time_sec);


      //! \brief Returns the frame interval time setting in seconds
      //
      //! @return
      //! the frame interval time in seconds.  minimum resolution is 1ms. (0.001)
      double IntervalTime();

      //! \brief Sets the exposure time in seconds
      //
      //! @param[out] time_sec
      //! the frame interval time in seconds.  minimum resolution is 1ms. (0.001)
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SetIntervalTime(double time_sec);

   private:
      double ExposureTimeInDetector();
      RxReturnStatus SetExposureTimeInDetector(double time_sec);
      double IntervalTimeInDetector();
      RxReturnStatus SetIntervalTimeInDetector(double time_sec);

   public:

      //! \brief Returns the type of testpattern, or data to be generated on  readout
      //
      //! @return
      //! returns TestPattern_t indicating type of test pattern or
      //! TESTPATTERN_NONE of data will be generated
      TestPattern_t TestPattern();


      //! \brief Sets the type of test image to produce when a test image is acquired
      //! If not changing pattern, but only turning it on and off, it is preffered to use UseTestPattern()
      //
      //! @param[in] testpattern
      //! The type of test pattern, or TESTPATTERN_NONE for data
      //! @return
      //! returns RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED
      RxReturnStatus SetTestPattern(TestPattern_t testpattern);

      //! \brief informs caller whether or not detector is generating test pattern
      //
      //! @return
      //! true if detector images will be test patterns, false if they will be data
      bool UsingTestPattern();

      //! \brief tells detector to generate test patterns or data on readout
      //
      //! @param[in] use_testpattern
      //! true indicats that detector should generate test patterns
      //! false indicats that detector should generate data
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus UseTestPattern(bool use_testpattern);

      //! \brief Updates parameters with fresh data from detector
      //! @param[in] cancel_changes
      //! if cancel_changes is false (default), then pending changes will not be cancelled and will be downloaded to the detector
      //! at the next call SendParamters()
      //! if cancel_changes is true, then pending changes will be overwritten by data from the detector
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus GetParameters(bool cancel_changes = false);

      //! \brief Gets the list of Names of Parameters in the detector
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus GetParameterNames(std::vector<std::string> &parameter_name_list);

      //! \brief Determines is a parameter is present in the parameter list for this detector
      //! @return
      //! returns true if present, false otherwise;
      bool HasParameter(const std::string& parameter_name);

      //! \brief Gets a single Parameter item from the detector
      //   RxReturnStatus GetParameterItem(const std::string& parameter_name_arg, RxDetectorParameter &r_parameter);

      //! \brief Gets the Parameter items from the detector
      //   RxReturnStatus GetParameterItems(std::vector<std::string> &parameter_name_list);
      //   RxReturnStatus GetParameterItems(std::vector<std::string> &parameter_name_list, std::vector<RxDetectorParameter> &parameter_list);
      //   RxReturnStatus GetParameterItemMap(std::vector<std::string> &parameter_name_list, std::map<std::string, RxDetectorParameter*> parameter_map);

      //! @return
      //! returns RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED
      RxReturnStatus GetParameterPulldownItem(const std::string& displayName, int PulldownIndex, std::string& PulldownValStr,
                                              std::string& PulldownName);
      //! @return
      //! returns RX_EXCEPTION_FEATURE_NOT_IMPLEMENTED
      RxReturnStatus GetParameterBitField(const std::string& displayName, std::string& maskStr, std::string& display);

      //! \brief Returns pointer to parameter - it may be retrieved from standard map, or changed map, if it has been changed,
      // but not yet downloaded by SendParameters()
      //! @param[in] displayName
      //! Parameter name
      //! @return
      //! returns parameter;
      //
      RxDetectorParameter GetParameter(const std::string& displayName);

      //! \brief Returns pointer to parameter - it may be retrieved from standard map, or changed map, if it has been changed,
      // but not yet downloaded by SendParameters()
      //! @param[in] displayName
      //! Parameter name
      //! @return
      //! returns iterator to map entry, otherwise returns NULL;
      std::map<std::string, RxDetectorParameter>::iterator GetParameterI(const std::string& displayName);

      //! \brief Returns value of parameter in it's correct scale and units into a typed variable - caller must know what type to expect
      template<class ReturnDataType>
      RxReturnStatus GetParameterValue(const std::string& displayName, ReturnDataType &value, bool warn = true);
      RxReturnStatus GetParameterValue(const std::string& displayName, std::string& value, bool warn = true);

      template<class ReturnDataType> RxReturnStatus GetParameterValueLimits(const std::string& displayName, ReturnDataType &min, ReturnDataType &max);

      //! \brief Returns value of a status parameter as a string
      std::string ParameterValueString(const std::string& displayName);

      //! \brief Returns value and units of a status parameter as a string
      std::string ParameterValueStringWithUnit(const std::string& displayName);

   //private:
   public:

      template<class DataType> bool IsValidParameterValue(const std::string& displayName, const DataType value);
      // A specialization (overload) for strings
      bool IsValidParameterValue(const std::string& displayName, const std::string& value);

      //! \brief Sets a Parameter 
      template<class T>
      RxReturnStatus SetParameterValue(const std::string& displayName, const T value);

      // A specialization (overload) for strings
      RxReturnStatus SetParameterValue(const std::string& displayName, const std::string& value);
      RxReturnStatus SetParameterValue(const std::string& displayName, const char*  value);

      RxReturnStatus SendParameters();

   public:

      //! \brief Sets detector for sequence of frames and registers callbacks.
      /*! If nframes is greater than nbuffers, then the buffers will be treated as a ring-buffer.
       *
       * @param[in] n_frames
       * the number of frames ( <= 0 indicates infinite number).
       * @param[in] start_frame_number
       * the number to be given to the first frame generated
       * @param[in] skip_initial_frames
       * the number of frames to be skipped initially before starting to generate callbacks
       * @return
       * returns status in RxReturnStatus object
       *
       * \bug multiple frame buffers not yet implemented in Spectral Plugins
       */
      RxReturnStatus SetupRawAcquisitionSequence(int n_frames, int start_frame_number = 1, int skip_initial_frames = 0);

   private:
      RxReturnStatus SetupRawAcquisitionSequenceInternal(int n_frames, int start_frame_number = 1, int skip_initial_frames = 0);
   public:

      //! \brief Sets detector for sequence of frames and registers callbacks.
      /*! If nframes is greater than nbuffers, then the buffers will be treated as a ring-buffer.
       *
       * @param[in] n_frames
       * the number of frames ( <= 0 indicates infinite number).
       * @param[in] start_frame_number
       * the number of the first frame (this is the starting number for the entire sequence).
       * This number will determine the number that is passed as an argument to all frame callback methods
       * @param[in] skip_initial_frames
       * the number of frames that will be discarded before any frame callback method is called.  The first frame AFTER
       * the skipped frames will be numbered with the start_frame_number.
       * @return
       * returns status in RxReturnStatus object
       *
       * \bug multiple frame buffers not yet implemented in Spectral Plugins
       */
      RxReturnStatus SetupAcquisitionSequence(int n_frames, int start_frame_number = 1, int skip_initial_frames = -1);

      bool NewBackgroundNeeded();

      RxReturnStatus AcquireNewBackground(bool block = false, int n_backgrounds = 0);

      RxReturnStatus ClearRawFrameBuffers();

      RxReturnStatus ClearCorrectedFrameBuffers();

      template<class PIXEL>
      RxReturnStatus SetupRawFrameBuffers(PIXEL**  buffer_list, size_t n_buffers, int fast_length, int slow_length);

      RxReturnStatus InitializeRawFrameBuffers(int value = 0);

      RxReturnStatus SetupCorrectedFrameBuffers();

      RxReturnStatus InitializeCorrectedFrameBuffers(int value = 0);

      RxReturnStatus SetupBufferInterlaceInfo(std::vector<RxFrame*>& frame_buffer_list, int interlaced, const DetectorFormat& detector_format);

#if NEWACQTYPE

      //! Set number of frames to collect and starting frame number
      RxReturnStatus SetNFrames(int n_frames, int start_frame_number = 1);

   private:
      //! Set number of frames to collect - private method can also set skip_initial_frames
      RxReturnStatus SetNFrames(int n_frames, int start_frame_number, int skip_initial_frames);
#endif

   public:

      RxReturnStatus SetAcquisitionUserCB(VirtualFrameCallback* cb = NULL);

   private:
      RxReturnStatus SetActiveAcquisitionCallback(VirtualFrameCallback* cb = NULL);


      //! Register a callback class containing methods to be called at various stages of frame acquisition
      
      //! @param[in] key
      //! @param[in] callback
      //! @return
      //! returns a value that can be used to later unregister the callback
      CallbackConnection_t RegisterFrameCallback(const std::string& key, VirtualFrameCallback* callback);

      //! Register a callback class containing methods to be called at various stages of frame acquisition
      
      //! @param[in] callback
      //! @return
      //! returns a value that can be used to later unregister the callback
      CallbackConnection_t RegisterFrameCallback(VirtualFrameCallback* callback);

      //! Unregister a callback previously registered with RegisterFrameCallback
      
      //! @param[in] conn
      //! a CallbackConnection_t returned by RegisterFrameCallback
      void UnregisterFrameCallback(CallbackConnection_t conn);

      //! Unregister all the callbacks register for frame acquisition
      void UnregisterAllFrameCallbacks();

   private:

      //! \brief Opens a Detector device without any other setup or intialization (for internal use, debugging, and development only)
      RxReturnStatus OpenRaw(const std::string& device_name = std::string(""));

      //! \brief Sets up default values from config file, including the detector device - call before OpenRaw();
      RxReturnStatus InitializeConfiguration(const std::string& detector_name);

      bool HardwareConfigurationIsOK(bool verbose = true, bool fatal = false);

      //! \brief Downloads defaults to camera - call after (or within) Open()
      RxReturnStatus DownloadDefaults();

      //! \brief Issue a general command to the camera, without checking to see if parameters are uptodate
      RxReturnStatus IssueCommandRaw(const std::string& command, const std::string& argument, std::string& return_value);

      //! \brief Sets the baud rate for serial communication to the Detector.
      RxReturnStatus SetBaudRate(int baud_rate);

      //! \brief Gets the baud rate for serial communication to the Detector.
      RxReturnStatus GetBaudRate(int &baud_rate);

      void SignalSequenceStarted(bool new_thread = false);
      void SignalSequenceEnded(bool new_thread = false);
      void SignalExposureStarted(int frame_number, bool new_thread = false);
      void SignalExposureEnded(int frame_number, bool new_thread = false);
      void SignalReadoutStarted(int frame_number, bool new_thread = false);
      void SignalReadoutEnded(int frame_number, bool new_thread = false);
      void SignalBackgroundFrameReady(RxFrame* frame_p, bool new_thread = false);
      void SignalRawFrameReady(int frame_number, RxFrame* frame_p, bool new_thread = false);
      void SignalFrameReady(int frame_number, RxFrame* frame_p, bool new_thread = false);
      void SignalFrameAborted(int frame_number, bool new_thread = false);
      void SignalFrameCompleted(int frame_number, bool new_thread = false);
      void SignalFrameError(int frame_number, int error_code, const std::string& error_string, bool new_thread = false);


   public:

      //! Reorient (rotate or mirror) a frame
      RxTransformationCode_t GetReorientation(RxTransformationCode_t transformation = R0);
#if 0
      bool ReorientFrame(RxTransformationCode_t transformation_code, RxFrame* frame_p);
      bool ReorientFrame(RxTransformationCode_t transformation_code, const RxFrame* input_frame_p, RxFrame* output_frame_p);
#endif


      //! Corrects a frame
      
      //! @param[in] frame_p
      //! pointer to a frame object containing a raw frame to be corrected
      bool CorrectFrame(RxFrame* frame_p);

      //! Corrects a frame
      
      //! @param[in] raw_frame_p
      //! @param[out] corrected_frame_p
      //! pointer to a frame object to receive the corrected frame.  If not present, or NULL, then corrected data will be written back to raw_frame_p
      //! @return
      //! returns true if frame is successfully corrected, false otherwise;
      bool CorrectFrame(const RxFrame* raw_frame_p, RxFrame* corrected_frame_p);

      //! Deinterlace a frame
      
      //! @param[in] input_frame_p
      //! pointer to a frame object to receive the corrected frame.  If not present, or NULL, then deinterlaced data will be written back to input_frame_p
      //! @return
      bool DeinterlaceFrame(RxFrame* input_frame_p);

      //! Deinterlace a frame
      
      //! @param[in] input_frame_p
      //! pointer to a frame object containing a raw frame to be corrected
      //! @param[out] output_frame_p
      //! pointer to a frame object to receive the corrected frame.  If not present, or NULL, then deinterlaced data will be written back to input_frame_p
      //! @return
      //! returns true if frame is successfully deinterlaced, false otherwise;
      bool DeinterlaceFrame(const RxFrame* input_frame_p, RxFrame* output_frame_p);

      //! Trigger the device to start accumulating data (stop continuous clearing)
      RxReturnStatus StartIntegration();

      //! Trigger the device to stop accumulating data (start continuous clearing)
      RxReturnStatus StopIntegration();

      //! Trigger the acquisition of a single or sequence of frames.
      RxReturnStatus StartAcquisition(RxFrameAcquisitionType acquistionType);

      RxReturnStatus AcquisitionStatus(double &r_series_percent, int &r_expose_frame_number, double &r_percent_exposed, int &r_readout_frame_number, double &r_percent_read);

      //! Retrieve integration time remaining, in secs, from detector
      double IntegrationTimeRemaining();

      //! Retrieve readout time remaining, in secs, from detector
      double ReadTimeRemaining();

      //! Ends a series of frames and deregisters callbacks, with optional forcible end of current acquisition
      
      //! EndRawAcquisition will cleanup up frame acquisition buffers and deregister all frame acquisition callbacks.
      
      //! @param[in] abort
      //! If abort is false, then EndRawAcquisition will wait until acquisition completes
      //! If abort is true, then acquistion will be terminated immediately
      //! @return
      //! returns RX_EXCEPTION_NONE;

      RxReturnStatus EndRawAcquisition(bool abort = false);

      //! Ends a series of frames and deregisters callbacks, with optional forcible end of current acquisition
      
      //! EndAcquisition will cleanup up frame acquisition buffers and deregister all frame acquisition callbacks.
      
      //! @param[in] abort
      //! If abort is false, then EndAcquisition will wait until acquisition completes
      //! If abort is true, then acquistion will be terminated immediately
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus EndAcquisition(bool abort = false);

      //! Issue a general command to the camera
      RxReturnStatus IssueCommand(const std::string& command, const std::string& argument, std::string& return_value);

      //! Operate the shutter.
      
      //! @param[in] open
      //! True to open shutter, false to close shutter
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus CommandShutter(bool open);

      //! Open the shutter.
      
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus OpenShutter();

      //! Close the shutter.
      
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus CloseShutter();

      //! Enable/Disable the cooler
      
      //! @param[in] enable
      //! True to enable cooler, false to disable cooler
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus CommandCooler(bool enable);

      //! Enable the detector cooling. Cooler will actuall come on only if
      //! controller determines that other conditions allow it
      
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus EnableCooler();

      //! Turns the detector cooling off.
      
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus DisableCooler();

      //! Enable/Disable the Vacuum Valve
      
      //! @param[in] enable
      //! True to enable vacuum valve, false to disable vacuum valve
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus CommandVacuumValve(bool enable);

      //! Enable the detector vacuum valve. Vacuum Valve will actually open only if
      //! controller determines that other conditions allow it
      
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus EnableVacuumValve();

      //! Disable (close) the detector vacuum valve.
      
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus DisableVacuumValve();

      //! Ignore the status of the vacuum pump.
      //! @param[in] ignore
      //! True to ignore pump status, False to pay attention to pump status when controlling vacuum valve
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus IgnoreVacuumPump(bool ignore = true);

      //! Set/Unset Purge Mode
      //! WARNING:
      //! Purge Mode disable any and all checks on valide conditions for opening the vacuum valve
      //! When Purge Mode is true, the valve will open when enabled regardless of the pressure in the line and chamber
      
      //! @param[in] state
      //! True to disable all checks. (WARNING - Vacuum valve may open and vent chamber suddenly!)
      //! @param[in] password
      //! Password is required to activate this mode
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SetPurgeMode(bool state, const std::string& password = std::string(""));

      //! Change binning
      //
      //! Changes both fast and slow binning
      
      //! @param[in] binning
      //! binning parameter to be used for both directions of frame
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SetBinning(int binning);

      //! Change binning
      
      //! Changes fast and slow binning independently
      
      //! @param[in] fast_binning
      //! binning parameter to be used for the fast_direction
      //! @param[in] slow_binning
      //! binning parameter to be used for the slow_direction
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SetBinning(int fast_binning, int slow_binning);
      RxReturnStatus SetBinning(std::pair<int,int> binning);

      //! Returns the number of pixels left to read.
      RxReturnStatus GetReadStatus();

      //! Saves the current parameters as a mode.
      
      //! @param[in] mode
      //! mode to save - modes are numbered from 1 to ?
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus ModeSave(int mode);

      //! Retrieve a saved mode to the current parameters.
      
      //! @param[in] mode
      //! mode to recall - see ModeSave()
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus ModeRecall(int mode);

      //! Deletes a saved mode.
      
      //! @param[in] mode
      //! mode to delete - see ModeSave()
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus ModeDelete(int mode);

      //! Aborts an integration/exposure/readout
      RxReturnStatus Abort();

      //! Reboots the detector controller and performs and closes and reopens the device
      //!
      //! @param[in] raw_reset
      //! Normally System reset will close and reopen the detector to synchonize parameters.
      //! If raw_reset is true, then no Close/Open will be done.   The parameters will be out-of-sync. Use raw_reset=true with extreme care!
      //! @return
      //! returns RX_EXCEPTION_NONE;
      RxReturnStatus SystemReset(bool raw_reset = false);

      //! Saves the Setup parameters to flash memory in detector controller
      RxReturnStatus SetupSave();
      
      //! Recalls the Setup parameters from flash memory in detector controller
      RxReturnStatus SetupRecall();

      //! Enables update of all Status items from the camera
      RxReturnStatus EnableRawStatusUpdate();
      //! Enables update of this Status item from the camera
      RxReturnStatus EnableRawStatusItemUpdate(const std::string& displayName);

      //! Disables update of all Status items from the camera
      RxReturnStatus DisableRawStatusUpdate();
      //! Disable update of this Status item from the camera
      RxReturnStatus DisableRawStatusItemUpdate(const std::string& displayName);

      //! Setup Correction data for correcting frames as they are collected
      //template<class PIXEL>
      //RxReturnStatus SetupCorrection(PIXEL &pixel, int n_fast, int n_slow, const InterlaceType& interlace_type, bool deinterlace);

      RxReturnStatus SetupCorrection(const RxFrame* template_frame_p, const InterlaceType& interlace_type, bool deinterlace, bool force, const std::string& base_filename = std::string(""), const std::string& base_pff_filename = std::string(""));

      //! Delete the Correction data
      RxReturnStatus DeleteCorrection();

      //! Register a callback to be notified on any change of parameters or status
      
      //! no specific information will be sent, just a  notification that a change has occured
      CallbackConnection_t RegisterStateChangeCallback(VirtualKeyedStateChangeCallback* callback);

      //! Register a callback for a specific Parameter or Status value
      
      //! callback will be called once for each variable and will receive name and new value of changed variable
      CallbackConnection_t RegisterStateChangeCallback(const std::string& key, VirtualKeyedStateChangeCallback* callback);

      //! callback will be called once for each variable and will receive name and new value of changed variable
      CallbackConnection_t RegisterStateChangeCallback(const StatusParameter_t status_item, VirtualKeyedStateChangeCallback* callback);

      //! callback will be called once for each variable and will receive name and new value of changed variable
      CallbackConnection_t RegisterStateChangeCallback(const VStatusFlag* VSF, VirtualKeyedStateChangeCallback* callback);

      //! Register a callback to be notified on every change of status values
      //
      //! callback will be called once for each variable and will receive name and new value of changed variable
      void RegisterEveryStatusChangeCallback(VirtualKeyedStateChangeCallback* callback);

      //! Unregister and callback previously registered
      void UnregisterStateChangeCallback(CallbackConnection_t conn);

   private:
      void SignalAnyStatusChange();
      void SignalStatusChange(const std::string& name, const std::string& value);
      void SignalStatusFlagChange(const VStatusFlag* VSF);
      void SignalVirtualStatusChange(const StatusParameter_t item, const std::string& value);
      void SignalAnyStatusChangeInThread();
      void SignalStatusChangeInThread(const std::string& name, const std::string& value);
      void SignalStatusFlagChangeInThread(const VStatusFlag* VSF);
      void SignalVirtualStatusChangeInThread(const StatusParameter_t item, const std::string& value);
      void SignalParameterChange();
      void SignalParameterChange(const std::string& name, const std::string& value);

   public:

      std::string logFilename() const;

      std::string configFilename() const;

      //! Gets a value from the configuration file
      
      //! @param[in] section
      //! name of section in which entry will be found
      //! @param[in] entry
      //! name of entry
      //! @return
      //! returns the value, which may be a string, or an int, or a double
      Chameleon getConfigValue(const std::string& section, const std::string& entry) const;

      //! Gets a value from the configuration file, but returns supplied default if there is no entry
      
      //! @param[in] section
      //! name of section in which entry will be found
      //! @param[in] entry
      //! name of entry
      //! @param[in] default_value
      //! default_value will be returned if the entry is not present in the configuration file
      //! @return
      //! returns the value, which may be a string, or an int, or a double
      template <class T>
      Chameleon getConfigValue(const std::string& section, const std::string& entry, T& default_value) const;

      //! Modify variable with a value from the configuration file, or create value in configuration if it does not exist
      //
      //! @param[in] section
      //! name of section in which entry will be found
      //! @param[in] entry
      //! name of entry
      //! @param[in,out] value
      //! value will be modified only if the entry is present in the configuration file
      //! but if entry does not exist, then this call will create it with the supplied value
      //! @return
      //! returns the true if value was modified, otherwise returns false
      template <class T>
      bool initializeConfigValue(const std::string& section, const std::string& entry, T& value) const;

      //! Modify variable with a value from the configuration file
      //
      //! @param[in] section
      //! name of section in which entry will be found
      //! @param[in] entry
      //! name of entry
      //! @param[out] value
      //! value will be modified only if the entry is present in the configuration file
      //! @return
      //! returns the true if value was modified, otherwise returns false
      template <class T>
      bool updateConfigValue(const std::string& section, const std::string& entry, T& value) const;

      bool ConfigSectionPresent(const std::string& section) const;


   public:
      void simulateStatusChange(const std::string& name);
      void simulateStatusChange(const StatusParameter_t item);

   private:
      //! \private
      int getCameraId() const;

      //! \private
      CMainApp* getSpectralDll();

      //! \private
      Mutex_t&  getSpectralMutex();

      //! Starts a thread to update status from camera on a regular interval
      /*!
       */
      void setStatusUpdateInterval(double update_interval = 1.0);
      
      //! Cancels (terminates) the status update thread started with setStatusUpdateInterval();
      void CancelStatusUpdate(bool wait = true);

      //! Waits for the status update thread to terminate after a call to CancelStatusUpdate()
      /*! It is not normally necessary to wait, but this is provided if the subcriber needs to
       * sync to the last update result
       */
      void WaitStatusUpdate();

      //! Starts a thread to monitor frame exposure, read, correction from camera and/or corrector on a regular interval
      /*!
       *
       */
      //void StartFrameMonitor(double update_interval = 1.0);
      
      //! Cancels (terminates) the frame monitor thread started with StartFrameMonitor();
      //void CancelFrameMonitor(bool wait = true);

      //! Waits for the frame monitor thread to terminate after a call to CancelFrameMonitor()
      /*! This should be used, for instance, if the callback objects will be destroyed.  It is
       * important that the callback objects not be destroyed before the FrameMonitor is completely finished.
       */
      //void WaitFrameMonitor();
      RxFrame* ProcessRawFrameFromSequence(int index, void *frame_buffer);
      RxReturnStatus ProcessFrameFromSequence(const RxFrame* raw_frame_p);
      void FrameAcquisitionFrameProcessor(const RxFrame* raw_frame_p, RxFrame* frame_p);

      void FrameAcquisitionFrameProcessorCB(int device_frame_number, void *device_frame_buffer);

      //! Retrieve a pointer to a numbered raw from from the acquistion buffers - only valid while buffer in ring is valid!
      RxFrame* rawFrame(int frame_number) const;
      RxFrame* rawFrame(const void *data_buffer) const;

      //! Retrieve a pointer to a numbered raw from from the acquistion buffers - only valid while buffer in ring is valid!
      RxFrame* correctedFrame(int frame_number) const;

   public:
      //! Retrieve a pointer to the current background frame
      RxFrame* backgroundFrame() const;

      VStatusFlag *findVirtualStatusFlag(StatusFlag_t key);
      

   private:

      // Private methods

      RxReturnStatus InitializeStatusMapFromCamera(const std::vector<std::string> &status_name_list);
      RxReturnStatus UpdateStatusMapFromCamera(std::vector<std::string> &updated_name_list);

      RxReturnStatus InitializeParameterMapFromCamera(const std::vector<std::string> &parameter_name_list);
      RxReturnStatus UpdateParameterMapFromCamera(std::vector<std::string> &updated_name_list);

      //! \brief Initialize a data map from the camera using a list of names
      RxReturnStatus InitializeDataMapFromCamera(const std::vector<std::string> &parameter_name_list, DataMap &parameter_map);

      //! \brief Fill a data map from the camera using a list of names.  Add to map if need be and return list of names of updated parameters and number changed and created.
      RxReturnStatus FillDataMapFromCamera(const std::vector<std::string> &parameter_name_list, DataMap &parameter_map, std::vector<std::string> &updated_name_list, int &n_changed, int &n_created);
      //! \brief Update a data map from the camera using the names already in the map and return a list of names of the changed parameters
      RxReturnStatus UpdateDataMapFromCamera(DataMap &parameter_map, std::vector<std::string> &changed_name_list);

      int RawStatusIndex(const std::string& displayName);

      RxDetectorParameter* CreateStatusFromDetector(const std::string& status_name);

      RxDetectorParameter* CreateParameterFromDetector(const std::string& parameter_name);
      
      //! \brief Updates status from the camera on a regular interval
      /*!
       * 
       * 
       * This should be started and stopped by setStatusUpdateInterval() and CancelStatusUpdater()
       * It is most useful if run in a separate thread, which those routines manage
       *
       */
      void StatusUpdater(double update_interval);

      //void FrameMonitor(double update_interval);

      void storeFrameProcessorThread(boost::thread* thread);

      int countFrameProcessorThreads();

      void waitFrameProcessorThreads();

      void clearFrameProcessorThreads(bool force = false);

      //! \brief returns value of microsecond counter embedded in frame by the detector hardware
      //!
      //! @param[in] frame_p
      //! pointer to frame object
      //! @return
      //! returns the value of the counter
      uint64_t FrameHardwareRawMicrosecondCounter(const RxFrame* frame_p) const;

      //! \brief returns value of hardware microsecond counter as an RxTimeDuration_t (since detector power up)
      //!
      //! @param[in] frame_p
      //! pointer to frame object
      //! @return
      //! returns the value of the embedded counter as a time since initialization
      RxTimeDuration_t FrameHardwareRawElapsedTime(const RxFrame* frame_p) const;

      //! \brief returns value of hardware microsecond counter as an RxTimeStamp_t (local clock time)
      //!
      //! @param[in] frame_p
      //! pointer to frame object
      //! @return
      //! returns the value of the counter as a local clock time
      RxTimestamp_t FrameHardwareTimestamp(const RxFrame* frame_p);

      //! \brief sets base time for converting hardware microsecond counter to local clock time
      void SetFrameHardwareTimestamp(const RxTimeDuration_t& raw_timestamp, const RxTimestamp_t& set_time);

      int EmbeddedValueOfPixel(const RxFrame *frame_p, size_t offset, unsigned int embedded_bits, unsigned int max_significant_bits) const;

      //! \brief Tests certain internal fiducial data in raw frame to verify that data was correctly read from detector
      //!
      //! @param[in] frame_p
      //! pointer to frame object to be verified
      //! @return
      //! returns true if value was frame data are OK, otherwise returns false
      bool VerifyRawFrameIntegrity(const RxFrame* frame_p) const;

      //! \brief Tests certain fiducial data in raw frame to verify that data was correctly read from detector
      //!
      //! @param[in] frame_number
      //! number of frame in collection sequence (starting at 0)
      //! @param[in] frame_p
      //! pointer to frame object to be verified
      //! @return
      //! returns the true if value was frame data are OK, otherwise returns false
      //
      bool VerifyRawFrameIdentity(int frame_number, const RxFrame* frame_p) const;

      //bool VerifyRawFrameIdentity(int received_frame_number, const RxFrame* frame_p, int& true_frame_number);
      int FrameNumberFromIndex(int index, const RxFrame* frame_p, bool adjust_dropped_frames, int& frames_dropped_this_time);

      int EmbeddedRawFrameNumber(int frame_number, const RxFrame* frame_p) const;

      //! \brief Tests certain fiducial data in corrected frame to verify that data was correctly read from detector
      //!
      //! @param[in] frame_number
      //! number of frame in collection sequence (starting at 0)
      //! @param[in] frame_p
      //! pointer to frame object to be verified
      //! @return
      //! returns the true if value was frame data are OK, otherwise returns false
      //
      bool VerifyFrameIntegrity(int frame_number, const RxFrame* frame_p) const;

   private:

      // Private members
      TimingLogger* time_logger_p_;
      ConfigFile *ConfigFile_;
      std::string ConfigSectionDetector_;

      //! A mutex for I/O
      Mutex_t  IOMutex;

      //! The Spectral Camera DLL object
      CMainApp* SpectralDll_;
      Mutex_t  SpectralMutex_;
      SpectralFrameCB *SpectralFrameCB_;
      RxCB::AcquisitionCB *SeriesAcquisitionCB_;
      RxCB::BackgroundAcquisitionCB *BackgroundAcquisitionCB_;
      VirtualFrameCallback *ActiveAcquisitionCB_;
      VirtualFrameCallback *UserAcquisitionCB_;

      //! The Spectral camera ID that this object has opened
      int CameraId_;

      std::string detector_canonical_name_;
      std::string detector_device_;

      //! The Correction object
      RxFrameCorrection* frameCorrection_p_;
      RxFrameCorrectionFilenameGenerator* correctionFilenameGenerator_p_;

      ExperimentMetaData *metaData_p_;

      //! The background frame used for Correction
      RxFrame* backgroundFrame_p_;
      int nBackgrounds_;
      int droppedFrames_;
      Mutex_t  droppedFramesMutex_;

      ReadoutMode_t ReadoutMode_;

      RxTransformationCode_t detectorFrameOrientation_;
      RxTransformationCode_t detectorMountOrientation_;
      RxTransformationCode_t frameTransformation_;

      int cameraHardwareFirstFrameNumber_;
      int cameraSkipInitialFrames_;
      int cameraSkipInitialBackgroundFrames_;

      RxTimestamp_t baseHardwareTimestamp_;
      RxTimestamp_t recentHardwareTimestamp_;

      //! A vector containing pointers to buffers for data acquisition
      //! One entry per buffer, not per frame, in acquisition
      std::vector<RxFrame*> rawFrameBuffers_;
      std::map<const void *, RxFrame*> rawFrameBufferMap_;
      int minFrameAcquisitionBuffers_;
      int maxFrameAcquisitionBuffers_;
      //! A vector containing pointers to buffers for corrected frame data (shadows the acquisition buffers)
      //! One entry per buffer, not per frame, in acquisition
      std::vector<RxFrame*> correctedFrameBuffers_;
      size_t nFrameCorrectionBuffers_;

      RxThreadGroup frameProcessorThreadGroup_;

      int frameAcquisitionUserFrameNumberOffset_;

      std::set<CallbackConnection_t> frameAcquisitionCallbackList_;

      //! a vector containing pointers to parameter objects - These are templated, so must be vector of  pointers, not objects
      std::vector<RxDetectorParameter> ParameterList_;

      ParameterMap virtualParameterMap_;
      ParameterMap parameterMap_;
      Mutex_t  parameterMapMutex_;
      ParameterMap newParameterMap_;
      Mutex_t  newParameterMapMutex_;

      StatusMap statusMap_;
      Mutex_t  statusMapMutex_;

      //VirtualStatusMap virtualStatusMap_;
      //VirtualStatusFlagMap virtualStatusFlagMap_;
      VStatusMap<VStatusParameter> virtualStatusMap_;
      VStatusMap<VStatusFlag> virtualStatusFlagMap_;

      bool correctThisSequence_;

      double exposureTime_;
      double intervalTime_;
      bool FastBulbEnabled_;
      bool MPPEnabled_;
      SequenceMode_t SequenceMode_;
      SequenceGate_t SequenceGate_;
      bool verifyRawFrameIdentity_;
      bool framesHaveEmbeddedFrameCounter_;
      bool framesHaveDuplicateEmbeddedFrameCounter_;
      bool framesHaveEmbeddedTimestamp_;
      bool useTestPattern_;
      TestPattern_t  testPattern_;
      int nFramesInSequence_;
      bool acquisitionActive_;
      bool rawAcquisitionActive_;
      ConditionVariable_t acquisitionStatusCondition_;
      Mutex_t acquisitionStatusMutex_;

      //boost::thread_group* StatusUpdateThreadGroup_;
      RxThreadGroup statusUpdateThreadGroup_;

      boost::thread StatusUpdateThread_;
      //boost::thread FrameMonitorThread_;

      RxStatusLogger *StatusLogger_p_;

};


class VSensorTemperatureMin : public VStatusParameter
{
   public:
      VSensorTemperatureMin(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = SensorTemperatureMin; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->SensorTemperatureMin();
	 return oss.str();
      }
};

class VSensorTemperatureMax : public VStatusParameter
{
   public:
      VSensorTemperatureMax(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = SensorTemperatureMax; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->SensorTemperatureMax();
	 return oss.str();
      }
};

class VSensorTemperatureAve : public VStatusParameter
{
   public:
      VSensorTemperatureAve(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = SensorTemperatureAve; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->SensorTemperatureAve();
	 return oss.str();
      }
};

class VSensorTemperatures : public VStatusParameter
{
   public:
      VSensorTemperatures(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = SensorTemperatures; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 std::vector<double> temperatures;
	 RxLog(LOG_TRACE) << "VSensorTemperatures::() - calling SensorTemperatures()" << oss.str() << endl;
	 p_rxd_->SensorTemperatures(temperatures);
	 for ( std::vector<double>::const_iterator ti = temperatures.begin(); ti != temperatures.end(); ) {
	    oss << *ti;
	    RxLog(LOG_TRACE) << "VSensorTemperatures::() - Temperature (double): " << *ti << ", Temperatures so far: " << oss.str() << endl;
	    if (++ti == temperatures.end()) break;
	    oss << ",";
	 }
	 return oss.str();
      }
      std::string setName(const std::string& name = std::string(""))
      {
	 if (!name.empty()) {
	    display_name_ = name;
	 }
	 else {
	    p_rxd_->SensorTemperatureNames(&display_name_);
	 }
	 id_name_ = display_name_;
	 return display_name_;
      }
};

class VCoolerTemperatureMin : public VStatusParameter
{
   public:
      VCoolerTemperatureMin(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = CoolerTemperatureMin; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->CoolerTemperatureMin();
	 return oss.str();
      }
};

class VCoolerTemperatureMax : public VStatusParameter
{
   public:
      VCoolerTemperatureMax(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = CoolerTemperatureMax; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->CoolerTemperatureMax();
	 return oss.str();
      }
};

class VCoolerTemperatureAve : public VStatusParameter
{
   public:
      VCoolerTemperatureAve(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = CoolerTemperatureAve; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->CoolerTemperatureAve();
	 return oss.str();
      }
};

class VCoolerTemperatures : public VStatusParameter
{
   public:
      VCoolerTemperatures(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = CoolerTemperatures; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 std::vector<double> temperatures;
	 RxLog(LOG_TRACE) << "VCoolerTemperatures::() - calling CoolerTemperatures()" << oss.str() << endl;
	 p_rxd_->CoolerTemperatures(temperatures);
	 for ( std::vector<double>::const_iterator ti = temperatures.begin(); ti != temperatures.end(); ) {
	    oss << *ti;
	    RxLog(LOG_TRACE) << "VCoolerTemperatures::() - Temperature (double): " << *ti << ", Temperatures so far: " << oss.str() << endl;
	    if (++ti == temperatures.end()) break;
	    oss << ",";
	 }
	 return oss.str();
      }
      std::string setName(const std::string& name = std::string(""))
      {
	 if (!name.empty()) {
	    display_name_ = name;
	 }
	 else {
	    //name_ = p_rxd_->CoolerTemperatureNames();
	    p_rxd_->CoolerTemperatureNames(&display_name_);
	 }
	 id_name_ = display_name_;
	 return display_name_;
      }
};

class VAmbientTemperatures : public VStatusParameter
{
   public:
      VAmbientTemperatures(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = AmbientTemperatures; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 std::vector<double> temperatures;
	 RxLog(LOG_TRACE) << "VAmbientTemperatures::() - calling AmbientTemperatures()" << oss.str() << endl;
	 p_rxd_->AmbientTemperatures(temperatures);
	 for ( std::vector<double>::const_iterator ti = temperatures.begin(); ti != temperatures.end(); ) {
	    oss << *ti;
	    RxLog(LOG_TRACE) << "VAmbientTemperatures::() - Temperature (double): " << *ti << ", Temperatures so far: " << oss.str() << endl;
	    if (++ti == temperatures.end()) break;
	    oss << ",";
	 }
	 return oss.str();
      }
      std::string setName(const std::string& name = std::string(""))
      {
	 if (!name.empty()) {
	    display_name_ = name;
	 }
	 else {
	    p_rxd_->AmbientTemperatureNames(&display_name_);
	 }
	 id_name_ = display_name_;
	 return display_name_;
      }
};

class VPowerSupplyTemperatures : public VStatusParameter
{
   public:
      VPowerSupplyTemperatures(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = PowerSupplyTemperatures; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 std::vector<double> temperatures;
	 RxLog(LOG_TRACE) << "VPowerSupplyTemperatures::() - calling PowerSupplyTemperatures()" << oss.str() << endl;
	 p_rxd_->PowerSupplyTemperatures(temperatures);
	 for ( std::vector<double>::const_iterator ti = temperatures.begin(); ti != temperatures.end(); ) {
	    oss << *ti;
	    RxLog(LOG_TRACE) << "VPowerSupplyTemperatures::() - Temperature (double): " << *ti << ", Temperatures so far: " << oss.str() << endl;
	    if (++ti == temperatures.end()) break;
	    oss << ",";
	 }
	 return oss.str();
      }
      std::string setName(const std::string& name = std::string(""))
      {
	 if (!name.empty()) {
	    display_name_ = name;
	 }
	 else {
	    p_rxd_->PowerSupplyTemperatureNames(&display_name_);
	 }
	 id_name_ = display_name_;
	 return display_name_;
      }
};

class VSystemTemperatures : public VStatusParameter
{
   public:
      VSystemTemperatures(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = SystemTemperatures; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 std::vector<double> temperatures;
	 RxLog(LOG_TRACE) << "VSystemTemperatures::() - calling SystemTemperatures()" << oss.str() << endl;
	 p_rxd_->SystemTemperatures(temperatures);
	 for ( std::vector<double>::const_iterator ti = temperatures.begin(); ti != temperatures.end(); ) {
	    oss << *ti;
	    RxLog(LOG_TRACE) << "VSystemTemperatures::() - Temperature (double): " << *ti << ", Temperatures so far: " << oss.str() << endl;
	    if (++ti == temperatures.end()) break;
	    oss << ",";
	 }
	 return oss.str();
      }
      std::string setName(const std::string& name = std::string(""))
      {
	 RxLog(LOG_TRACE) << "VSystemTemperatures::setName(" << name << ")" <<  endl;
	 if (!name.empty()) {
	    display_name_ = name;
	 }
	 else {
	    p_rxd_->SystemTemperatureNames(&display_name_);
	 }
	 RxLog(LOG_TRACE) << "VSystemTemperatures::setName() - set name to " << display_name_ << endl;
	 id_name_ = display_name_;
	 return display_name_;
      }
};

class VCoolerPressures : public VStatusParameter
{
   public:
      VCoolerPressures(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = CoolerPressures; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 std::vector<double> pressures;
	 p_rxd_->CoolerPressures(pressures);
	 for ( std::vector<double>::const_iterator pi = pressures.begin(); pi != pressures.end(); ) {
	    oss << *pi;
	    if (++pi == pressures.end()) break;
	    oss << ",";
	 }
	 return oss.str();
      }
      std::string setName(const std::string& name = std::string(""))
      {
	 RxLog(LOG_TRACE) << "VCoolerPressures::setName(" << name << ")" <<  endl;
	 if (!name.empty()) {
	    display_name_ = name;
	 }
	 else {
	    p_rxd_->CoolerPressureNames(&display_name_);
	 }
	 RxLog(LOG_TRACE) << "VCoolerPressures::setName() - set name to " << display_name_ << endl;
	 id_name_ = display_name_;
	 return display_name_;
      }
};

class VChamberPressure : public VStatusParameter
{
   public:
      VChamberPressure(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = ChamberPressure; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->ChamberPressure();
	 return oss.str();
      }
};

class VLinePressure : public VStatusParameter
{
   public:
      VLinePressure(RxDetector* p_rxd) { p_rxd_ = p_rxd; key_ = LinePressure; setName(VStatusParameterName(key_)); }
      std::string operator() () const
      {
	 std::ostringstream oss;
	 oss << p_rxd_->LinePressure(); return oss.str(); } };

}

#endif	// RX_DETECTOR_H
