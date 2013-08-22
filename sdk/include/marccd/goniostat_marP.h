#ifndef goniostat_marP_h
#define goniostat_marP_h

#define TIMEOUT_SECS	5

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

#endif /* goniostat_marP_h */
