#include "encoding.h"
#include <iostream>
#include <vector>
#include <string>

std::vector<int> encode_alphanumeric(const std::string &alphanumeric){
  std::vector<int> bitstream;
  const char* data = alphanumeric.c_str();
  int l = alphanumeric.length();

  for(int i = 0; i < l; i++){
    unsigned char c = data[i];
    for(int j = 0; j < 8; j++){
      bitstream.push_back((c >> j) & 1);
    }
  }

  return bitstream;
}
