#ifndef RX_FRAME_H
#define RX_FRAME_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <memory>
#include <vector>

#include <boost/date_time.hpp>
#include <boost/format.hpp>

#include "RxFrameMetaData.h"
#include "RxFrameMathGPU.h"
#include "RxLog.h"
#include "PixelTypes.h"
#include "geometry.h"

namespace craydl {

using std::endl;

typedef boost::posix_time::ptime RxTimestamp_t;
typedef boost::posix_time::time_duration RxTimeDuration_t;

typedef uint32_t FrameChecksum_t;

class RectangleStats {
   public:
      RectangleStats() :
         minValue(INT_MAX),
         maxValue(INT_MIN),
         meanValue(0),
         standardDeviationOfValue(0) {}

      int minValue;
      int maxValue;
      double meanValue;
      double standardDeviationOfValue;
      std::vector<int> intensityCounts;
};

class LineStats {
   public:
      LineStats() :
         numPoints(0),
         minimumValue(INT_MAX),
         maximumValue(INT_MIN) {}

      std::vector<double> positions;
      std::vector<double> values;
      int numPoints;
      int minimumValue;
      int maximumValue;
};

class SaxsStats {
   public:
      SaxsStats() :
         pixelsPerBin(0) {}

      int pixelsPerBin;
      std::vector<double> meanIntensitiesPerBin;
};

// Advance declaration
class GPUDeviceBufferBase;

//! \class RxFrame
//! \brief Base class for frame data
class RxFrame
{
   public:
      // pure virtual destructor mean that this is a virtual class that can only be used as a base for another derived class
      RxFrame() {};
      virtual ~RxFrame() = 0;


   private:
      // These are impossible, because must use derived class....
      RxFrame(const RxFrame& source);
      RxFrame& operator=(const RxFrame&  rhs);

   public:

      virtual bool copy(const RxFrame *frame_p) = 0;

      virtual RxFrame *clone() const = 0;

      virtual bool isEquivalentType(const RxFrame* frame_p) const = 0;

      virtual bool isCompatible(int depth, bool signed_pixel, int nfast, int nslow) const = 0;

      virtual bool isCompatible(const RxFrame* frame_p) const = 0;

      virtual bool isSaved() const { return constMetaData().saved_; }

      virtual void setSaved() { metaData().saved_ = true; }

      virtual void setUnsaved() { metaData().saved_ = false; }

      virtual std::string savedFilename() const { return constMetaData().saved_filename_; }

      virtual void setSavedFilename(std::string filename) { metaData().saved_filename_ = filename; }

#if USEREADMETHOD
      //! read a frame from disk
      virtual bool read(const std::string &filename) = 0;
#endif

      //! write a frame to disk
      virtual bool write(const std::string &filename) = 0;

      virtual bool importFromGPUDeviceBuffer(const GPUDeviceBufferBase &device_buffer) = 0;

      //! get number of pixels in fast direction
      virtual int getNFast() const = 0;

      //! get number of pixels in slow direction
      virtual int getNSlow() const = 0;

      //! get depth of pixel in bytes
      virtual size_t getDepth() const = 0;

      //! Returns true if this data frame uses signed pixel data
      virtual bool getIsSignedData() const = 0;

      //! get number of pixels in frame
      virtual size_t NPixels() const = 0;

      //! get size of frame in bytes
      virtual size_t getSize() const = 0;

      //! get address of buffer containing frame data
      virtual void *getBufferAddress() const = 0;

      //! return a pixel value as an integer, regardless of underlying pixel data type
      virtual int getPixelValue (size_t offset) const = 0;
      virtual int getPixelValue (const Point<int> &point) const = 0;

      //! return value of the first pixel in frame
      virtual int getFirstPixelValue () const = 0;

      //! return value of the last pixel in frame
      virtual int getLastPixelValue () const = 0;

      virtual void setFrameIntegrity() {}

      virtual bool verifyFrameIntegrity() const { return true; }

      virtual GPUDeviceBufferBase* createGPUDeviceBuffer() const {return NULL;}

#if 0
      virtual RxTimeDuration_t ExposureElapsedTime() const
      {
	 return ExposureEndTimestamp() - ExposureStartTimestamp();
      }

      virtual RxTimeDuration_t ReadoutElapsedTime() const
      {
	 return ReadoutEndTimestamp() - ReadoutStartTimestamp();
      }

      virtual RxTimeDuration_t AcquisitionElapsedTime() const
      {
	 return AcquisitionEndTimestamp() - AcquisitionStartTimestamp();
      }

      virtual RxTimeDuration_t CorrectionElapsedTime() const
      {
	 return CorrectionEndTimestamp() - CorrectionStartTimestamp();
      }

      virtual RxTimeDuration_t WriteElapsedTime() const
      {
	 return WriteEndTimestamp() - WriteStartTimestamp();
      }

      virtual RxTimestamp_t AcquisitionEndTimestamp() const
      {
	 return constMetaData().getEndAcquisitionTimestamp();
      }

      virtual RxTimestamp_t CorrectionEndTimestamp() const
      {
	 return constMetaData().getEndCorrectionTimestamp();
      }

      virtual RxTimestamp_t ExposureEndTimestamp() const
      {
	 return constMetaData().getEndExposureTimestamp();
      }

      virtual RxTimestamp_t ReadoutEndTimestamp() const
      {
	 return constMetaData().getEndReadoutTimestamp();
      }

      virtual RxTimestamp_t WriteEndTimestamp() const
      {
	 return constMetaData().getEndWriteTimestamp();
      }

      virtual RxTimestamp_t AcquisitionStartTimestamp() const
      {
	 return constMetaData().getStartAcquisitionTimestamp();
      }

      virtual RxTimestamp_t CorrectionStartTimestamp() const
      {
	 return constMetaData().getStartCorrectionTimestamp();
      }

      virtual RxTimestamp_t ExposureStartTimestamp() const
      {
	 return constMetaData().getStartExposureTimestamp();
      }

      virtual RxTimestamp_t ReadoutStartTimestamp() const
      {
	 return constMetaData().getStartReadoutTimestamp();
      }

      virtual RxTimestamp_t WriteStartTimestamp() const
      {
	 return constMetaData().getStartWriteTimestamp();
      }

      virtual RxTimestamp_t HardwareTimestamp() const
      {
	 return constMetaData().getHardwareTimestamp();
      }

      virtual int NReads() const
      {
	 return constMetaData().getNReads();
      }

      virtual bool rawDataIsValid() const
      {
	 return constMetaData().rawDataIsValid();
      }


      virtual bool correctionIsApplied() const
      {
	 return constMetaData().correctionIsApplied();
      }

      virtual void setAcquisitionStartTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setStartAcquisitionTimestamp(timestamp);
      }

      virtual void setAcquisitionEndTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setEndAcquisitionTimestamp(timestamp);
      }

      virtual void setExposureStartTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setStartExposureTimestamp(timestamp);
      }

      virtual void setExposureEndTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setEndExposureTimestamp(timestamp);
      }

      virtual void setReadoutStartTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setStartReadoutTimestamp(timestamp);
      }

      virtual void setReadoutEndTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setEndReadoutTimestamp(timestamp);
      }

      virtual void setCorrectionStartTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setStartCorrectionTimestamp(timestamp);
      }

      virtual void setCorrectionEndTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setEndCorrectionTimestamp(timestamp);
      }

      virtual void setWriteStartTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setStartWriteTimestamp(timestamp);
      }

      virtual void setWriteEndTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setEndWriteTimestamp(timestamp);
      }

      virtual void setHardwareTimestamp(const RxTimestamp_t& timestamp)
      {
	 metaData().setHardwareTimestamp(timestamp);
      }

      virtual void setNReads(int nreads)
      {
	 metaData().setNReads(nreads);
      }

      virtual void setRawDataIsValid(bool valid)
      {
	 metaData().setRawDataIsValid(valid);
      }


      virtual void setFrameIntegrityChecksum(FrameChecksum_t checksum)
      {
	 metaData().setFrameIntegrityChecksum(checksum);
      }

      virtual FrameChecksum_t frameIntegrityChecksum() const
      {
	 return constMetaData().frameIntegrityChecksum();
      }

      virtual void setDataIsValid(bool valid)
      {
	 metaData().setDataIsValid(valid);
      }
#endif

      virtual int InternalFrameID() const { return constMetaData().internal_frame_ID; }

      virtual void setInternalFrameID(int frame_number) { metaData().internal_frame_ID = frame_number; }

      virtual void setCorrectionIsApplied(bool applied)
      {
	 metaData().setCorrectionIsApplied(applied);
      }

      virtual RxOrientation Orientation() const
      {
	 return constMetaData().orientation_;
      }

      virtual void setOrientation(RxOrientation orientation)
      {
	 metaData().orientation_ = orientation;
      }

      // Prints a portion of a frame
      virtual std::string printROIFrame(Rect<int> &area) const = 0;

      //! returns a pointer to a new RxFrame  constaining a subimage of the original frame
      virtual RxFrame *createROIFrame(Rect<int> &area) const = 0;

      //! Calculate the statistics under the user-drawn rectangle.
      /*! \param margin_fast is the number of pixels to ignore at each edge of each section
       *  \param margin_slow is the number of pixels to ignore at each edge of each section
       *  \param min will hold the calculated minimum pixel value
       *  \param max will hold the calculated maximum pixel value
       *  \param mean will hold the calculated mean pixel value
       *  \param std_dev will hold the calculated standard deviation of pixel values */
      virtual void calcSectionStats(int margin_fast, int margin_slow, std::vector<int> &min, std::vector<int> &max, std::vector<double> &mean, std::vector<double> &std_dev) const = 0;

      //! Calculate the statistics under the user-drawn rectangle.
      /*! \param area is the area rectangle on the data frame for which to calculate the statistics
       *  \return data returned in RectangleStats object
       */
      virtual RectangleStats calcRectStats(const Rect<int> &area) const = 0;

      //! Calculate the statistics under the user-drawn line.
      /*! Assumes saturated pixel is 65535.
       *  \param line is the line under which to calculate the statistics on the data frame
       *  \param line_width is the width of the line to use for calculations
       *  \return data returned in LineStats object
       */
      virtual LineStats calcLineStats(const Line<int> &line, int line_width) const = 0;

      //! Calculate the SAXS statistics from the center of the user-drawn circle.
      /*! \param center is the center point of the circle on the data frame for which to calculate the statistics
       *  \param num_bins is the number of bins to use in calc, from center point to farthest corner
       *  \return data returned in SaxStats object
       */
      virtual SaxsStats calcSaxsStats(const Point<int> &center, int num_bins) const = 0;

      // Frame manipulation
      virtual void swapAxisLengths()  = 0;
      virtual bool interlace(bool force = false, int interlace_code = 0, int n_modules_fast = 0, int n_modules_slow = 0) = 0;
      virtual bool deinterlace(bool force = false) = 0;
      virtual bool reorient(RxTransformationCode_t transformation_code) = 0;
      
      //! Return an 8-bit representation of the image for displaying to screen
      /*! \param render_min minimum value to which to assign a color
       *  \param render_max maximum value to which to assign a color
       *  \return 8 bit image buffer for use in screen display.
	  Caller must "delete[]".
       */
      virtual uint8_t *createScreenBuffer(int *render_min, int *render_max) const = 0;
      
      //! return typeid.name() of pixel data type
      //!
      //! This can be used to determine data type of pixels in the buffer by comparing to, eg, typeid(uint16_t)
      virtual const char * getPixelTypeIDName() const = 0;

      virtual bool resizeBuffer(const int n_fast, const int n_slow) = 0;

      virtual bool Interlaced() const = 0;

      virtual bool getInterlace(int& interlace_code, int& fast_modules, int& slow_modules) const = 0;

      virtual void setInterlaced(bool interlaced) = 0;

      virtual void setInterlace(bool interlaced, int interlace_code, int fast_modules, int slow_modules) = 0;

      virtual void setPixelValues(int value) = 0;

      virtual void copyMetaData(const RxFrame* frame_p) = 0;
      virtual void importExperimentMetaData(const ExperimentMetaData& meta_data) {acquisition_data_.experiment = meta_data;}

      //virtual FrameMetaData& metaData() = 0;

      //virtual FrameMetaData& constMetaData() const = 0;

      FrameMetaData& metaData() {return acquisition_data_;}

      const FrameMetaData& constMetaData() const {return acquisition_data_;}


      virtual bool mergeByDezingering(const RxFrame* input_frame) = 0;
      virtual bool dezingerFrames(const std::vector<const RxFrame*> input_frames) = 0;

   protected:

      FrameMetaData acquisition_data_;

   private:



};
// Requires implementation
inline RxFrame::~RxFrame() {};
// Forward declaration because RxTypedFrame needs it
template <class PIXEL> class GPUDeviceBuffer;

//! \class RxTypedFrame
//! \brief used for allocating and passing frame data to and from the GPU in interaction with GPUDeviceBuffer
template <class PIXEL>
class RxTypedFrame : public RxFrame
{
   public:
      typedef PIXEL PixelType;

      //! RxTypedFrame that allocates its own storage
      RxTypedFrame(int n_fast = 1, int n_slow = 1);
      //! RxTypedFrame that uses storage passed in - cannot be resized!
      RxTypedFrame(PIXEL *buffer, int n_fast = 1, int n_slow = 1);

      ~RxTypedFrame();

      //! Override copy constructor to do deep copy
      RxTypedFrame(const RxTypedFrame& source);

      // Assignment operator
      RxTypedFrame<PIXEL>& operator=(const RxTypedFrame&  rhs);

      bool resizeBuffer(const int n_fast, const int n_slow);

      bool copy(const RxFrame *frame_p);

      RxFrame *clone() const;

      bool isEquivalentType(const RxFrame* frame_p) const;

      bool isCompatible(int depth, bool signed_pixel, int nfast, int nslow) const;

      bool isCompatible(const RxFrame* frame_p) const;

#if USEREADMETHOD
      bool read(const std::string& filename);
#endif

      bool write(const std::string& filename);

      bool importData(const int n_fast, const int n_slow, PIXEL *data_p);

      bool importFromGPUDeviceBuffer(const GPUDeviceBufferBase &device_buffer);
      //bool importFromGPUDeviceBuffer(const GPUDeviceBuffer<PIXEL> &device_buffer);

      int getNFast() const;

      int getNSlow() const;

      size_t getDepth() const;

      bool getIsSignedData() const;

      size_t NPixels() const;

      size_t getSize() const;

      void *getBufferAddress() const;

      int getPixelValue (size_t offset) const;

      int getPixelValue (const Point<int> &point) const;

      int getFirstPixelValue () const;

      int getLastPixelValue () const;

      const char * getPixelTypeIDName() const;

      void truncateROI(Rect<int> &area) const;

      std::string printROIFrame(Rect<int> &area) const;

      RxFrame *createROIFrame(Rect<int> &area) const;

      void calcSectionStats(int margin_fast, int margin_slow, std::vector<int> &min, std::vector<int> &max, std::vector<double> &mean, std::vector<double> &std_dev) const;

      RectangleStats calcRectStats(const Rect<int> &area) const;

      LineStats calcLineStats(const Line<int> &line, int line_width) const;

      SaxsStats calcSaxsStats(const Point<int> &center, int num_bins) const;

      // Frame manipulation
      void swapAxisLengths();
      bool interlace(bool force = false, int interlace_code = 0, int n_modules_fast = 0, int n_modules_slow = 0);
      bool deinterlace(bool force = false);
      bool reorient(RxTransformationCode_t transformation_code);

      PIXEL* data() const;
      
      //Caller must "delete[]"
      uint8_t *createScreenBuffer(int *render_min, int *render_max) const;

      bool Interlaced() const ;
      bool getInterlace(int& interlace_code, int& fast_modules, int& slow_modules) const ;
      void setInterlaced(bool interlaced);
      void setInterlace(bool interlaced, int interlace_code, int fast_modules, int slow_modules);
      void setPixelValues(int value);

      void copyMetaData(const RxFrame* frame_p) {acquisition_data_ = dynamic_cast<const RxTypedFrame<PIXEL>*>(frame_p)->constMetaData();}

      //void getMetaData(FrameMetaData& metaData) {metaData = metaData(); return;}

      // Various frame operations
      bool mergeByDezingering(const RxFrame* input_frame);

      bool dezingerFrames(const std::vector<const RxFrame*> input_frames);

      void setFrameIntegrity() {

	 metaData().setFrameIntegrityChecksum(frameChecksum());

	 return;
      }

      bool verifyFrameIntegrity() const { return (frameChecksum() == constMetaData().frameIntegrityChecksum()); }

      GPUDeviceBufferBase* createGPUDeviceBuffer() const
      {
	 // May fail if no space available
	 try {
	    return new GPUDeviceBuffer<PIXEL>(getNFast(),getNSlow());
	 }

	 catch(std::bad_alloc) {
	    return NULL;
	 }
      }

   private:

      FrameChecksum_t frameChecksum() const
      {
	 return getPixelValue(0) + getPixelValue(1) + getPixelValue(2) + 
		getPixelValue(3) + getPixelValue(4) + getPixelValue(5) + getLastPixelValue();

      }

      template <class T>
      bool TgetROI(Rect<int> &area, T* buffer) const;

   private:
      PIXEL *buffer_;
      bool mapped_buffer_;
      int n_fast_;
      int n_slow_;
      bool interlaced_;
      int interlace_code_;
      int interlaced_modules_fast_;
      int interlaced_modules_slow_;

};

template <class PIXEL>
RxFrame* createRxFrame(PIXEL* buffer, int nfast, int nslow);

template <class PIXEL>
inline RxFrame* createRxFrame(const PIXEL& pix, int nfast, int nslow);

RxFrame* createRxFrame(const int depth, const bool signed_value, int nfast = 1, int nslow = 1);

//! Allocates a new frame, reads into it, and returns it
RxFrame* readRxFrame(std::string filename);

class GPUDeviceBufferBase
{
   public:
      GPUDeviceBufferBase() {}

      virtual ~GPUDeviceBufferBase()  = 0;

      virtual bool resizeBuffer(int n_fast, int n_slow) = 0;

      virtual bool writeBuffer(const std::string& filename) const = 0;

      //virtual bool importData(const int n_fast, const int n_slow, const void *data_p, const bool update_stats = true) = 0;

      //virtual bool exportData(void *buffer, const int buffer_size) const = 0;

      virtual bool importRxFrame(const RxFrame& frame) = 0;

      virtual bool stat() = 0;

      virtual int getNFast() const { return n_fast_; }

      virtual int getNSlow() const { return n_slow_; }

      virtual size_t getDepth() const  = 0;

      virtual size_t NPixels() const { return getNFast() * getNSlow(); }

      virtual size_t getSize() const = 0;

      virtual int getMin() const = 0;

      virtual int getMax() const = 0;

      virtual float getMean() const = 0;

      virtual float getStdDev() const = 0;
      
   private:
      int n_fast_;
      int n_slow_;
};
// Requires implementation
inline GPUDeviceBufferBase::~GPUDeviceBufferBase() {}

//! \class GPUDeviceBuffer
//! \brief used for passing frame data to and from the GPU
template <class PIXEL>
class GPUDeviceBuffer : public GPUDeviceBufferBase
{
   public:
      typedef PIXEL PixelType;
      typedef RxTypedFrame<PIXEL> FrameType;
      GPUDeviceBuffer(int n_fast, int n_slow) :
      n_fast_(n_fast),
      n_slow_(n_slow),
      nused_(0),
      nbelow_(0),
      nabove_(0),
      min_(0),
      max_(0),
      mean_(0.0),
      stddev_(0.0)
      {
	 if (sizeof(PIXEL) == 1) {
	    minimum_value_ = 1;
	    maximum_value_ = (1 << 8) - 2;
	 }
	 else if (sizeof(PIXEL) == 2) {
	    minimum_value_ = 1;
	    maximum_value_ = (1 << 16) - 2;
	 }
	 else if (sizeof(PIXEL) == 4) {
	    minimum_value_ = 1;
	    maximum_value_ = (1 << 18) - 2;
	 }
	 else {
	    // Assume that this is a correction table - with a 16-bit flatfield entry */
	    minimum_value_ = 1;
	    maximum_value_ = (1 << 16) - 2;
	 }
	 buffer_ = static_cast<PIXEL *>(malloc_gpu(getSize()));
	 if (!buffer_) {
	    n_fast_ = 0;
	    n_slow_ = 0;
	    throw std::bad_alloc();
	 }
      }
      ~GPUDeviceBuffer(){
	 free_gpu(buffer_);
      }

      // Requires override do to deep copy (copy on GPU device)
      GPUDeviceBuffer<PIXEL>& operator=(const GPUDeviceBuffer<PIXEL> & rhs) // Assigmnent operator
      {
	 // Check for self assignment
	 if (this == &rhs) return *this;

	 // (re)allocates space on GPU
	 resizeBuffer(rhs.getNFast(), rhs.getNSlow());

	 // Copies data in buffer, internally to gpu
	 copy_frame_gpu(n_fast_, n_slow_, rhs.data(), buffer_);

	 // copy all the private variables
	 minimum_value_  = rhs.minimum_value_;
	 maximum_value_  = rhs.maximum_value_;
	 nused_          = rhs.nused_;
	 nbelow_         = rhs.nbelow_;
	 nabove_         = rhs.nabove_;
	 min_            = rhs.min_;
	 max_            = rhs.max_;
	 mean_           = rhs.mean_;
	 stddev_         = rhs.stddev_;

	 RxLog(LOG_TRACE) << "GPUDeviceBuffer::= copied buffer" << endl;

	 return *this;
      }

      PIXEL* data() const {return buffer_;}

      bool resizeBuffer(int n_fast, int n_slow) {
	 if (n_fast != getNFast() || n_slow != getNSlow()) {
	    n_fast_ = n_fast;
	    n_slow_ = n_slow;
	    RxLog(LOG_DEBUG) << "GPUDeviceBuffer::resizeBuffer() - resizing device buffer to " << getNFast() << "x" <<  getNSlow() << "(" << getSize() << " Bytes)" << endl;
	    free_gpu(buffer_);
	    buffer_ = static_cast<PIXEL *>(malloc_gpu(getSize()));
	    if (!buffer_) {
	       RxLog(LOG_ERROR) << "GPUDeviceBuffer::resizeBuffer() - Failed to get new buffer " << NPixels() << " elements (" <<  getSize() << " bytes)." << endl;
	       return false;
	    }
	 }
	 else {
	    RxLog(LOG_TRACE) << "GPUDeviceBuffer::resizeBuffer() - resize not needed (" << getNFast() << "x" <<  getNSlow() << ") (" << getSize() << " Bytes)" << endl;
	 }
	 if (!buffer_) {
	    n_fast_ = 0;
	    n_slow_ = 0;
	 }
	 return true;
      }

      bool writeBuffer(const std::string& filename) const
      {
	 RxTypedFrame<PIXEL> tmp_buffer(getNFast(), getNSlow());

	 tmp_buffer.importFromGPUDeviceBuffer(*this);

	 return tmp_buffer.write(filename);

      }

      bool importData(const int n_fast, const int n_slow, const PIXEL *data_p, const bool update_stats = true)
      {
	 RxLog(LOG_TRACE) << "GPUDeviceBuffer::importData()" << endl;
	 if (!data_p) {
	    RxLog(LOG_ERROR) << "GPUDeviceBuffer::importData() - cannot import data from NULL" << endl;
	    return false;
	 }

	 RxLog(LOG_TRACE) << "GPUDeviceBuffer::importData() - resizing" << endl;
         // Must resize device buffer if necessary to receive data;
	 if (!resizeBuffer(n_fast, n_slow)) {
	    RxLog(LOG_ERROR) << "GPUDeviceBuffer::importData() - failed to resize device buffer to " << n_fast << "x" <<  n_slow << endl;
	    return false;
	 }

	 RxLog(LOG_TRACE) << "GPUDeviceBuffer::importData() - copying" << endl;
         // Then copy into device buffer
	 if (!copy_to_gpu(data_p, getSize(), data())) {
	    RxLog(LOG_ERROR) << "GPUDeviceBuffer::importData() - Error copying " << NPixels() << " elements (" <<  getSize() << " bytes)." << endl;
	    return false;
	 }
	 RxLog(LOG_DEBUG) << "GPUDeviceBuffer::importData() - copied " << NPixels() << " elements (" <<  getSize() << " bytes)." << endl;

	 if (update_stats) {
	    RxLog(LOG_TRACE) << "GPUDeviceBuffer::importData() - updating stats" << endl;
	    stat();
	 }

	 return true;
      }

      bool exportData(PIXEL *buffer, const int buffer_size) const
      {
	 int bytes_to_copy = getSize();

	 if (buffer_size < bytes_to_copy) {
	    RxLog(LOG_WARNING) << "GPUDeviceBuffer::exportData() - truncating export from  " << bytes_to_copy << " Bytes to " <<  buffer_size << " Bytes" << endl;
	    bytes_to_copy = buffer_size;
	 }

         // Then copy out of device buffer
	 if (!copy_from_gpu(data(), bytes_to_copy, buffer)) {
	    RxLog(LOG_ERROR) << "GPUDeviceBuffer::exportData() - Error copying " << NPixels() << " elements (" <<  getSize() << " bytes)." << endl;
	    return false;
	 }
	 RxLog(LOG_DEBUG) << "GPUDeviceBuffer::exportData() - copied " << bytes_to_copy << " bytes." << endl;

	 return true;
      }

      bool importRxFrame(const RxFrame& frame)
      {
	 RxLog(LOG_TRACE) << "GPUDeviceBuffer::importRxFrame()" << endl;
	 return importData(frame.getNFast(), frame.getNSlow(), dynamic_cast<const FrameType&>(frame).data());
      }

      bool stat();

      int getNFast() const {
	 return n_fast_;
      }

      int getNSlow() const {
	 return n_slow_;
      }

      size_t getDepth() const {
	 return (int) sizeof(PIXEL);
      }

      size_t NPixels() const {
	 return getNFast() * getNSlow();
      }

      size_t getSize() const {
	 return NPixels() * getDepth();
      }

      int getMin() const {
	 return min_;
      }

      int getMax() const {
	 return max_;
      }

      float getMean() const {
	 return mean_;
      }

      float getStdDev() const {
	 return stddev_;
      }
      
   private:
      PIXEL *buffer_;
      int n_fast_;
      int n_slow_;
      int minimum_value_;
      int maximum_value_;
      int nused_;
      int nbelow_;
      int nabove_;
      int min_;
      int max_;
      float mean_;
      float stddev_;
};

}

#endif //RX_FRAME_H
