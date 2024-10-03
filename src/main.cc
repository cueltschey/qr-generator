#include <gtk/gtk.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "encoding.h"
#include "qr.h"

// smallest QR code

#define SQUARE_SIZE 35


gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    auto* data = static_cast<std::pair<std::vector<std::vector<int>>*, int>*>(user_data);
    std::vector<std::vector<int>>* matrix = data->first;
    int grid_size = data->second;

    for (int row = 0; row < grid_size; ++row) {
        for (int col = 0; col < grid_size; ++col) {
            if ((*matrix)[row][col] == 1) {
                cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
            } else {
                cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
            }
            cairo_rectangle(cr, col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
            cairo_fill(cr);
        }
    }
    return FALSE;
}

int main(int argc, char *argv[]) {

    // Arguments
    if(argc < 2){
      std::cerr << "Usage: qr-gen <string to encode>" << std::endl;
      return 1;
    }

    std::string input_alphanumeric = argv[1];

    std::cout << "Encoded Bytes: ";
    std::vector<int> encoded_bits = encode_alphanumeric(input_alphanumeric);
    for(int i = 0; i < (int)encoded_bits.size(); i++){
      std::cout << encoded_bits[i];
      if((i + 1) % 8 == 0){
        std::cout << " ";
      }
    }
    std::cout << std::endl;

    gtk_init(&argc, &argv);

    qr::qr_code generated_qr = qr::init_qr(qr::qr_type_options::QR_MODEL_2, qr::data_type_options::ALPHANUMERIC);

    encode_data(encoded_bits, generated_qr);


    // initialize GUI
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Generated QR");
    gtk_window_set_default_size(GTK_WINDOW(window), generated_qr.grid_size * SQUARE_SIZE, generated_qr.grid_size * SQUARE_SIZE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, generated_qr.grid_size * SQUARE_SIZE, generated_qr.grid_size * SQUARE_SIZE);

    auto *data = new std::pair<std::vector<std::vector<int>>*, int>(&generated_qr.matrix, generated_qr.grid_size);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), data);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    gtk_widget_show_all(window);
    gtk_main();

    delete data;

    return 0;
}

