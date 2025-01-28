#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <limits.h>

#define W_W 1200
#define W_H 900
#define I_W 800
#define I_H 650
#define MLX_ERROR 1
#define RED_PIXEL 0xFF0000

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    t_img img;
}   t_data;


void calculate_offsets_int(t_map_p *s, t_scale scale, int *offset_x, int *offset_y) {
    int min_x = INT_MAX, max_x = INT_MIN;
    int min_y = INT_MAX, max_y = INT_MIN;

    // Precompute integer approximations for scaling and angles
    int cos_angle = 866; // cos(30°) ≈ 0.866 scaled by 1000
    int sin_angle = 500; // sin(30°) = 0.5 scaled by 1000
    int z_scale = scale.x / 4;

    for (int i = 0; i < s->dims.height; i++) {
        for (int j = 0; j < s->dims.width; j++) {
            int x = j * scale.x;
            int y = i * scale.y;
            int z = s->map[i][j].z * z_scale;

            // Integer-based isometric projection
            int iso_x = ((x - y) * cos_angle) / 1000;
            int iso_y = ((x + y) * sin_angle) / 1000 - z;

            // Update min/max bounds
            if (iso_x < min_x) min_x = iso_x;
            if (iso_x > max_x) max_x = iso_x;
            if (iso_y < min_y) min_y = iso_y;
            if (iso_y > max_y) max_y = iso_y;
        }
    }

    // Calculate offsets to center the image
    *offset_x = (I_W / 2) - (max_x + min_x) / 2;
    *offset_y = (I_H / 2) - (max_y + min_y) / 2;
}

t_map isometric(int x, int y, int z) {
    t_map point;

    point.x = (x - y) * cos(0.523599);
    point.y = (x + y) * sin(0.523599) - z;
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

    int offset_x = 2 ;int  offset_y = 2;
    calculate_offsets_int(&s, scale, &offset_x, &offset_y);

    // for (int i = 0; i < s.dims.height; i++)
    // {
    //     for (int j = 0; j < s.dims.width; j++)
    //     {
    //          s.map[i][j] = isometric(s.map[i][j].x,s.map[i][j].y,s.map[i][j].z);
    //     }
    // }



    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
            s.map[i][j].x *= scale.x;
            s.map[i][j].y *= scale.y;
            my_mlx_pixel_put(&data.img,s.map[i][j].x,s.map[i][j].y,0xFFFFFF);
        }
    }

    ////////////////////////////////////////////////////////////
    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
            if (j + 1 < s.dims.width)
            {
                draw_myline(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i][j + 1].x,s.map[i][j + 1].y,0xFFFFFF);
            }
            if (i + 1 < s.dims.height)
            {
               draw_myline(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i + 1][j].x,s.map[i + 1][j].y,0xFFFFFF);
            }
        }
    }



    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 250, 150);

    mlx_loop(data.mlx_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}
