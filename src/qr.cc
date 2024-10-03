#include <vector>
#include <iostream>

#include "qr.h"


std::vector<std::vector<int>> init_qr(int grid_size){
  std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(grid_size, std::vector<int>(grid_size, 0));

  // square bounds
  uint32_t bound_l = 1;
  uint32_t bound_r = 9;

  uint32_t bound_t = 1;
  uint32_t bound_b = 9;

  insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);


  bound_l = grid_size - 9;
  bound_r = grid_size - 1;

  bound_t = 1;
  bound_b = 9;

  insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);


  bound_l = 1;
  bound_r = 9;

  bound_t = grid_size - 9;
  bound_b = grid_size - 1;

  insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);

  bound_l = grid_size - 9;
  bound_r = grid_size - 6;

  bound_t = grid_size - 9;
  bound_b = grid_size - 6;

  insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);

  return matrix;
}

void insert_position_square(std::vector<std::vector<int>> &matrix, uint32_t bound_l, uint32_t bound_r, uint32_t bound_t, uint32_t bound_b){
  for(uint32_t col = bound_l; col < bound_r; col++){
    for(uint32_t row = bound_t; row < bound_b; row++){
      if(row == bound_t || row == bound_b - 1){
        matrix[row][col] = 1;
      } else if (row != bound_t + 1 && row != bound_b - 2) {
        if(col != bound_l + 1 && col != bound_r - 2){
          matrix[row][col] = 1;
        }
      } else {
        if (col == bound_l || col == bound_r - 1){
          matrix[row][col] = 1;
        }
      }
    }
  }
}

