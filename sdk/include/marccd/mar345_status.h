#ifndef mar345_status_h
#define mar345_status_h

/***********************************************************************
 *
 * mar345: mar_status.h
 *
 * Copyright by:        Dr. Claudio Klein
 *                      X-ray Research GmbH, Hamburg
 *
 * Version:     1.1
 * Date:        03/03/1997
 *
 ***********************************************************************/

typedef struct {
		int	firmware;
		int	hw_status1;	
		int	hw_status2;	
		int	task_number;
		int	task_mode;
		int	task_active;
		int	task_error;
		int	scanmode;
		int	distance;
		int	phi;
		int	omega;
		int	chi;
		int	theta;
		int	intensity;
		int	complete;
		int	status_count;
		int	blocks_sent;
		int	blocks_scanned;
		int	xfer_counter;
		int	plate_locked;
} STATUS_INFO;

#endif /* mar345_status_h */
