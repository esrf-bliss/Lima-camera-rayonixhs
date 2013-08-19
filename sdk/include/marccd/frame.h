#ifndef frame_h
#define frame_h

#include "types.h"
#include "image.h"


/* This has to go somewhere else eventually */ 

typedef struct spot_type {
	double          x, y, z;		/* x, y, z */
	double          vx, vy, vz;		/* x, y, z variances */
	unsigned long   ns, nb;		/* number of pixels in sum and background */
	double          sum, vs;		/* sum, variance */
	double          back, vb;		/* background, variance */
	long            minpix, maxpix;	/* minimum and maximum pixel value */
	double          fh, fk, fl;		/* real crystallographic index */
	long            h, k, l;		/* integer crystallographic index */
} spot_struct;


typedef enum _ImageSampling {
	BY_SUBSAMPLING, BY_AVERAGING
	} ImageSampling;

/* frame.h Format for frame header */

#define MAXIMAGES 9
#define MAXSUBIMAGES 4096
#define MAXFRAMEDIMENSION	8192
#define MAXSUPPORTEDBITS 20


/* Use locally defined types because this header get written to a file to 
   be shared among different machines
*/
typedef struct pix_overflow_type {               /*  overflow table entry */
	UINT32        offset;
	UINT32        value;
	} pix_overflow;

typedef struct frame_header_type {
	/* File/header format parameters (256 bytes) */
	UINT32        header_type;	/* flag for header type  (can be used as magic number) */
	char 		  header_name[16];		/* header name (MARCCD) */
	UINT32        header_major_version;	/* header_major_version (n.) */
	UINT32        header_minor_version; 	/* header_minor_version (.n) */
	UINT32        header_byte_order;/* BIG_ENDIAN (Motorola,MIPS); LITTLE_ENDIAN (DEC, Intel) */
	UINT32        data_byte_order;	/* BIG_ENDIAN (Motorola,MIPS); LITTLE_ENDIAN (DEC, Intel) */
	UINT32        header_size;	/* in bytes			*/
	UINT32        frame_type;	/* flag for frame type */
	INT32         magic_number;	/* to be used as a flag - usually to indicate new file */
	UINT32        compression_type;	/* type of image compression    */
	UINT32        compression1;	/* compression parameter 1 */
	UINT32        compression2;	/* compression parameter 2 */
	UINT32        compression3;	/* compression parameter 3 */
	UINT32        compression4;	/* compression parameter 4 */
	UINT32        compression5;	/* compression parameter 4 */
	UINT32        compression6;	/* compression parameter 4 */
	UINT32        nheaders;	        /* total number of headers 	*/
 	UINT32        nfast;		/* number of pixels in one line */
 	UINT32        nslow;		/* number of lines in image     */
 	UINT32        depth;		/* number of bytes per pixel    */
 	UINT32        record_length;	/* number of pixels between succesive rows */
 	UINT32        signif_bits;	/* true depth of data, in bits  */
 	UINT32        data_type;	/* (signed,unsigned,float...) */
 	UINT32        saturated_value;	/* value marks pixel as saturated */
	UINT32        sequence;	        /* TRUE or FALSE */
	UINT32        nimages;	        /* total number of images - size of each is nfast*(nslow/nimages) */
 	UINT32        origin;		/* corner of origin 		*/
 	UINT32        orientation;	/* direction of fast axis 	*/
    UINT32        view_direction;   /* direction to view frame      */
	UINT32        overflow_location;/* FOLLOWING_HEADER, FOLLOWING_DATA */
	UINT32        over_8_bits;	/* # of pixels with counts > 255 */
	UINT32        over_16_bits;	/* # of pixels with count > 65535 */
	UINT32        multiplexed;	/* multiplex flag */
	UINT32        nfastimages;	/* # of images in fast direction */
	UINT32        nslowimages;	/* # of images in slow direction */
	UINT32        darkcurrent_applied; /* flags correction has been applied - hold magic number ? */
	UINT32        bias_applied;	  /* flags correction has been applied - hold magic number ? */
	UINT32        flatfield_applied;  /* flags correction has been applied - hold magic number ? */
	UINT32        distortion_applied; /* flags correction has been applied - hold magic number ? */
	UINT32        original_header_type;	/* Header/frame type from file that frame is read from */
	UINT32        file_saved;         /* Flag that file has been saved, should be zeroed if modified */
	UINT32        n_valid_pixels;     /* Number of pixels holding valid data - first N pixels */
	UINT32        defectmap_applied; /* flags correction has been applied - hold magic number ? */
	UINT32        subimage_nfast; 	    /* when divided into subimages (eg. frameshifted) */
	UINT32        subimage_nslow;       /* when divided into subimages (eg. frameshifted) */
	UINT32        subimage_origin_fast; /* when divided into subimages (eg. frameshifted) */
	UINT32        subimage_origin_slow; /* when divided into subimages (eg. frameshifted) */
	UINT32        readout_pattern;      /* BIT Code - 1 = A, 2 = B, 4 = C, 8 = D */
 	UINT32        saturation_level;	    /* at this value and above, data are not reliable */
 	UINT32        orientation_code;	    /* Describes how this frame needs to be rotated to make it "right" */
 	UINT32        frameshift_multiplexed;  /* frameshift multiplex flag */
 	UINT32        prescan_nfast;		/* Number of non-image pixels preceeding imaging pixels - fast direction - also used with CTBL for ROI.A.x */
 	UINT32        prescan_nslow;		/* Number of non-image pixels preceeding imaging pixels - slow direction - also used with CTBL for ROI.A.y */
 	UINT32        postscan_nfast;		/* Number of non-image pixels followng imaging pixels - fast direction - also used with CTBL for ROI.B.x */
 	UINT32        postscan_nslow;		/* Number of non-image pixels followng imaging pixels - slow direction - also used with CTBL for ROI.B.y */
 	UINT32        prepost_trimmed;		/* trimmed==1 means pre and post scan pixels have been removed */
	UINT32		  orig_frameformat_serial_length; //Used for CTBL with region-of-interest to store full CTBL serial length
	UINT32		  orig_frameformat_parallel_length; //Used for CTBL with region-of-interest to store full CTBL parallel length
 	char reserve1[12];

	/* Data statistics (128) */
	UINT32        total_counts[2];	/* 64 bit integer range = 1.85E19*/
	UINT32        special_counts1[2];
	UINT32        special_counts2[2];
	UINT32        min;
	UINT32        max;
	UINT32        mean;			/* mean * 1000 */
	UINT32        rms;			/* rms * 1000 */
	UINT32        n_zeros;			/* number of pixels with 0 value  - not included in stats in unsigned data */
	UINT32        n_saturated;		/* number of pixels with saturated value - not included in stats */
	UINT32        stats_uptodate;		/* Flag that stats OK - ie data not changed since last calculation */
    UINT32        pixel_noise[MAXIMAGES];		/* 1000*base noise value (ADUs) */
	char reserve2[(32-13-MAXIMAGES)*sizeof(INT32)];

#if 0
	/* More statistics (256) */
	UINT16 percentile[128];
#else
	/* Sample Changer info */
	char          barcode[16];
	UINT32        barcode_angle;
	UINT32        barcode_status;
	/* Pad to 256 bytes */
	char reserve2a[(64-6)*sizeof(INT32)];
#endif


	/* Goniostat parameters (128 bytes) */
        INT32 xtal_to_detector;		/* 1000*distance in millimeters */
        INT32 beam_x;			/* 1000*x beam position (pixels) */
        INT32 beam_y;			/* 1000*y beam position (pixels) */
        INT32 integration_time;		/* integration time in milliseconds */
        INT32 exposure_time;		/* exposure time in milliseconds */
        INT32 readout_time;		/* readout time in milliseconds */
        INT32 nreads;			/* number of readouts to get this image */
        INT32 start_twotheta;		/* 1000*two_theta angle */
        INT32 start_omega;		/* 1000*omega angle */
        INT32 start_chi;			/* 1000*chi angle */
        INT32 start_kappa;		/* 1000*kappa angle */
        INT32 start_phi;			/* 1000*phi angle */
        INT32 start_delta;		/* 1000*delta angle */
        INT32 start_gamma;		/* 1000*gamma angle */
        INT32 start_xtal_to_detector;	/* 1000*distance in mm (dist in um)*/
        INT32 end_twotheta;		/* 1000*two_theta angle */
        INT32 end_omega;			/* 1000*omega angle */
        INT32 end_chi;			/* 1000*chi angle */
        INT32 end_kappa;			/* 1000*kappa angle */
        INT32 end_phi;			/* 1000*phi angle */
        INT32 end_delta;			/* 1000*delta angle */
        INT32 end_gamma;			/* 1000*gamma angle */
        INT32 end_xtal_to_detector;	/* 1000*distance in mm (dist in um)*/
        INT32 rotation_axis;		/* active rotation axis (index into above ie. 0=twotheta,1=omega...) */
        INT32 rotation_range;		/* 1000*rotation angle */
        INT32 detector_rotx;		/* 1000*rotation of detector around X */
        INT32 detector_roty;		/* 1000*rotation of detector around Y */
        INT32 detector_rotz;		/* 1000*rotation of detector around Z */
        INT32 total_dose;		/* Hz-sec (counts) integrated over full exposure */
	char reserve3[(32-29)*sizeof(INT32)]; /* Pad Gonisotat parameters to 128 bytes */

	/* Detector parameters (128 bytes) */
	INT32 detector_type;		/* detector type */
	INT32 pixelsize_x;		/* pixel size (nanometers) */
	INT32 pixelsize_y;		/* pixel size (nanometers) */
        INT32 mean_bias;			/* 1000*mean bias value */
        INT32 photons_per_100adu;	/* photons / 100 ADUs */
        INT32 measured_bias[MAXIMAGES];	/* 1000*mean bias value for each image*/
        INT32 measured_temperature[MAXIMAGES];	/* Temperature of each detector in milliKelvins */
        INT32 measured_pressure[MAXIMAGES];	/* Pressure of each chamber in microTorr */
	/* Retired reserve4 when MAXIMAGES set to 9 from 16 and two fields removed, and temp and pressure added
	char reserve4[(32-(5+3*MAXIMAGES))*sizeof(INT32)];
	*/

	/* X-ray source and optics parameters (128 bytes) */
	/* X-ray source parameters (14*4 bytes) */
        INT32 source_type;		/* (code) - target, synch. etc */
        INT32 source_dx;			/* Optics param. - (size microns) */
        INT32 source_dy;			/* Optics param. - (size microns) */
        INT32 source_wavelength;		/* wavelength (femtoMeters) */
        INT32 source_power;		/* (Watts) */
        INT32 source_voltage;		/* (Volts) */
        INT32 source_current;		/* (microAmps) */
        INT32 source_bias;		/* (Volts) */
        INT32 source_polarization_x;	/* () */
        INT32 source_polarization_y;	/* () */
        INT32 source_intensity_0;	/* (arbitrary units) */
        INT32 source_intensity_1;	/* (arbitrary units) */
	char reserve_source[2*sizeof(INT32)];

	/* X-ray optics_parameters (8*4 bytes) */
        INT32 optics_type;		/* Optics type (code)*/
        INT32 optics_dx;			/* Optics param. - (size microns) */
        INT32 optics_dy;			/* Optics param. - (size microns) */
        INT32 optics_wavelength;		/* Optics param. - (size microns) */
        INT32 optics_dispersion;		/* Optics param. - (*10E6) */
        INT32 optics_crossfire_x;	/* Optics param. - (microRadians) */
        INT32 optics_crossfire_y;	/* Optics param. - (microRadians) */
        INT32 optics_angle;		/* Optics param. - (monoch. 2theta - microradians) */
        INT32 optics_polarization_x;	/* () */
        INT32 optics_polarization_y;	/* () */
	char reserve_optics[4*sizeof(INT32)];

	char reserve5[((32-28)*sizeof(INT32))]; /* Pad X-ray parameters to 128 bytes */

	/* File parameters (1024 bytes) */
	char filetitle[128];		/* Title 				*/
	char filepath[128];		/* path name for data file		*/
	char filename[64];		/* name of data file			*/
        char acquire_timestamp[32];	/* date and time of acquisition		*/
        char header_timestamp[32];	/* date and time of header update	*/
        char save_timestamp[32];	/* date and time file saved 		*/
        char file_comment[512];	/* comments  - can be used as desired 	*/
	char reserve6[1024-(128+128+64+(3*32)+512)]; /* Pad File parameters to 1024 bytes */

	/* Dataset parameters (512 bytes) */
        char dataset_comment[512];	/* comments  - can be used as desired 	*/

	/* Reserved for user definable data - will not be used by Mar! */
	char user_data[512];

	/* char pad[----] USED UP! */     /* pad out to 3072 bytes */

	} frame_header;

typedef struct ctb_header_type { //NOT USED
	/* File/header format parameters (256 bytes) */
	UINT32	header_type;				/* flag for header type */
	char	header_name[32];			/* header name (RAYONIX_CORRECTION_TABLE) */
	UINT32	header_major_version;			/* header_major_version (n.) */
	UINT32	header_minor_version;			/* header_minor_version (.n) */
	UINT32	header_byte_order;			/* BIG_ENDIAN (Motorola,MIPS); LITTLE_ENDIAN (DEC, Intel) */
	UINT32	data_byte_order;			/* BIG_ENDIAN (Motorola,MIPS); LITTLE_ENDIAN (DEC, Intel) */
	UINT32	header_size;				/* in bytes			*/
	UINT32	frame_type;				/* flag for frame type */
	UINT32	magic_number;				/* to be used as a flag - usually to indicate new file */
	UINT32	compression_type;			/* type of image compression    */
	UINT32	compression_parameter[16];		/* compression parameters */
 	UINT32 	nbytes;					/* number of bytes of correction data */
	char	reserve0[(64-27)*sizeof(INT32)]; 

	/* Source image */
 	UINT32	source_nfast;				/* number of pixels in one line */
 	UINT32	source_nslow;				/* number of lines in image     */
 	UINT32	source_depth;				/* number of bytes per pixel    */
 	UINT32	source_data_type;			/* (signed,unsigned,float...) */
	UINT32	source_multiplexed;			/* multiplex flag */
 	UINT32	source_frameshift_multiplexed;		/* frameshift multiplex flag */
	UINT32	source_subimage_readout_configuration;	/* Future - physical arrangement of readout channels */
	UINT32	source_subimage_readout_code;		/* (readout_pattern) BIT Code: 1 = A, 2 = B, 4 = C, 8 = D */
	UINT32	source_nfastimages;			/* # of images in fast direction */
	UINT32	source_nslowimages;			/* # of images in slow direction */
	UINT32	source_subimage_origin_fast;		/* as for serial prescan */
	UINT32	source_subimage_origin_slow;		/* as for parallel prescan */
	UINT32	source_subimage_size_fast;		/* when divided into subimages (eg. frameshifted) */
	UINT32	source_subimage_size_slow;		/* when divided into subimages (eg. frameshifted) */
 	UINT32	source_orientation_code;		/* Describes how this frame needs to be rotated to make it "right" */
	char	reserve1[(32-15)*sizeof(INT32)]; 

	/* target image */
 	UINT32	target_nfast;				/* number of pixels in one line */
 	UINT32	target_nslow;				/* number of lines in image     */
 	UINT32	target_depth;				/* number of bytes per pixel    */
 	UINT32	target_data_type;			/* (signed,unsigned,float...) */
	UINT32	target_multiplexed;			/* multiplex flag */
 	UINT32	target_frameshift_multiplexed;		/* frameshift multiplex flag */
	UINT32	target_subimage_readout_configuration;	/* Future - physical arrangement of readout channels */
	UINT32	target_subimage_readout_code;		/* (readout_pattern) BIT Code: 1 = A, 2 = B, 4 = C, 8 = D */
	UINT32	target_nfastimages;			/* # of images in fast direction */
	UINT32	target_nslowimages;			/* # of images in slow direction */
	UINT32	target_subimage_origin_fast;		/* as for serial prescan */
	UINT32	target_subimage_origin_slow;		/* as for parallel prescan */
	UINT32	target_subimage_size_fast;		/* when divided into subimages (eg. frameshifted) */
	UINT32	target_subimage_size_slow;		/* when divided into subimages (eg. frameshifted) */
 	UINT32	target_orientation_code;		/* Describes how this frame needs to be rotated to make it "right" */
	char	reserve2[(32-15)*sizeof(INT32)]; 

	UINT32	file_saved;				/* Flag that file has been saved, should be zeroed if modified */

	UINT32	gain_corrections[MAXSUBIMAGES];		/* ADCU/DACU * 1000 */	/* Order is A0a, B0a, C0a, A1a, ... C2a, A0b, BOb... C2d */
	UINT32	calibration_wavelength;			/* wavelength (femtoMeters) */
	UINT32	calibration_distance;			/* distance   (um) */
	UINT32	calibration_reserve[62];



	/* File parameters (1024 bytes) */
	char	filename[1024];				/* name of data file			*/
	char	filepath[1024];				/* path name for data file		*/
	char	filetitle[1024];			/* Title 				*/
	char	data_modification_timestamp[32];	/* date and time of acquisition		*/
	char	header_modification_timestamp[32];	/* date and time of header update	*/
	char	file_save_timestamp[32];		/* date and time file saved 		*/
	char	dummy_timestamp[32];			/* date and time reserved 		*/
	char	file_comment[512];				/* comments  - can be used as desired 	*/
	char	reserve6[1024-(128+128+64+(3*32)+512)]; /* Pad File parameters to 1024 bytes */

	/* Dataset parameters (512 bytes) */
	char	dataset_comment[512];			/* comments  - can be used as desired 	*/

	/* Reserved for user definable data - will not be used by Mar! */
	char	user_data[512];

	/* char	pad[----] USED UP! */     /* pad out to 3072 bytes */

	} ctb_header;

typedef struct data_frame_type {
	frame_header *header;
	int  header_mapped;
        int  header_fixed_address;
	int  data_size;
	int  data_mapped;
        int  data_fixed_address;
	int  data_locked;
	void *data;
	int  data1_size;
	int  data1_mapped;
        int  data1_fixed_address;
	int  data1_locked;
	void *data1; //used for defect map, methinks
	void *additional_header;
	} data_frame;


/* possible types of detector frame headers (header_type) */

#define NO_HEADER			0
#define UNKNOWN_HEADER			1
#define MMX_HEADER			2
#define PHOTOMETRICS_SEQUENCE_HEADER	3
#define PHOTOMETRICS_HEADER		4
#define XENTRONICS_HEADER		5
#define SIEMENS_HEADER			6
#define RAXIS2_HEADER			7
#define FUJI_PF_HEADER			8
#define FUJI_HEADER			9
#define IPLAB_HEADER			10
#define FILMAN_HEADER			11
#define XEDAR_HEADER			12
#define MAR300_HEADER			13
#define TV6_HEADER			14
#define TIFF_HEADER			15
#define CSMA_HEADER			16
#define ADSC_HEADER			17
#define SPECTRAL_HEADER			18
#define FITS_HEADER			19
#define MAR345_HEADER			20
#define MAR_PROFILE_HEADER		21
#define PBM_PLAIN_HEADER		22
#define PBM_HEADER			23
#define PGM_PLAIN_HEADER		24
#define PGM_HEADER			25
#define PPM_PLAIN_HEADER		26
#define PPM_HEADER			27
#define PNG_HEADER			28
#define CBF_HEADER			29
#define MAX_HEADER_TYPES		30

/* possible types of detector frame (frame_type) */
#define EMPTY_FRAME	0
#define GENERIC_512	1
#define GENERIC_1K	2
#define GENERIC_2K	3
#define SIEMENS_512	4
#define SIEMENS_1024	5
#define PM_TEK_1K	6
#define PM_TEK_2K	7
#define PI_EEV_1	8
#define RAXIS2		9
#define FUJI_PF		10
#define FUJI		11
#define IPLAB		12
#define FILMAN		13
#define XEDAR		14
#define MAR		15
#define TV6		16
#define TIFF		17
#define BUDDHA_20	18
#define BUDDHA_30	19
#define MARCCD_CORRECTION_TABLE		20 //"Type 1"
#define MARCCD_CORRECTION_TABLE1	21 //"Type 2"
#define MARCCD_CORRECTION_TABLE2	22 //"Type 3"

/* size of frame */
#define NFAST			1024
#define NSLOW			1024

/* possible orientations of frame data */
#define HFAST			0
#define VFAST			1

/* possible origins of frame data */
#define UPPER_LEFT		0
#define LOWER_LEFT		1
#define UPPER_RIGHT		2
#define LOWER_RIGHT		3

/* possible view directions of frame data for
   any given orientation and origin */
/* KLUDGE - These are used as option array indices - must be 0,1... */
#define FROM_SOURCE		0
#define TOWARD_SOURCE		1


/* possible locations in file of overflow table */
#define FOLLOWING_DATA		0
#define FOLLOWING_HEADER	1

/* possible types of file format */
#define LINEAR_8 		1001
#define LINEAR_OVERFLOW_8	1002
#define LINEAR_16		1003
#define LINEAR_OVERFLOW_16	1004
#define LOG_8			1005
#define LOG_OVERFLOW_8		1006
#define LOG_16			1007
#define LOG_OVERFLOW_16		1008
#define HEX_16			1009

/* possible types of compression format */
#define BUDDHA_20_COMPRESSION		1
#define BUDDHA_30_COMPRESSION		2
#define SIEMENS_8BIT_COMPRESSION	3
#define LOG_COMPRESSION			4
#define BUDDHA_20_PEAKS			5
#define PCK_COMPRESSION			6

/* possible types of data */
#define DATA_UNSIGNED_INTEGER	0
#define DATA_SIGNED_INTEGER	1
#define DATA_FLOAT		2

//Magic number error codes
#define MN_FILE_NOT_FOUND	-1
#define MN_FILE_READ_ERROR	-2

/* types of geometric transformation for reading or rendering image */

typedef enum _ImageTransformation {
   R0,
   R90,
   R180,
   R270,
   M0,
   M45,
   M90,
   M135
} ImageTransformation;

#if 0
#define R0   0
#define R90  1
#define R180 2
#define R270 3
#define M0   4
#define M45  5
#define M90  6
#define M135 7
#endif

/* possible ways of dealing with multiple images */
#define STORE_MERGED_SEQUENCE		0
#define STORE_SEQUENCE			1
#define STORE_FIRST_IMAGE		2
#define STORE_LAST_IMAGE		3
#define STORE_NEXT_IMAGE		4

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


/* Initialize a default frame */
extern int init_frame (
#if NeedFunctionPrototypes
void
#endif
);

/* Return the default frame */
extern data_frame * default_frame (
#if NeedFunctionPrototypes
void
#endif
);

/* Return the current frame */
extern data_frame * current_frame (
#if NeedFunctionPrototypes
void
#endif
);

/* set up parameters for write_frame */
extern void set_write_frame(
#if NeedFunctionPrototypes
int *file_format,
int *header_type,
int *trans_type,
int *compression
#endif
);

/* get current parameters for write_frame */
extern void get_write_frame(
#if NeedFunctionPrototypes
int *file_format,
int *header_type,
int *trans_type,
int *compression
#endif
);

extern int write_frame_new(int *percent_complete, data_frame *framep, const char *filename,    int file_format, int header_type, int trans_type, int compression, char *error_buffer, int buflen);
extern int write_frame_in_thread(void **thread_handle, data_frame *framep, const char *filename,    int file_format, int header_type, int trans_type, int compression, char *error_buffer, int buflen);
extern int finished_write_frame_thread(void *thread_struct, char *error_buffer, int buflen);
extern int cancel_write_frame_thread(void *thread_struct);
extern int percent_remaining_write_frame_thread(void *thread_struct);

/* write a frame of data to a file */
extern int write_frame (
#if NeedFunctionPrototypes
data_frame * framep,
const char * filename
#endif
);

/* set up parameters for read_frame */
extern int set_read_frame(
#if NeedFunctionPrototypes
int *header_type,
int *nfast,
int *nslow,
int *depth,
int *trans_type,
int *sequence_ok
#endif
);

/* read a frame of data from a file */
extern int read_frame( data_frame *dataframep, const char *filename, int warn);

/* read a frame of data from a file */
extern int map_frame(
#if NeedFunctionPrototypes
data_frame * dataframep,
char * filename
#endif
);

extern int read_frame_header(
#if NeedFunctionPrototypes
int             fd,
frame_header   *hp,
int            header_type,
int            *nimages
#endif
);

/* acquire a frame of data from device */
extern int acquire_frame (
#if NeedFunctionPrototypes
char * image_data, frame_header * statsp, int device_id
#endif
);

/* create a test pattern image */
extern int fill_test_frame (
#if NeedFunctionPrototypes
data_frame * framep, int pattern_type
#endif
);

/* calculate overflow table for frame */
extern int fill_frame_ot (
#if NeedFunctionPrototypes
char * image_data, frame_header * statsp
#endif
);

/* copy a frame */
extern int copy_frame(
#if NeedFunctionPrototypes
data_frame *framep1,
data_frame *framep2
#endif
);

/* copy a frame's data1 */
extern int copy_frame_data1(
#if NeedFunctionPrototypes
data_frame *framep1,
data_frame *framep2
#endif
);

/* copy a frame header */
extern int copy_frame_header (
#if NeedFunctionPrototypes
frame_header * headerp1,
frame_header * headerp2 
#endif
);

/* allocate and initialize frame header */
extern data_frame *create_frame (
#if NeedFunctionPrototypes
int format
#endif
);

/* deallocate data in a data frame structure */
extern void destroy_frame_data(
#if NeedFunctionPrototypes
data_frame     *framep
#endif
);

/* deallocate data in a data frame structure */
extern void destroy_frame_data1(
#if NeedFunctionPrototypes
data_frame     *framep
#endif
);

/* deallocate a data frame structure */
extern void destroy_data_frame(
#if NeedFunctionPrototypes
data_frame     *framep
#endif
);

/* allocate and initialize frame header */
extern frame_header *create_frame_header (
#if NeedFunctionPrototypes
int format
#endif
);

/* deallocate a frame header structure */
extern int destroy_frame_header(
#if NeedFunctionPrototypes
frame_header   *headerp
#endif
);


/* initialize frame header */
extern int initialize_frame_header (
#if NeedFunctionPrototypes
frame_header *headerp,
int format
#endif
);


extern int get_frame_size(
#if NeedFunctionPrototypes
data_frame *framep,
int *width,
int *height,
int *depth
#endif
);

/* Compress a frame */
extern int compress_frame (
#if NeedFunctionPrototypes
data_frame * framep1,
data_frame * framep2,
int compression_type
#endif
);

extern int frame_printbox(
#if NeedFunctionPrototypes
data_frame *dataframep,
int x1,
int y1,
int x2,
int y2
#endif
);

extern int frame_statbox(
#if NeedFunctionPrototypes
void *spotptr,
data_frame *dataframep,
int x1,
int y1,
int x2,
int y2,
double min,
double max
#endif
);

extern void print_spotstats(
#if NeedFunctionPrototypes
void *spotptr
#endif
);

/* allocate new data frame based on original, do NOT copy data */
extern data_frame *duplicate_frame_structure (
#if NeedFunctionPrototypes
data_frame *framep
#endif
);

extern int read_frame_data(
#if NeedFunctionPrototypes
int fd,
data_frame *framep,
int transformation_type
#endif
);

extern int get_value_from_frame(
#if NeedFunctionPrototypes
data_frame *framep,
int x,
int y
#endif
);

int get_value_from_frame_by_offset(data_frame *framep, intptr_t offset);

extern int exchange_frames(
#if NeedFunctionPrototypes
data_frame *frame1p,
data_frame *frame2p
#endif
);

extern int exchange_frame_data(
#if NeedFunctionPrototypes
data_frame *frame1p,
data_frame *frame2p
#endif
);

extern int init_read_from_records(
#if NeedFunctionPrototypes
int reclen,
int start_bytes,
int end_bytes
#endif
);

extern int need_read_from_records(
#if NeedFunctionPrototypes
void
#endif
);

extern int read_from_records(
#if NeedFunctionPrototypes
int fd,
char *buffer,
int ntoread
#endif
);

extern int mult_frame_transform(
#if NeedFunctionPrototypes
int transform2,
int transform1
#endif
);

extern int determine_frame_transformation(
#if NeedFunctionPrototypes
int view_direction,
int orientation,
int origin
#endif
);

extern int invert_frame_transformation(
#if NeedFunctionPrototypes
int transformation
#endif
);

extern int get_framestats(
#if NeedFunctionPrototypes
frame_header    header,
pix_overflow   *overflowtable
#endif
);

extern int frame_can_hold_this_frame(data_frame *framep, int nfast, int nslow, int depth);

extern int make_frame_hold_this_frame(data_frame *framep, int nfast, int nslow, int depth);

extern int resize_frame( data_frame *framep, int size);

extern int resize_frame1( data_frame *framep, int size);

extern void expand_array(
#if NeedFunctionPrototypes
void *array,
int old_depth,
int new_depth,
int nelements
#endif
);

extern void decode_array(
#if NeedFunctionPrototypes
void *array,
int old_depth,
int new_depth,
int base,
int nelements
#endif
);

extern int transform_coord(int *newfast, int *newslow, int offset, int nfast, int nslow, int trans_type);

extern int transform_offset (int transformation, int nfast, int nslow, int offset);

extern void get_profile(
#if NeedFunctionPrototypes
data_frame *framep,
float x1,
float y1,
float x2,
float y2,
float **position,
float **value,
int *npts
#endif
);

extern void get_value_under_line_from_frame (
#if NeedFunctionPrototypes
data_frame *framep,
float x1,
float y1,
float x2,
float y2,
float width,
float **position,
float **value,
int *npts,
int option,
double *min,
double *max
#endif
);

extern void get_histogram_under_box_from_frame(
#if NeedFunctionPrototypes
data_frame *framep,
int ix1,
int iy1,
int ix2,
int iy2,
float **values,
float **histogram,
int *npts,
int option,
double *min,
double *max,
double *mean,
double *rms
#endif
);

extern data_frame *create_shared_frame(
#if NeedFunctionPrototypes
int key,
int format,
int image_size
#endif
);

extern int mlock_frames(data_frame *first_framep, ...);
extern int munlock_frames(data_frame *first_framep, ...);
extern int mlock_frame(data_frame * framep);
extern int munlock_frame(data_frame * framep);
extern int mlocked(data_frame * framep);
extern int read_frame_header_only(frame_header *hp, const char *filename);
extern int frame_specialstats(data_frame *frame_ptr, int cutoff, int ix1, int iy1, int ix2, int iy2, int *nlower, int *ngreater);
extern void setup_ctb_header_from_template(int table_type, frame_header *new_header, frame_header *template_header);

extern uintmax_t SupportedPixelBitMask(data_frame* framep);
extern uintmax_t SupportedPixelRange(data_frame* framep);
extern intmax_t MaxSupportedPixelValue(data_frame* framep);
extern intmax_t MinSupportedPixelValue(data_frame* framep);

#endif /* frame_h */
