#ifndef RX_FRAME_CORRECTION_FILENAME_GENERATOR_H
#define RX_FRAME_CORRECTION_FILENAME_GENERATOR_H

#include <iostream>
#include <string>

namespace craydl {

//! \namespace  craydl All RxDetector classes and functions are encapsulated in the craydl namespace

using std::cout;
using std::cerr;
using std::endl;

enum RxFrameCorrectionFilenameStyle_t { CORRECTION_FILENAME_STYLE_CRAYDL, CORRECTION_FILENAME_STYLE_MARCCD};

class RxFrameCorrectionFilenameGenerator {

   public:
      RxFrameCorrectionFilenameGenerator(int n_fast = 0, int n_slow = 0, const std::string& basename = std::string(""));

      ~RxFrameCorrectionFilenameGenerator();

      std::string PostFlatfieldFilename() const;

      std::string FrameCorrectionTableFilename() const;

      void setDimensions(int n_fast, int n_slow);

      void setBasename(const std::string& name);

      void setCTBBasename(const std::string& name);

      void setPFFBasename(const std::string& name);

      void setCTBSuffix(const std::string& name);

      void setPFFSuffix(const std::string& name);

      RxFrameCorrectionFilenameStyle_t Style(const std::string& style_name);
      void setStyle(RxFrameCorrectionFilenameStyle_t style);

   private:
      std::string GeneralFilename(const std::string& suffix) const;

   private:
      RxFrameCorrectionFilenameStyle_t style_;
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
      std::string CTBBasename_;
      std::string PFFBasename_;
      std::string CTBSuffix_;
      std::string PFFSuffix_;
};

}

#endif //RX_FRAME_CORRECTION_FILENAME_GENERATOR_H

