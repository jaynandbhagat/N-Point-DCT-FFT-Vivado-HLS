#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "1024dct.h"

#define TOL 1e-4

int main() {
    int result = 0;

    // Arrays for input, output, and expected output
    float in_signal[DCT_LENGTH];
    float out_dct[DCT_LENGTH];
    float exp_dct[DCT_LENGTH];

    std::ifstream DCTfileIN("input.txt");     // Input file: 1024 float values (one per line)
    std::ifstream DCTfileEXP("expected.txt");      // Expected output file: 1024 float values

    if (!DCTfileIN || !DCTfileEXP) {
        std::cerr << "Failed to open input or expected output file." << std::endl;
        exit(-1);
    }

    // Read DCT input data from file
    for (int i = 0; i < DCT_LENGTH; i++) {
        DCTfileIN >> in_signal[i];
    }
    DCTfileIN.close();

    // Call DCT function
    dct(in_signal, out_dct);

    // Save the DCT output to a file (for debugging or verification)
    std::ofstream outputFile("out_dct.txt");
    if (!outputFile) {
        std::cerr << "Failed to open output file." << std::endl;
        exit(-1);
    }
    for (int i = 0; i < DCT_LENGTH; i++) {
        outputFile << out_dct[i] << std::endl;
    }
    outputFile.close();

    // Read the expected DCT output from file
    for (int i = 0; i < DCT_LENGTH; i++) {
        DCTfileEXP >> exp_dct[i];
    }
    DCTfileEXP.close();

    // Compare computed DCT output with the expected output
    for (int i = 0; i < DCT_LENGTH; i++) {
        float norm = std::abs(exp_dct[i] - out_dct[i]);
        if (norm > TOL) {
            result++;
            std::cout << "Mismatch at index " << i << ": Expected " << exp_dct[i]
                      << ", Got " << out_dct[i] << ", Norm: " << norm << std::endl;
        } else {
            std::cout << "Match at index " << i << ": Expected " << exp_dct[i]
                      << ", Got " << out_dct[i] << ", Norm: " << norm << std::endl;
        }
    }

    if (result == 0) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL: " << result << " errors" << std::endl;
    }

    return result;
}
