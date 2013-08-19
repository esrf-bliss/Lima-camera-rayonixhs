#ifndef goniostat_marnetv1P_h
#define goniostat_marnetv1P_h

#define TIMEOUT_SECS	5

#define	CMD_NULL     		0
#define	CMD_MOVE_DIST		1
#define	CMD_MOVE_PHI 		2
#define	CMD_MOVE_OMEGA 		3
#define	CMD_MOVE_CHI   		4
#define	CMD_MOVE_THETA		5
#define CMD_ABORT               6
#define CMD_COLLECT             7
#define CMD_SHUTTER             8
#define	CMD_CHANGE_MODE		9
#define	CMD_SCAN		10
#define	CMD_ERASE		11
#define CMD_RESET		12
#define	CMD_SET      		13
#define	CMD_TEST 		14
#define	CMD_LOADFILE 		15
#define	CMD_LISTEN		16
#define	CMD_QUIT  		17
#define	CMD_ION_CHAMBER		18
#define CMD_QUERY_STATUS	19	
#define CMD_SET_OPTION		20
#define MAX_CMD			20	

#define	CMD_MODE_MOVE_REL	0
#define	CMD_MODE_MOVE_ABS	1
#define	CMD_MODE_MIN     	2
#define	CMD_MODE_MAX     	3
#define	CMD_MODE_SET     	4

#define	CMD_MODE_CLOSE		0
#define	CMD_MODE_OPEN 		1

#define	CMD_MODE_DISABLE	0
#define	CMD_MODE_ENABLE 	1

#define	CMD_MODE_DOSE		0
#define	CMD_MODE_TIME		1

#define CMD_MODE_STATUS_TYPE	1
#define    STATUS_TYPE_BINARY	0
#define    STATUS_TYPE_ASCII	1

#define CMD_MODE_OUTPUT_ENABLE	2
#define    OUTPUT_CONSOLE	0x1
#define    OUTPUT_SERIAL	0x2
#define    OUTPUT_SPY_SERIAL	0x4
#define    OUTPUT_SPY_NETWORK	0x8

/* A local function for each function to be performed on or by a goniostat */

/* Semi-private methods */
static GoniostatType goniostat_type_P(void);
static int find_goniostat_P(GoniostatType type, char *device, int port, int number);
static int init_goniostat_P(char * config_dir, char * log_dir, char * device, int port);
static int init_data_goniostat_P(GoniostatValues *goniostat_values);
static int get_data_goniostat_P(GoniostatValues *cg);
static int set_data_goniostat_P(GoniostatValues *cg);
static int get_option_goniostat_P(int option, void *argument);
static int set_option_goniostat_P(int option, void *argument);
static int command_goniostat_P(int option, void *argument);
static char *print_goniostat_P(void);
static void load_goniostat_P(void);
static int query_goniostat_P(int);
static void set_positions_P(int all);
static int query_positions_P(void);
static void load_speeds_P(void);
static void query_speeds_P(void);
static int query_movings_P(void);
static int query_limit_statuses_P(void);
static void load_oscillations_P(void);
static void query_oscillations_P(void);
static void load_ok_flags_P(void);
static int query_ok_flags_P(void);
static int move_positions_conditional_P(void);
static int move_positions_P(void);
static int start_oscillations_P(void);
static int stop_oscillations_P(void);
static int restore_positions_P(void);
static int open_goniostat_shutter_P(void);
static int close_goniostat_shutter_P(void);
static int query_goniostat_shutter_P(void);
static void wait_goniostat_P(void);
static int abort_goniostat_P(void);
static int close_goniostat_P(void);
static int validate_positions_P(GoniostatValues *gvp, char *buffer, int buffer_size);
static int validate_positions_conditional_P(GoniostatValues *gvp, char *buffer, int buffer_size);
static char *printf_goniostat_P(char * format, ...);



/* Truly private methods */

static void set_position(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static double query_position(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static void load_speed(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static double query_speed(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int query_moving(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int query_limit_status(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static void load_oscillation(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static double query_oscillation(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int load_ok_flag(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int query_ok_flag(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int move_position(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int start_oscillation(
#ifdef NeedFunctionPrototypes
axis_parameters *axis
#endif
);

static int init_gon_cont (
#if NeedFunctionPrototypes
void
#endif
);

static int close_gon_cont (
#if NeedFunctionPrototypes
void
#endif
);


#if defined(_SVID_SOURCE) && !defined(_BSD_COMPAT) && !defined(_BSD_SIGNALS)
#if defined(_SGI_SOURCE)
static void gon_cont_timeout();
#else
static int gon_cont_timeout(
#if NeedFunctionPrototypes
void
#endif
);
#endif
#elif defined(_BSD_SOURCE) || defined(_BSD_COMPAT) || defined(_BSD_SIGNALS)
static void gon_cont_timeout(
#if NeedFunctionPrototypes
void
#endif
);
#else
static void gon_cont_timeout();
#endif

#endif /* goniostat_marnetv1P_h */
