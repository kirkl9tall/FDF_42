#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

t_step choice (t_pos start, t_pos end)
{
        t_step guid;
        guid.y= 0; guid.x= 0;
        if  (start.y > end.y)
            guid.y = -1;
        else if (end.y > start.y)
            guid.y = 1;
        else if  (start.y == end.y)
            guid.y = 0;

        if  (start.x > end.x)
            guid.x = -1;
        else if (end.x > start.x)
            guid.x = 1;
        else if  (start.x == end.x)
            guid.x = 0;
    return (guid);
}
void initial_step(void *mlx_ptr,void *win_ptr,t_pos start,int p,t_step step,int color)
{
    if (p < 0)
     start.x += step.x;
     else 
     {
        start.x +=step.x;
        start.y +=step.y;
     }
     mlx_pixel_put(mlx_ptr,win_ptr,start.x,start.y,color);
}
void nega_decision(void *mlx_ptr,void *win_ptr,t_line line,int color)
{
    line.start.x += line.step.x;
    mlx_pixel_put(mlx_ptr,win_ptr,line.start.x,line.start.y,color);
}
void posi_decision(void *mlx_ptr,void *win_ptr,t_line line,int color)
{
    line.start.x += line.step.x;
    line.start.y+=line.step.y;
    mlx_pixel_put(mlx_ptr,win_ptr,line.start.x,line.start.y,color);
}
void draw_myline (void *win_ptr, void *mlx_ptr ,int x1,int y1,int x2,int y2,int color)
{
    t_line line;

    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    line.diff.x = abs(line.end.x - line.start.x);
    line.diff.y = abs(line.end.y - line.start.y);
    line.step = choice(line.start,line.end);
    line.p = (2*line.diff.y) - line.diff.x;
    mlx_pixel_put(mlx_ptr, win_ptr, line.start.x, line.start.y, color);
        while (line.start.x != line.end.x || line.start.y != line.end.y) 
        {
            if (line.p < 0) {
                line.start.x += line.step.x;
                mlx_pixel_put(mlx_ptr, win_ptr, line.start.x, line.start.y, color);
                line.p += 2 * line.diff.y;
            } else {
                line.start.x += line.step.x;
                line.start.y += line.step.y;
                mlx_pixel_put(mlx_ptr, win_ptr, line.start.x, line.start.y, color);
                line.p += (2 * line.diff.y) - (2 * line.diff.x);
            }
        }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void put_pixel_to_img(t_img *img, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= 1000 || y >= 800)
        return; 

    int pos = (y * img->size_line) + (x * (img->bits_per_pixel / 8));
    *(int *)(img->img_data + pos) = color;
}

void draw_mylinee(t_img *img, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 || y1 != y2)
    {
        put_pixel_to_img(img, x1, y1, color);

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}