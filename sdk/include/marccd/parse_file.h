#ifndef parse_file_h
#define parse_file_h


/* possible types of connections */
#define LOCAL_UNIX_CONNECTION 1
#define TCPIP_CONNECTION 2
#define DECNET_CONNECTION 3
#define LOCAL_VMS_CONNECTION 4

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern void parse_filename(
#if NeedFunctionPrototypes
const char *filename,
int *net_type,
char *node,
char *path,
char *name
#endif
);


#endif /* parse_file_h */
