#ifndef LINE_STATS_H
#define LINE_STATS_H

#include <vector>
#include <cmath>
#include <limits.h>
#include <iostream>
#include <stdio.h>

#include <boost/format.hpp>

#include "RxUtils.h"

namespace craydl {

using std::vector;
using std::cout;
using std::cerr;
using std::endl;

/*! \file 
    \brief Code borrwed and tweaked from marccd for calculating stats under a plotted line over the image. */

//! Number of points to sample
const int NPOINTS = 10000;

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
void get_value_under_line_from_frame(PIXEL *data_in, int nfast, int nslow, int depth, bool is_signed, int saturated_value, double fx1, double fy1, double fx2, double fy2, double fwidth, double **positionp, 				     double **valuep, int *npts, int option, double *min, double *max)
{
   //unsigned int	   uvalue;
   int i, j, n;
   unsigned long size;
   double   length;
   double t,u;
   double x,y;
   double slope;
   double dx,dy;
   int x1, y1, x2, y2;
   unsigned int     offset;
   unsigned int offset1,offset2,offset3,offset4;
   PIXEL value1,value2,value3,value4;
   int signed_pix = 0;
   PIXEL *datap = data_in;
   double min_found = INT_MAX ,max_found = INT_MIN;
   double *position;
   double *value;
   int verbose = 0;

   *npts = 0;

   size = (unsigned long) (nfast * nslow);

   /* if the box is entirely outside the frame, then return */
   if ((floor(fx1) < 0 && floor(fx2) < 0) || (floor(fx1) >= nfast && floor(fx2) >= nfast) ||
       (floor(fy1) < 0 && floor(fy2) < 0) || (floor(fy1) >= nslow && floor(fy2) >= nslow)) {
      return;
   }

   if (is_signed)
      signed_pix = 1;
   else
      signed_pix = 0;

   /*if ((verbose > 3)) {
      cerr << boost::format("get_value...: data_type = %d, signed_pix = %d, saturated_value = %d\n") %  framep->header->data_type % signed_pix % saturated_value;
   }*/


   /* Look only at the intersection of the box and the frame */
   /*
   fx1 = LIMIT(0.0,fx1,(double)nfast);
   fy1 = LIMIT(0.0,fy1,(double)nslow);
   fx2 = LIMIT(0.0,fx2,(double)nfast);
   fy2 = LIMIT(0.0,fy2,(double)nslow);

   if (floor(fx1) < 0 || floor(fy1) < 0 || ceil(fx1) >= nfast || ceil(fy1) >= nslow) {
      return;
   }
   if (floor(fx2) < 0 || floor(fy2) < 0 || ceil(fx2) >= nfast || ceil(fy2) >= nslow) {
      return;
   }
   */

   /* If line hangs off frame, then interpolate back to the edge of the frame */
   /* Treat ends hanging off high side */
   if ((fx2 - fx1) != 0.0) {
      slope = (fy2 - fy1) / (fx2 - fx1);
      if (fx2 > (double)(nfast-1)) {
	 fx2 = nfast-1;
	 fy2 = fy1 + (fx2-fx1) * slope;
      }
      if (fx1 > (double)(nfast-1)) {
	 fx1 = nfast-1;
	 fy1 = fy2 - (fx2-fx1) * slope;
      }
      if (fy2 > (double)(nslow-1)) {
	 fy2 = nslow-1;
	 fx2 = fx1 + (fy2-fy1) / slope;
      }
      if (fy1 > (double)(nslow-1)) {
	 fy1 = nslow-1;
	 fx1 = fx2 - (fy2-fy1) / slope;
      }
      /* Treat ends hanging off low side */
      if (fx1 < (double)(0)) {
	 fx1 = 0;
	 fy1 = fy2 - (fx2-fx1) * slope;
      }
      if (fx2 < (double)(0)) {
	 fx2 = 0;
	 fy2 = fy1 + (fx2-fx1) * slope;
      }
      if (fy1 < (double)(0)) {
	 /* This should never happen if slope is zero */
	 if (slope == 0.0) cerr << boost::format("get_value_under_line: About to divide by ZERO (1): %f,%f,%f,%f\n") %  fx1 % fy1 % fx2 % fy2;
	 fy1 = 0;
	 fx1 = fx2 - (fy2-fy1) / slope;
      }
      if (fy2 < (double)(0)) {
	 if (slope == 0.0) cerr << boost::format("get_value_under_line: About to divide by ZERO (2): %f,%f,%f,%f\n") %  fx1 % fy1 % fx2 % fy2;
	 fy2 = 0;
	 fx2 = fx1 + (fy2-fy1) / slope;
      }
   }
   else {
      /* Slope is infinite - vertical line */
      if (fy2 > (double)(nslow-1)) {
	 fy2 = nslow-1;
	 fx2 = fx1; /* This must be true anyway */
      }
      if (fy1 > (double)(nslow-1)) {
	 fy1 = nslow-1;
	 fx1 = fx2; /* This must be true anyway */
      }
   }

   /* Now look at slope of a line perpendicular to the line we
      will plot - To use in integrating over a width */
   if (fwidth > 1.0) {
      /* Slope of perpendicular line */
      if ((fy2 - fy1) != 0.0) {
	 slope =  (fx1 - fx2)/(fy2 - fy1);
	 /* starting end of perpendicular line */
	 /* dx is always positive - distance moved along x per pixel moved along slope*/
	 dx = sqrt( 1.0 / (1.0 + slope*slope));
	 dy = slope * dx;
      }
      else {
	 /* Vertical */
	 dx = 0.0;
	 dy = 1.0;
      }
   }
   else {
      dx = 0.0;
      dy = 0.0;
   }

   /* if the box is entirely outside the frame, then return */
   if ((floor(fx1) < 0 && floor(fx2) < 0) || (floor(fx1) >= nfast && floor(fx2) >= nfast) ||
       (floor(fy1) < 0 && floor(fy2) < 0) || (floor(fy1) >= nslow && floor(fy2) >= nslow)) {
      cerr << boost::format("It still didn't work!!!!! %f,%f,%f,%f\n") %  fx1 % fy1 % fx2 % fy2;
      return;
   }


   //datap = data_in;
   //sdatap = (signed short *) datap;

    length = (fx2-fx1)*(fx2-fx1)+(fy2-fy1)*(fy2-fy1);
    length = sqrt(length);

    if (!*positionp) {
       *positionp = (double *) malloc((NPOINTS+1)*sizeof(double));
       if ((verbose > 3)) {
           cerr << boost::format("get_value...: allocated %d bytes for abscissa at %p\n") % ((NPOINTS+1)*sizeof(double)) % *positionp;
       }
    }
    if (!*valuep) {
       *valuep = (double *) malloc((NPOINTS+1)*sizeof(double));
       if ((verbose > 3)) {
          cerr << boost::format("get_value...: allocated %d bytes for ordinate at %i\n") % ((NPOINTS+1)*sizeof(double)) % *valuep;
       }
    }
    position = *positionp;
    value = *valuep;

    n = 0;
    for (i = 0; i < NPOINTS; i++) {
	position[n] =  (length/NPOINTS)*i;
	x = fx1 + i * (double)(fx2-fx1)/NPOINTS;
	y = fy1 + i * (double)(fy2-fy1)/NPOINTS;
/*******
	 switch (depth) {
	 case 1:
	    bptr = (unsigned char *) framep->data;
	    uvalue =  (int) bptr[x+(y*nfast)];
	    break;
	 case 2:
	    wptr = (unsigned short *) framep->data;
	    uvalue =  (int) wptr[x+(y*nfast)];
	    break;
	 case 4:
	    lptr = (unsigned long *) framep->data;
	    uvalue =  (int) lptr[x+(y*nfast)];
	    break;
	 default:
	    uvalue = 0;
	    break;
	 }
********/
#define RAW		0
#define INTERPOLATE	1
	 offset = NINT(x + NINT(y) * nfast);
	 switch(option) {
	 case INTERPOLATE:
	    x1 = (int)floor(x);
	    y1 = (int)floor(y);
	    x2 = x1 + 1;
	    y2 = y1 + 1;
	    offset1 = x1 + y1 *nfast; 
	    offset2 = offset1 + 1;
	    offset3 = offset2 + nfast;
	    offset4 = offset1 + nfast;
	    if (offset3 > size-1) {
	       if ((verbose > 3)) cerr << boost::format("get_value_under_line: ERROR x,y,offset3,size %f,%f,%d,%d\n") % x % y % offset3 % size;
		  value1 = 0;
		  value2 = 0;
		  value3 = 0;
		  value4 = 0;
	    }
	    else {
	       value1 = datap[offset1];
	       value2 = datap[offset2];
	       value3 = datap[offset3];
	       value4 = datap[offset4];
	    }

	    if (value1 != (PIXEL)saturated_value &&
	        value2 != (PIXEL)saturated_value &&
	        value3 != (PIXEL)saturated_value &&
	        value4 != (PIXEL)saturated_value ) {
	       t = (x-x1)/(x2-x1);
	       u = (y-y1)/(y2-y1);

	       value[n] = (1.0-t)*(1.0-u)*value1 +  t*(1.0-u)*value2 +
				      t*u*value3 + (1.0-t)*u*value4;
	        min_found = std::min<double>(min_found,value[n]);
	        max_found = std::max<double>(max_found,value[n]);
		n++;
	    }
	    break;
	 case RAW:
/*
	    if ((verbose > 3)) {
	      cerr << boost::format("x,y,offset %f,%f,%d\n") % x % y % offset;
	    }
*/
	    if (fwidth > 1.0) {
	       int localx, localy;
	       int localn;
	       double localvalue;
	       double startx, starty;
 
	       /* Loop over each point along the width and
		  sum the values, and calculate mean to use
		  as the value on the line */
	       localn = 0;
	       localvalue = 0.0;
	       startx = x - fwidth/2 * dx;
	       starty = y - fwidth/2 * dy;
	       for ( j = 0; j < fwidth; j++) {
		  localx = NINT(startx);
		  localy = NINT(starty);

		  /* Check that we are in frame */
		  if (localx >= 0 && localx < nfast &&
		      localy >= 0 && localy < nslow) {
		     offset = localx + (localy * nfast);
		     if (offset > size-1) {
			if ((verbose > 3)) cerr << boost::format("get_value_under_line: ERROR x,y,offset,size %f,%f,%d,%d\n") % x % y % offset % size;
			value1 =  0;
		     }
		     else {
			value1 =  datap[offset];
		     }
		     if (value1 != (PIXEL)saturated_value ) {
			localvalue +=  value1;
			localn++;
		     }
		  }

		  startx += dx;
		  starty += dy;
	       }
	       
	       if (localn) {
		  value[n] =  localvalue/localn;
		  min_found = std::min<double>(min_found,value[n]);
		  max_found = std::max<double>(max_found,value[n]);
		  n++;
	       }

	    }
	    else {
	       offset = NINT(x + NINT(y) * nfast);
	       if (offset > size-1) {
		  if ((verbose > 3)) cerr << boost::format("get_value_under_line: ERROR x,y,offset,size %f,%f,%d,%d\n") % x % y % offset % size;
		  value1 =  0;
	       }
	       else {
		  value1 =  datap[offset];
	       }
	       if (value1 != (PIXEL)saturated_value ) {
		  value[n] =  value1;
		  min_found = std::min<double>(min_found,value[n]);
		  max_found = std::max<double>(max_found,value[n]);
		  n++;
	       }
	    }
	    break;
	 default:
	    cerr << boost::format("get_value_under_line_from_frame: Invalid option!\n");
	    break;
	 }
    }
    *npts = n;
    *min = min_found;
    *max = max_found;
    return;
}

//! We don't ever want to calculate line stats with a data type of CorrectionTableEntry
template <>
void get_value_under_line_from_frame<CorrectionTableEntry_t>(CorrectionTableEntry_t *data_in, int nfast, int nslow, int depth, bool is_signed, int saturated_value, double fx1, double fy1, double fx2, double fy2, double fwidth, double **positionp, 				     double **valuep, int *npts, int option, double *min, double *max);

}

#endif
