#ifndef angle_subs_h
#define angle_subs_h

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int degrees(
#if NeedFunctionPrototypes
double radians
#endif
);

extern int minutes(
#if NeedFunctionPrototypes
double radians
#endif
);

extern int degree_part_of (
#if NeedFunctionPrototypes
double deg
#endif
);

extern int minute_part_of (
#if NeedFunctionPrototypes
double deg
#endif
);

extern char *deg_string (
#if NeedFunctionPrototypes
double deg,
int punctuation
#endif
);

extern int valid_angle(
#if NeedFunctionPrototypes
double *angle,
double min,
double max
#endif
);


#endif /* angle_subs_h */
