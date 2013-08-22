#ifndef time_subs_h
#define time_subs_h

#include <time.h>
#include <sys/time.h>

#define UNIXTIME	1
#define VAXTIME		2
#define FITSDATE	3
#define FITSTIME	4

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */



extern char *time_to_ascii(time_t bintim, char *ascii_time, size_t ascii_time_len);

extern char *tod_to_ascii(struct timeval tod, char *ascii_time, size_t ascii_time_len);

extern char *formattime( int type, char *asctim, char *fmttim);

extern char *timestamp(char *buffer, int bufsize);

extern char *stamp_this_time(struct timeval tod, char *buffer, int bufsiz);


extern double timediffd(struct timeval *start_time, struct timeval *end_time, struct timeval *delta_time);

extern unsigned long timediff(struct timeval *start_time, struct timeval *end_time, struct timeval *delta_time);

extern char *timediff_stamp(struct timeval *previous_time, struct timeval *current_time, char *buffer, int bufsize);

extern char *seconds_to_hhmmss(char *buffer, int bufsize, int seconds_in, int print_leading, int *hours, int *minutes, int *seconds);
extern char *seconds_to_hhmm(char *buffer, int bufsize, int seconds_in, int print_leading, int *hours, int *minutes);

//Returns current date like YYYYMMDD
int iso_date(void);

#endif /* time_subs_h */
