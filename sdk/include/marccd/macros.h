#ifndef macros_h
#define macros_h

#include <math.h>


#ifdef NINT
#undef NINT
#endif
#define NINT(x) ((int) floor((double) (x) + 0.5)) /* fortran nint */
#ifdef MAX
#undef MAX
#endif
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#ifdef MIN
#undef MIN
#endif
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#ifdef MOD
#undef MOD
#endif
#define	MOD(x, y) ((x) - (int)((x) / (y)) * (y))

#define MIN3(a,b,c)     (MIN(a,MIN(b,c)))
#define MAX3(a,b,c)     (MAX(a,MAX(b,c)))
#define LIMIT(x,y,z) MAX((x),MIN((y),(z)))

#ifndef PI		/* May be defined in <math.h> */
#define PI 		3.14159265358979
#endif
#ifndef PI2		/* May be defined in <math.h> */
#define PI2 		1.57079632679489
#endif
#define TWOPI 		6.28318530717958
#define DEG 		57.29577951308232
#define RAD 		0.01745329251994

#define  EV(x)		(((x) > 0.01) ? 12398.10000/(double)(x): 0.0)
#define  ANGSTROM(x)	(((x) > 0.01) ? 12398.10000/(double)(x) : 0.0)

#define ABSOLUTE_ZERO_CELSIUS	(-273.15)

/* Ka is intensity weighted average or Ka1 and Ka2 */
/* from www-structure.llnl.gov/Xray/comp/compserv */
#define  WAVELENGTH_Cu_Ka	1.541838
#define  WAVELENGTH_Cu_Ka1	1.540562
#define  WAVELENGTH_Cu_Ka2	1.544390
#define  WAVELENGTH_Cu_Kb	1.392218

#define  WAVELENGTH_Mo_Ka	0.710730
#define  WAVELENGTH_Mo_Ka1	0.709300
#define  WAVELENGTH_Mo_Ka2	0.713590
#define  WAVELENGTH_No_Kb	0.632288




#define MILLISECONDS	1000

#define RADS(x)      ((x) * RAD)
#define DEGS(x)      ((x) * DEG)

/* Trigonometric functions  (in degrees) */
#ifndef sind
#define sind(x)      sin((double)RADS(x))
#define cosd(x)      cos((double)RADS(x))
#define tand(x)      tan((double)RADS(x))
#define asind(x)     DEGS(asin((double)(x)))
#define acosd(x)     DEGS(acos((double)(x)))
#define atand(x)     DEGS(atan((double)(x)))
#define atan2d(y,x)  DEGS(atan2((double)(y),(double)(x)))
#endif

#ifndef sqr
#define sqr(x)       pow(fabs((double)(x)), 2.0) /* VMS BUG - requires 
							   absolute value */
#endif

/* macros for normalizing angles*/

/* Finds stop angle closest <<around the circle>> to start angle */
#define CLOSEST(start,stop) \
( (((stop)-(start)) < -180.0) ? ((stop)+360.0):\
 ((((stop)-(start)) >  180.0) ? ((stop)-360.0):(stop)) )
/* Normalize to -360.0 < 360.0 */
#define NORMAL360(angle)  fmod (((double)angle), 360.0)
/* Normalize to 0-360.0 */
#define NORMALP360(angle)  (fmod ((fmod (((double)angle), 360.0) + 360.0), 360.0))
/* Normalize to +/- 180.0 */
#define NORMAL180(angle) (fmod ((fmod (((double)angle), 360.0) + 540.0), 360.0) - 180.0)
/* Normalize to -270 -> +90 */
#define FORBID90(angle)  (fmod ((fmod (((double)angle), 360.0) + 630.0), 360.0) - 270.0)


#endif /* macros_h */
