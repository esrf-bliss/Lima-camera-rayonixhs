#ifndef mmx_math_h
#define mmx_math_h
/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern double local_random(
#if NeedFunctionPrototypes
int *iseed
#endif
);

extern double gaussdev(
#if NeedFunctionPrototypes
int *idum
#endif
);

extern void simple_ttest(double mean1, double var1, int n1, double mean2, double var2, int n2, double *t, double *prob);

extern double betai(double a, double b, double x);

extern double gammln(double x);

extern double cflentz(double a, double b, double x);

extern int linefit(double x[], double y[], int nstart, int nend,double *a,double *b,double *chi2);

#endif /* mmx_math_h */
