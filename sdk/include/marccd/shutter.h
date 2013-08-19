#ifndef shutter_h
#define shutter_h

#define SHUTTER_ON_GONIOSTAT_CONTROLLER		1
#define SHUTTER_ON_DETECTOR_CONTROLLER		2
#define SHUTTER_ON_INDEPENDENT_CONTROLLER	3

#define SHUTTER_OPTION_HAS_MANUAL_MODE	1

typedef enum {
   ShutterOnGoniostatController,
   ShutterOnDetectorController,
   ShutterOnIndependentController
} ShutterDeviceType;

typedef enum {
   ShutterModeManual,
   ShutterModeAutomatic
} ShutterModeType;

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int set_shutter_device(int shutter_device);
extern int get_shutter_device(void);
extern int open_shutter(void);
extern int close_shutter(void);
extern int set_mode_shutter(int mode);
extern int get_mode_shutter(int *mode);
extern int set_option_shutter(int option, int *argument);
extern int get_option_shutter(int option, int *argument);
extern int query_shutter(int *open, int *commanded_open);

#endif /* shutter_h */
