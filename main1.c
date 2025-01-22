#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

typedef struct  s_pos
{
    int x;
    int y;
}   t_pos;
typedef struct s_step
{
    int x;
    int y;
}   t_step;
typedef struct s_diff
{
    int  x;
    int y;
}t_diff;

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
void nega_decision(void *mlx_ptr,void *win_ptr,t_pos start,t_step step,int color)
{
    start.x += step.x;
    mlx_pixel_put(mlx_ptr,win_ptr,start.x,start.y,color);
}
void posi_decision(void *mlx_ptr,void *win_ptr,t_pos start,t_step step,int color)
{
    start.x += step.x;
    start.y+=step.y;
    mlx_pixel_put(mlx_ptr,win_ptr,start.x,start.y,color);
}
void draw_myline (void *win_ptr, void *mlx_ptr ,int x1,int y1,int x2,int y2,int color)
{
    t_pos start;
    t_pos end;
    t_step step;
    t_diff d;
    int p;

    start.x = x1;
    start.y = y1;
    end.x = x2;
    end.y = y2;
    
    d.x = abs(end.x - start.x);
    d.y = abs(end.y - start.y);
    step = choice(start,end);
    p = (2*d.y) - d.x;
    mlx_pixel_put(mlx_ptr, win_ptr, start.x, start.y, color);
    //initial_step(win_ptr,mlx_ptr,start,p,step,color);
    while ((start.x != end.x) && (start.y != end.y))
    {
        if (p < 0)
        {
            nega_decision(win_ptr,mlx_ptr,start,step,color);
            p = p + 2*d.y;
        }
        else
        { 
            posi_decision(win_ptr,mlx_ptr,start,step,color);
            p += p +((2*d.y)- (2*d.x));
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