#ifndef RXVDETECTOR_H
#define RXVDETECTOR_H

/*! \file RxVDetector.h
 *
 * \brief RxVDetector Virtual Class (Interface)
 *
 * \author Michael Blum 
 * \version -0.0
 * \date    February 2011
 * \warning Don't try to link to use this yet!
  
 */

//! \namespace craydl
//! \brief  The namespace for the entire craydl library
//!

#include <string>

namespace craydl {

// Advance Declaration
class RxReturnStatus;


//! \brief RxVDetector interface declaration
/*! This is the specification of the detector interface class.
 *  A concrete class must be derived form this virtual class.
 */
class RxVDetector
{
public:

   RxVDetector() {}
   virtual ~RxVDetector() {}

   //! \brief Opens a Detector device.
   virtual RxReturnStatus Open(const std::string& device_name) = 0;

private:

};

} // namespace craydl
#endif	// RXVDETECTOR_H
