#ifndef marnet_h
#define marnet_h

extern void init_marnet(const char *host, int port);

extern int net_open(void);
extern int net_close(void);
extern int net_data(int);
extern int net_send(char *);
extern int net_select(int);


#endif /* marnet_h */
