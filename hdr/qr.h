#ifndef QR_H
#define QR_H

#include <vector>
#include <iostream>

// Function to generate QR matrix with position squares
std::vector<std::vector<int>> init_qr(int grid_size);

void insert_position_square(std::vector<std::vector<int>> &matrix, uint32_t bound_l, uint32_t bound_r, uint32_t bound_t, uint32_t bound_b);

#endif  // QR_H

