#ifndef goniostat_swP_h
#define goniostat_swP_h

/* A local function for each function to be performed on or by a goniostat */

static GoniostatType goniostat_type_sw(void);
static int find_goniostat_sw(GoniostatType type, char *device, int port, int number);
static int init_goniostat_sw(char * config_dir, char * log_dir, char * device, int port);
static int init_data_goniostat_sw(GoniostatValues *goniostat_values);
static int get_data_goniostat_sw(GoniostatValues *cg);
static int set_data_goniostat_sw(GoniostatValues *cg);
static int get_option_goniostat_sw(int option, void *argument);
static int set_option_goniostat_sw(int option, void *argument);
static int command_goniostat_sw(int option, void *argument);
static char *print_goniostat_sw(void);
static void load_goniostat_sw(void);
static int query_goniostat_sw(int);
static void set_positions_sw(int all);
static int query_positions_sw(void);
static void load_speeds_sw(void);
static void query_speeds_sw(void);
static int query_movings_sw(void);
static int query_limit_statuses_sw(void);
static void load_oscillations_sw(void);
static void query_oscillations_sw(void);
static void load_ok_flags_sw(void);
static int query_ok_flags_sw(void);
static int move_positions_conditional_sw(void);
static int move_positions_sw(void);
static int start_oscillations_sw(void);
static int stop_oscillations_sw(void);
static int restore_positions_sw(void);
static int open_goniostat_shutter_sw(void);
static int close_goniostat_shutter_sw(void);
static int query_goniostat_shutter_sw(void);
static void wait_goniostat_sw(void);
static int abort_goniostat_sw(void);
static int close_goniostat_sw(void);
static int validate_positions_sw(GoniostatValues *gvp, char *buffer, int buffer_size);
static int validate_positions_conditional_sw(GoniostatValues *gvp, char *buffer, int buffer_size);
static char *printf_goniostat_sw(char * format, ...);

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

#endif /* goniostat_swP_h */
