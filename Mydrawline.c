#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->img_ptr + (y * img->size_line + x * (img->bits_per_pixel / 8));
    *(int *)pixel = color;
}

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
void initial_step(t_img *img ,t_pos start,int p,t_step step,int color)
{
    if (p < 0)
     start.x += step.x;
     else 
     {
        start.x +=step.x;
        start.y +=step.y;
     }
     img_pix_put(img,start.x, start.y, color);
}
void nega_decision(t_img *img ,t_line line,int color)
{
    line.start.x += line.step.x;
    img_pix_put(img,line.start.x, line.start.y, color);
}
void posi_decision(t_img *img ,t_line line,int color)
{
    line.start.x += line.step.x;
    line.start.y+=line.step.y;
    img_pix_put(img,line.start.x, line.start.y, color);
}
void draw_myline (t_img *img ,int x1,int y1,int x2,int y2,int color)
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
    img_pix_put(img,line.start.x, line.start.y, color);
        while (line.start.x != line.end.x || line.start.y != line.end.y) 
        {
            if (line.p < 0) {
                line.start.x += line.step.x;
               img_pix_put(img,line.start.x, line.start.y, color);
                line.p += 2 * line.diff.y;
            } else {
                line.start.x += line.step.x;
                line.start.y += line.step.y;
                img_pix_put(img,line.start.x, line.start.y, color);
                line.p += (2 * line.diff.y) - (2 * line.diff.x);
            }
        }
}