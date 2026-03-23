#ifndef MPPT_CONTROL_H
#define MPPT_CONTROL_H

#include "tmwtypes.h" // MATLAB 데이터형 호환을 위해 필수 [cite: 981]

// Ipv, Vpv를 입력받아 계산된 Vmpp를 포인터(*Vmpp)로 출력합니다. [cite: 625-633, 959]
extern void mppt_run(double Ipv, double Vpv, double *Vmpp);

#endif