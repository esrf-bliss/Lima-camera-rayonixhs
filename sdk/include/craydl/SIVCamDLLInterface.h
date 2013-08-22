#ifndef SIVCAMDLLINTERFACE_H
#define SIVCAMDLLINTERFACE_H

/*! \file SIVCamDLLIntervace.h

 \brief interface to Spectral Library

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


#include "RxTransformation.h"
#include "RxFrame.h"

// Advance declarations
class CMainApp;

namespace craydl {

#if 1

//! \private
class SpectralUnitDescriptor
{
   public:
      SpectralUnitDescriptor() :
	 scaler(1.0),
	 unitType(UNIT_NONE)
      {
      }

      SpectralUnitDescriptor(const std::string& unitName, const std::string& description, double scaler, RxUnitType unitType,
                             const std::string& dataTypeName);

      virtual ~SpectralUnitDescriptor()
      {
      }

      const std::string getFullDescription() const;
      const std::string getDataTypeName() const;
      const std::string getDescription() const;
      double getScaler() const;
      const std::string getUnitName() const;
      RxUnitType getUnitType() const;
      void setDataTypeName(const std::string& dataTypeName);
      void setDescription(const std::string& description);
      void setScaler(double scaler);
      void setUnitName(const std::string& unitName);
      void setUnitType(RxUnitType unitType);

   private:
      std::string unitName;
      std::string description;
      double scaler;
      RxUnitType unitType;
      std::string dataTypeName;
};

//! \private
class SpectralParameterRecord
{
   public:
      SpectralParameterRecord()
      {
         setParameterName(std::string(""));
         setParameterValue(std::string(""));
         setUnit(0);
         setParameterMinValue(std::string(""));
         setParameterMaxValue(std::string(""));
         setParameterStep(std::string(""));
      }
      SpectralParameterRecord(const std::string& parameterName, int index, const std::string& parameterValue, int unit, const std::string& minValue, const std::string& maxValue, const std::string& step, const std::string& bitMask = std::string(""), const std::string& bitNames = std::string(""));
      ~SpectralParameterRecord()
      {
      }
      const std::string getParameterName() const;
      const std::string getBitMask() const;
      const std::string getBitNames() const;
      int getParameterIndex() const;
      const std::string getParameterValue() const;
      const std::string getParameterMinValue() const;
      const std::string getParameterMaxValue() const;
      const std::string getParameterStep() const;
      const std::string getParameterPulldown(int item) const;
      //const std::string getParameterBit(int bit) const;
      const std::map<int, std::string> getParameterPulldownMap() const;
      const SpectralUnitDescriptor getUnitDescriptor() const;
      const std::string getFullDescription() const;
      void setParameterName(const std::string& parameterName);
      void setBitNames(const std::string& bitmask, const std::string& parameterName);
      void setParameterIndex(int parameterIndex);
      void setParameterValue(const std::string& parameterValue);
      void setParameterMinValue(const std::string& parameterMinValue);
      void setParameterMaxValue(const std::string& parameterMaxValue);
      void setParameterStep(const std::string& parameterStep);
      void setParameterPulldown(int item, const std::string& itemName);
      void setUnit(int unit);

   //private:
      //void setParameterBit(int bit, const std::string& itemName);

   private:
      std::string parameterName;
      int parameterIndex;
      std::string parameterValue;
      std::string parameterMinValue;
      std::string parameterMaxValue;
      std::string parameterStep;
      std::string bitMask;
      std::string bitNames;
      std::map<int, std::string> pulldownMap;
      SpectralUnitDescriptor unitDescriptor;

      void setUnitDescriptor(SpectralUnitDescriptor unit_descriptor)
      {
         unitDescriptor = unit_descriptor;
         return;
      }
};

//! \private
const std::map<int, const SpectralUnitDescriptor*>& InitSpectralUnitMap();

//! \private
const std::map<int, const SpectralUnitDescriptor*> SpectralUnitMap = InitSpectralUnitMap();

//! \private
class RxSpectralError
{
   public:

      // Constructors
      RxSpectralError(int return_code)
      {
         ReturnCode = return_code;
      }
      ;
      ~RxSpectralError()
      {
      }
      //! Overload the = operator for receiving an int, so the object can receive a returncode from a SpectralDll call
      RxSpectralError & operator=(const int& rhs)
      {
         ReturnCode = rhs;
         return *this;
      }

      // Public Methods
      int Value() const;
      int CameraId() const;
      bool IsValidCameraId() const;
      bool IsValidCameraId(int camera_id) const;
      bool IsImplemented() const;
      bool IsError() const;
      std::string ErrorText() const;

   private:
      int ReturnCode;

};

#endif




} // namespace craydl

#endif // SIVCAMDLLINTERFACE_H
