#include "fdf.h"

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
