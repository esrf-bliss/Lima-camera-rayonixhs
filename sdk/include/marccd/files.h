#ifndef files_h
#define files_h

#include <stdio.h>

/*	format-independent file i/o documentation	

INTRODUCTION

 Many of the Xentronics programs (e.g. 'lookfile') are written to be
independent of the exact format of the files they access. These
programs require that the relevant files have descriptions as declared
below and initialized in init_files.h.

In the interests of standardization any future fixed record length
files should have their descriptions entered into init_files.h.
The program describe_file can be used for this purpose.

A file is a string of bytes which is considered here to consist of
records each of which contains a fixed number of items. In the following
routines 'record' is a pointer to the beginning of a record and
'position' is an integer giving the byte-offset of a particular item
from the beginning of a record. The global array FILES contains 
structures (named FILE_DESCRIPTIONS) which contain the names, data
types and positions of the items in each file. In addition, the 
structures contain information used to display  file
information on a terminal (i.e. which records to display in what order)
and the positions of commonly occuring record items ('generic items') such
as reflection x, y and z coordinates etc.

Two methods of reading and writing files are provided: Whole files
can be transferred into memory and efficiently processed. The program
'lookfile', which can sort files, uses this method. Alternatively, 
single record transfers can be used where memory usage is restricted
or only part of a file is required. The program 'test_files' demonstrates
both forms of i/o.

********************* DETECTOR FACE COORDINATES ************************

The C programs written for the detector by the people at Xentronics/Nicolet
and by P. Metcalf use a coordinate system with the origin at 0,0 at the
lower left hand corner of the detector as seen from 'behind' i.e. looking
into the x_ray source. This origin is mapped onto the video display in
the lower left hand corner.
	The fortran programs originally developed by R. Durbin on the
VAX (then modified by J Moulai and further developed and transferred
to the Cadmus by M. Blum) use a coordinate system with an origin
of 1,1 (i.e. 1-512 rather than 0-511) at the upper left hand corner
looking into the x-ray source, following film processing conventions.
Eventually it is hoped to convert the fortran programs to the c convention.

The conversion routines are called for_to_c and c_to_for.

**************************************************************************

Files are read into memory with

		char *read_file(filename, description)

which returns a pointer to the beginning of the file in memory.
The file is a byte string of length FILE_SIZE and records can
be accessed by character pointer manipulations.



READING INDIVIDUAL RECORDS FROM FILES

Files are opened using the routine

	FILE *open_file(file_descriptor_name, real_file_name, "r")

	(which returns a pointer to a unix FILE structure)

and records are accessed sequentially using

	read_record(FILE_ptr, record)

	(where FILE_ptr points to the opened FILE structure)



READING DATA FROM RECORD ITEMS

Data in records is accessed with the following macros (and function
equivalents in lower_case):

FLOAT_READ(record, position)	 reads a float item at record[position]
				 and returns float

LONG_READ(record, position)	 ... same for a long item
INT_READ(record, position)	 ... int 

item_read(record, position)	 reads any item and returns float

float_read(record, position)
long_read(record, position)
int_read(record, position)

The position of a particular item can be obtained using the routine

		position(item_name)

WRITING WHOLE FILES

		write_file(filename, buffer)

creates a file from the byte string pointed to by buffer.


WRITING RECORDS TO FILES

Files are opened using the routine

		FILE *open_file(file_descriptor_name, real_file_name, "w")

and records are written using

		write_record(FILE_ptr, record)



WRITING DATA TO RECORDS

The record is filled using routines similar to those described above

		FLOAT_WRITE(record, position, float data )
		LONG_WRITE(record, position, long data )
		INT_WRITE(record, position, int data )

		float_write(record, position, float data )
		long_write(record, position, long data )
		int_write(record, position, int data )

Files are closed by using the unix command fclose(FILE_ptr), where FILE_ptr is the 
file pointer returned by openfile().

FILE UTILITIES:

	char *display_file(record, file_pointer)

is an interactive display program which returns a pointer to the last
record selected

	display_record(record)

displays a single record

	display_all_names()

displays the names of all the record items

	display_names()

displays only those selected for display in FILE_DESCRIPTIONS

	change_display()

allows a new choice of displayed items

	extract_spot(&x, &y, filename, record)

uses the 'item_generic' option of FILE_DESCRIPTIONS to return the x
and y location and filename of a record containing a data spot.

Files included in FILE_DESCRIPTIONS can be selected with

	choose_description(filename)


*/

#define MAXFILES 20			/* max. number of files */
#define BLOCKSIZE 512			/* i/o blocksize */
#define MAXRECSIZE 200			/* maximum recordsize in bytes */
#define MAXITEMS 50			/* max. number of file record items */
#ifndef MAXKEYS				/* may be defined in sort.h         */
#define MAXKEYS 5			/* max. number of sort keys per file */
#endif

typedef struct 				/* FILE_DESCRIPTIONS */
	{
	char *name;			/* enviroment or real filename */
	int file_type;			/* 'F' for fortran file, 0 otherwise */
	int rec_length;			/* record length in bytes 
					(not used for fortran files)	*/
	char *item_name[MAXITEMS];
	int item_position[MAXITEMS]; 	/* byte positions of record items */
	int item_type[MAXITEMS];	/* i = int l = long f = float */
	int item_generic[MAXITEMS];	/* byte positions of x, y, frame, etc */
	int display_order[MAXITEMS];	/* order for the display of
			record items on terminal.  0 means no display */
	int sort_key[MAXKEYS * 4 + 1];	/* see sort.h */
	} FILE_DESCRIPTIONS;

 
#define ITEM_READ(record, position)  item_read((record), (position))
/*
#define FLOAT_READ(record, position)  *((float *) ((record) + (position)))
*/
#define FLOAT_READ(record, position)  *((float *) ((intptr_t)(record) + (intptr_t)(position)))
#define INT_READ(record, position)  *((int *) ((record) + (position)))
#define SHORT_READ(record, position)  *((short *) ((record) + (position)))
#define LONG_READ(record, position)  *((long *) ((record) + (position)))
#define UINT_READ(record, position)  *((unsigned int *) ((record) + (position)))
#define USHORT_READ(record, position)  *((unsigned short *) ((record) + (position)))
#define ULONG_READ(record, position)  *((unsigned long *) ((record) + (position)))

#define FLOAT_WRITE(record, position, value) *(float *) ((record) + (position)) = (float) value
#define INT_WRITE(record, position, value) *(int *) ((record) + (position)) = (int) value
#define SHORT_WRITE(record, position, value) *(short *) ((record) + (position)) = (short) value
#define LONG_WRITE(record, position, value) *(long *) ((record) + (position)) = (long) value
#define UINT_WRITE(record, position, value) *(unsigned int *) ((record) + (position)) = (unsigned int) value
#define USHORT_WRITE(record, position, value) *(unsigned short *) ((record) + (position)) = (unsigned short) value
#define ULONG_WRITE(record, position, value) *(unsigned long *) ((record) + (position)) = (unsigned long) value

/*
extern char *display_file(), *newfilename();
*/

/* These are the bits in the reflections file flag that can be used to filter */
#define NOBITS      0
#define GOODBIT     1
#define WIDEBIT     2
#define BRIBIT      3
#define MBRBIT      4
#define MOVEBIT     5
#define WEAKBIT     6
#define BDBKBIT     7
#define LCBKBIT     8
#define OVLAPBIT    9
#define OVLPBKBIT   10
#define EDGEBIT     11
#define MVGBIT      12
#define OLDBIT      13
#define ENDBIT      14
#define TAILBIT     15
#define BADPIXBIT   16

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern FILE *open_file(
#if NeedFunctionPrototypes
char *descriptor_name, 
char *real_name, 
char *type
#endif
);

extern char *read_file(
#if NeedFunctionPrototypes
char *filename,
char *description
#endif
);

extern long write_file(
#if NeedFunctionPrototypes
char *filename,
char *buffer
#endif
);


/*  Reading and writing from records */

extern void *get_record(
#if NeedFunctionPrototypes
int n,
void * buffer
#endif
);

extern float item_read(
#if NeedFunctionPrototypes
char *record,
int position
#endif
);

extern float float_read(
#if NeedFunctionPrototypes
char *record,
int position
#endif
);

extern long long_read(
#if NeedFunctionPrototypes
char *record,
int position
#endif
);

extern int int_read(
#if NeedFunctionPrototypes
char *record,
int position
#endif
);

extern int read_record(
#if NeedFunctionPrototypes
FILE *fd,
char *record
#endif
);


extern void item_write(
#if NeedFunctionPrototypes
char *record,
int position,
float value
#endif
);

extern void float_write(
#if NeedFunctionPrototypes
char *record,
int position,
float value
#endif
);

extern void long_write(
#if NeedFunctionPrototypes
char *record,
int position,
long value
#endif
);

extern void int_write(
#if NeedFunctionPrototypes
char *record,
int position,
int value
#endif
);

extern void write_record(
#if NeedFunctionPrototypes
FILE *fd,
char *record
#endif
);

extern int item(
#if NeedFunctionPrototypes
int     position
#endif
);

extern int position(
#if NeedFunctionPrototypes
char *item_name
#endif
);

extern int choose_file(
#if NeedFunctionPrototypes
char *filename,
char *description
#endif
);

extern int check_filename(
#if NeedFunctionPrototypes
char  *filename,
char  *description
#endif
);

extern int check_description(
#if NeedFunctionPrototypes
char  *description
#endif
);

extern int choose_description(
#if NeedFunctionPrototypes
char  *description
#endif
);

extern int streql (
#if NeedFunctionPrototypes
char * p1,
char * p2
#endif
);

extern void display_all_names(
#if NeedFunctionPrototypes
void
#endif
);

extern void display_all_types(
#if NeedFunctionPrototypes
void
#endif
);

extern void display_names(
#if NeedFunctionPrototypes
void
#endif
);

#endif /* files_h */

