#include "mppt_control.h"
#include <math.h> // fabs() 함수 사용을 위해 추가

static double Vprev = 0;
static double Pprev = 0;
static double Vmpp_out = 100; 

void mppt_run(double Ipv, double Vpv, double *Vmpp) {
    double Pnow = Vpv * Ipv;
    double dP = Pnow - Pprev;
    double dV = Vpv - Vprev;
    
    // --- [여기서부터 수정 및 추가] ---
    double K = 0.01;      // 기울기 민감도 (실험을 통해 0.001 ~ 0.1 사이 조정)
    double MAX_STEP = 2.0; // 한 번에 너무 크게 튀는 것 방지 (안전 장치)
    double MIN_STEP = 0.1; // 정점 근처에서 너무 안 움직이는 것 방지
    
    double step;
    
    if (dV != 0) {
        // P-V 곡선의 기울기(dP/dV)에 비례하여 보폭 결정
        step = K * fabs(dP / dV); 
        
        // 보폭이 너무 크거나 작지 않게 제한 (Saturation)
        if (step > MAX_STEP) step = MAX_STEP;
        if (step < MIN_STEP) step = MIN_STEP;
    } else {
        step = MIN_STEP; // 전압 변화가 없으면 최소 보폭 유지
    }
    // --- [수정 끝] ---

    // Perturbation and Observation (P&O) 로직 (기존과 동일하지만 변하는 step 사용)
    if (dP > 0) {
        if (dV > 0) Vmpp_out += step;
        else Vmpp_out -= step;
    } else if (dP < 0) {
        if (dV > 0) Vmpp_out -= step;
        else Vmpp_out += step;
    }

    *Vmpp = Vmpp_out;
    Vprev = Vpv;
    Pprev = Pnow;
}