#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

// int dada (int fd)
// {
//     int x;
//     x = 0;
//     int y = 0;
//     char *buffer;

//      while (x= read(fd,buffer,1)<=0)
//      {

//         y += x;
//      }
//      printf("%d\n",y);
//      return (y);
// }

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
////////////////////////////////////

int t = open("10-2.fdf", O_RDONLY , 0666);
        if (t < 0) return 1;

    dada (t);

    int i = 1;
    int j = 1;
    
    t_scale scale;

    scale.x = x_w / width;   
    scale.y = y_w / hight;

    if (scale.x < scale.y) {
        scale.y = scale.x;  
    } 
    else
    {
        scale.x = scale.y;
    }

    int x;
    int y;
    while (i <= hight)
    {
        j = 0;
        while (j  <= width)
        {
              x = j * scale.x;
              y = i * scale.y; 
            mlx_pixel_put(mlx_ptr,win_ptr,x,y,0xFFFFFF);
            j++;
        }
        i++;
    }
    

    mlx_loop(mlx_ptr);
}