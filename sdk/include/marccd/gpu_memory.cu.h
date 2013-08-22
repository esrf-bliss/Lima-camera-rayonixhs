#ifdef __cplusplus
    extern "C" {
#endif //__cplusplus

#ifndef GPU_MEMORY_CU_H
#define GPU_MEMORY_CU_H

#include <stdio.h> 

#include "frame.h"
#include "pvtstdio.h"
#include <sys/timeb.h>

int gpu_malloc(data_frame *, data_frame *, data_frame *, data_frame *);

#ifdef __cplusplus
    }
#endif //GPU_MEMORY_CU_H

#endif //__cplusplus
