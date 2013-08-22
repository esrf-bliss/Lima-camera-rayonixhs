/***********************************************************************
 *
 * mar345: marglobals.h
 *
 * Copyright by:        Dr. Claudio Klein
 *                      X-ray Research GmbH, Hamburg
 *
 * Version:     1.0
 * Date:        16/01/1997
 *
 ***********************************************************************/

#define MAX_MODE 	8
#define MAX_SET 	4

#define OUT_SPIRAL	0
#define OUT_MAR		1
#define OUT_IMAGE	2

typedef struct  {
        int add;
        int val;
} STRONG;


#ifdef MAR_GLOBAL
#define EXT
#else
#define EXT extern
#endif
#ifdef MAR_STATIC_CLOBALS
#undef EXT
#define EXT static
#endif

EXT int		mar_number;
EXT int         mar_mode;
EXT int         mar_par1;
EXT int         mar_par2;

EXT char	buf[2048], str[1024];

EXT char	working_dir[128];
EXT char	marhelp_dir[128];

EXT char	config_file[128];
EXT char	output_file[128];
EXT char	save_file[128];
EXT char	scanner_no[8];

EXT char	spiral_file[128];
EXT char	image_file[128];
EXT char	msg_file[128];

EXT FILE	*fpout;
EXT FILE	*fpmsg;
EXT char	*trntable;

EXT int		fdnd;
EXT int		debug;

/*
 * The following are status indicators passed to GUI
 */

EXT	float	stat_pixelsize;
EXT	float	stat_xray_units;

EXT	float	com_kV;
EXT	float	com_mA;
EXT	float	com_slitx;
EXT	float	com_slity;
EXT	float	com_dist;
EXT     float   com_theta;
EXT     float   com_chi;

EXT	float	com_phibeg;
EXT	float	com_phiend;
EXT	float	com_dphi;

EXT     float   com_omebeg;
EXT     float   com_omeend;
EXT     float   com_dome;

EXT     int     com_phiosc;
EXT     int     com_omeosc;

EXT     float   com_dosebeg;                                 
EXT     float   com_doseend;                                 
EXT     float   com_doseavg;                                 
EXT     float   com_dosesig;                                 
EXT     float   com_dosemin;                                 
EXT     float   com_dosemax;                                 
EXT     int     com_dosen;                                   
                                    
EXT	float	com_time;
EXT	float	com_units;
EXT	float	com_intensity;
EXT	float	com_polar;

EXT	float	com_wavelength;
EXT	float	com_multiplier;
EXT	float	com_pixelsize;
EXT	float	com_diam;
EXT	int	com_mode;
EXT	int	com_format;
EXT	int	com_size;
EXT	int 	com_scanmode;
EXT	char	com_use_spiral;

EXT	char	stat_scanmode;
EXT	int 	stat_scanner_op;
EXT	int 	stat_scanner_msg;
EXT	int 	stat_scanner_control;
EXT	int 	stat_xray_shutter;
EXT	int	stat_output;
EXT	int 	stat_xform_msg;
EXT	int 	stat_size;
EXT	int 	stat_format;

EXT	char	com_filter[80];
EXT	char	com_source[80];
EXT	char	com_dir[80];
EXT	char	com_root[80];
EXT	char	com_remark[80];
EXT	char	com_file[80];

/*
 * The following are counters, variables, etc.  used during data collection
 */

EXT 	int	nb_size;
EXT	int	netcontrol;
EXT	int	mar_cmd;

EXT	int	dcop;
EXT	int	dc_stop;
EXT	float	delta;	
EXT	float	sum_xray_units;

EXT	int	fdmar;

/*
 * The following are variables read from config file
 */

EXT     int     cur_mode;
EXT     short	cur_size;
EXT     short	cur_diameter;
EXT	short	cur_nfrm;
EXT     float	cur_pixelsize;
EXT     float	cur_intensmin;
EXT     int     cur_scantime;



#ifdef MAR_GLOBAL

unsigned short 		i2_image[3450*3450];
unsigned char  		ch_image[3450*3450];

int	nstrong=0;
int	nsat=0;
int    	verbose     = 0;
char   	keep_spiral = 0;

#else

EXT	char    keep_spiral;
EXT	char    big_scanner;
/* EXT	int     verbose;*/

#endif

