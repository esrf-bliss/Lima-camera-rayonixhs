#ifndef detcom_h
#define detcom_h


#define DETCOM_FAILURE          -1
#define DETCOM_SUCCESS          0


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int init_detcom(
#if NeedFunctionPrototypes
char *hostname,
int port
#endif
);

extern int quit_detcom(
#if NeedFunctionPrototypes
void
#endif
);

extern int open_detcom(
#if NeedFunctionPrototypes
int channel
#endif
);

extern int open_detdat(
#if NeedFunctionPrototypes
void
#endif
);

extern int close_detdat(
#if NeedFunctionPrototypes
void
#endif
);

extern int close_detcom(
#if NeedFunctionPrototypes
int channel
#endif
);

extern int write_detcom(
#ifdef NeedFunctionPrototypes
char *format,
...
#endif
);

extern int read_detcom(
#if NeedFunctionPrototypes
void *buffer,
int size
#endif
);

extern long write_detdat(
#if NeedFunctionPrototypes
void *buffer,
long size
#endif
);

extern long read_detdat(
#if NeedFunctionPrototypes
void *buffer,
long size
#endif
);

#endif /* detcom_h */
