#ifndef ENCODE_ALPHANUMERIC_H
#define ENCODE_ALPHANUMERIC_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Function to encode an alphanumeric string into a vector of bits (integers 0 or 1)
std::vector<int> encode_alphanumeric(std::string alphanumeric);
std::vector<int> encode_error_protection(std::vector<int> bitstream);

#endif  // ENCODE_ALPHANUMERIC_H

