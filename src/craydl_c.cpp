#include "craydl_c.h"

using namespace craydl;

C_RxDetector_t  Craydl_RxDetectorCtor(const char* config_path)
{
    return reinterpret_cast<void*>(new RxDetector(config_path));
}

void Craydl_RxDetectorDctor(C_RxDetector_t obj)
{
    delete reinterpret_cast<RxDetector *>(obj);
}

void Craydl_RxDetectorOpen(C_RxDetector_t obj)
{
    RxDetector self = reinterpret_cast<RxDetector *>(obj);
    self->Open();
}

bool Craydl_RxDetector_GetDetectorID(C_RxDetector_t obj, const char* name, const char* serial_number)
{
    RxDetector self = reinterpret_cast<RxDetector *>(obj);

    std::string tmp_name, tmp_serial_number;
    bool res = self->GetDetectorID(tmp_name, tmp_serial_number).IsError();

    strcpy(name, tmp_name);
    strcpy(name, tmp_name);

    return res;
}

bool Craydl_RxDetector_GetDetectorFirmwareID(C_RxDetector_t obj, const char* name, const char* version)
{
    RxDetector self = reinterpret_cast<RxDetector *>(obj);

    std::string tmp_name, tmp_version;
    bool res = self->GetDetectorFirmwareID(tmp_name, tmp_version).IsError();

    strcpy(name, tmp_name);
    strcpy(version, tmp_version);

    return res;
}
