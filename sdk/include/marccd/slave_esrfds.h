#ifndef slave_esrfds_h
#define slave_esrfds_h

#define ESRF_DSMAR_IDLE 0
#define ESRF_DSMAR_ACQUIRE 1
#define ESRF_DSMAR_READOUT 2
#define ESRF_DSMAR_CORRECT 3
#define ESRF_DSMAR_WRITING 4
#define ESRF_DSMAR_ABORTING 5
#define ESRF_DSMAR_UNAVAILABLE 6
#define ESRF_DSMAR_ERROR 7
#define ESRF_DSMAR_BUSY 8


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int esrf_dserver_init_child(void);
extern int esrf_dserver_init_com(const char *path, const char *nethost, const char *personal_name);
extern int esrf_dserver_close(void); 
extern int esrf_dserver_send(const char *command, ...);
extern int esrf_dserver_check(void); 
extern char *esrf_dserver_read(void); 

extern int esrf_dserver_is_size (int x, int y); 
extern int esrf_dserver_is_size_bkg (int x, int y);
extern int esrf_dserver_get_size (void); 
extern int esrf_dserver_get_size_bkg (void);
extern int esrf_dserver_set_size(int x, int y);

extern int esrf_dserver_is_bin (int x,int y); 
extern int esrf_dserver_is_temp (float temp); 
extern int esrf_dserver_is_press (float press);
extern int esrf_dserver_get_bin (void); 
extern int esrf_dserver_set_bin(int x,int y);

extern int esrf_dserver_is_stability (double target);
extern int esrf_dserver_is_frameshift (int shift);

extern int esrf_dserver_is_preset (double time);
extern int esrf_dserver_is_thumbnail1 (const char *type, int size_x, int size_y);
extern int esrf_dserver_is_thumbnail2 (const char *type, int size_x, int size_y);
extern int esrf_dserver_get_preset (void); 
extern int esrf_dserver_set_preset(double time);
extern int esrf_dserver_is_mode (int mode);
extern int esrf_dserver_is_state (int state);
extern int esrf_dserver_is_readout_mode (int mode);
extern int esrf_dserver_is_goniostatus_short (int goniostatus);
extern int esrf_dserver_is_goniostatus_format (char *format);
extern int esrf_dserver_is_goniostatus (char *status);
extern int esrf_dserver_get_state (void); 
extern int esrf_dserver_is_roi (int x0, int y0, int x1, int y1);

extern int esrf_dserver_start_acq (void);
extern int esrf_dserver_running(int really_check);
int remote_mode_running();
extern int esrf_dserver_abort (void);
extern int esrf_dserver_readout (int background_flag);
extern int esrf_dserver_writefile (const char *filename, int correct_flag);
extern int esrf_dserver_correct (void);
extern int esrf_dserver_check_in (void); 
extern int esrf_dserver_check_in_client (void);

#endif /* slave_esrfds_h */
