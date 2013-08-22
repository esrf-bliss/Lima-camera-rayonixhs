#ifndef profile_stack_h
#define profile_stack_h

#include "frame.h"

#define MAX_PROFILE_STACK_FRAMES	512

#define FIRST_OF_STACK	0
#define CENTER_OF_STACK	1
#define LAST_OF_STACK	2

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int set_default_frame_filename(
#if NeedFunctionPrototypes
char *name,
int base,
int position,
int stacksize
#endif
);

char * get_default_frame_filenameformat(
#if NeedFunctionPrototypes
char *buffer,
int framenumber
#endif
);


extern data_frame **get_profile_stack(
#if NeedFunctionPrototypes
void
#endif
);

extern data_frame **fill_profile_stack(
#if NeedFunctionPrototypes
void
#endif
);

extern data_frame **fill_profile_stack_worker(
#if NeedFunctionPrototypes
int initialize
#endif
);

extern data_frame *get_next_frame_in_stack(
#if NeedFunctionPrototypes
int direction
#endif
);

extern data_frame **empty_profile_stack(
#if NeedFunctionPrototypes
void
#endif
);

extern int n_in_profile_stack(
#if NeedFunctionPrototypes
void
#endif
);

extern int setup_stack_from_frame(const char *search_path, const char *input_filename, data_frame *framep, int position, int stack_size, char *error_buffer, int error_buffer_size, char *progress_buffer, int progress_buffer_size);

extern int simple_setup_stack_from_frame(data_frame *framep, int position, int stack_size);

#endif /* profile_stack_h */
