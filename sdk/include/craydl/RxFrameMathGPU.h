#ifndef RX_FRAME_MATH_GPU_H
#define RX_FRAME_MATH_GPU_H

#include <stdint.h>

namespace craydl {

#define DATATYPE_BUFFER int32_t

void device_query_gpu(int verbose, int device);

void mem_info_gpu(size_t *used, size_t *free = NULL, size_t *total = NULL);

void *malloc_gpu(size_t size);

bool free_gpu(void *buffer);

bool copy_to_gpu(const void *host_buffer, size_t size, void *gpu_buffer);

bool copy_from_gpu(const void *gpu_buffer, size_t size, void *host_buffer);

bool stat_ctb_gpu(int n_fast, int n_slow, int minimum_value, int maximum_value, const void *correction_table, int *nused_p, int *nbelow_p, int *nabove_p, int *min_p, int *max_p, float *mean_p, float *stdev_p);

template <class PIXELTYPE> bool stat_frame_gpu(int n_fast, int n_slow, int minimum_value, int maximum_value, const PIXELTYPE *input_data, int *nused_p, int *nbelow_p, int *nabove_p, int *min_p, int *max_p, float *mean_p, float *stdev_p);

template <class PIXELTYPE> bool copy_frame_gpu(int n_fast, int n_slow, const PIXELTYPE *input_data, PIXELTYPE *output_data);

template <class PIXELTYPE> bool interlace_frame_gpu(int n_fast, int n_slow, int nfastmodules, int nslowmodules, int deinterlace_code, const PIXELTYPE *input_data, PIXELTYPE *output_data);

template <class PIXELTYPE> bool deinterlace_frame_gpu(int n_fast, int n_slow, int nfastmodules, int nslowmodules, int deinterlace_code, const PIXELTYPE *input_data, PIXELTYPE *output_data);

template <class PIXELTYPE> bool subtract_frame_gpu(int n_fast, int n_slow, int min, int max, int input_bias, int output_bias, const PIXELTYPE *minuend_data, const PIXELTYPE *subtrahend_data, PIXELTYPE *difference_data);

template <class PIXELTYPE> bool divide_frame_gpu(int n_fast, int n_slow, int min, int max, int input_bias, int output_bias, float mean_divisor, const PIXELTYPE *dividend_data, const PIXELTYPE *divisor_data, PIXELTYPE *quotient_data);

template <class PIXELTYPE> bool reorient_frame_gpu(int n_fast, int f_slow, int transformation_code, const PIXELTYPE *input_data, PIXELTYPE *output_data);

bool initialize_buffer32_gpu(int n_fast, int n_slow, int value, DATATYPE_BUFFER *data);

template <class PIXELTYPE> bool apply_correction_gpu(int n_fast, int n_slow, int bias_in, int bias_out, int min, int max, int bad_pixel, int max_fraction, int unused_pixel_flag, float mean_flatfield, const void *correction_table, const PIXELTYPE *input_data, const PIXELTYPE *background_data, DATATYPE_BUFFER *result_buffer);

template <class PIXELTYPE> bool rescale_correction_result32_to_frame16_gpu(int n_fast, int n_slow, int min, int max, int bad_pixel, int max_fraction, int unused_flag, int bias_out, const DATATYPE_BUFFER *input_data, PIXELTYPE *ouput_data);

template <class PIXELTYPE> bool flatfield_correction_result32_gpu(int n_fast, int n_slow, int unused_flag, int bad_pixel_flag, int max_input_value, int max_output_value, int bad_ff, float mean_ff, const DATATYPE_BUFFER *input_data, const PIXELTYPE *flatfield_data, DATATYPE_BUFFER *output_data);

}

#endif /* RX_FRAME_MATH_GPU_H */
