#include <gtk/gtk.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

int SQUARE_SIZE = 10;


std::vector<std::vector<int>> generate_random_matrix(int rows, int cols) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    std::srand(std::time(0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = std::rand() % 2;
        }
    }
    return matrix;
}

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
    int GRID_SIZE = 21;

    if (argc > 1) {
        GRID_SIZE = std::atoi(argv[1]);
        if (GRID_SIZE <= 0) {
            std::cerr << "Invalid grid size provided. Using default size of 21." << std::endl;
            GRID_SIZE = 21;
        }
    }

    SQUARE_SIZE = 900 / GRID_SIZE;

    gtk_init(&argc, &argv);

    std::vector<std::vector<int>> grid_matrix = generate_random_matrix(GRID_SIZE, GRID_SIZE);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Generated QR");
    gtk_window_set_default_size(GTK_WINDOW(window), GRID_SIZE * SQUARE_SIZE, GRID_SIZE * SQUARE_SIZE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, GRID_SIZE * SQUARE_SIZE, GRID_SIZE * SQUARE_SIZE);

    auto *data = new std::pair<std::vector<std::vector<int>>*, int>(&grid_matrix, GRID_SIZE);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), data);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    gtk_widget_show_all(window);
    gtk_main();

    delete data;

    return 0;
}

