#ifndef PIXEL_TYPES_H
#define PIXEL_TYPES_H

#include <limits>

namespace craydl {

// This file declares types that may be used as "pixels" in class and structures
// that manipulate images.
//
// More usual types, do not need declaration here as the normal collection of types
// is covered by the types in <stdint.h>


   struct  CorrectionTableEntry_t {
      uint32_t offset;
      uint16_t correction_factor;
      uint8_t flag;
      uint8_t fractions[9];
   };

   //! \namespace craydl::PixelType contains utility information functions for pixels
   namespace PixelType {
      template <class T> bool is_signed(T);

      template <class T> inline bool is_signed(T) {return std::numeric_limits<T>::is_signed; }
      template <> inline bool is_signed(CorrectionTableEntry_t) {return false;}

   }

}

#endif //PIXEL_TYPES_H
