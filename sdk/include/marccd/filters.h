#ifndef filters_h
#define filters_h

typedef struct RecordFilter_ {
   char *name;								/* functions which select records ('filters') */
   /* are called as follows: filter_hkl(record, command, positions, params) */
   int (*function)( char *record, char *command, int *positions, void *params);
   char command[80];  /* should reflect filter action , an empty string causes the filter function to go interactive */
   int positions[4];							/* positions of record items used by filter */
   char params[16];							/* parameters used by filter */
   struct RecordFilter_ *next;
} RecordFilter;

/* list of available filter functions */
#define NFILTERS  8


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern RecordFilter *create_filter_list(
#if NeedFunctionPrototypes
void
#endif
) ;

extern RecordFilter *add_filter(
#if NeedFunctionPrototypes
RecordFilter *filter_list,
int type
#endif
);


extern int dofilter(
#if NeedFunctionPrototypes
char *record,
RecordFilter *filter_list
#endif
);

extern void choose_filter(
#if NeedFunctionPrototypes
RecordFilter *filter_list
#endif
);

extern void set_filter(
#if NeedFunctionPrototypes
RecordFilter *filter,
int *positions,
void *params
#endif
);


extern int filter_hkl(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);

extern int filter_upper(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);

extern int filter_lower(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);

extern int filter_difference(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);

extern int hklsel_(
#if NeedFunctionPrototypes
char *command,
long *hklid
#endif
);


extern int filter_ratio(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);

extern int filter_bit_mask(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);

extern int coord_change(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);

extern int abs_value(
#if NeedFunctionPrototypes
char *record,
char *command,
int *positions,
void *params
#endif
);


#endif /* filters_h */
