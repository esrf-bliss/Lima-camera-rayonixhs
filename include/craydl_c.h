#ifdef  __cplusplus
#include "craydl.h"
else
#include <stdbool.h>
#endif


typedef void* Craydl_RxReturnStatus_t;
typedef void* Craydl_RxDetector_t;
typedef void* Craydl_CallbackConnection_t;

extern "C" {

//RxDetector
C_RxDetector_t  Craydl_RxDetector_Ctor(const char* config_path);
void Craydl_RxDetector_Dctor(C_RxDetector_t);

void Craydl_RxDetector_Open(C_RxDetector_t);
bool Craydl_RxDetector_GetDetectorID(C_RxDetector_t, const char* name, const char* serial_number);
bool Craydl_RxDetector_GetDetectorFirmwareID(C_RxDetector_t, const char* name, const char* version);

C_CallbackConnection_t Craydl_RegisterFrameCallback(C_RxDetector_t);

//RxReturnStatus
bool Craydl_RxReturnStatus_IsError(Craydl_RxReturnStatus_t);

}
