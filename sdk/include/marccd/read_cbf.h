/* Justin Anderson - Rayonix, LLC
   Sept - Oct 2007 */

#ifndef READ_CBF_H
#define READ_CBF_H

#include "cbf.h"
#include "frame.h"
#include "pvtstdio.h"

int read_cbf_frame (
int fd,
data_frame *dfp
);

#endif
