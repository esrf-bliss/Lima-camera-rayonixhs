#ifndef goniostat_file_h
#define goniostat_file_h

#include "goniostat.h"

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern char *get_goniostat_filename(
#if NeedFunctionPrototypes
char *root_dir
#endif
);

extern int open_goniostat_file (
#if NeedFunctionPrototypes
void
#endif
);

extern int read_goniostat_file (
#if NeedFunctionPrototypes
GoniostatValues *theGVP
#endif
);

extern int write_goniostat_file (
#if NeedFunctionPrototypes
GoniostatValues theGV
#endif
);

extern int close_goniostat_file (
#if NeedFunctionPrototypes
void
#endif
);


#endif	/* goniostat_file_h */
