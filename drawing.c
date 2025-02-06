#include "fdf.h"    

void prepare_line_coordinates(t_point *start, t_point *end, int *steep)
{
    int tmp;

    *steep = abs(end->y - start->y) > abs(end->x - start->x);

    if (*steep)
    {
        tmp = start->x;
        start->x = start->y;
        start->y = tmp;
        tmp = end->x;
        end->x = end->y;
        end->y = tmp;
    }
    if (start->x > end->x)
    {
        tmp = start->x;
        start->x = end->x;
        end->x = tmp;
        tmp = start->y;
        start->y = end->y;
        end->y = tmp;
        tmp = start->color;
        start->color = end->color;
        end->color = tmp;
    }
}
void karawatcha(t_line_tools * line_tools , t_point *start, t_point *end, int steep, t_line line, t_fdf *fdf)
{
    line_tools->ratio = (float)line_tools->current_step / line_tools->total_steps;
    line_tools->color = interpolate_color(start->color, end->color, line_tools->ratio);
    if (steep)
        my_mlx_pixel_put(fdf, start->y, start->x, line_tools->color);
    else
        my_mlx_pixel_put(fdf, start->x, start->y, line_tools->color);
    line_tools->err -= line.diff.y;
    if (line_tools->err < 0)
    {
        start->y += line_tools->ystep;
        line_tools->err += line.diff.x;
    }
    start->x++;
    line_tools->current_step++;

}
void draw_line_pixel(t_fdf *fdf, t_point start, t_point end, int steep, t_line line)
{
    t_line_tools line_tools;

    line_tools.total_steps = line.diff.x;
    line_tools.current_step = 0;
    line_tools.err = line.diff.x / 2;
    line_tools.ystep = (start.y < end.y) ? 1 : -1;
    while (start.x <= end.x)
    {
        karawatcha(&line_tools, &start, &end, steep, line, fdf);
    }
}
void draw_myline(t_fdf *fdf, t_point start, t_point end)
{
    t_line line;
    int steep;

    prepare_line_coordinates(&start, &end, &steep);
    line.diff.x = abs(end.x - start.x);
    line.diff.y = abs(end.y - start.y);
    draw_line_pixel(fdf, start, end, steep, line);
}

void draw_lines(t_fdf *fdf)
{   
    int i = -1;
    while (++i < fdf->height) {
        int j = -1;
        while (++j < fdf->width) 
        {
            my_mlx_pixel_put(fdf, fdf->mapv[i][j].x , fdf->mapv[i][j].y, fdf->mapv[i][j].color);
            if (j+1 < fdf->width)
                draw_myline(fdf, fdf->mapv[i][j] , fdf->mapv[i][j+1]);
            if (i+1 < fdf->height)
                draw_myline(fdf, fdf->mapv[i][j], fdf->mapv[i+1][j]);
         }
     }
}