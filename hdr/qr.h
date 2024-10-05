#ifndef QR_H
#define QR_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>


namespace qr {

  typedef enum {
    QR_MODEL_1,  // Original QR Code model
    QR_MODEL_2,  // Updated QR Code model (most common)
    MICRO_QR,    // Micro QR Code (smaller version)
    IQR,         // iQR Code (ISO/IEC 20830)
    SQRC,        // Secure QR Code
    FRAME_QR     // Frame QR (by Denso Wave)
  } qr_type_options;


  typedef enum {
    NUMERIC,
    ALPHANUMERIC,
    BINARY,
    KANJI
  } data_type_options;

  typedef struct {
    uint32_t grid_size;
    std::vector<int> bitstream;
    std::vector<std::vector<int>> matrix;
    qr_type_options qr_type;
    data_type_options data_type;
  } qr_code;


  qr_code init_qr(qr_type_options qr_type, data_type_options data_type);
  void insert_position_square(std::vector<std::vector<int>> &matrix, uint32_t bound_l, uint32_t bound_r, uint32_t bound_t, uint32_t bound_b);
  void encode_data(std::vector<int> bitstream, qr_code &generated_qr);
  void encode_data(std::vector<int> bitstream, std::vector<int> error_bitstream, qr_code &generated_qr);

  uint32_t init_qr_code_size(qr_type_options type);
}

#endif  // QR_H
