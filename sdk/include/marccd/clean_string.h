#ifndef clean_string_h
#define clean_string_h

#define MINANGLECHARS	7
#define MAXANGLECHARS	16

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern char *clean_expstr( char *string1, int stringlen, char *string2);

extern int str_to_exp (
#if NeedFunctionPrototypes
const char *command
#endif
);

extern char *exp_to_str(char *string, int stringlen, int seconds);

extern int str_to_msecs (
#if NeedFunctionPrototypes
const char *string
#endif
);

extern char *clean_degstr(char *string1, int stringlen, char *string2);

extern double str_to_deg (
#if NeedFunctionPrototypes
const char   *command
#endif
);


char *deg_to_str(char *string, int stringlen, double angle, int places, int punctuation);

extern char *strrepctrl(
#ifdef NeedFunctionPrototypes
char *s1,
const char *s2
#endif
);


extern char *strtoupper(
#ifdef NeedFunctionPrototypes
char *s1,
const char *s2
#endif
);

extern char *strtolower(
#ifdef NeedFunctionPrototypes
char *s1,
const char *s2
#endif
);

#endif /* clean_string_h */
