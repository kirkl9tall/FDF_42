#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

// Function to apply rotation around the Z-axis
t_pos rotate_z(int x, int y, double angle) {
    t_pos result;
    result.x = x * cos(angle) - y * sin(angle);
    result.y = x * sin(angle) + y * cos(angle);
    return result;
}

// Function to apply isometric projection
t_pos isometric(int x, int y, int z) {
    t_pos result;
    double angle = 0.523599; // 30 degrees in radians
    result.x = (x - y) * cos(angle);
    result.y = (x + y) * sin(angle) - z;
    return result;
}

// Function to draw a line between two points
void draw_line(void *mlx_ptr, void *win_ptr, t_pos start, t_pos end, int color) {
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx_ptr, win_ptr, start.x, start.y, color);
        if (start.x == end.x && start.y == end.y) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

void render_map(t_map **map, int width, int height, void *mlx_ptr, void *win_ptr) {
    // Scaling factors to fit the map in the window
    int scale_x = 20;
    int scale_y = 20;

    // Offset to center the map in the window
    int offset_x = 500;
    int offset_y = 300;

    // Rotation angle (optional)
    double rotation_angle = 0.0; // No rotation by default

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Scale the points
            int x = j * scale_x;
            int y = i * scale_y;
            int z = map[i][j].z * scale_x; // Scale height as well

            // Apply rotation (optional)
            t_pos rotated = rotate_z(x, y, rotation_angle);

            // Apply isometric projection
            t_pos iso = isometric(rotated.x, rotated.y, z);

            // Offset to center the map
            iso.x += offset_x;
            iso.y += offset_y;

            // Draw the point (optional, as lines will cover the points)
            mlx_pixel_put(mlx_ptr, win_ptr, iso.x, iso.y, map[i][j].colors);

            // Draw horizontal line to the right neighbor
            if (j + 1 < width) {
                int x2 = (j + 1) * scale_x;
                int y2 = i * scale_y;
                int z2 = map[i][j + 1].z * scale_x;

                t_pos rotated2 = rotate_z(x2, y2, rotation_angle);
                t_pos iso2 = isometric(rotated2.x, rotated2.y, z2);
                iso2.x += offset_x;
                iso2.y += offset_y;

                draw_line(mlx_ptr, win_ptr, iso, iso2, map[i][j].colors);
            }

            // Draw vertical line to the bottom neighbor
            if (i + 1 < height) {
                int x2 = j * scale_x;
                int y2 = (i + 1) * scale_y;
                int z2 = map[i + 1][j].z * scale_x;

                t_pos rotated2 = rotate_z(x2, y2, rotation_angle);
                t_pos iso2 = isometric(rotated2.x, rotated2.y, z2);
                iso2.x += offset_x;
                iso2.y += offset_y;

                draw_line(mlx_ptr, win_ptr, iso, iso2, map[i][j].colors);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Initialize MiniLibX
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 1000, 800, "FDF");

    // Parse the map file (assume this is already done)
    int width = 10; // Example width
    int height = 10; // Example height
    t_map **map = parse_map("test.fdf", &width, &height);

    // Render the map
    render_map(map, width, height, mlx_ptr, win_ptr);

    // Enter the MiniLibX event loop
    mlx_loop(mlx_ptr);

    // Free memory (not shown here)
    return 0;
}