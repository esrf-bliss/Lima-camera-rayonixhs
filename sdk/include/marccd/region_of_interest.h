#ifndef H_REGION_OF_INT
#define H_REGION_OF_INT

#include "macros.h"
#include "geometry.h"
#include "detector.h"

int have_roi(struct RectCartInt roi);
struct RectCartInt get_roi_from_ctbl(data_frame *ctbl);

#endif
