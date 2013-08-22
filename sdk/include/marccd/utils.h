#ifndef utils_h
#define utils_h

#include <stdio.h>

#include "types.h"

#define NInArray(arr)           ((int) (sizeof(arr) / sizeof(arr[0])))

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern void swab2( void *in, void *out, int n);

extern void swab4( void *in, void *out, int n);

extern void mem2set(void *buffer, INT16 value, int n);

extern void mem4set(void *buffer, INT32 value, int n);

extern char *strncpy_null(char *dest, const char *src, size_t n);

extern void pause_milliseconds( int delay);

extern char *extract_numbered_filename_format(
#if NeedFunctionPrototypes
char *filename,
int base,
int *digits,
int *file_number,
char *filename_format
#endif
);

extern int get_next_filename (
#if NeedFunctionPrototypes
char *outname,
char *inname,
int next
#endif
);

extern void *bswap_array(
#if NeedFunctionPrototypes 
void  *data1,
void *data2,
int depth,
int size
#endif /* Need Function Prototypes */
);

extern void drop_into_background(
#if NeedFunctionPrototypes 
int doit
#endif
);

extern char *root_this_path(char *outputpath, const char *inputpath, const char *root_path);
extern char *reroot_this_path(char *output_path, const char *input_path, const char *root_path);

extern void construct_filename_template(const char *directory, const char *basename, char* template,
                            char field1_char, char **field1_ptr, char *field1_fmt, int *field1_size, int force_field1,
			    char field2_char, char **field2_ptr, char *field2_fmt, int *field2_size, int force_field2);

extern void construct_filename_from_template(char *filename, const char* template,
                            int field1_number, char *field1_ptr, char *field1_fmt, int field1_size,
			    int field2_number, char *field2_ptr, char *field2_fmt, int field2_size);

extern void construct_filename(char *filename, const char *directory, const char *basename,
                            char field1_char, char field2_char, int field1_number, int field2_number);

extern char *dir_name(char *fullpath, char *directory);

#define MEMORY_LEAK 0
#if MEMORY_LEAK
extern unsigned long memory_leak(const char *string);
#define memory_leak_off(x)
#else
#define memory_leak_off(x)
#define memory_leak(x)
#endif

extern unsigned long memory_used(void);
extern unsigned long memory_total(unsigned long *total, unsigned long *used, unsigned long *free);

extern char * char_sprintf_alloc(const char *format, ...);
extern int sprintf_alloc(char **string, const char *format, ...);
extern char *strncatf(char *string, size_t stringlen, const char *format, ...);

extern int find_index_by_name(char *name, char **name_list, int n_names, int case_sensitive);

extern int util_system(const char *command, int block, int *pid_return, int ignore_sigchld);
extern int util_fork(const char *command);
extern int util_poll_pid(int pid);
extern int util_kill(int pid);
extern char *popen_message(void **pipe_handle, int block, const char *command, char *message_buffer, int buflen);
extern int poll_popen_message(void *pipe_pointer, int multiline);
extern char *get_popen_message(void *pipe_pointer, int whole);
extern void kill_popen_message(void *pipe_pointer);
extern FILE *popen_command(void **pipe_handle, const char *command, char *message_buffer, int buflen);
extern int put_popen_command(void *pipe_pointer, void *buffer, int buflen);
extern int close_popen_command(void *pipe_pointer);
extern int poll_input_fd(int fd);
extern int get_rtc_date(char *buf);
extern char *safe_strdup(const char *s);
extern int launch_browser (const char *URL);
extern double check_writable_diskspace(const char *directory);
extern void print_memory_usage(FILE *out);
extern char *format_binary(char *buffer, int buflen, int value);

#endif /* utils_h */
