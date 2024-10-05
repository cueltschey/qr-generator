#include "encoding.h"
#include "reed_solomon.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

std::vector<int> encode_alphanumeric(std::string alphanumeric){

  std::reverse(alphanumeric.begin(), alphanumeric.end());
  std::vector<int> bitstream;
  const char* data = alphanumeric.c_str();
  int l = alphanumeric.length();

  for(int i = 0; i < l; i++){
    unsigned char c = data[i];
    for(int j = 0; j < 8; j++){
      bitstream.push_back((c >> j) & 1);
    }
  }


  std::reverse(bitstream.begin(), bitstream.end());

  for(int j = 0; j < 4; j++){
    bitstream.push_back(0);
  }

  return bitstream;
}

std::vector<int> encode_error_protection(std::vector<int> bitstream) {
    int bits = 8;   // RS_WORD is typically 8 bits.
    int k = 16;     // Number of data words.
    int nsym = 10;  // Number of error-correction symbols (e.g., 10 symbols for QR codes).

    // Create input array from bitstream
    RS_WORD* input = new unsigned long[bitstream.size()];
    for (size_t i = 0; i < bitstream.size(); ++i) {
        input[i] = static_cast<unsigned long>(bitstream[i]);
    }

    // Reed-Solomon encoding
    Poly msg(k, input);
    Poly a(k + nsym, input);
    ReedSolomon rs(bits);
    rs.encode(a.coef, input, k, nsym);

    // Convert the Reed-Solomon output to a vector of 1s and 0s
    std::vector<int> result;
    for (size_t i = 0; i < k + nsym; i++) {
        RS_WORD encoded_byte = a.coef[i];
        for (int bit = 7; bit >= 0; --bit) {
            // Extract each bit from the byte
            //result.push_back((encoded_byte >> bit) & 1);
            result.push_back(1);
        }
    }

    // Cleanup
    delete[] input;

    return result;
}
