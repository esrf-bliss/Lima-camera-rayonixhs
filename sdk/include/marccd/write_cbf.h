/* Justin Anderson - Rayonix, LLC
   Sept - Oct 2007 */

#ifndef WRITE_CBF_H
#define WRITE_CBF_H

#include "cbf.h"
#include "cbf_simple.h"
#include "frame.h"

int write_cbf_frame (
data_frame *dfp,
const char *filename
);

char *unixDateToCBFDate(
char *unixDate
);

char *getEncodingType(
data_frame *dfp
);

#endif
