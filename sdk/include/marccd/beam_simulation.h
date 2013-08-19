#include "goniostat.h"

//beam simulation external functions
extern int simulation_fn_load(char *beam_simulation_filename);
extern void calculate_simulated_intensity(int *data_adc1, int *data_adc2, double s1h_current_val, double s1v_current_val, double s2h_current_val, 
      double s2v_current_val, double tth_current_val, double ttv_current_val, double trh_current_val, double trv_current_val);
extern int beam_sim_loaded_access(int option, int input);
/*extern int beam_sim_offset_access(int option, int input);
extern int beam_sim_sigma_access(int option, int input);*/

