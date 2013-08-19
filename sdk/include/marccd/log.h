#ifndef log_h
#define log_h

#define TIME_ENTRY	1
#define TIME_EXIT	2
#define TIME_ELAPSED	3


extern FILE * dataset_log_open(
#if NeedFunctionPrototypes
const char *filename
#endif
);

extern void dataset_log_close(
#if NeedFunctionPrototypes
void
#endif
);

extern int dataset_log_entry(
#if NeedFunctionPrototypes
int printit,
const char *format,
...
#endif
);

extern FILE* spy_log_open(const char *directory, const char *filename);
extern void spy_log_close(void);
extern int spy_log_entry(int printit, const char *format, ...);

extern void log_time(FILE *file, const char *label, int type, struct timeval *entry_time, struct timeval *exit_time);


#endif /* log_h */
