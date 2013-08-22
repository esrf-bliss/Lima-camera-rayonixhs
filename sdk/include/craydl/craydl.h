#ifndef CRAYDL_H
#define CRAYDL_H

/*! \file craydl.h

 \brief Main header file for the craydl library

 This is the only header file that an application must include
 to use the craydl library

 Programs that include craydl.h must be linked to libcraydl

 */

/*! \mainpage craydl Control Rayonix Detector Library
 *
 * \authors Michael Blum 
 * \authors Justin Anderson
 * \version 0.1.10
 * \date    April 2013
 * \warning This is an "beta" release - please report bugs!
 *
 * \section intro_sec Introduction
 *
 * craydl is the C++ class library for controlling Rayonix X-ray Detectors.
 * It's purpose is to allow X-ray user facilities to incoporate control of Rayonix detectors into
 * their own beamline control software and obtain the highest possible performance.
 *
 * Note that craydl makes use of several third-party software libraries including
 * - boost - the the boost collection of C++ algorithms (date_time, signals and thread)
 * - MIL - Matrox Imaging Library for control of some data acquisition cards
 * - CUDA - nVidia libraries for performing calculations on nVidia GPUs
 * - marccd - legacy Rayonix software libraries
 *  - marccd application for inspecting images
 *  - marccd libraries for accessing some image processing algorithms from marccd
 * - CBFLib - library for reading and writing CBF format X-ray data frames
 
 * Therefore, any application
 * using the craydl library must have access to link to those libraries
 *
 * \section install_sec Installation of Library
 *
 * \subsection copy Copy library to appropriate place
 * \code cp libcraydl.so /usr/local/lib \endcode
 *
 * \section link_sec Linking to library
 *
 * \subsection link Link user code to the library
 * \code ld -o app app.o -lcraydl -lboost_date_time -lboost_signals -lboost_thread \endcode or
 *
 * etc...
 *
 * \bug This is the very first release - it is likely to be buggy!
 */


/*! \page  "Example Program"
 * 
 * This is an example program that uses the craydl library.
 * \n
 * \n It:
 * \n 1) Opens a detector
 * \n 2) Starts up a status updater thread
 * \n 3) registers a few callbacks to receive status updates
 * \n 4) checks a few parameters
 * \n 5) Sends a few commands to illustrate that they exist
 * \n 6) sets up a frame sequence (and registers a callback)
 * \n 7) reads out a frame
 * \n 8) demonstrates manipulating the updater thread and callbacks
 * \n
 * It has many command line options and is a useful utility program
 *
 * \include hsutil.cpp
 *
 */

/*! \page  "Example Makefile"
 * 
 * This is an example Makefile that will build the example program (hsutil)
 * from the example source hsutil.cpp and the craydl library
 *
 * \include Makefile
 *
 */

#include "RxDetector.h"
#include "RxFrame.h"

#include "RxVDetector.h"
#include "RxUtils.h"
#include "RxLog.h"
#include "RxFrameCorrection.h"
#include "RxUtils.h"
#include "Chameleon.h"
#include "ConfigFile.h"

namespace craydl {

   // Anything added to this file must be in the craydl namespace

}

#endif	// CRAYDL_H
