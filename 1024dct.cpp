#include "1024dct.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void dct(float in[DCT_LENGTH], float out[DCT_LENGTH]) {

#pragma HLS INTERFACE s_axilite register port=in
#pragma HLS INTERFACE s_axilite register port=out
#pragma HLS INTERFACE s_axilite port=return

    const float scale0 = sqrtf(1.0f / DCT_LENGTH);
    const float scale = sqrtf(2.0f / DCT_LENGTH);

    for (int k = 0; k < DCT_LENGTH; k++) {
        float sum = 0.0f;
        for (int n = 0; n < DCT_LENGTH; n++) {
            sum += in[n] * cosf(M_PI * (2 * n + 1) * k / (2.0f * DCT_LENGTH));
        }
        out[k] = (k == 0) ? sum * scale0 : sum * scale;
    }
}
