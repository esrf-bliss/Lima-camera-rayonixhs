#ifndef goniostat_remote_server_h
#define goniostat_remote_server_h

#define ESRF_DSMAR_IDLE 0
#define ESRF_DSMAR_ACQUIRE 1
#define ESRF_DSMAR_READOUT 2
#define ESRF_DSMAR_CORRECT 3
#define ESRF_DSMAR_WRITING 4
#define ESRF_DSMAR_ABORTING 5
#define ESRF_DSMAR_UNAVAILABLE 6
#define ESRF_DSMAR_ERROR 7
#define ESRF_DSMAR_BUSY 8

struct goniostat_remote_vars {
  int x;
  int y;
  int xbin;
  int ybin;
  double preset;
  int state;
};


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int goniostat_remote_init_child(void);
extern int goniostat_remote_init_com(const char *path, const char *nethost, const char *personal_name, const char *logfile);
extern int goniostat_remote_close(void); 
extern int goniostat_remote_send(); 
extern int goniostat_remote_check(void); 
extern char *goniostat_remote_read(void); 

extern int goniostat_remote_is_size (int x, int y); 
extern int goniostat_remote_get_size (void); 
extern int goniostat_remote_set_size(int x, int y);

extern int goniostat_remote_is_bin (int x,int y); 
extern int goniostat_remote_get_bin (void); 
extern int goniostat_remote_set_bin(int x,int y);

extern int goniostat_remote_is_preset (double time);
extern int goniostat_remote_get_preset (void); 
extern int goniostat_remote_set_preset(double time);
extern int goniostat_remote_is_state (int state);
extern int goniostat_remote_get_state (void); 

extern int goniostat_remote_start_acq (void);
extern int goniostat_remote_running(void);
extern int goniostat_remote_abort (void);
extern int goniostat_remote_readout (int background_flag);
extern int goniostat_remote_writefile (const char *filename, int correct_flag);
extern int goniostat_remote_correct (void);
extern int goniostat_remote_check_in (void); 
extern int goniostat_remote_check_in_client (void);

#endif /* goniostat_remote_server_h */
