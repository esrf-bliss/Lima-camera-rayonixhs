#include "RayonixHsBinCtrlObj.h"

using namespace lima;
using namespace lima::RayonixHs;

BinCtrlObj::BinCtrlObj(Camera *cam)
   : m_cam(cam) {
    
    DEB_CONSTRUCTOR();
}

BinCtrlObj::~BinCtrlObj() {
    DEB_DESTRUCTOR();
}

void BinCtrlObj::setBin(const Bin& bin) {
    DEB_MEMBER_FUNCT();    
    m_cam->setBin(bin);
}

void BinCtrlObj::getBin(Bin& bin) {
    DEB_MEMBER_FUNCT();    
    m_cam->getBin(bin);
}

void BinCtrlObj::checkBin(Bin& bin) {
    DEB_MEMBER_FUNCT();    
    m_cam->checkBin(bin);
}
