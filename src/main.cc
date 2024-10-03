#include <gtk/gtk.h>

const int GRID_SIZE = 8;      // Number of squares per row/column
const int SQUARE_SIZE = 50;   // Size of each square in pixels

// Callback to handle drawing the grid
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            // Alternate between black and white squares
            if ((row + col) % 2 == 0) {
                cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);  // Black
            } else {
                cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);  // White
            }
            // Draw the square
            cairo_rectangle(cr, col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
            cairo_fill(cr);
        }
    }
    return FALSE;
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Grid of Squares");
    gtk_window_set_default_size(GTK_WINDOW(window), GRID_SIZE * SQUARE_SIZE, GRID_SIZE * SQUARE_SIZE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a drawing area widget
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, GRID_SIZE * SQUARE_SIZE, GRID_SIZE * SQUARE_SIZE);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);

    // Add the drawing area to the window
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Show the window and all child widgets
    gtk_widget_show_all(window);

    // Enter the GTK main loop
    gtk_main();

    return 0;
}

