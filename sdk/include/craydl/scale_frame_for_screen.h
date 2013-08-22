
#include <pthread.h>

#include "frame.h"

#if 0
void lock_colors_rx(void);

void unlock_colors_rx(void);

void set_color_scaling_source_rx(int scaling_source, int min, int max);

void get_color_scaling_source_rx(int *scaling_source, int *min, int *max);

void determine_frame_rendering_limits_rx(data_frame *framep, long *render_min, long *render_max);

void scale_colors_rx( int scale_type, int startarray, int endarray, int minvalue, int maxvalue, unsigned long **colortable, unsigned long *colors, int ncolors, double gamma);

int render_frame(data_image *imagep, data_frame *framep, double zoom, int zoom_x, int zoom_y, int transformation, unsigned long *colortable, int sampling);

void graphics_to_data(data_image *imagep, int *dx, int *dy, int gx, int gy);

void data_to_graphics(data_image *imagep, int *gx, int *gy, int dx, int dy);

void set_data_to_graphics_transformation (data_image *imagep, int render_transformation, int data_xorigin, int data_yorigin, int image_xorigin, int image_yorigin, double zoom);
#endif

int scale_frame_for_screen(data_frame *dataframep, data_image *imagep, int size_fast, int size_slow, int depth, int *render_min_in, int *render_max_in);
