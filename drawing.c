#include "fdf.h"    

void my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= I_W || y < 0 || y >= I_H)
        return;
    dst = fdf->img.img_data + (y * fdf->img.size_line + x * (fdf->img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
void draw_myline(t_fdf *fdf, t_point start, t_point end)
{
    t_line line;
    int steep = abs(end.y - start.y) > abs(end.x - start.x);
    int tmp;

    // Swap x and y if the line is steep
    if (steep)
    {
        tmp = start.x;
        start.x = start.y;
        start.y = tmp;
        tmp = end.x;
        end.x = end.y;
        end.y = tmp;
    }
    // Ensure start.x is less than end.x
    if (start.x > end.x)
    {
        tmp = start.x;
        start.x = end.x;
        end.x = tmp;
        tmp = start.y;
        start.y = end.y;
        end.y = tmp;
        tmp = start.color;
        start.color = end.color;
        end.color = tmp;
    }
    // Calculate differences
    line.diff.x = abs(end.x - start.x);
    line.diff.y = abs(end.y - start.y);
    int err = line.diff.x / 2;
    // Determine the y-step direction
    int ystep;
    if (start.y < end.y)
        ystep = 1;
    else
        ystep = -1;

    int total_steps = line.diff.x;
    int current_step = 0;
    // Draw the line
    while (start.x <= end.x)
    {
        float ratio;
        if (total_steps != 0)
            ratio = (float)current_step / total_steps;
        else
            ratio = 0.5f;

        int color = interpolate_color(start.color, end.color, ratio);

        if (steep)
            my_mlx_pixel_put(fdf, start.y, start.x, color);
        else
            my_mlx_pixel_put(fdf, start.x, start.y, color);

        err -= line.diff.y;
        if (err < 0)
        {
            start.y += ystep;
            err += line.diff.x;
        }
        start.x++;
        current_step++;
    }
}


void draw_lines(t_fdf *fdf)
{   
    int i = -1;
    while (++i < fdf->height) {
        int j = -1;
        while (++j < fdf->width) 
        {
            my_mlx_pixel_put(fdf, fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j].color);
            if (j+1 < fdf->width)
                draw_myline(fdf, fdf->map[i][j], fdf->map[i][j+1]);
            if (i+1 < fdf->height)
                draw_myline(fdf, fdf->map[i][j], fdf->map[i+1][j]);
         }
     }
}