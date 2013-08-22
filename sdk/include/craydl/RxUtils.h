#ifndef RX_UTILS_H
#define RX_UTILS_H

/*! \file RxUtils.h
 
  \brief Generally useful utility functions for the craydl System
  
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

namespace craydl {

enum RxUnitType
{
   UNIT_NONE,
   UNIT_ENUMERATED,
   UNIT_ENUMERATED_SPARSE,
   UNIT_CUSTOM,
   UNIT_ARBITRARY,
   UNIT_REVOLUTION,
   UNIT_RPM,
   UNIT_DEGREE,
   UNIT_ARCMINUTE,
   UNIT_ARCSECOND,
   UNIT_METER,
   UNIT_CENTIMETER,
   UNIT_MILLIMETER,
   UNIT_MICRON,
   UNIT_NANOMETER,
   UNIT_ANGSTROM,
   UNIT_PICOMETER,
   UNIT_FEMTOMETER,
   UNIT_EV,
   UNIT_KEV,
   UNIT_MEV,
   UNIT_GEV,
   UNIT_DAY,
   UNIT_HOUR,
   UNIT_MINUTE,
   UNIT_SECOND,
   UNIT_MILLISECOND,
   UNIT_MICROSECOND,
   UNIT_NANOSECOND,
   UNIT_PICOSECOND,
   UNIT_FEMTOSECOND,
   UNIT_HERZ,
   UNIT_KILOHERZ,
   UNIT_MEGAHERZ,
   UNIT_GIGAHERZ,
   UNIT_BAR,
   UNIT_MILLIBAR,
   UNIT_TORR,
   UNIT_MILLITORR,
   UNIT_VOLT,
   UNIT_MILLIVOLT,
   UNIT_AMP,
   UNIT_MILLIAMP,
   UNIT_PERCENT,
   UNIT_KELVIN,
   UNIT_CELSIUS,
   UNIT_FAHRENHEIT,
   UNIT_PIXEL,
   UNIT_BYTE,
   UNIT_KILOBYTE,
   UNIT_MEGABYTE,
   UNIT_GIGABYTE,
   UNIT_TERABYTE,
   UNIT_PETABYTE,
   UNIT_EXABYTE,
   UNIT_KIBIBYTE,
   UNIT_MEBIBYTE,
   UNIT_GIBIBYTE,
   UNIT_TEBIBYTE,
   UNIT_PEBIBYTE,
   UNIT_EXBIBYTE,
   UNIT_LOOKUP_PRESSURE,
   UNIT_BITFIELD,
   UNIT_STRING,
   UNIT_IPADDRESS
};


// Needs base specifier - needs argument  std::hex, std::dec or std::oct
template<class T>
bool from_string(const std::string& s, T& t, std::ios_base& (*f)(std::ios_base&))
{
   std::istringstream iss(s);
   return !(iss >> f >> t).fail();
}
// Overload - assumes base 10
template<class T>
bool from_string(const std::string& s, T& t)
{
   // This one assumes base 10
   std::istringstream iss(s);
   return !(iss >> t).fail();
}


//! \fn LittleEndian()
//! \brief  returns true if the host byte order is Little Endian
inline bool LittleEndian() {int num = 1; return *(char *)&num == 1 ? 1 : 0;}

//! \fn SplitStringIntoTokens(const string& str, vector<string>& tokens, const string& delimiters = " ")
//! \brief  Splits a C++ string object into a vector of strings based on suppliled delimiters
//!
//! Default delimitor is ' ' (space)

void SplitStringIntoTokens(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");

//! \fn SplitFirstToken(const string& str, vector<string>& split, const string& delimiters = " ")
//! \brief  Splits a C++ string object into a vector of strings based on suppliled delimiters
//!
//! Default delimitor is ' ' (space)
void SplitFirstToken(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");

//! \fn RxSleep(double seconds)
//! \brief  sleeps for specified time
//!
//! RxSleep is reliable, wrt signals, etc - internaly it uses nanosleep

void RxSleep(double seconds);


/*! \fn LIMIT(const T& low, const T& value, const T& high)
 *
 * \brief limits a value to a range between low and  high
 *
 * Takes a value and and low and high limit and returns the value or the exceeded limit
 *
 * @param low 
 * the lower limit on the returned value
 * @param value
 * the input value
 * @param high
 * the upper limit on the returned value
 *
 * @return
 *   returns the input value, if value is between low and high limits
 *   otherwise, returns the exceeded limit
 */



template <class T>
inline int NINT(const T& afloat) {return (int)floor(afloat + 0.5);}
//template const int NINT<double>(const double&);
//template const int NINT<float>(const float&);

template <class T>
inline const T LIMIT(const T& low, const T& value, const T& high)
{return low > value ? low : ( high < value ? high : value ); }

inline const double Celsius_to_Kelvin(const double &temperature_C)
{
   return temperature_C+273.15;
}

inline const double Kelvin_to_Celsius(const double &temperature_K)
{
   return temperature_K-273.15;
}



/*! \fn EV(const double &wavelength)
 *
 * \brief converts Angstroms to eV
 *
 * Converts X-ray Wavelength in Angstroms units to Energy in eV units
 *
 * @param wavelength  X-ray wavelength in Angstroms

 * @return
 *   returns X-ray energy in electron Volts (eV)
 */

inline const double EV(const double& wavelength)
{ return wavelength > 0.01 ? 12398.10000/wavelength : 0.0; }

/*!
 * \brief converts eV to Angstroms
 *
 * Converts Energy in eV units to X-ray Wavelength in Angstroms units
 *
 * @param energy  X-ray energy in electron Volts

 * @return
 *   returns X-ray wavelength in Angstroms
 */

inline const double ANGSTROM(const double& energy)
{ return (energy > 0.01) ? 12398.10000/energy : 0.0; }

//! \brief returns total memory being used
//
//! @return
//! returns total memory being used
//

unsigned long RxMemory(void);

} // namespace craydl


#endif	// RX_UTILS_H
