#include <vector>
#include <iostream>
#include <algorithm>

#include "qr.h"

namespace qr {
  qr_code init_qr(qr_type_options qr_type, data_type_options data_type){

    qr_code generated_qr;
    generated_qr.qr_type = qr_type;
    generated_qr.grid_size = init_qr_code_size(generated_qr.qr_type);
    generated_qr.data_type = data_type;

    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(generated_qr.grid_size, std::vector<int>(generated_qr.grid_size, 0));


    // square bounds
    uint32_t bound_l = 0;
    uint32_t bound_r = 7;

    uint32_t bound_t = 0;
    uint32_t bound_b = 7;

    insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);


    bound_l = generated_qr.grid_size - 7;
    bound_r = generated_qr.grid_size;

    bound_t = 0;
    bound_b = 7;

    insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);


    bound_l = 0;
    bound_r = 7;

    bound_t = generated_qr.grid_size - 7;
    bound_b = generated_qr.grid_size;

    insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);

    bound_l = generated_qr.grid_size - 9;
    bound_r = generated_qr.grid_size - 4;

    bound_t = generated_qr.grid_size - 9;
    bound_b = generated_qr.grid_size - 4;

    insert_position_square(matrix, bound_l, bound_r, bound_t, bound_b);


    // draw alternating format lines
    bool alternating_bit = true;
    uint32_t indent = 6;

    for(uint32_t i = 8; i < generated_qr.grid_size - 8; i++){
      matrix[i][indent] = alternating_bit? 1: 0;
      matrix[indent][i] = alternating_bit? 1: 0;
      alternating_bit = !alternating_bit;
    }

    // reserved bit
    matrix[generated_qr.grid_size - 8][8] = 1;

    // data type prefix

    std::vector<int> data_prefix;

    switch (generated_qr.data_type) {
      case NUMERIC:
        data_prefix = {0,0,0,1};
        break;
      case ALPHANUMERIC:
        data_prefix = {0,0,1,0};
        break;
      case BINARY:
        data_prefix = {0,1,0,0};
        break;
      case KANJI:
        data_prefix = {1,0,0,0};
        break;
      default:
        data_prefix = {0,0,0,1};
        break;
    }
    int index = 0;
    for(int i = generated_qr.grid_size - 2; i < generated_qr.grid_size; i++){
      for(int j = generated_qr.grid_size - 2; j < generated_qr.grid_size; j++){
        matrix[i][j] = data_prefix[index];
        index++;
      }
    }

    uint8_t data_length = 26;
    std::vector<uint8_t> data_length_binary;


    for(uint8_t i = 0; i < 8; i++){
      data_length_binary.push_back((data_length >> i) & 1);
    }

    std::reverse(data_length_binary.begin(), data_length_binary.end());

    matrix[generated_qr.grid_size - 3][generated_qr.grid_size - 1] = data_length_binary[0];

    index = 1;

    for(uint8_t i = generated_qr.grid_size - 3; i > generated_qr.grid_size - 6; i--){
      matrix[i][generated_qr.grid_size - 2] = data_length_binary[index];
      index++;
      matrix[i - 1][generated_qr.grid_size - 1] = data_length_binary[index];
      index++;
    }


    generated_qr.matrix = matrix;
    return generated_qr;
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


  uint32_t init_qr_code_size(qr_type_options type) {
    switch(type) {
      case QR_MODEL_1:
        return 21;
      case QR_MODEL_2:
        return 25;
      case MICRO_QR:
        return 11;
      case IQR:
        return 33;
      case SQRC:
        return 33;
      case FRAME_QR:
        return 35;
      default:
        return 21;
    }
  }


  void encode_data(std::vector<int> bitstream, std::vector<int> error_bitstream, qr_code &generated_qr){
    generated_qr.bitstream = bitstream;

    uint32_t x = generated_qr.grid_size - 7;
    uint32_t y = generated_qr.grid_size - 1;
    // true is up, false is down
    bool direction = true;

    bool wrap_triggered = false;


    for(uint32_t bit_index = 0; bit_index + 1 < generated_qr.bitstream.size(); bit_index += 2){
      if(
          (y >= generated_qr.grid_size - 9 && y <= generated_qr.grid_size - 4) 
          &&
          (x >= generated_qr.grid_size - 9 && x < generated_qr.grid_size - 4)
          ){
        if(y - 1 < generated_qr.grid_size - 9){
          generated_qr.matrix[x][y - 1] = generated_qr.bitstream[bit_index];
          bit_index -= 1;
        } else {
          bit_index -= 2;
        }
      } else{
        generated_qr.matrix[x][y] = generated_qr.bitstream[bit_index];
        generated_qr.matrix[x][y - 1] = generated_qr.bitstream[bit_index + 1];
      }

      // wrap if encountering edge or position square
      if(
          (x <= 9 && (y >= generated_qr.grid_size - 7 || y <= 7) 
           || x >= generated_qr.grid_size - 1 
           || x <= 0)
          && !wrap_triggered
          ){
        wrap_triggered = true;
        y -= 2;
        direction = !direction;
      } else{
        wrap_triggered = false;
      }
      if(wrap_triggered){
        continue;
      }
      if(direction){
        x--;
      } else{
        x++;
      }
    }


    for(uint32_t bit_index = 0; bit_index + 1 < error_bitstream.size(); bit_index += 2){
      if(
          (y >= generated_qr.grid_size - 9 && y <= generated_qr.grid_size - 4) 
          &&
          (x >= generated_qr.grid_size - 9 && x < generated_qr.grid_size - 4)
          ){
        if(y - 1 < generated_qr.grid_size - 9){
          generated_qr.matrix[x][y - 1] = error_bitstream[bit_index];
          bit_index -= 1;
        } else {
          bit_index -= 2;
        }
      } else{
        generated_qr.matrix[x][y] = error_bitstream[bit_index];
        generated_qr.matrix[x][y - 1] = error_bitstream[bit_index + 1];
      }

      // wrap if encountering edge or position square
      if(
          ((x <= 7 || x >= generated_qr.grid_size - 8) && (y >= generated_qr.grid_size - 7 || y <= 7) 
           || x >= generated_qr.grid_size - 1 
           || x <= 0) 
          && !wrap_triggered
          ){
        wrap_triggered = true;
        std::cout << y << " : " << x << std::endl;
        if(y <= 8){
          x = 7;
        }
        y -= 2;
        direction = !direction;
      } else{
        wrap_triggered = false;
      }
      if(wrap_triggered){
        continue;
      }
      if(direction){
        x--;
      } else{
        x++;
      }
    }
  }
}


