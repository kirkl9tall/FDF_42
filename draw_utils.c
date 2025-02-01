#include "fdf.h"

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

t_map isometric(int x, int y, int z,int color, int no_color) {
    t_map point;

    point.x = (x - y) * cos(0.523599); // 30 degrees
    point.y = (x + y) * sin(0.523599) - z;  // 30 degrees
    point.z = z  ;
    point.colors = color; // Preserve the color
    point.no_color = no_color; 

    return point;
}



int	handle_keypress(int keysym, t_data *data)
{
    int i = 0;

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
            s->map[i][j].z *= scale.z /2.7;
        }
    }
}