#include "2048fft.h"

void bitreverse(data_comp data_IN[N], data_comp data_OUT[N]) {
    for (int i = 0; i < N; i++) {
    #pragma HLS PIPELINE
        int index = rev_2048[i];
        data_OUT[i] = data_IN[index];
    }
}

void FFT0(int FFT_stage, int pass_check, int index_shift, int pass_shift,
          data_comp data_IN[N], data_comp data_OUT[N]) {
    int butterfly_span = 0, butterfly_pass = 0;

    for (int i = 0; i < N / 2; i++) {
    #pragma HLS PIPELINE
        int index = butterfly_span << index_shift;
        int Ulimit = butterfly_span + (butterfly_pass << pass_shift);
        int Llimit = Ulimit + FFT_stage;

        data_comp Product = W[index] * data_IN[Llimit];
        data_OUT[Llimit] = data_IN[Ulimit] - Product;
        data_OUT[Ulimit] = data_IN[Ulimit] + Product;

        if (butterfly_span < FFT_stage - 1) {
            butterfly_span++;
        } else if (butterfly_pass < pass_check - 1) {
            butterfly_span = 0;
            butterfly_pass++;
        } else {
            butterfly_span = 0;
            butterfly_pass = 0;
        }
    }
}

void FFT(float in_real[N], float out_real[N], float out_imag[N]) {

    data_comp data_1[N];
    data_comp data_2[N];

    for (int i = 0; i < N; i++) {
    #pragma HLS PIPELINE
        data_1[i] = data_comp((data_t)in_real[i], (data_t)0);
    }

    bitreverse(data_1, data_2);

    // 11 stages for 2048 = 2^11
    FFT0(1,     1024, 10, 1, data_2, data_1);
    FFT0(2,      512, 9,  2, data_1, data_2);
    FFT0(4,      256, 8,  3, data_2, data_1);
    FFT0(8,      128, 7,  4, data_1, data_2);
    FFT0(16,      64, 6,  5, data_2, data_1);
    FFT0(32,      32, 5,  6, data_1, data_2);
    FFT0(64,      16, 4,  7, data_2, data_1);
    FFT0(128,      8, 3,  8, data_1, data_2);
    FFT0(256,      4, 2,  9, data_2, data_1);
    FFT0(512,      2, 1, 10, data_1, data_2);
    FFT0(1024,     1, 0, 11, data_2, data_1);

    for (int i = 0; i < N; i++) {
    #pragma HLS PIPELINE
        out_real[i] = (float)data_1[i].real();
        out_imag[i] = (float)data_1[i].imag();
    }
}
