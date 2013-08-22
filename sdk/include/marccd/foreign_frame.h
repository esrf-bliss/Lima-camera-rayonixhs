#ifndef foreign_frame_h
#define foreign_frame_h

#include "types.h"
#include "frame.h"


/* Different types of file formats */
#define FILE_FORMAT_UNKNOWN			0
#define FILE_FORMAT_NATIVE			1
#define FILE_FORMAT_FOREIGN_RAW			2
#define FILE_FORMAT_FOREIGN_XENTRONICS1		3
#define FILE_FORMAT_FOREIGN_XENTRONICS2		4
#define FILE_FORMAT_FOREIGN_FILMAN		5
#define FILE_FORMAT_FOREIGN_SIEMENS		6
#define FILE_FORMAT_FOREIGN_PHOTOMETRICS	7
#define FILE_FORMAT_FOREIGN_RAXIS2		8
#define FILE_FORMAT_FOREIGN_FUJI_PF		9
#define FILE_FORMAT_FOREIGN_FUJI		10
#define FILE_FORMAT_FOREIGN_IPLAB		11
#define FILE_FORMAT_FOREIGN_XEDAR		12
#define FILE_FORMAT_FOREIGN_MAR300		13
#define FILE_FORMAT_FOREIGN_TV6			14
#define FILE_FORMAT_FOREIGN_CSMA		15
#define FILE_FORMAT_FOREIGN_ADSC		16
#define FILE_FORMAT_FOREIGN_SPECTRAL		17
#define FILE_FORMAT_FOREIGN_FITS		18
#define FILE_FORMAT_FOREIGN_MAR345		19
#define FILE_FORMAT_FOREIGN_MAR_PROFILE		20
#define FILE_FORMAT_FOREIGN_PGM			21
#define FILE_FORMAT_FOREIGN_CBF			22

/*  Xedar / Fisher header - 34 bytes long */
/* Beware that this header is designed for software running on a DOS PC.
   for shorts, the byte order is reversed.
   for floats, the byte order is reversed and the floating point format may not be IEEE.
   last two bytes are NOT swapped.

   This structure is designed, unlike the true header structure, to be aligned properly.
   This makes the floats difficult to access, but floats are not very portable anyway.
*/

#define XEDAR_HDR_RES 	1			/* number of reserved bytes in image header */

typedef struct {
   UINT16 type;			/* Picture type */
   UINT16 hdrByten;		/* Size of this header in bytes */
   UINT16 xExt;			/* Picture x extent (pixels) */
   UINT16 yExt;			/* Picture y extent (pixels) */
   UINT16 bpp;			/* Picture depth (bits per pixel) */
   /*float*/UINT16 min[2];			/* %%%% minimum pixel value */
   /*float*/UINT16	max[2];			/* %%%% maximum pixel value */
   /*float*/UINT16	ave[2];			/* average pixel value (mean) */
   /*float*/UINT16	rms[2];			/* standard deviation of image */
   UINT16	win;			/* display parameters */
   UINT16	lnv;			/* # window, level and invert */
   UINT16	inv;			/*  */
   UINT8	mini;			/* minified image preset */
   UINT8	empty[XEDAR_HDR_RES];	/* reserved for later */
} xedar_aligned_header;


/*  Photometrics Inc. header  - 160 bytes long  (from "ccd" code on Sun SparcStation system) */
/*  But actual header appears to be 160 bytes long, an original "sizeof" structure was 164 bytes */
/*  Modified (filter[8] -> filter[4]) to make header correct size (160 bytes) */
typedef struct {
      CHAR8   com[80];		/* an identification */
      CHAR8   obj[16];		/* object being observed */
      FLOAT32  bias;		/* reference bias level */
      INT32   expt;		/* exposure time */
      INT16  addups;		/* The number of addups */
      INT16  imscale;		/* Binary power of two scaler */
      INT16  t1;		/* generally an unused short */
      INT16  t2;		/* generally an unused short */
      UINT32   time;	/* long integer time */
      INT16  corg;		/* holds the image column origin */
      INT16  rorg;		/* holds the image row origin */
      INT16  cols;		/* holds the image row length */
      INT16  rows;		/* holds the image number of rows */
      INT16  cbin;		/* holds the image row binning */
      INT16  rbin;		/* holds the image column binning */
      INT16  gain;		/* holds the readout gain */
      INT16  invert;		/* Holds the status of regular or inverted */
      CHAR8   acam[4];		/* alternate sub-image specification */
      INT16  acols;		/* holds the original row length */
      INT16  arows;		/* holds the original number of rows */
      INT32   nbytes;		/* Holds the number of bytes in the image */
      CHAR8   bcam[2];		/* A space */
      UINT16 rate;	/* A/TO/D readout */
      INT16  qct;		/* count of the number of sub-images */
      INT16  obstyp;		/* the type of observation */
      CHAR8   filter[4];		/* The filter in use */
      INT16  bitsize;		/* The image depth and type */
      } photometrics_header;


/* XENTRONICS / NICOLET / SIEMENS header and overflow definitions */


/*	used when compacting data for writing to disk		*/
/*	both Wicat and Cadmus versions 				*/

typedef struct {
	UINT16 value;
	UINT32 offset;
	} xentronics_oflow;


/* Vax Overflow	used when compacting data for writing a vax format tape	*/

typedef struct {
	UINT16 value;
	UINT16 xcoord;
	UINT16 ycoord;
	} xentronics_voflow;

	/* SGI machine will align all elements of a structure on the natural
	   bouandaries of the longest datatype in the structure!!!
	   This structure will be used to work around this "feature" in
	   all the ipc routines that read and write files so that the files
	   will be compatible with those from other machines.
	*/

typedef struct {
	UINT16 value;
	UINT16 offset[2];
	} xentronics_oflow_packed;

	/* used by BUDDHA v2.0 (FORTRAN) for internal storage of overflow table */
typedef struct {
	 UINT16  value;
	 UINT16  slowcoord;
	 UINT16  fastcoord;
      }  buddha_20_oflow;

/*  This is the "2nd generation" header (mailbox) used with the PCS by Xentronics/Nicolet */

/*	mail structure for use with PCS computers, allows 
*	multiple processes to access data space
*	addresses are offset from bigining of mailbox
*/
typedef struct {
	UINT32 format;		/* 16=word data, 8=byte data,
					   10=Cadmus data		*/
	UINT32 status;		/* bit0=1 read lock, bit1=1 
					   write lock 			*/
	UINT32 mailbox;		/* offset to mailbox		*/
	UINT32 correctx;	/* offset x correction array	*/
        UINT32 correcty;	/* offset y correction array	*/
	UINT32 thedata;		/* offset to data space 	*/
        UINT32 topdata;		/* offset to end of data space  */
 	UINT32 dimen;		/* one side of data space	*/
 	UINT32 cellsize;		/* size of pixel in 1024 bins	*/
        UINT32 zoom;		/* magnification of image 	*/
        UINT32 quadrant;		/* 0=center, 1=upper left,
					   2=ur, 3=ll, 4=lr		*/
	UINT32 eventcount;	/* total counts in active area	*/
	UINT32 over_8_bits;	/* pixels with counts > 255	*/
	UINT32 over_16_bits;	/* pixels with count > 65535	*/
	UINT32 zmax;		/* maximum count in a pixel	*/
	UINT32 zmaxx;		/* x value of maximum pixel 	*/
	UINT32 zmaxy;		/* y value of maximum pixel	*/
	UINT32 zdisp;		/* default display value	*/
	UINT32 ontime;		/* total ontime when polled 	*/
	UINT32 late;		/* data present when polled	*/
        UINT32 datetime[2];	/* date and time		*/
	UINT32 elapsed[2];	/* time of data collection	*/
	UINT32 ontime_inc;	/* ontime from last add 	*/
	INT32 dummy[7];			/* extra space for variables	*/
	UINT32 overflow[96];	/* offsets of 16 bit overflows	*/
	/* pointers and variables take 512 bytes of space		*/
	CHAR8 filename[16];		/* name of data frame		*/
	CHAR8 file_info[240];		/* asci space for frame info	*/
	CHAR8 dataset_info[256];		/* asci comment space,dataset	*/
	/* total space used by mailbox is 1024 bytes 			*/
	} xentronics_header_2;

/*  This is the "1st generation" header (mailbox) used with the Cadmus by Xentronics */

/*	mailbox for US Cadmus computer system format = 10 	*/
typedef struct {
	UINT32 format;
	UINT16 *thedata;
        UINT16 *topdata;
	xentronics_oflow *overflow;
        xentronics_oflow *oflowend;
 	UINT32 dimen;
        UINT32 zoom;
        UINT32 quadrant;
	UINT32 eventcount;
	UINT32 oflowcount;
	UINT32 zmax;
	UINT16 zmaxx;
	UINT16 zmaxy;
	UINT32 zdisp;
	UINT32 ontime;
	UINT32 late;
        UINT32 datetime[2];
	UINT32 elapsed[2];
 	UINT32 cellsize;
	INT32 dummy[8];
	CHAR8 filename[16];
	} xentronics_header_1;

/* Genex addition to the xentronics_header_2 format - this structure defines the
   data found in xentronics_header_2.dataset_info */
/* This structure should align OK  on the SGI (4byte boundaries) */
typedef struct {                /* structure type for a data run: 256 bytes */
                CHAR8    col_code[8];    /* 8-character code name of run */
                CHAR8    col_notes[64];  /* notes on the run */
                INT16   col_id;         /* integer identifier of the run */
                INT16   col_volxray;    /* X-ray voltage in kV */
                INT16   col_curxray;    /* X-ray current in ma */
                INT16   col_chvol;      /* chamber voltage in kV */
                INT16   col_stepsize;   /* stepsize,units of 1/96 deg*/
                INT16   col_nframes;    /* number of frames in run */
                INT16   col_motor;      /* motor being moved during run */
                INT16   col_nshifts;    /* number of shifts in the run */
                INT16   col_nchams;     /* # of chambers being used */
                INT16   col_temp;       /* temperature during run */
                CHAR8    col_space[4];   /* space holder */
                INT32    col_ninteg;     /* # of refls successfully integrated*/
                INT32    col_nexam;      /* # of refls examined during run */
                        /* several of these parameters are different from
                        the forms they have on the Vax because I don't want
                        to deal with floating point on the PCS...
                        In particular, all angles are in grads (100ths of deg)
                        and distances are in microns */
                INT32    col_ltakeoff;   /* takeoff angle in 100ths of deg */
                INT32    col_lstartpos[3]; /* start-of-run goniostat position */
                FLOAT32   col_recip[3][3]; /* reciprocal-space unit cell matrix:
                                                columns are a*, b*, c* */
                INT32    col_lrefval;    /* reference value of motor in motion */
                INT32    col_lexpos;     /* exposure time /frame,100ths of sec */
                INT32    col_lbgiexpo;   /* expos time/frame in background run*/
                INT32    col_ldetecpos0[3]; /*coords of center of detector #0 */
                INT32    col_ldetecang0[3]; /*angular attitude of detector #0 */
                INT32    col_ldetecpos1[3]; /* coords of center of detector #1 */
                INT32    col_ldetecang1[3]; /* angular attitude of detector #1 */
                FLOAT32   col_wtsum;      /* sum of weights in the next 3 aves */
                FLOAT32   col_intave;     /* average value of I in run */
                FLOAT32   col_sigave;     /* average value of sigma in run */
                FLOAT32   col_iosave;     /* <I/sigma> */
                FLOAT32   col_delomave;   /* <delta(omega)>*/
                FLOAT32   col_rmsomave;   /* RMS error in omega */
                FLOAT32   col_ssqave;     /* <square of scattering vector length*/
                FLOAT32   col_fwhmave;    /* <fwhm of profiles> */
                INT32    col_lreslim;    /* resolution limit in picometers*/
                INT32    col_lssqmax;    /* 10000 *largest squared scattvector */
	     } genex_datarun;



/*  Rigaku RAXIS-II header  - 2048 bytes long  (from RAXIS documentation v1.1) */

typedef struct {

   /* 256 bytes */
   CHAR8  device_name[10];
   CHAR8  version[10];
   CHAR8  crystal_name[20];
   CHAR8  crystal_system[12];
   FLOAT32 a;
   FLOAT32 b;
   FLOAT32 c;
   FLOAT32 alpha;
   FLOAT32 beta;
   FLOAT32 gamma;
   CHAR8  space_group[12];
   FLOAT32 mosaic_spread;
   CHAR8  memo[80];
   CHAR8  reserve1[84];

   /* 256 bytes */
   CHAR8  date[12];
   CHAR8  measurer[20];
   CHAR8  target[4];
   FLOAT32 wavelength;
   CHAR8  monochromator[20];
   FLOAT32 monochromator_2theta;
   CHAR8  collimator[20];
   CHAR8  filter[4];
   FLOAT32 camera_length;
   FLOAT32 KV;
   FLOAT32 mA;
   CHAR8  reserve2[156];

   /* 256 bytes */
   CHAR8  mount_axis[4];
   CHAR8  beam_axis[4];
   FLOAT32 phi_0;
   FLOAT32 phi_start;
   FLOAT32 phi_end;
   FLOAT32 num_of_oscs;
   INT32  exposure_time;
   FLOAT32 direct_beam_x;
   FLOAT32 direct_beam_z;
   FLOAT32 omega;
   FLOAT32 chi;
   FLOAT32 two_theta;
   CHAR8  reserve3[208];

   /* 256 bytes */
   INT32  num_of_x_pixels;
   INT32  num_of_z_pixels;
   FLOAT32 x_pixel_size;
   FLOAT32 z_pixel_size;
   INT32  record_length;
   INT32  num_of_records;
   INT32  reading_start_line;
   INT32  IP_number;
   FLOAT32 output_ratio;
   FLOAT32 fading_time_1;
   FLOAT32 fading_time_2;
   CHAR8  reserve4[212];

   /* 256 bytes */
   CHAR8  processing_program[20];
   FLOAT32 refined_a;
   FLOAT32 refined_b;
   FLOAT32 refined_c;
   FLOAT32 refined_alpha;
   FLOAT32 refined_beta;
   FLOAT32 refined_gamma;
   FLOAT32 refined_phi_x;
   FLOAT32 refined_phi_y;
   FLOAT32 refined_phi_z;
   FLOAT32 refined_camera_length;
   FLOAT32 refined_direct_beam_x;
   FLOAT32 refined_direct_beam_z;
   FLOAT32 refined_delta_x;
   FLOAT32 refined_delta_z;
   FLOAT32 refined_delta_phi;
   FLOAT32 background;
   INT32  box_x;
   INT32  box_z;
   INT32  box_line_x;
   INT32  box_line_z;
   INT32  corner;
   FLOAT32 setting_matrix[9];
   INT32  refine_status[6];
   CHAR8  reserve5[92];

   CHAR8  user_area[768];

   } raxis2_header;

/*  FUJI scanner at the Photon Factory - deduced from images from 8/92 trip with pjb */
typedef struct {
   CHAR8 title[50];			/* Not NULL terminated ! */
   CHAR8 unknown1[6];
   CHAR8 media_type[10]; 		/* Contains string "FUJI FILM " Not NULL terminated ! */
   CHAR8 the_rest[8192-50-6-10];
   } fuji_pf_header;


/*  Mar Research header - 2400 bytes long  - only the first 31 long words used
    Data are written on VAX so they probably need to be swapped
    File is always (?) 1+1200+overflow_records records;
    Overflows are at end of file.
 */

typedef struct {
   INT32 total_pixels_x;			/* total pixels in x direction */
   INT32 total_pixels_y;			/* total pixels in y direction */
   INT32 lrecl;				/* length of a record in bytes */
   INT32 max_rec;			/* number of data record in file */
   INT32 overflow_pixels;		/* number of pixels > 65535 */
   INT32 overflow_records;		/* number of overflow records at end */
   INT32 counts_per_sec_start;		/* not yet used */
   INT32 counts_per_sec_end;		/* ion chamber reading at end of exposure*/
   INT32 exposure_time_sec;		/* not yet used */
   INT32 programmed_exp_time_units;	/* not yet used */
   INT32 programmed_exposure_time;	/* not yet used */
   FLOAT32 r_min;				/* start and end of spiral as */
   FLOAT32 r_max;				/* defined in scanning table (mm) */
   FLOAT32 p_r;				/* radial width of spiral pixel */
   FLOAT32 p_l;				/* same value as P_R  */
   FLOAT32 p_x;				/* size of cartesian pixel after */
   FLOAT32 p_y;				/* transformation */
   FLOAT32 centre_x;			/* centre of cartesian image */
   FLOAT32 centre_y;			/* (currently always 600,600) */
   FLOAT32 lambda;			/* wavelength */
   FLOAT32 distance;			/* crystal to plate distance */
   FLOAT32 phi_start;			/* not currently used */
   FLOAT32 phi_end;			/* phi end of current exposure */
   FLOAT32 omega;				/* not currently used */
   FLOAT32 multiplier;			/* high intensity multiplier */
   CHAR8 scanning_date_time[24];		/* current date and time */
   } mar300_header;


typedef struct {

	INT32	byteorder;		/* Always = 1234 */
        CHAR8    version[8];		/* Program version           */
        CHAR8    program[16];		/* Program name              */

	/* Scanner specific things */
	INT16	scanner;		/* Scanner serial no. */
	INT16	size;  			/* No. of pixels in 1 dimension */
	CHAR8	format;			/* Image format */
	CHAR8	mode;			/* Exposure mode */
	INT32	high;			/* No. high intensity pixels */
        INT32     pixels;			/* No. of pixels in image */
	INT32	adc_A;			/* Offset from channel A of ADC */
	INT32	adc_B;			/* Offset from channel B of ADC */
	INT32	add_A;			/* ADD to channel A of ADC */
	INT32	add_B;			/* ADD to channel B of ADC */
	INT32	gap;			/* GAP position seen by controller */

        FLOAT32	pixel_length;		/* Length of 1 pixel */
        FLOAT32	pixel_height;		/* Height of 1 pixel */
        FLOAT32   multiplier;     	/* Multiplication factor */
        FLOAT32   xcen;			/* Center x of transf. image */
        FLOAT32   ycen;			/* Center y of transf. image */
        FLOAT32   roff;			/* Radial offset             */
        FLOAT32   toff;			/* Tangential offset         */
        FLOAT32   gain;			/* Gain of detector          */

	/* Experimental conditions for this image */
        FLOAT32   time;			/* Exposure time in secs */
        FLOAT32   dosebeg;		/* Dose at start of expose */
        FLOAT32   doseend;		/* Dose at end   of expose */
        FLOAT32   dosemin;		/* Min. dose during expose */
        FLOAT32   dosemax;		/* Max. dose during expose */
        FLOAT32   doseavg;		/* Avg. dose during expose */
        FLOAT32   dosesig;		/* Sig. dose during expose */
        FLOAT32   wave;  			/* Wavelength [Ang.] */
        FLOAT32   dist;			/* Distance [mm] */
        FLOAT32   resol;			/* Max. resolution */
        FLOAT32   phibeg;			/* Starting PHI */
        FLOAT32   phiend;			/* Ending   PHI */
        FLOAT32   omebeg;			/* Starting Omega */
        FLOAT32   omeend;			/* Ending   Omega */
        FLOAT32   theta;			/* Two theta */
        FLOAT32   chi;			/* Chi */
	INT32	phiosc;			/* Phi oscillations */
	INT32	omeosc;			/* Omega oscillations */
        INT32     dosen;  		/* No. of X-ray readings   */

	/* Generator settings */
	CHAR8	source[32];		/* Type of source */
        FLOAT32   kV;  			/* Generator: kV */
        FLOAT32   mA;  			/* Generator: mA */
	
	/* Monochromator */
	CHAR8	filter[32];		/* Type of monochromator */
        FLOAT32   polar; 			/* Beam polarization factor */
        FLOAT32   slitx; 			/* Slit width               */
        FLOAT32   slity; 			/* Slit height              */

	/* Image statistics  */
	INT32	valmin;			/* Min. pixel value */
	INT32	valmax;			/* Max. pixel value */
	FLOAT32	valavg;			/* Avg. pixel value */
	FLOAT32	valsig;			/* Sig. pixel value */
	INT32	histbeg;		/* Start of histogram */
	INT32	histend;		/* End   of histogram */
	INT32	histmax;		/* Max.  of histogram */

	/* Remark             */
	CHAR8	remark[56];		/* Remark */

	/* Time of production */
	CHAR8	date[24];		/* Creation date */

   } mar345_header;






/*  Dave Filmans film scanner format (from Scripps/Harvard)
 */

typedef struct {

   /* 130 bytes */
   CHAR8  fortran_cc;
   CHAR8  title[80];
   CHAR8  nslow[6];
   CHAR8  nfast[6];
   CHAR8  origin_slow[6];
   CHAR8  origin_fast[6];
   CHAR8  sub_nslow[6];
   CHAR8  sub_nfast[6];
   CHAR8  sub_origin_slow[6];
   CHAR8  sub_origin_fast[6];
   CHAR8  new_line;

   } filman_header;


/*  IPLab software (Macintosh version of Princeton Instruments CCD)
    72 + 2048 bytes CLUT (from IPLab Documentation for version 2.0a 1991)  */

   /* This structure has an alignment/portability problem
      width and height are entered here as char[4] but are really long so
      must be copied to a properly aligned segment before being interpreted.
   */

typedef struct {

   /* 72 bytes */
   CHAR8  version[4];
   CHAR8  IPLab_file_format;
   CHAR8  data_type;
   CHAR8  data_width[4];
   CHAR8  data_height[4];
   CHAR8  reserved[58];

   /* 2048 bytes */
   CHAR8  CLUT[2048];

   } IPLab_header;



/*  Princeton Biophysics Dept. (Sol Gruner)  TV6 detector
    as used at CHESS 4/94     Example was TV6 TIFF v 1.3
    Header is 4096 bytes long
*/

#define TV6_TIFFTAG_UNKNOWN01			36864
#define TV6_TIFFTAG_UNKNOWN02			36865
#define TV6_TIFFTAG_UNKNOWN03			36866
#define TV6_TIFFTAG_UNKNOWN04			36867
#define TV6_TIFFTAG_UNKNOWN05			36868
#define TV6_TIFFTAG_UNKNOWN06			36869
#define TV6_TIFFTAG_DETECTOR_PARAMETERS		36870	/* ASCII description of Voltages/Temps. etc. */
#define TV6_TIFFTAG_UNKNOWN08			36873	/* ? Bits/pixel */
#define TV6_TIFFTAG_UNKNOWN09			36874	/* ? pixels/? */
#define TV6_TIFFTAG_UNKNOWN10			36875	/* ? pixels/? */
#define TV6_TIFFTAG_UNKNOWN11			36876
#define TV6_TIFFTAG_UNKNOWN12			36877
#define TV6_TIFFTAG_UNKNOWN13			36878
#define TV6_TIFFTAG_UNKNOWN14			36879
#define TV6_TIFFTAG_UNKNOWN15			36880
#define TV6_TIFFTAG_UNKNOWN16			37120

typedef struct {
   CHAR8 pad0[30];
   CHAR8 date_time[20];
   CHAR8 chip[20];
   CHAR8 version[20];
   CHAR8 pad1[486];
   CHAR8 comment[1024];
   CHAR8 pad[4096-(30+3*20+486+1024)];		/* Fill it out to 4096 bytes */
   } tv6_header;


/*  TIFF header - structure for holding a TIFF header, which
    must be interpreted at run-time
*/
#define PADDED_TIFF_HEADER_SIZE		1024

typedef struct {
   CHAR8 header[8192];
   } tiff_header;


/*  Princeton Instruments "CSMA" header
    Header is 4100 bytes long

    Members that are misaligned are replaced by arrays of shorts.
*/

typedef struct {
   INT16  diodeni;
   INT16  avgexp;
   INT16  exposure;
   INT16  datarange;
   INT16  mode;
   INT16  wexsy[2];			/* float  wexsy; */
   INT16  asyavg;
   INT16  asyseq;
   INT16  linefreq;
   INT16  date[5];
   INT16  ehour;
   INT16  eminute;
   INT16  noscan;
   INT16  fastacc;
   INT16  avgtime;
   INT16  dmatotal;
   INT16  faccount;
   INT16  stdiode;
   INT16  nanox[2];			/* float  nanox; */
   INT16  calibdio[20];			/* float  calibdio[10]; */
   CHAR8   fastfile[16];
   INT16  asynen;
   INT16  datatype;
   INT16  calibnan[20];			/* float  calibnan[10]; */
   INT16  rtanum;
   INT16  astdiode;
   INT16  int78;
   INT16  int79;
   INT16  calibpol[16];			/* double calibpol[4]; */
   INT16  int96;
   INT16  int97;
   INT16  int98;
   INT16  int90;
   INT16  int100; 		/* 84 */
   CHAR8   exprem[5][80];	/* 284 */
   INT16  int301;
   CHAR8   label[16];		/* 293 */
   INT16  gsize;
   INT16  lfloat;
   CHAR8   califile[16];
   CHAR8   bkgdfile[16];		/* 311	*/
   INT16  srccmp;
   INT16  stripe;
   INT16  scramble;
   INT32   lexpos;
   INT32   lnoscan;
   INT32   lavgexp;
   CHAR8   stripfil[16];
   CHAR8   version[16];
   INT16  controller_type;
   INT16  yt_file_defined;
   INT16  yt_fh_calib_mode;
   INT16  yt_fh_calib_type;
   INT16  yt_fh_element[12];
   FLOAT64 yt_fh_calib_data[12];
   FLOAT32  yt_fh_time_factor;
   FLOAT32  yt_fh_start_time;
   INT16  reverse_flag;
   INT16  start_exposure_time[2];	/* float  start_exposure_time; */
   INT16  stop_exposure_time[2];	/* float  stop_exposure_time; */
   INT16  cosmetics_done;
   CHAR8   pad[4100-(856)];		/* Fill it out to 4100 bytes */
   } csma_header;

/*  ADSC header as found on 1st 82mm 1152x1552 instrument at CHESS
    and written by ADSC software on a DEC Alpha UNIX workstation

*/

/* These lengths are an arbitrary guesstimate to be used in identifying 
   ADSC files
*/
#define MIN_ADSC_RECORD_LENGTH		1024
#define MAX_ADSC_RECORD_LENGTH		4800

typedef struct {
   INT32   nfast;
   INT32   nslow;
   INT32   ints[6];
   FLOAT32 dummy1[2];
   FLOAT32 exposure_time;
   FLOAT32 dummy2[4];
   FLOAT32 xpixelsize;
   FLOAT32 ypixelsize;
   FLOAT32 dummy3[2];
   FLOAT32 wavelength;
   FLOAT32 xtal_to_detector;
   FLOAT32 start_phi;
   FLOAT32 end_phi;
   FLOAT32 dummy4[5];
   CHAR8   pad[1024-30*4];
   } adsc_header;

typedef struct {
   CHAR8   type;
   INT32   title_length;
   CHAR8   title[128];
   CHAR8   date[8];
   CHAR8   time[11];
   INT32   n_parameters;	/* Usually 16 */
   FLOAT32 parameters[16];
   INT32   nslow;
   INT32   nfast;
   } spectral_header;

typedef struct {
   CHAR8   type;
   CHAR8   title_length[4];
   /* CHAR8 title[?]; */
   CHAR8   date[8];
   CHAR8   time[11];
   CHAR8   n_parameters[4];	/* Usually 16 */
   CHAR8   parameters[64];
   CHAR8   nslow[4];
   CHAR8   nfast[4];
   } aligned_spectral_header;

/* FITS header always has n * 36 * 80 characters  (n >= 1) */
typedef struct {
   CHAR8   simple[80];
   CHAR8   bitpix[80];
   CHAR8   naxis[80];
   CHAR8   naxis1[80];
   CHAR8   naxis2[80];
   CHAR8   date[80];
   CHAR8   time[80];
   CHAR8   nparam[80];
   CHAR8   comment[80];
   CHAR8   end[80];
   CHAR8   records[26][80];
   } fits_header;

/* mar profile header always has 1024 characters */
typedef struct {
   CHAR8   text[1024];
   } mar_profile_header;

typedef union {
   xedar_aligned_header		xedar;
   photometrics_header		photometrics;
   xentronics_header_1		xentronics1;
   xentronics_header_2		xentronics2;
   raxis2_header		raxis2;
   fuji_pf_header		fuji_pf;
   mar300_header		mar300;
   mar345_header		mar345;
   mar_profile_header		mar_profile;
   filman_header		filman;
   IPLab_header			iplab;
   tv6_header			tv6;
   tiff_header			tiff;
   csma_header			csma;
   adsc_header			adsc;
   spectral_header		spectral;
   aligned_spectral_header	aligned_spectral;
   fits_header	                fits;
   } foreign_header;



/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern int write_foreign_frame(
#if NeedFunctionPrototypes
data_frame *framep, const char *filename, int format
#endif
);

#endif /* foreign_frame_h */
