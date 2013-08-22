#ifndef mardtb_net_h
#define mardtb_net_h

#include <sys/time.h>

#define DTB_NPORTS	4
#define DTB_COMM	0
#define DTB_STAT	1
#define DTB_DATA	2
#define DTB_MESS	3

extern void mardtb_init_net(const char *host, int port);

extern int mardtb_net_open(void);
extern int mardtb_net_close(void);
extern int mardtb_net_send(int channel, void *buffer, int size);
extern int mardtb_net_select(int channel, int mode, struct timeval timeout);
extern int mardtb_net_read(int channel, void *buffer, int size);
/*
extern int mardtb_net_data(int);
*/

#endif /* mardtb_net_h */
