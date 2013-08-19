#ifndef tiffmmx_h
#define tiffmmx_h

#include "frame.h"
#include "image.h"
#include "tiff.h"

/* These 5 Tags were assigned to Macrometrix by Aldus Developer Desk in Fax dated 5/27/94 */
#define MMX_TIFFTAG_MMX_HEADER			34710
#define MMX_TIFFTAG_MMX_TIFFIFD			34711
#define MMX_TIFFTAG_UNASSIGNED03		34712
#define MMX_TIFFTAG_UNASSIGNED04		34713
#define MMX_TIFFTAG_UNASSIGNED05		34714

typedef struct _tiff_frame_header {
	char tiff_part[1024];
	frame_header native_part;
	} tiff_frame_header;

typedef struct _tiff_image_header {
	char tiff_part[1024];
	unsigned short colormap[1024];
	} tiff_image_header;


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern void fill_tiff_dir_entry(
#if NeedFunctionPrototypes
void *destinatation,
TIFFDirEntry *source
#endif
);

tiff_frame_header *create_tiff_frame_header(
#if NeedFunctionPrototypes
frame_header *headerp
#endif
);

tiff_image_header * create_tiff_image_header(
#if NeedFunctionPrototypes
image_header *headerp,
void *colortable
#endif
);


#endif /* tiffmmx_h */
