
#include "RxFrame.h"

namespace craydl {

//! \namespace  craydl All RxDetector classes and functions are encapsulated in the craydl namespace

class RxFrameMathBase
{
   public:
      RxFrameMathBase() {};
      virtual ~RxFrameMathBase() = 0;

      virtual bool interlaceFrame(const RxFrame* input_frame_p, RxFrame* output_frame_p = NULL, bool force = false, int interlace_code = 0, int modules_fast = 0, int modules_slow = 0) = 0;

      virtual bool deinterlaceFrame(const RxFrame* input_frame_p, RxFrame* output_frame_p = NULL, bool force = false, int interlace_code = 0, int modules_fast = 0, int modules_slow = 0) = 0;

      virtual bool reorientFrame(RxTransformationCode_t transformation_code, const RxFrame* input_frame_p, RxFrame* output_frame_p = NULL) = 0;

      //virtual bool subtractFrame(const RxFrame* minuend_frame_p, const RxFrame* subtrahend_frame_p, RxFrame* difference_frame_p = NULL);

      //virtual bool divideFrame(const RxFrame* dividend_frame_p, const RxFrame* divisor_frame_p, RxFrame* quotient_frame_p = NULL);

};
// Requires implementation
inline RxFrameMathBase::~RxFrameMathBase() {};

template <class FRAME> class RxFrameMath : public RxFrameMathBase
{
   public:
      typedef FRAME FrameType;
      typedef typename FRAME::PixelType PixelType;
      //typedef typename FrameType::PixelType PixelType;
      RxFrameMath() {};
      ~RxFrameMath() {};

      bool interlaceFrame(const RxFrame* input_frame_p, RxFrame* output_frame_p = NULL, bool force = false, int interlace_code = 0, int modules_fast = 0, int modules_slow = 0);

      bool deinterlaceFrame(const RxFrame* input_frame_p, RxFrame* output_frame_p = NULL, bool force = false, int interlace_code = 0, int modules_fast = 0, int modules_slow = 0);

      bool reorientFrame(RxTransformationCode_t transformation_code, const RxFrame* input_frame_p, RxFrame* output_frame_p = NULL);
      //bool subtractFrame(const RxFrame* minuend_frame_p, const RxFrame* subtrahend_frame_p, RxFrame* difference_frame_p = NULL);

      //bool divideFrame(const RxFrame* dividend_frame_p, const RxFrame* divisor_frame_p, RxFrame* quotient_frame_p = NULL);

};

} // namespace craydl
