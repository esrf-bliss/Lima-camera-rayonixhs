#ifndef image_h
#define image_h

typedef enum {
      IMAGEFILE_TYPE_PGM,
      IMAGEFILE_TYPE_RAW,
      IMAGEFILE_TYPE_TIFF,
      IMAGEFILE_TYPE_JPEG,
      IMAGEFILE_TYPE_GIF,
      IMAGEFILE_TYPE_PNG,
      IMAGEFILE_TYPE_EPS,
      IMAGEFILE_TYPE_MIFF,
      IMAGEFILE_TYPE_HTML,
      IMAGEFILE_TYPE_FITS
} ThumbnailType;


typedef struct _image_header {
 	unsigned long nfast;		/* number of pixels in one line */
 	unsigned long nslow;		/* number of lines in image     */
 	unsigned long bit_depth;	/* number of bits per pixel    */
 	void     *source_frame;	        /* pointer to data frame used to create this image */
	long     render_transformation;	/* transformation type used when creating image */
	long     data_xorigin;		/* x origin of image in data coordinates */
	long     data_yorigin;		/* y origin of image in data coordinates */
	long     image_xorigin;		/* x origin of data  in image coordinates */
	long     image_yorigin;		/* y origin of data  in image coordinates */
	double   data_pix_per_image_pix;/* scale */
 	void     *graphics_parent;	/* pointer to parent structure ,which also contains a
					   pointer to data, required by whatever graphics
					   system is used */
	} image_header;

typedef struct _data_image {
	image_header *header;
	int  data_size;
	void *data;
	} data_image;

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


/* Initialize a default image */
extern int init_image (
#if NeedFunctionPrototypes
int depth
#endif
);

/* Return the default image */
extern data_image *default_image (
#if NeedFunctionPrototypes
void
#endif
);

/* Return the current image */
extern data_image *current_image (
#if NeedFunctionPrototypes
void
#endif
);

/* allocate and initialize a data image */
extern data_image *create_new_image (
#if NeedFunctionPrototypes
int width,
int height,
int depth
#endif
);

/* deallocate a data image structure */
extern int destroy_data_image (
#if NeedFunctionPrototypes
data_image *imagep
#endif
);

/* allocate and initialize image header */
extern int create_image_header (
#if NeedFunctionPrototypes
image_header **headerpp,
int width,
int height,
int depth
#endif
);

/* deallocate an image header structure */
extern int destroy_image_header (
#if NeedFunctionPrototypes
image_header *headerp
#endif
);

extern int get_image_size(
#if NeedFunctionPrototypes
data_image *imagep,
int *width,
int *height,
int *depth
#endif
);

extern int set_image_size(
#if NeedFunctionPrototypes
data_image *imagep,
int width,
int height,
int depth
#endif
);

/* resize data image */
int resize_image(
#if NeedFunctionPrototypes
data_image     *imagep,
int             size
#endif
);

#endif /* image_h */
