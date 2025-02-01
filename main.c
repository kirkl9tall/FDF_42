#include "fdf.h"

void initialize_data(t_data *data)
{
    data->mlx_ptr = mlx_init();

    if (data->mlx_ptr == NULL)
    {
        data->error = MLX_ERROR;
        return ;
    }
    data->win_ptr = mlx_new_window(data->mlx_ptr, W_W, W_H, "My window");
            if (data->win_ptr == NULL)
        {
            free(data->win_ptr);
            data->error = MLX_ERROR;
            return ;
        }
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, I_W, I_H);
    data->img.img_data = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.size_line, &data->img.endian);
    return;
}
void scaler (t_scale *scale, t_map_p *s)
{
    scale->x = (I_H / s->dims.height / 1.5) ;
    scale->y = (I_W / s->dims.width / 1.5) ;
    scale->z = scale->x ;

    if (scale->x < scale->y) 
        scale->y = scale->x;
    else
        scale->x = scale->y;
}
void iso (t_map_p *s)
{
    for (int i = 0; i < s->dims.height; i++)
    {
        for (int j = 0; j < s->dims.width; j++)
        {
            s->map[i][j] = isometric(s->map[i][j].x,s->map[i][j].y,s->map[i][j].z,s->map[i][j].colors, s->map[i][j].no_color);
        }
    }
}

    void add_offset(t_map_p *s, t_offset *offsets)
    {
        for (int i = 0; i < s->dims.height; i++)
        {
            for (int j = 0; j < s->dims.width; j++)
            {
                s->map[i][j].x += offsets->x;
                s->map[i][j].y += offsets->y;
            }
        }
    }

    void coloring(t_map_p *s, t_z *z_values)
    {
        for (int i = 0; i < s->dims.height; i++)
        {
            for (int j = 0; j < s->dims.width; j++)
            {   
                if (s->map[i][j].no_color)
                {
                     s->map[i][j].colors = get_color(s->map[i][j].z, z_values->z_min, z_values->z_max);
                }
            }
        }
    }
    void draw_lines(t_data *data, t_map_p *s)
    {
        for (int i = 0; i < s->dims.height; i++)
        {
            for (int j = 0; j < s->dims.width; j++)
            {
                my_mlx_pixel_put(&data->img,s->map[i][j].x,s->map[i][j].y,s->map[i][j].colors);
                if (j + 1 < s->dims.width)
                {
                    draw_myline(&data->img,s->map[i][j].x, s->map[i][j].y ,s->map[i][j + 1].x, s->map[i][j + 1].y,s->map[i][j].colors, s->map[i][j + 1].colors);
                }
                if (i + 1 < s->dims.height)
                {
                    draw_myline(&data->img,s->map[i][j].x, s->map[i][j].y,s->map[i + 1][j].x, s->map[i + 1][j].y,s->map[i][j].colors, s->map[i + 1][j].colors);
                }
            }
        }
    }

void holishiiit (int fd)
{
    t_data data;
    t_map_p s;

    initialize_data(&data);
    mlx_key_hook(data.win_ptr,handle_keypress,&data);
    s = parssing(fd);
///////////////////////////// apply scale /////////////////////
    t_scale scale;
    scaler(&scale, &s);
    scaling(&s,scale); 
    ///////// iso  projection  //////////////////////////
    iso(&s);
        //////////// offset  the  map  to the  center  of  the  window  ////////////////////////
    t_offset offsets;
    calculate_offsets(&s, &offsets);
    add_offset(&s, &offsets);
    t_z z_values ;
    calculate_min_max_z(&s, &z_values);
    ///////////// calculate the  color  of  the  pixel  //////////////////////////
    coloring(&s, &z_values);

        /////// draw the  map  //////////////////////////
    draw_lines(&data, &s);
    // for (int i = 0; i < s.dims.height; i++)
    // {
    //     for (int j = 0; j < s.dims.width; j++)
    //     {
    //         my_mlx_pixel_put(&data.img,s.map[i][j].x,s.map[i][j].y,s.map[i][j].colors);
    //         if (j + 1 < s.dims.width)
    //         {
    //             draw_myline(&data.img,s.map[i][j].x, s.map[i][j].y ,s.map[i][j + 1].x, s.map[i][j + 1].y,s.map[i][j].colors, s.map[i][j + 1].colors);
    //         }
    //         if (i + 1 < s.dims.height)
    //         {
    //             draw_myline(&data.img,s.map[i][j].x, s.map[i][j].y,s.map[i + 1][j].x, s.map[i + 1][j].y,s.map[i][j].colors, s.map[i + 1][j].colors);
    //         }
    //     }
    // }
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 0, 0);

    mlx_loop(data.mlx_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}
