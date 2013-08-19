#ifndef MARCCD_INTERFACE_H
#define MARCCD_INTERFACE_H

#include <limits>
#include <stdint.h>

#include "RxLog.h"
#include "RxUtils.h"
#include "PixelTypes.h"
#include "RxFrame.h"

#include <boost/date_time.hpp>

namespace craydl {

#define MARCCD_AVAILABLE 1
#if MARCCD_AVAILABLE

#if INCLUDEHERE
//! \namespace craydl::marccd encapsulates symbols from the marccd libraries
namespace marccd {
   extern "C" {
//#include "application.h"
#include "frame.h"
#include "foreign_frame.h"
#include "frame_math.h"
   }
}
#endif


class marccd_frame_file_header_t;

#endif


#define MAXIMUM_MARCCD_CORRECTION_FRACTION 250
class MarCCDDataFrame;
class MarCCDCorrectionTable;

class MarCCDHeader
{
   public: 
      MarCCDHeader();
      ~MarCCDHeader();

      //! \brief Read the header from an open file
      bool read(std::ifstream &file);

      //! \brief Write the header to an open file
      bool write(std::ofstream &file);

      bool import_frame_header(void *data);

      bool export_frame_header(void *data);

      int size() const;

      int data_n_fast() const;

      int data_n_slow() const;

      int data_depth() const;

      bool data_signed() const;

      bool dataInterlaced() const;
      int dataInterlaceCode() const;
      int dataInterlacedModulesFast() const;
      int dataInterlacedModulesSlow() const;

      std::string data_typeid_name() const;

      int data_size() const;

      int setDataNFast(int n_fast);

      int setDataNSlow(int n_slow);

      int setDataDepth(int depth);

      void setDataInterlaced(bool interlaced);
      void setDataInterlaceCode(int interlace_code);
      void setDataInterlacedModulesFast(int nmodules);
      void setDataInterlacedModulesSlow(int nmodules);

      boost::posix_time::time_duration IntegrationTime();
      boost::posix_time::time_duration ExposureTime();
      boost::posix_time::time_duration ReadoutTime();

      void setIntegrationTime(boost::posix_time::time_duration time);
      void setExposureTime(boost::posix_time::time_duration time);
      void setReadoutTime(boost::posix_time::time_duration time);

      boost::posix_time::ptime AcquireTimestamp();
      boost::posix_time::ptime HeaderTimestamp();
      boost::posix_time::ptime SaveTimestamp();

      void setAcquireTimestamp(boost::posix_time::ptime timestamp);
      void setHeaderTimestamp(boost::posix_time::ptime timestamp);
      void setSaveTimestamp(boost::posix_time::ptime timestamp);


      double Wavelength();
      void setWavelength(double nm);

      RxRotationAxis_t RotationAxis();
      double RotationRange();

      void setRotationAxis(RxRotationAxis_t axis);
      void setRotationRange(double degrees);

      double TwoTheta();
      double Omega();
      double Chi();
      double Kappa();
      double Phi();
      double Delta();
      double Gamma();
      double Distance();

      void setTwoTheta(double degrees);
      void setOmega(double degrees);
      void setChi(double degrees);
      void setKappa(double degrees);
      void setPhi(double degrees);
      void setDelta(double degrees);
      void setGamma(double degrees);
      void setDistance(double mm);

      void adjustAxisEnds();

      std::pair<double,double> PixelSize();

      void setPixelSize(double mm);
      void setPixelSize(std::pair<double,double> mm);
      void setPixelSize(double x_mm, double y_mm);

      std::pair<double,double> BeamPosition();
      void setBeamPosition(double mm);
      void setBeamPosition(std::pair<double,double> mm);
      void setBeamPosition(double x_mm, double y_mm);


   private:
      friend class MarCCDDataFrame;
      friend class MarCCDCorrectionTable;
      marccd_frame_file_header_t *header_p_;
};

struct  MarCCDCorrectionTableEntry_t {
   uint32_t offset;
   //uint32_t offset :31;
   //uint32_t extra :1;
   uint16_t ff;
   uint8_t flag;
   uint8_t fractions[8];
}; 
class MarCCDCorrectionTableEntry {

   public:
      MarCCDCorrectionTableEntry();
      ~MarCCDCorrectionTableEntry();

   private:
      MarCCDCorrectionTableEntry(MarCCDCorrectionTableEntry const&);	// copy constructor
      MarCCDCorrectionTableEntry& operator=(MarCCDCorrectionTableEntry const& rhs); // Assigmnent operator


   public:

      //! Full size (maximum size) of an entry
      int full_size() const;

      //! Number of fractions in this entry as indectaed by the flag
      int n_fractions() const;

      int n_fractions(const MarCCDCorrectionTableEntry_t *entry) const;

      //! Actual size of this entry
      int size() const;

      int size(const MarCCDCorrectionTableEntry_t *entry) const;

      //! Import data for entry from a buffer (as written in a file) to entry_t_ structure
      // Be careful to only copy as much data as there is, not any more!
      int import_data(const char *data_p);

      //! Export data from entry_t_ structure to a buffer (as written in a file)
      int export_data(void *data_p) const;

      //! export data to string
      std::string getFullDescription();

      void setOffset(const uint32_t offset);
      void setFF(const uint16_t ff);
      void initFlag();
      void setFlag(const uint8_t flag);
      void setFlagBit(const int bit);
      void initFractions();
      void setFraction(const int index, const uint8_t fraction);

      size_t getOffset() const;
      //bool getExtra const;
      int getFF() const;
      int getFlag() const;
      int getFraction(const int index) const;

   private:
      MarCCDCorrectionTableEntry_t entry_;
};

class MarCCDCorrectionTable
{
   public:
      MarCCDCorrectionTable();
      ~MarCCDCorrectionTable();

      bool resize_buffer(const int size);

      bool import_buffer(const char* const buffer, const int size);

      bool read(std::string filename);

      bool write(std::string filename);

      int getMaxFraction() const;

      size_t getNRecords() const;

      char *data() const;

      MarCCDHeader& Header() { return file_header_;}

   private:
      int size(bool count = false);
      int header_size();
      MarCCDHeader file_header_;
      char *buffer_p_;
      int buffer_size_;
      int n_records_;
      int max_fraction_;
      double mean_correction_factor_;
};


class MarCCDDataFrame
{
   public:
      MarCCDDataFrame();
      ~MarCCDDataFrame();

      bool read(const std::string& filename);

      bool write(const std::string& filename);

      bool export_buffer(char* const buffer, const int buffer_size);

      bool export_buffer(char* const buffer, const int buffer_size, int& n_fast, int& n_slow, int& depth);

      template <class T>
      bool import_buffer(const T* const buffer, const int n_fast, const int n_slow);

      int header_size() const;

      char *data() const;

      int getNFast() const;

      int getNSlow() const;

      size_t getDepth() const;

      bool getSigned() const;

      size_t getNPixels() const;

      size_t getSize() const;

      bool dataInterlaced() const;
      int dataInterlaceCode() const;
      int dataInterlacedModulesFast() const;
      int dataInterlacedModulesSlow() const;

      void setDataInterlaced(bool interlaced);
      void setDataInterlaceCode(int interlace_code);
      void setDataInterlacedModulesFast(int nmodules);
      void setDataInterlacedModulesSlow(int nmodules);

      //void setIntegrationTime(boost::posix_time::time_duration time) {file_header_.setIntegrationTime(time); }
      //void setExposureTime(boost::posix_time::time_duration time) {file_header_.setExposureTime(time); }
      //void setReadoutTime(boost::posix_time::time_duration time) {file_header_.setReadoutTime(time); }
      //void setAcquireTimestamp(boost::posix_time::ptime timestamp) {file_header_.setAcquireTimestamp(timestamp); }
      //void setHeaderTimestamp(boost::posix_time::ptime timestamp) {file_header_.setHeaderTimestamp(timestamp); }
      //void setSaveTimestamp(boost::posix_time::ptime timestamp) {file_header_.setSaveTimestamp(timestamp); }

      //Return 8-bit image buffer for screen display
      //Caller must "delete[]"
      uint8_t *createScreenBuffer(int *render_min, int *render_max);

      //! Calculate data frame statistics under the user-drawn line
      /*! \param data_in is the pixel buffer for the image
       *  \param nfast is the number of fast pixels in the image
       *  \param nslow is the number of slow pixels in the image
       *  \param depth is the depth (bytes) of the pixels in the image
       *  \param is_signed is true if the pixels are signed values
       *  \param saturated_value is the saturated pixel value
       *  \param fx1 is the x value of the first point describing the line
       *  \param fy1 is the y value of the first point describing the line
       *  \param fx2 is the x value of the second point describing the line
       *  \param fy2 is the y value of the second point describing the line
       *  \param fwidth is the width of the line to use for calculations
       *  \param positionp will be filled in with the distance values from start of line
       *  \param valuep will be filled in with the pixel values for their corresponding distance
       *  \param npts will be filled in with the number of points considered for the calculation
       *  \param option  is 0 for Raw or 1 for Interpolate
       *  \param min will be filled with the minimum observed pixel value from calculations
       *  \param max will be filled with the maximum observed pixel value from calculations
       */
      template <typename PIXEL>
      static void get_value_under_line_from_frame(PIXEL *data_in, int nfast, int nslow, int depth, bool is_signed, int saturated_value, double fx1, double fy1, double fx2, double fy2,
					   	  double fwidth, double **positionp, double **valuep, int *npts, int option, double *min, double *max);

      MarCCDHeader& Header() { return file_header_;}

   private:

      int marccd_data_type() const;


   private:
      MarCCDHeader file_header_;
      char *buffer_p_;
      int buffer_size_;
      int n_fast_;
      int n_slow_;
      int pixel_depth_;
      int pixel_signed_;
      std::string pixel_typeid_name_;
};

// Wrappers for various marccd functions
template <class PIXEL>
bool LowPixelArray(const PIXEL* data1, const PIXEL* data2, int maxdiff, int weight1, int weight2, int size , PIXEL* data_out);

} // namepace craydl

#endif // MARCCD_INTERFACE_H
