#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

t_map  isometric(int x, int y, int z)
{
t_map point;

 point.x = (x - y) * cos(0.523599);
 point.y = (x + y) * sin(0.523599) - z;
 point.z = z;
 return (point);
}

int main (int argc , char **argv)
{
    t_map_p s;
    t_map_p scal;
    void * win_ptr;
    void * mlx_ptr;
    void * img_ptr;
    int x_w = 1000;
    int y_w = 800;
    int x_i = 600;
    int y_i = 600;

    

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,x_w,y_w,"test map !");

   scal = s = parssing(open("10-2.fdf", O_RDONLY , 0666));

    t_scale scale;

    scale.x = x_w / s.dims.width;
    scale.y = y_w / s.dims.height;

    if (scale.x < scale.y) 
        scale.y = scale.x;
    else
        scale.x = scale.y;
    // for (int i = 0; i < s.dims.height; i++)
    // {
    //     for (int j = 0; j < s.dims.width; j++)
    //     {

    //         s.map[i][j].x *= scale.x ;
    //         s.map[i][j].y *= scale.y ;
    //         s.map[i][j] = isometric(s.map[i][j].x,s.map[i][j].y,s.map[i][j].z);
    //         mlx_pixel_put(mlx_ptr,win_ptr,s.map[i][j].x,s.map[i][j].y,0xFFFFFF);
    //     }
    // }
    // for (int i = 0; i < s.dims.height; i++)
    // {
    //     for (int j = 0; j < s.dims.width; j++)
    //     {
    //         if (j + 1 < s.dims.width)
    //         {
    //             draw_myline(win_ptr,mlx_ptr,s.map[i][j].x,s.map[i][j].y,s.map[i][j + 1].x,s.map[i][j + 1].y,s.map[i][j].colors);
    //         }
    //         if (i + 1 < s.dims.height)
    //         {
    //             draw_myline(win_ptr,mlx_ptr,s.map[i][j].x,s.map[i][j].y,s.map[i + 1][j].x,s.map[i + 1][j].y,s.map[i][j].colors);
    //         }
    //     }
    // }

    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
            s.map[i][j].x *= scale.x ;
            s.map[i][j].y *= scale.y ;
            s.map[i][j] = isometric(s.map[i][j].x,s.map[i][j].y,s.map[i][j].z);
            mlx_pixel_put(mlx_ptr,win_ptr,s.map[i][j].x,s.map[i][j].y,0xFFFFFF);
        }
    }
    mlx_loop(mlx_ptr);
}