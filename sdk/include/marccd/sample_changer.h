#ifndef sample_changer_h
#define sample_changer_h


typedef enum {
   SampleChangerNone,
   SampleChangerOnGoniostatController,
   SampleChangerOnDetectorController,
   SampleChangerOnIndependentController
} SampleChangerDeviceType;

typedef enum {
   SC_ERROR_STATUS,
   SC_OPERATION_MODE,
   SC_AT_OPERATING_TEMPERATURE,
   SC_SAMPLE_CODE_RECENT,
   SC_SAMPLE_CODE_MOUNTED,
   SC_CURRENT_SAMPLE_MOUNTED,
   SC_SAMPLE_CODE_STATUS,
   SC_SAMPLE_ANGLE,
   SC_SAMPLE_MOUNTED_FLAG,
   SC_CURRENT_CAROUSEL_POSITION,
   SC_MAXIMUM_SAMPLE_NUMBER,
   SC_CURRENT_CAROUSEL_MOUNTED,
   SC_MAXIMUM_CAROUSEL_NUMBER
} SampleChangerOptions;

#define SC_ERROR_UNKNOWN	-1
#define SC_ERROR_NONE		0
#define SC_ERROR_NOCAP		1
#define SC_ERROR_NOVIAL		2
#define SC_ERROR_NOEMPTY	3
#define SC_ERROR_NOPINLENGTH	4
#define SC_ERROR_CAP		5
#define SC_ERROR_VIAL		6
#define SC_ERROR_EMPTY		7

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

#define SC_IS_AUTOMATIC_MODE (get_manual_mode_sample_changer() ? 0 : 1)  //Justin - Mar, 2008 - Extended Command Set - Phase2

extern int sample_changer_present(void);
extern int sample_changer_easymount_present(void);
extern int sample_changer_ready(void);
extern int sample_changer_busy(void);
extern int sample_changer_automatic_mode(void);
extern void abort_sample_changer(void);
extern int sample_changer_check_range(void);
extern int set_sample_changer_device(int sample_changer_device);
extern int get_sample_changer_device(void);
extern int initialize_sample_changer(int init_mode);
extern int sample_changer_test_load(int sample_number, int *old_sample_number);
extern int sample_changer_load(int sample_number);
extern int sample_changer_change_carousel(int unload_to, int load_from, char *command);
extern void sample_changer_abort_carousel_change(void);
extern int sample_changer_poll_carousel_change(void);
extern int get_manual_mode_sample_changer(void);
extern int set_option_sample_changer(int option, void *argument);
extern int get_option_sample_changer(int option, void *argument);
extern int sample_changer_error_status(int *retriable, int *unload_error, char *error_buffer, int buflen);
//Begin Justin - Mar, 2008 - Extended Command Set - Phase2 - Prototypes.....
extern void set_auto_and_vial(int auto_on, int vial);
extern int load_or_change_sample(int new_sample);
extern void unload_sample(int cur_samp_mntd);
extern void anneal_sample(double anneal_time);
extern void give_vial(int vial_to_give);
extern void init_goniostat_wrapper(void);
extern void read_vial_barcode(int vial_to_read);
extern void take_vial(void);
//.....End Justin - Mar, 2008 - Extended Command Set - Phase2 - Prototypes

extern void sample_changer_easymount_sample(void);
extern int sample_changer_vial_given(int *given_vial_number);
extern int sample_changer_read_param_values(int nparams, int *params, int *values);

#endif /* sample_changer_h */
