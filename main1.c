#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

t_step choice (t_pos start, t_pos end)
{
        t_step guid;

        printf("start.x %d    start.y   %d   end.x  %d end.y   %d \n", start.x, start.y, end.x, end.y);
        guid.y= 0; guid.x= 0;
        if  (start.y > end.y)
            guid.y = -1;
        else if (end.y > start.y)
            guid.y = 1;

        if  (start.x > end.x)
            guid.x = -1;
        else if (end.x > start.x)
            guid.x = 1;
        printf("guid.x ==  %d \n ",guid.x);
        printf("guid.y == %d   \n",guid.y);
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

int main(void)
{
    void * win_ptr;
    void * mlx_ptr;
    void * img_ptr;
    int x_w = 1000;
    int y_w = 800;
    int hight = 15;
    int width = 15;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,x_w,y_w,"test map !");

    int x1 = 90 ; int y1 = 95; int x2 = 400; int y2 = 250;
    mlx_pixel_put(mlx_ptr,win_ptr,x1,y1,0xFFFFFF);
    mlx_pixel_put(mlx_ptr,win_ptr,x2,y2,0xFFFFFF);
    draw_myline(win_ptr,mlx_ptr,x1,y1,x2,y2,0xFFFFFF);

    
////////////////////////////////////

// int t = open("10-2.fdf", O_RDONLY , 0666);
//         if (t < 0) return 1;

//     dada (t);
////**************************************************************************************** */
    // int i = 1;
    // int j = 1;
    
    // t_scale scale;

    // scale.x = x_w / width;   
    // scale.y = y_w / hight;

    // if (scale.x < scale.y) {
    //     scale.y = scale.x;  
    // } 
    // else
    // {
    //     scale.x = scale.y;
    // }

    // int x;
    // int y;
    // while (i <= hight)
    // {
    //     j = 0;
    //     while (j  <= width)
    //     {
    //           x = j * scale.x;
    //           y = i * scale.y; 
    //         mlx_pixel_put(mlx_ptr,win_ptr,x,y,0xFFFFFF);
    //         j++;
    //     }
    //     i++;
    // }
    

    mlx_loop(mlx_ptr);
}