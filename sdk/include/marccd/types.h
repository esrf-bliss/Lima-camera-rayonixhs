#ifndef types_h
#define types_h

#include <stdint.h>

#if defined(__alpha) 
#define CHAR8	char
#define INT8	signed char
#define UINT8	unsigned char
#define INT16	signed short
#define UINT16	unsigned short
#define INT32	signed int
#define UINT32	unsigned int
#define INT64	signed long
#define UINT64	unsigned long
#define FLOAT32	float
#define FLOAT64	double
/*
#elif defined(__hpux)
#define CHAR8	char
#define INT8	char
#define UINT8	unsigned char
#define INT16	short
#define UINT16	unsigned short
#define INT32	long
#define UINT32	unsigned long
#define FLOAT32	float
#define FLOAT64	double
*/
#elif defined(__sgi)
#if defined(_MIPS_SIM_ABI64)
#define CHAR8	char
#define INT8	signed char
#define UINT8	unsigned char
#define INT16	signed short
#define UINT16	unsigned short
#define INT32	signed int
#define UINT32	unsigned int
#define INT64	long long
#define UINT64	unsigned long long
#define FLOAT32	float
#define FLOAT64	double
#else //__sgi but not _MIPS_SIM_ABI64
#define CHAR8	char
#define INT8	signed char
#define UINT8	unsigned char
#define INT16	signed short
#define UINT16	unsigned short
#define INT32	signed long
#define UINT32	unsigned long
#define INT64	long long
#define UINT64	unsigned long long
#define FLOAT32	float
#define FLOAT64	double
#endif //_MIPS_SIM_ABI64
#else  //not __alpha or __sgi

#define CHAR8	char
#define INT8	int8_t
#define UINT8	uint8_t
#define INT16	int16_t
#define UINT16	uint16_t
#define INT32	int32_t
#define UINT32	uint32_t
#define INT64	int64_t
#define UINT64	uint64_t
#define FLOAT32	float
#define FLOAT64	double


#define MAX_INT8	127
#define MIN_INT8	-128
#define MAX_UINT8	255
#define MIN_UINT8	0

#if 0
#define CHAR8	char
#define INT8	signed char
#define UINT8	unsigned char
#define INT16	signed short
#define UINT16	unsigned short
#define INT32	signed long
#define INT64	long long
#define UINT64	unsigned long long
#define UINT32	unsigned long
#define FLOAT32	float
#define FLOAT64	double

#define MAX_INT8	127
#define MIN_INT8	-128
#define MAX_UINT8	255
#define MIN_UINT8	0
#endif

#endif //__alpha __sgi etc.


#if 0
// declaration of this union will catch size errors.
// Put this somewhere in a source file
static union
{
   char   INT8_incorrect[(sizeof(  INT8) == 1) ? 1 : -1];
   char  UINT8_incorrect[(sizeof( UINT8) == 1) ? 1 : -1];
   char  INT16_incorrect[(sizeof( INT16) == 2) ? 1 : -1];
   char UINT16_incorrect[(sizeof(UINT16) == 2) ? 1 : -1];
   char  INT32_incorrect[(sizeof( INT32) == 4) ? 1 : -1];
   char UINT32_incorrect[(sizeof(UINT32) == 4) ? 1 : -1];
   char  INT64_incorrect[(sizeof( INT64) == 8) ? 1 : -1];
   char UINT64_incorrect[(sizeof(UINT64) == 8) ? 1 : -1];
   char FLOAT32_incorrect[(sizeof(FLOAT32) == 4) ? 1 : -1];
   char FLOAT64_incorrect[(sizeof(FLOAT64) == 8) ? 1 : -1];
};
#endif


#endif /* types_h */
