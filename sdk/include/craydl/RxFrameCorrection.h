#ifndef RX_FRAME_CORRECTION_H
#define RX_FRAME_CORRECTION_H

#include <boost/thread.hpp>

#include "RxFrame.h"
#include "MarCCD.h"
#include "PixelTypes.h"
#include "RxFrameCorrectionFilenameGenerator.h"

namespace craydl {

//! \namespace  craydl All RxDetector classes and functions are encapsulated in the craydl namespace

using std::cout;
using std::cerr;
using std::endl;


class CorrectionTableEntry {

   public:
      CorrectionTableEntry();
      ~CorrectionTableEntry();

      // Overload of = operator for importing CorrectionTableEntry_t
      //CorrectionTableEntry& operator=(CorrectionTableEntry_t const& rhs); // Assigmnent operator
      CorrectionTableEntry& operator=(CorrectionTableEntry_t const& rhs); // Assigmnent operator


      // Overload of = operator for importing MarCCD correction tables
      CorrectionTableEntry& operator=(MarCCDCorrectionTableEntry  const& rhs); // Assigmnent operator

      int exportToMarCCDEntry(MarCCDCorrectionTableEntry &new_marccd_record); //Export to MarCCD... 

      //! \brief creates an entry that make no change to pixel
      void setIdentity(int offset = 0);

      //! \brief creates an entry that smears pixel into neighbors
      void setTestEntry(int offset = 0, int n_entries = 5);

      //! \brief calculates the correct flag to correspond to the the fractions
      uint8_t calculateFlag();

      int full_size() const;

      int n_fractions() const;
      int size() const;
      CorrectionTableEntry_t data() const;

      unsigned int offset() const;
      //bool extra() const;
      int correction_factor() const;
      int flag() const;
      int fraction(int index) const;

   private:
      CorrectionTableEntry_t entry_;
};

#if 0
class CorrectionFilenameGenerator {
   public:
      CorrectionFilenameGenerator(int n_fast = 0, int n_slow = 0, const std::string& basename = std::string(""));

      ~CorrectionFilenameGenerator();

      std::string PostFlatfieldFilename() const;

      std::string CorrectionTableFilename() const;

      std::string GeneralFilename(const std::string& suffix) const;

      void setDimensions(int n_fast, int n_slow);

      void unsetBasename();

      void setBasename(const std::string& basename);

   private:
      std::string basename_;
      int n_fast_;
      int n_slow_;
      std::string filename_;
      bool table_interlaced_;
      bool table_interlace_code_;
      bool deinterlace_;
      int deinterlace_code_;
      bool mode_;
      std::string Model_;
      std::string Delimiter_;
      std::string SN_;
      std::string Fast_;
      std::string Slow_;
      std::string InterlaceCode_;
      std::string Mode_;
      std::string CTBSuffix_;
      std::string PFFSuffix_;
};
#endif

//! \class RxFrameCorrection
//! \brief base class for FrameCorrection class template
class RxFrameCorrection
{
   public:
      //virtual RxFrameCorrection(int n_fast, int n_slow) = 0;
      //virtual RxFrameCorrection(const std::string& correction_base_filename, int n_fast, int n_slow) = 0;
      // pure virtual destructor mean that this is a virtual class that can only be used as a base for another derived class
      virtual ~RxFrameCorrection() = 0;

      virtual bool readCorrectionTable(std::string filename = std::string("")) = 0;
      virtual bool writeCorrectionTable(const std::string& filename = std::string("")) = 0;
      virtual bool writeCorrectionTable_FormatMarCCD(const std::string& filename) = 0;
      virtual bool createIdentityCorrectionTable() = 0;
      virtual bool createTestCorrectionTable(int n_entries = 5) = 0;
      virtual bool printCorrectionTableEntry(int pixel) = 0;
      virtual bool printCorrectionTableEntry(int pixel, GPUDeviceBuffer<CorrectionTableEntry_t> *d_table_p) = 0;
      //! \brief checks that frame is compatible with this correction object
      virtual bool isCompatibleFrame(const RxFrame *frame_p) = 0;
      //! \brief reads a frame file directly to a GPUDeviceBuffer
      //virtual bool readFrame(const std::string& filename, GPUDeviceBuffer<PIXEL> &d_frame, bool resize = false) = 0;
      //! \brief reads a frame file directly to a RxTypedFrame
      //virtual bool readFrame(const std::string& filename, RxTypedFrame<PIXEL> &h_frame, bool allow_resize = false) = 0;
      //! \brief writes a frame file directly from a GPUDeviceBuffer
      //virtual bool writeFrame(const std::string& filename, GPUDeviceBuffer<PIXEL> &d_frame) const = 0;
      //! \brief writes a frame file directly from a RxTypedFrame
      //virtual bool writeFrame(const std::string& filename, RxTypedFrame<PIXEL> &h_frame) const = 0;
      //! \brief imports data from a buffer to use as a raw frame
      //virtual bool importRawFrame(int n_fast, int n_slow, PIXEL *data) = 0;
      //! \brief read a frame from a file to use as a raw frame
      //virtual bool readRawFile(const std::string& filename) = 0;
      virtual bool createZeroBackgroundFrame() = 0;
      //! \brief imports data from a buffer to use as a background frame
      //virtual bool importBackgroundFrame(int n_fast, int n_slow, PIXEL *data) = 0;
      //! \brief imports data from a RxFrame to use as a background frame
      virtual bool importBackgroundFrame(RxFrame* background_frame_p) = 0;
      //! \brief read a frame from a file to use as a background frame
      virtual bool readBackgroundFile(const std::string& filename) = 0;
      //! \brief write a frame from a file to use as a background frame
      virtual bool writeBackgroundFile(const std::string& filename) = 0;
      virtual bool createFlatPostFlatfieldFrame(int value = 10000) = 0;
      //! \brief read a frame from a file to use as a postflat frame - resize correction tables, if this is different size than present size
      virtual bool readPostFlatfieldFile(const std::string& filename = std::string("")) = 0;
      //! \brief write the postflat frame to a file
      virtual bool writePostFlatfieldFile(const std::string& filename = std::string("")) = 0;
      //! \brief applies correction to a RxFrame, in-place
      virtual bool applyCorrection(RxFrame* frame_p, RxTransformationCode_t reorientation_code = R0) = 0;
      //! \brief apply correction to the RxFrame input and produce a RxFrame output
      virtual bool applyCorrection(const RxFrame *input_frame_p, RxFrame *output_frame_p, RxTransformationCode_t reorientation_code = R0) = 0;

      virtual bool deinterlaceFrame(RxFrame *frame_p, bool force = false) = 0;
      virtual bool deinterlaceFrame(const RxFrame *input_frame_p, RxFrame *output_frame_p, bool force = false) = 0;


#if 0
      virtual bool reorientFrame(RxTransformationCode_t transformation_code, RxFrame *frame_p, bool force = false) = 0;
      virtual bool reorientFrame(RxTransformationCode_t transformation_code, const RxFrame *input_frame_p, RxFrame *output_frame_p, bool force = false) = 0;
#endif

      virtual int getNFast() const = 0;
      virtual int getNSlow() const = 0;
      virtual int getNPixels() const = 0;
      virtual std::string getCorrectionTableFilename() const = 0;
      virtual std::string getPostFlatfieldFilename() const = 0;
      virtual void setDimensions(int n_fast, int n_slow) = 0;
      virtual bool getTableInterlaced() = 0;
      virtual bool getTableInterlaced(int& table_interlace_code) = 0;
      virtual void setTableInterlaced(bool table_interlaced) = 0;
      virtual void setTableInterlaced(bool table_interlaced, int table_interlace_code) = 0;
      virtual bool getDeinterlace() = 0;
      virtual bool getDeinterlace(int& deinterlace_code) = 0;
      virtual void setDeinterlace(bool deinterlace) = 0;
      virtual void setDeinterlace(bool deinterlace, int deinterlace_code) = 0;
      //virtual bool getReoriention(int& reorientation_code) = 0;
      //virtual void setReoriention(bool reorient) = 0;
      //virtual void setReoriention(bool reorient, int reorientation_code) = 0;

      virtual void setCorrectionFilenameGenerator(const RxFrameCorrectionFilenameGenerator& correction_filename_generator) = 0;
      virtual void SetBiasFinal(int bias) = 0;
      virtual void SetBiasIn(int bias) = 0;
      virtual void SetBiasWorking(int bias) = 0;
};
// Requires implementation
inline RxFrameCorrection::~RxFrameCorrection() {};

//! \class RxTypedFrameCorrection
//! \brief manages correction of raw data frames on GPU
template <class PIXEL>
class RxTypedFrameCorrection : public RxFrameCorrection
{

   typedef boost::posix_time::ptime timestamp_t;
   typedef boost::posix_time::time_duration time_duration_t;

   public:

      RxTypedFrameCorrection(const std::string& correction_base_filename = std::string(""), int n_fast = 1, int n_slow = 1);

      ~RxTypedFrameCorrection();

      typedef std::vector<PIXEL> data_frame_t;

      bool readCorrectionTable(std::string filename = std::string(""));

      bool writeCorrectionTable(const std::string& filename = std::string(""));

      bool writeCorrectionTable_FormatMarCCD(const std::string& filename);

      bool createIdentityCorrectionTable();

      bool createTestCorrectionTable(int n_entries = 5);

      bool printCorrectionTableEntry(int pixel);

      //! \brief checks that frame is compatible with this correction object
      bool isCompatibleFrame(const RxFrame *frame_p);

      bool printCorrectionTableEntry(int pixel, GPUDeviceBuffer<CorrectionTableEntry_t> *d_table_p);

      //! \brief reads a frame file directly to a GPUDeviceBuffer
      bool readFrame(const std::string& filename, GPUDeviceBuffer<PIXEL> &d_frame, bool resize = false);

      //! \brief reads a frame file directly to a RxTypedFrame
      //bool readFrame(const std::string& filename, RxTypedFrame<PIXEL> &h_frame, bool allow_resize = false);
      bool readFrame(const std::string& filename, RxFrame *h_frame_p, bool allow_resize = false);

      //! \brief writes a frame file directly from a GPUDeviceBuffer
      bool writeFrame(const std::string& filename, GPUDeviceBuffer<PIXEL> &d_frame) const;

      //! \brief writes a frame file directly from a RxTypedFrame
      bool writeFrame(const std::string& filename, RxTypedFrame<PIXEL> &h_frame) const;

      //! \brief imports data from a buffer to use as a raw frame
      bool importRawFrame(int n_fast, int n_slow, PIXEL *data);

      bool createZeroBackgroundFrame();

      //! \brief imports data from a buffer to use as a background frame
      bool importBackgroundFrame(int n_fast, int n_slow, PIXEL *data);

      //! \brief imports data from a RxTypedFrame to use as a background frame
      bool importBackgroundFrame(RxFrame* background_frame_p);

      //! \brief read a frame from a file to use as a background frame
      bool readBackgroundFile(const std::string& filename);

      //! \brief write a frame from a file to use as a background frame
      bool writeBackgroundFile(const std::string& filename);

      bool createFlatPostFlatfieldFrame(int value = 10000);

      //! \brief read a frame from a file to use as a postflat frame - resize correction tables, if this is different size than present size
      bool readPostFlatfieldFile(const std::string& filename = std::string(""));

      //! \brief write the postflat frame to a file
      bool writePostFlatfieldFile(const std::string& filename = std::string(""));

      //! \brief applies correction to a RxTypedFrame, in-place
      bool applyCorrection(RxFrame *frame_p, RxTransformationCode_t reorientation_code = R0);

      //! \brief apply correction to the RxTypedFrame input and produce a RxTypedFrame output
      //bool applyCorrection(RxTypedFrame<PIXEL> &input_frame, RxTypedFrame<PIXEL> &output_frame)
      bool applyCorrection(const RxFrame *input_frame_p, RxFrame *output_frame_p, RxTransformationCode_t reorientation_code = R0);

      //! \brief apply correction to the RxTypedFrame argument
      bool applyCorrection(RxTransformationCode_t reorientation_code, bool deinterlace, int deinterlace_code, int n_modules_fast, int n_modules_slow, int input_n_fast, int input_n_slow, const PIXEL *input_data_p, int output_n_fast, int output_n_slow, PIXEL *output_data_p);

      bool deinterlaceFrame(RxFrame *frame_p, bool force = false);

      bool deinterlaceFrame(const RxFrame *input_frame_p, RxFrame *output_frame_p, bool force = false);

      bool deinterlaceFrame(int deinterlace_code, int n_modules_fast, int n_modules_slow, int input_n_fast, int input_n_slow, const PIXEL *input_data_p, int output_n_fast, int output_n_slow, PIXEL *output_data_p);

      bool reorientFrame(RxTransformationCode_t reorientation_code, RxFrame *frame_p, bool force = false);
      bool reorientFrame(RxTransformationCode_t reorientation_code, const RxFrame *input_frame_p, RxFrame *output_frame_p, bool force = false);
      bool reorientFrame(RxTransformationCode_t reorientation_code, int input_n_fast, int input_n_slow, const PIXEL *input_data_p, int output_n_fast, int output_n_slow, PIXEL *output_data_p);

      int getNFast() const;

      int getNSlow() const;

      int getNPixels() const;

      std::string getCorrectionTableFilename() const;

      std::string getPostFlatfieldFilename() const;

      void setDimensions(int n_fast, int n_slow);

      bool getTableInterlaced(){return table_interlaced_;}
      bool getTableInterlaced(int& table_interlace_code){table_interlace_code = table_interlace_code_; return table_interlaced_;}
      void setTableInterlaced(bool table_interlaced) {table_interlaced_ = table_interlaced;}
      void setTableInterlaced(bool table_interlaced, int table_interlace_code) {table_interlaced_ = table_interlaced; table_interlace_code_ = table_interlace_code;}
      bool getDeinterlace(){return deinterlace_;}
      bool getDeinterlace(int& deinterlace_code){deinterlace_code = deinterlace_code_; return deinterlace_;}
      void setDeinterlace(bool deinterlace) {deinterlace_ = deinterlace;}
      void setDeinterlace(bool deinterlace, int deinterlace_code) {deinterlace_ = deinterlace; deinterlace_code_ = deinterlace_code;}
      //bool getReorientation(int& reorientation_code){reorientation_code = reorientation_code_; return reorient_;}
      //void setReorientation(bool reorient) {reorient_ = reorient;}
      //void setReorientation(bool reorient, int reorientation_code) {reorient_ = reorient; reorientation_code_ = reorientation_code;}

      void setCorrectionFilenameGenerator(const RxFrameCorrectionFilenameGenerator& correction_filename_generator) {correction_filename_generator_ = correction_filename_generator;}

      void SetBiasFinal(int bias);
      void SetBiasIn(int bias);
      void SetBiasWorking(int bias);

   private: 
      bool init(const std::string& correction_base_filename = std::string(""), int n_fast = 1, int n_slow = 1);

      bool allocateBuffers(int n_fast, int n_slow);

      bool deallocateBuffers();

      bool resize(int n_fast, int n_slow);

   private:
      //CorrectionTable correction_table_;
      RxTypedFrame<PIXEL> *raw_frame_p_;
      RxTypedFrame<PIXEL> *corrected_frame_p_;
      RxTypedFrame<PIXEL> *background_frame_p_;
      GPUDeviceBuffer<PIXEL> *d_frame_buffer_p_;
      GPUDeviceBuffer<PIXEL> *d_work_buffer0_p_;
      GPUDeviceBuffer<PIXEL> *d_work_buffer1_p_;
      GPUDeviceBuffer<CorrectionTableEntry_t> *d_correction_table_p_;
      GPUDeviceBuffer<int32_t> *d_correction_buffer_p_;
      GPUDeviceBuffer<PIXEL> *d_background_frame_p_;
      //GPUDeviceBuffer<PIXEL> *d_postflat_frame_p_;
      GPUDeviceBuffer<uint16_t> *d_postflat_frame_p_;
      //GPUDeviceBufferBase *d_postflat_frame_p_;
      GPUDeviceBuffer<PIXEL> *d_scratch_buffer0_p_;
      GPUDeviceBuffer<PIXEL> *d_scratch_buffer1_p_;
      boost::mutex  GPUScratchBuffer0Mutex_;
      boost::mutex  GPUScratchBuffer1Mutex_;

      std::vector<RxTypedFrame<PIXEL>**> h_buffers_;
      std::vector<GPUDeviceBuffer<PIXEL>**> d_buffers_;

      //! A mutex for running corrections
      boost::mutex  GPUMutex_;
      boost::thread ActiveCorrectionThread_;

      //CorrectionFilenameGenerator correction_filename_generator_;
      RxFrameCorrectionFilenameGenerator correction_filename_generator_;
      bool buffers_allocated_;
      int n_fast_;
      int n_slow_;
      int bias_in_;
      int bias_working_;
      int bias_final_;
      int correction_max_fraction_;
      float correction_mean_ff_;
      bool table_interlaced_;
      int table_interlace_code_;
      int deinterlace_code_;
      bool deinterlace_;
      int reorientation_code_;
      bool reorient_;
};

RxFrameCorrection* createRxFrameCorrection(const RxFrame *frame_p, const std::string& correction_base_filename);

//RxFrameCorrection* createRxFrameCorrection(int depth, const bool signed_value);
inline RxFrameCorrection* createRxFrameCorrection(const RxFrame *frame_p, const RxFrameCorrectionFilenameGenerator& correction_filename_generator)
{
   RxFrameCorrection* RxFCp = createRxFrameCorrection(frame_p, "");
   RxFCp->setCorrectionFilenameGenerator(correction_filename_generator);
   return RxFCp;
}


// RxFrameCorrection object factory
inline RxFrameCorrection* createRxFrameCorrection(const RxFrame *frame_p, const std::string& correction_base_filename)
{
   RxLog(LOG_DEBUG) << "createRxFrameCorrection() - creating RxFrameCorrection<" << typeid(*frame_p).name() << ">" << endl;

   try {

      if (typeid(*frame_p) == typeid(RxTypedFrame<uint16_t>)) {
	 RxLog(LOG_DEBUG) << "createRxFrameCorrection() - creating RxTypedFrameCorrection<uint16_t>" << endl;
	 return (RxFrameCorrection *) new RxTypedFrameCorrection<uint16_t>(correction_base_filename, frame_p->getNFast(), frame_p->getNSlow());
      }
      else if (typeid(*frame_p) == typeid(RxTypedFrame<uint32_t>)) {
	 RxLog(LOG_DEBUG) << "createRxFrameCorrection() - creating RxTypedFrameCorrection<uint32_t>" << endl;
	 return (RxFrameCorrection *) new RxTypedFrameCorrection<uint32_t>(correction_base_filename, frame_p->getNFast(), frame_p->getNSlow());
      }
      else if (typeid(*frame_p) == typeid(RxTypedFrame<int16_t>)) {
	 RxLog(LOG_DEBUG) << "createRxFrameCorrection() - creating RxTypedFrameCorrection<int16_t>" << endl;
	 return (RxFrameCorrection *) new RxTypedFrameCorrection<int16_t>(correction_base_filename, frame_p->getNFast(), frame_p->getNSlow());
      }
      else if (typeid(*frame_p) == typeid(RxTypedFrame<int32_t>)) {
	 RxLog(LOG_DEBUG) << "createRxFrameCorrection() - creating RxTypedFrameCorrection<int32_t>" << endl;
	 return (RxFrameCorrection *) new RxTypedFrameCorrection<int32_t>(correction_base_filename, frame_p->getNFast(), frame_p->getNSlow());
      }

   }
   catch (std::bad_alloc) {
   }

   RxLog(LOG_ERROR) << "createRxFrameCorrection() - Failed to create RxFrameCorrection object" << endl;
   return NULL;
}

}

#endif //RX_FRAME_CORRECTION_H

