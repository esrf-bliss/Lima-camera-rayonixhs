/* 
   Chameleon.h

   Copyright (C) 2002-2004 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

   Note: This version was modified to be a header-only package by inlining all methods
         and added explicit constructors/operators for char* int and bool.
	 Added vector<string> and vector<double> operators to return multiple values.
	 Added boolean operators to interpret true/false,t/f,yes/no,y/no
         Michael Blum and Justin Anderson - Rayonix, L.L.C.  2011

*/

#ifndef CHAMELEON_H__
#define CHAMELEON_H__

//#include <stdlib.h>
//#include <cstdlib>
//#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


#include <boost/algorithm/string.hpp>

#include "RxTransformation.h"

namespace craydl {

using namespace boost;

class Chameleon {
public:
   Chameleon() {}
   explicit Chameleon(std::string const& value) { value_ = value; }
   explicit Chameleon(const char* c) { value_ = std::string(c); }
   explicit Chameleon(double d) { std::stringstream s; s << d; value_ = s.str(); }
   explicit Chameleon(int i) { std::stringstream s; s << i; value_ = s.str(); }
   explicit Chameleon(size_t i) { std::stringstream s; s << i; value_ = s.str(); }
   explicit Chameleon(const bool b) { std::stringstream s; s<<b; value_=s.str(); }

   Chameleon(Chameleon const& other) { value_ = other.value_; }
   Chameleon& operator=(Chameleon const& other) { value_ = other.value_; return *this; }

   Chameleon& operator=(double d) { std::stringstream s; s << d; value_ = s.str(); return *this; }
   Chameleon& operator=(int i) { std::stringstream s; s << i; value_ = s.str(); return *this; }
   Chameleon& operator=(size_t i) { std::stringstream s; s << i; value_ = s.str(); return *this; }
   Chameleon& operator=(std::string const& s) { value_ = s; return *this; }
   Chameleon& operator=(const char *c) { value_ = std::string(c); return *this; }
   Chameleon& operator=(bool b) { std::stringstream s; s << b; value_ = s.str(); return *this; }

   bool operator==(const Chameleon &cham) const { return value_ == cham.value_; }
   bool operator==(const std::string &str) const { return value_ == str; }

public:
   operator std::string() const { return value_; }

   operator double( ) const { return toDouble(); }

   //operator double() const { return std::atof(value_.c_str()); }

   operator int() const { return toInt();  }

   //operator int() const { return atoi(value_.c_str()); } // causes ambiguity whenc Chameleon c = string; ??

   operator bool() const { return toBool(); }

   operator RxTransformationCode_t() const { return toRxTransformation(); }

   //Return value as a vector of strings
   operator std::vector<std::string>() const {
      return toStringVector();
   }

   //Return value as a vector of doubles
   operator std::vector<double>() const {
      return toDoubleVector();
   }

   bool toBool() const {
      std::string s(value_);
      bool b = false;
      if (!strcasecmp(s.c_str(), "y")
       || !strcasecmp(s.c_str(), "yes")
       || !strcasecmp(s.c_str(), "t")
       || !strcasecmp(s.c_str(), "true")
       || !strcasecmp(s.c_str(), "on")
       || (atoi(s.c_str()) > 0)
       ) {
	 b = true;
      }
      return b;
   }

   int toInt() const {
      std::istringstream iss(value_);
      int anInt; iss >> anInt;
      return anInt;
   }

   double toDouble() const {
      std::istringstream iss(value_);
      double dbl; iss >> dbl;
      return dbl;
   }

   std::string toString() const {
      return value_;
   }

   RxTransformationCode_t toRxTransformation() const
   {
      return StringToTransformationCode(value_);
   }

   std::vector<double> toDoubleVector() const {
      std::string tmpStr(value_), value_str;  //Working copy of line and current value string
      std::vector<double> values;  //Holds return values
      double val;  //Holds current value

      tmpStr.append(" ");  //Add a space to end of line as a marker
      while (tmpStr.length() > 0) {
         //Not done processing the line yet
         int end0 = tmpStr.find_first_of(" ");  //First space in line
         int end1 = tmpStr.find_first_not_of(" ", end0) - 1;  //First character after space(s) (i.e. next value)
         value_str = tmpStr.substr(0, end0);  //The value as a string
         std::istringstream value_str_strm(value_str);
         value_str_strm >> val;  //Convert string value to double
         values.push_back(val);  //Push value
         tmpStr.erase(0, end1 + 1);  //Delete the value and trailing space(s) from line
      }
      return values;
   }

   std::vector<std::string> toStringVector() const {
      std::string tmpStr(value_);  //Holds working copy of the line
      std::vector<std::string> values;  //Holds return values

      tmpStr.append(" "); //Add a space to end of line as a marker
      while (tmpStr.length() > 0) {
         //Not done processing the line yet
         int end0 = tmpStr.find_first_of(" "); //First space in line
         int end1 = tmpStr.find_first_not_of(" ", end0) - 1; //First character after space(s) (i.e. next value)
         values.push_back(tmpStr.substr(0, end0));  //Push the value, sans spaces
         tmpStr.erase(0, end1 + 1);  //Delete the value and trailing space(s) from line
      }
      return values;
   }

private:
   std::string value_;
};

}

#endif
