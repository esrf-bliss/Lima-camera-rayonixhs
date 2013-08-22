#ifndef network_h
#define network_h

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */



#define read_socket(a,b,c)	read(a,b,c)
#define write_socket(a,b,c)	write(a,b,c)
#define close_socket(s)		close(s)

extern int open_remote_buddha_daemon (
#if NeedFunctionPrototypes
char *hostname,
char *filename
#endif
);

extern int open_remote (
#if NeedFunctionPrototypes
char *hostname
#endif
);

extern void lost_remote (
#if NeedFunctionPrototypes
int   sig
#endif
);

extern int open_socket (
#if NeedFunctionPrototypes
char *hostname,
int  port
#endif
);

extern void showAddr(
#if NeedFunctionPrototypes
char           *str,
struct sockaddr_in *a
#endif
);

extern int open_decnet (
#if NeedFunctionPrototypes
char *hostname,
char *filename
#endif
);

#endif /* network_h */
