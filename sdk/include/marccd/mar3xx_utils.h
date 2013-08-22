#ifndef mar3xx_utils_h
#define mar3xx_utils_h

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int	InputType(char *string);
extern void	WrongType(int type, char *key, char *string);
extern float	GetResol(float radius, float distance, float wave);
extern void	RemoveBlanks(char *str);
extern void	mar3xx_swapshort(void *data, int n);
extern void    	mar3xx_swaplong(void *data, int n);
extern void	mar3xx_swapvms(float *data, int n );

#endif /* mar3xx_utils_h */
