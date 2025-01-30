#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <limits.h>


#define MLX_ERROR 1
#define RED_PIXEL 0xFF0000

typedef struct s_z
{
    int z_min;
    int z_max;    
}   t_z;
typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    t_img img;
}   t_data;


void calculate_min_max_z(t_map_p *s, t_z *z_values) {
    z_values->z_min = INT_MAX;
    z_values->z_max = INT_MIN;

    for (int i = 0; i < s->dims.height; i++) {
        for (int j = 0; j < s->dims.width; j++) {
            if (s->map[i][j].z < z_values->z_min)
                z_values->z_min = s->map[i][j].z;
            if (s->map[i][j].z > z_values->z_max)
                z_values->z_max = s->map[i][j].z;
        }
    }
}

void calculate_offsets(t_map_p *s, t_offset *offsets) {
    int min_x = INT_MAX, max_x = INT_MIN;
    int min_y = INT_MAX, max_y = INT_MIN;

    // Find min/max coordinates of projected points
    for (int i = 0; i < s->dims.height; i++) {
        for (int j = 0; j < s->dims.width; j++) {
            int x = s->map[i][j].x;
            int y = s->map[i][j].y;
            
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
            if (y < min_y) min_y = y;
            if (y > max_y) max_y = y;
        }
    }

    // Calculate centering offsets
    offsets->x = (I_W / 2) - (max_x + min_x) / 2;
    offsets->y = (I_H / 2) - (max_y + min_y) / 2;
}

t_map isometric(int x, int y, int z) {
    t_map point;

    point.x = (x - y) * cos(0.523599);
    point.y = (x + y) * sin(0.523599) - z;
    point.z = z ;

    return point;
}



int	handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
    }
    return (0);
}

int get_color(int z, int z_min, int z_max)
{
    double ratio;
    int red;
    int green;
    int blue;

    if (z_min == z_max)
        return (0xFFFFFF);
    ratio = (double)(z - z_min) / (z_max - z_min);
    red = (int)(255 * ratio);
    green = (int)(255 * (1 - ratio));
    blue = 200;
    return ((red << 16) | (green << 8) | blue);
}

void  scaling (t_map_p *s, t_scale scale)
{
    for (int i = 0; i < s->dims.height; i++)
    {
        for (int j = 0; j < s->dims.width; j++)
        {
            s->map[i][j].x = j * scale.x  -  (scale.x/10);
            s->map[i][j].y = i * scale.y -  (scale.y/10);
            s->map[i][j].z = s->map[i][j].z  * s->map[i][j].z;
        }
    }
}

int main ()
{
    t_data data;
    t_map_p s;
    int fd = open("42.fdf",O_RDONLY | 0666);
    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, W_W, W_H, "My window");
        if (data.win_ptr == NULL)
        {
            free(data.win_ptr);
            return (MLX_ERROR);
        }
    data.img.img_ptr = mlx_new_image(data.mlx_ptr, I_W, I_H);
    data.img.img_data = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.size_line, &data.img.endian);
    mlx_key_hook(data.win_ptr,handle_keypress,&data);

    s = parssing(fd);

    t_scale scale;
    scale.x = (I_H / s.dims.height / 1.5) ;
    scale.y = (I_W / s.dims.width / 1.5) ;
    scale.z = scale.x / 4;

    if (scale.x < scale.y) 
        scale.y = scale.x;
    else
        scale.x = scale.y;

    int offset_x, offset_y ;
   // calculate_offsets_int(&s, scale, &offset_x, &offset_y);
    scaling(&s,scale); 
    
    t_z z_values ;
    calculate_min_max_z(&s, &z_values);

    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
           s.map[i][j] = isometric(s.map[i][j].x,s.map[i][j].y,s.map[i][j].z);
           s.map[i][j].colors = get_color(s.map[i][j].z, z_values.z_min, z_values.z_max);
          //  s.map[i][j].x += offset_x ;
            //s.map[i][j].y += offset_y ;
        }
    }
    t_offset offsets;

    calculate_offsets(&s, &offsets);
    
    for (int i = 0; i < s.dims.height; i++) {
    for (int j = 0; j < s.dims.width; j++) {
        s.map[i][j].x += offsets.x;
        s.map[i][j].y += offsets.y;
    }
}

    for (int i = 0; i < s.dims.height; i++)
    {
        for (int j = 0; j < s.dims.width; j++)
        {
            my_mlx_pixel_put(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i][j].colors);
            if (j + 1 < s.dims.width)
                draw_myline(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i][j + 1].x,s.map[i][j + 1].y,s.map[i][j].colors);
            if (i + 1 < s.dims.height)
               draw_myline(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i + 1][j].x,s.map[i + 1][j].y,s.map[i][j].colors);
        }
    }
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 0, 0);

    mlx_loop(data.mlx_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);

    // for (int i = 0; i < s.dims.height; i++)
    // {
    //     for (int j = 0; j < s.dims.width; j++)
    //     {
    //         printf("%d ",s.map[i][j].z);
    //     }
    //     printf("\n");
    // }
}
