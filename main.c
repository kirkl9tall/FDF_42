#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

// #define W_W 600
// #define W_H 300
// #define MLX_ERROR 1
// #define RED_PIXEL 0xFF0000

// typedef struct s_data
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     t_img img;
// }   t_data;

// int	handle_keypress(int keysym, t_data *data)
// {
//     if (keysym == XK_Escape)
//     {
//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
//         data->win_ptr = NULL;
//     }
//     return (0);
// }

// int	render(t_data *data)
// {
//     if (data->win_ptr != NULL)
//         mlx_pixel_put(data->mlx_ptr, data->win_ptr, W_W / 2, W_H / 2, RED_PIXEL);
//     return (0);
// }


// int main (int argc , char **argv)
// {
//     t_data data;

//     data.mlx_ptr = mlx_init();
//     if (data.mlx_ptr == NULL)
//         return (MLX_ERROR);
//     data.win_ptr = mlx_new_window(data.mlx_ptr, W_W, W_H, "My window");
//         if (data.win_ptr == NULL)
//         {
//             free(data.win_ptr);
//             return (MLX_ERROR);
//         }

//     mlx_loop_hook(data.mlx_ptr,&render,&data);
//     mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

//     data.img.img_ptr = mlx_new_image(data.mlx_ptr, W_H, W_H);


//     mlx_loop(data.mlx_ptr);
//     mlx_destroy_display(data.mlx_ptr);
//     free(data.mlx_ptr);

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
    t_img img ;
    void * win_ptr;
    void * mlx_ptr;
    int x_w = 1000;
    int y_w = 800;
    int x_i = 600;
    int y_i = 600;

    

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,x_w,y_w,"test map !");

   scal = s = parssing(open("10-2.fdf", O_RDONLY , 0666));

   img.img_ptr = mlx_new_image(mlx_ptr,x_i,y_i);


    t_scale scale;

    scale.x = x_w / s.dims.width;
    scale.y = y_w / s.dims.height;

    if (scale.x < scale.y) 
        scale.y = scale.x;
    else
        scale.x = scale.y;
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
    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
            if (j + 1 < s.dims.width)
            {
                draw_myline(win_ptr,mlx_ptr,s.map[i][j].x,s.map[i][j].y,s.map[i][j + 1].x,s.map[i][j + 1].y,0xFFFFFF);
            }
            if (i + 1 < s.dims.height)
            {
                draw_myline(win_ptr,mlx_ptr,s.map[i][j].x,s.map[i][j].y,s.map[i + 1][j].x,s.map[i + 1][j].y,0xFFFFFF);
            }
        }
    }

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
    mlx_loop(mlx_ptr);
}
