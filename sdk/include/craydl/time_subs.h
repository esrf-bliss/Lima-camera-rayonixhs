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



extern char *time_to_ascii( time_t bintim, char *asctim);

extern char *formattime( int type, char *asctim, char *fmttim);

extern char *timestamp( void);

extern char *stamp_this_time(struct timeval tod, char *buffer, int bufsiz);


extern double timediffd(struct timeval *start_time, struct timeval *end_time, struct timeval *delta_time);

extern unsigned long timediff(struct timeval *start_time, struct timeval *end_time, struct timeval *delta_time);

extern char *timediff_stamp(struct timeval *previous_time, struct timeval *current_time);

#endif /* time_subs_h */
