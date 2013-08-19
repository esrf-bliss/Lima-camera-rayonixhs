#ifndef beam_alignment_h
#define beam_alignment_h

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include "goniostat.h"

#define SLITS_CURRENT	2
#define SLITS_DEFAULT	1

#define ACCESS_VALUE_INIT	0
#define ACCESS_VALUE_ASK	1
#define ACCESS_VALUE_CHANGE	2
#define ACCESS_VALUE_INCR	3
#define ACCESS_VALUE_DECR	4
#define ACCESS_VALUE_TOGGLE	5

#define DATASET_ALIGNMENT_STATUS_FAIL   -1  //means most recent alignment failed (i.e. no beam in 2nd chamber after optimize)
#define DATASET_ALIGNMENT_STATUS_NOOPTI 0   //means no optimize has been done since program start
#define DATASET_ALIGNMENT_STATUS_BUSY	1   //means alignment is being done
#define DATASET_ALIGNMENT_STATUS_OPTI	2   //means most recent alignment finished with successful optimize

#define BEAM_ALIGNMENT_STATUS_BUSY 		(1)
#define BEAM_ALIGNMENT_STATUS_NOTALIGNED 	(1 << 1)
#define BEAM_ALIGNMENT_STATUS_ERROR 		(1 << 2)
#define BEAM_ALIGNMENT_STATUS_RESERVED		(1 << 3)

//extern Widget create_beam_alignment_window(Widget parent_w, const char *name, Dimension wdt, Dimension hgt);
extern Widget create_beam_alignment_window(Widget parent_w, const char *name);
extern void update_beam_alignment_window(int intensities[2]);
extern int dataset_alignment_status_access(int option, int input);
extern int dataset_alignment(int slit_setting_flag, int offset_measure_flag, int do_find_flag, int do_full_flag);
extern void stop_alignment(int dataset_flag);
int autoalign_done(void);
//extern int beam_alignment_start(long int procedure_list);
#if 0
extern void beam_sim_replace(
      double data_position, 
      int beam_sim_scan_axs, 
      axis_parameters *s1hp_val, 
      axis_parameters *s1vp_val, 
      axis_parameters *s2hp_val, 
      axis_parameters *s2vp_val, 
      axis_parameters *tthp_val,
      axis_parameters *ttvp_val,
      axis_parameters *trhp_val,
      axis_parameters *trvp_val,
      int *adc1_data,
      int *adc2_data);
//extern int calculate_simulated_intensity(int true_int_val, int ion_chamber_no);
extern void calculate_simulated_intensity(
      int *data_adc1,
      int *data_adc2,
      double s1h_cur, 
      double s1v_cur, 
      double s2h_cur, 
      double s2v_cur, 
      double tth_cur,
      double ttv_cur,
      double trh_cur,
      double trv_cur);
#endif

#endif /* beam_alignment_h */
