#ifndef mmx_frames_h
#define mmx_frames_h

#include "frame.h"

#define  MAX_MMX_SCRATCH_BUFFERS	4

typedef enum _MMXFrame {
   MMXframeNone,
   MMXframeDisplayed,
   MMXframePreRawDetector,
   MMXframeDetector,
   MMXframeCorrectedDetector,
   MMXframeProcessing,
   MMXframeBackground,
   MMXframeFlatfield,
   MMXframeCalibrationPlate,
   MMXframeInvertedFlatfield,
   MMXframePostFlatfield,
   MMXframeInvertedPostFlatfield,
   MMXframeXCorrection,
   MMXframeYCorrection,
   MMXframeAreaCorrection,
   MMXframeCorrectionTable,
   MMXframeROICorrectionTable,
   MMXframeDarkOnly,
   MMXframeDarkStandard,
   MMXframeBias,
   MMXframeInputMask,
   MMXframeOutputMask,
   MMXframeDefectMap,
   MMXframeOverlapMap,
   MMXframeMean,
   MMXframeSigma,
   MMXframeStdErr,
   MMXframeNUsed,
   MMXframeCrystals0,
   MMXframeCrystals90,
   MMXframeScratch,
   MMXframeScratch1,
   MMXframeScratch2,
   MMXframeScratch3,
   MMXframeOverscan,
   MMXframePseudoOverscan,
   MMXframeSystemScratch,
   MMXframeSystemScratch1,
   MMXframeSystemScratch2,
   MMXframeHoldingBuffer0,
   MMXframeHoldingBuffer1,
   MMXframeHoldingBuffer2,
   MMXframeHoldingBuffer3,
   MMXframePreCorrectBuffer0,
   MMXframePreCorrectBuffer1,
   MMXframePreCorrectBuffer2,
   MMXframePreCorrectBuffer3,
   MMXframePostCorrectBuffer0,
   MMXframePostCorrectBuffer1,
   MMXframePostCorrectBuffer2,
   MMXframePostCorrectBuffer3
} MMXFrame;


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern void set_displayed_frame(
#if NeedFunctionPrototypes
data_frame *a_framep
#endif
);

extern data_frame *get_mmx_frame(
#if NeedFunctionPrototypes
int frame_name
#endif
);

extern void set_detector_frame_busy(
#if NeedFunctionPrototypes
void
#endif
);

extern int get_detector_frame_busy(
#if NeedFunctionPrototypes
void
#endif
);

extern void set_detector_frame_not_busy(
#if NeedFunctionPrototypes
void
#endif
);

extern int get_mmx_frame_by_name(
#if NeedFunctionPrototypes
const char *name
#endif
);

#if 0
void set_correction_table(
#if NeedFunctionPrototypes
data_frame *ctbl
#endif
);
#endif

#endif /* mmx_frames_h */
