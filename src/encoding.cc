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
  return bitstream;
}

std::vector<int> encode_error_protection(std::vector<int> bitstream){

	int bits = 8, k = 16, nsym = 10;
  RS_WORD* input = new unsigned long[bitstream.size()];
  RS_WORD* output = new unsigned long[bitstream.size()];

  for (size_t i = 0; i < bitstream.size(); ++i) {
      input[i] = static_cast<unsigned long>(bitstream[i]);
  }
	Poly msg(k, input);
	Poly a(k + nsym, input);
	ReedSolomon rs(bits);
	rs.encode(a.coef, input, k, nsym);

  std::vector<int> result;
  for(size_t i = 0; i < bitstream.size(); i++){
    result.push_back(static_cast<int> (a.coef[i]));
  }
  delete[] input;
  delete[] output;

  return result;
}
