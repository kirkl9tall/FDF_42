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
void free_map (t_map_p *s)
{
    int i;

    i = 0;
    if (!s || !s->map) 
        return;
    while(i<s-> dims.height)
    {
        if (s->map[i])
            free (s->map[i]);
        i++;
    }
     free(s->map);
    s->map = NULL;
}

void holishiiit (int fd)
{
    t_data data;
    t_map_p s;
    t_scale scale;
    t_offset offsets;
    t_z z_values ;

    initialize_data(&data);
    mlx_key_hook(data.win_ptr,handle_keypress,&data);
    s = parssing(fd);
    scaler(&scale, &s);
    scaling(&s,scale); 
    iso(&s);
    calculate_offsets(&s, &offsets);
    add_offset(&s, &offsets);
    calculate_min_max_z(&s, &z_values);
    coloring(&s, &z_values);
    draw_lines(&data, &s);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 0, 0);
    free_map(&s);
    mlx_loop(data.mlx_ptr);
    free(data.mlx_ptr);
}
