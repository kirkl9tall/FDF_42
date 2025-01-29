#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= I_W || y < 0 || y >= I_H)
        return;
    dst = img->img_data + (y * img->size_line + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

t_step choice(t_pos start, t_pos end)
{
    t_step guid;
    guid.y = 0;
    guid.x = 0;
    if (start.y > end.y)
        guid.y = -1;
    else if (end.y > start.y)
        guid.y = 1;

    if (start.x > end.x)
        guid.x = -1;
    else if (end.x > start.x)
        guid.x = 1;
    return guid;
}

void draw_myline(t_img *img, int x1, int y1, int x2, int y2, int color)
{
    t_line line;
    int steep = abs(y2 - y1) > abs(x2 - x1);

    if (steep) {
        // Swap x and y coordinates
        int tmp;
        tmp = x1; x1 = y1; y1 = tmp;
        tmp = x2; x2 = y2; y2 = tmp;
    }

    if (x1 > x2) {
        // Swap start and end points
        int tmp;
        tmp = x1; x1 = x2; x2 = tmp;
        tmp = y1; y1 = y2; y2 = tmp;
    }

    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    line.diff.x = abs(line.end.x - line.start.x);
    line.diff.y = abs(line.end.y - line.start.y);
    line.step = choice(line.start, line.end);
    int err = line.diff.x / 2;
    int ystep = (y1 < y2) ? 1 : -1;

    while (line.start.x <= line.end.x) {
        if (steep) {
            my_mlx_pixel_put(img, line.start.y, line.start.x, color);
        } else {
            my_mlx_pixel_put(img, line.start.x, line.start.y, color);
        }

        err -= line.diff.y;
        if (err < 0) {
            line.start.y += ystep;
            err += line.diff.x;
        }
        line.start.x++;
    }
}

/*
    The problem with handling steep lines in your current implementation is likely due to the Bresenham's line algorithm not 
    being correctly adjusted for cases where the slope is greater than 1. When the line is steep,
     the increments should happen in the y-axis rather than the x-axis.

Explanation:
Steepness Check:

Determine if the line is steep by comparing the absolute differences between y and x coordinates.
If the line is steep, swap the x and y coordinates for both start and end points.
 This ensures that the algorithm increments along the longer axis.Coordinate Swapping:

Ensure that x1 is always less than x2 by swapping the start and end points if necessary. This simplifies the loop condition.
Drawing Loop:

Use the modified Bresenham's algorithm to plot points. If the line is steep, plot the points using swapped coordinates.
Error Calculation:

Adjust the error term and y-coordinate appropriately to handle the steepness.
By implementing these changes, the function will correctly handle steep lines and ensure that all pixels are plotted 
in the correct order.


*/

