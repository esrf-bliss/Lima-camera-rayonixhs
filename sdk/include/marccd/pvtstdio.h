#ifndef pvtstdio_h
#define pvtstdio_h

#include <stdarg.h>
#include <stdio.h>

extern void *pvtstderr;
extern void *pvtstdin;
extern void *pvtstdout;


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

#if !defined (__linux) && !defined (__APPLE__)
extern int snprintf(char *string, int size, const char *format, ...);
extern int vsnprintf(char *string, int size, const char *format, va_list args);
#endif

FILE * stdouterr_log_open(const char *filename);

void setPrintToSpecial(
#if NeedFunctionPrototypes
int state
#endif
);

void setstdPrintSpecials(
#if NeedFunctionPrototypes
void *in,
void *out,
void *err,
void *log
#endif
);

extern int pvtfprintf(
#if NeedFunctionPrototypes
void *output,
const char *format,
...
#endif
);

extern int pvtprintf(
#if NeedFunctionPrototypes
const char *format,
...
#endif
);

extern void pvtperror(
#if NeedFunctionPrototypes
const char *string
#endif
);

extern void pvtperrorno(
#if NeedFunctionPrototypes
const char *string,
int error
#endif
);

#endif /* pvtstdio_h */
