#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>


#define W_W 1200
#define W_H 900
#define I_W 700
#define I_H 600
#define MLX_ERROR 1
#define RED_PIXEL 0xFF0000

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    t_img img;
}   t_data;

void calculate_offsets(t_map_p *s, t_scale scale, double *offset_x, double *offset_y) {
    double min_x = INFINITY, max_x = -INFINITY;
    double min_y = INFINITY, max_y = -INFINITY;

    // Find the min and max coordinates after isometric projection
    for (int i = 0; i < s->dims.height; i++) {
        for (int j = 0; j < s->dims.width; j++) {
            double x = j * scale.x;
            double y = i * scale.y;
            double z = s->map[i][j].z * (scale.x / 4);  // Reduced z scale for better visualization
            
            // Calculate isometric coordinates without centering
            double iso_x = (x - y) * cos(0.523599);
            double iso_y = (x + y) * sin(0.523599) - z;
            
            min_x = fmin(min_x, iso_x);
            max_x = fmax(max_x, iso_x);
            min_y = fmin(min_y, iso_y);
            max_y = fmax(max_y, iso_y);
        }
    }

    // Calculate offsets to center the image
    *offset_x = (I_W / 2) - (max_x + min_x) / 2;
    *offset_y = (I_H / 2) - (max_y + min_y) / 2;
}

t_map isometric(double x, double y, double z) {
    t_map point;
    // Apply isometric projection
    point.x = (x - y) * cos(0.523599) + I_W / 2;  // 30 degrees in radians
    point.y = (x + y) * sin(0.523599) - z + I_H / 2;
    point.z = z;

    return point;
}

int	handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
    }
    // if (keysym == XK_r)
    // {
    //     color_screen(&data->img, 0xFF0000);
    // }
    //     if (keysym == XK_g)
    // {
    //         color_screen(&data->img,0x00FF00);

    // }
    // if (keysym == XK_b)
    // {
    //     color_screen(&data->img,0x0000FF);

    // }
   // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
    return (0);
}

int main ()
{
    t_data data;
    t_map_p s;
    int fd = open("10-2.fdf",O_RDONLY | 0666);
    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, W_W, W_H, "My window");
        if (data.win_ptr == NULL)
        {
            free(data.win_ptr);
            return (MLX_ERROR);
        }
///////////////////////////////// image put in the  screen  /////////////////////////////////
    data.img.img_ptr = mlx_new_image(data.mlx_ptr, I_W, I_H);
    data.img.img_data = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.size_line, &data.img.endian);
    mlx_key_hook(data.win_ptr,handle_keypress,&data);

    s = parssing(fd);

     t_scale scale;

    scale.x = I_H / s.dims.height;
    scale.y = I_W / s.dims.width;

    if (scale.x < scale.y) 
        scale.y = scale.x;
    else
        scale.x = scale.y;

    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
            s.map[i][j].x *= scale.x;
            s.map[i][j].y *= scale.y;
          //  s.map[i][j] = isometric(s.map[i][j].x,s.map[i][j].y,s.map[i][j].z);
          
         //   if (s.map[i][j].x >= 0 && s.map[i][j].x < I_W && s.map[i][j].y >= 0 && s.map[i][j].y < I_H) 
                 my_mlx_pixel_put(&data.img,s.map[i][j].x,s.map[i][j].y,0xFFFFFF);
        }
    }
    ////////////////////////////////////////////////////////////////
    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
            if (j + 1 < s.dims.width)
            {
             //   if (s.map[i][j].x >= 0 && s.map[i][j].x < I_W && s.map[i][j].y >= 0 && s.map[i][j].y < I_H)
                draw_myline(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i][j + 1].x,s.map[i][j + 1].y,0xFFFFFF);
            }
            if (i + 1 < s.dims.height)
            {
              //  if (s.map[i][j].x >= 0 && s.map[i][j].x < I_W && s.map[i][j].y >= 0 && s.map[i][j].y < I_H)
               draw_myline(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i + 1][j].x,s.map[i + 1][j].y,0xFFFFFF);
            }
        }
    }
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 250, 150);

    mlx_loop(data.mlx_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}
