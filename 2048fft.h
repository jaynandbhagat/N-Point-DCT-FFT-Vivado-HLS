#ifndef __2048FFT_H__
#define __2048FFT_H__

#include <math.h>
#include <complex>
#include <ap_fixed.h>

using namespace std;

#define N 2048
#define FFT_FIXED_TOTAL_BITS 32
#define FFT_FIXED_INT_BITS   10

typedef ap_fixed<FFT_FIXED_TOTAL_BITS, FFT_FIXED_INT_BITS> fixed_t;
typedef fixed_t data_t;
typedef complex<data_t> data_comp;

#include "2048fftvalues.h"  // Contains rev_2048[] and W[]

void FFT(float in_real[N], float out_real[N], float out_imag[N]);

#endif
