#ifndef marccd_h
#define marccd_h

#include "frame.h"

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */


extern void update_displayed_statistics(data_frame *framep);

extern void quit_marccd(int sig, int force);

#endif /* marccd_h */
