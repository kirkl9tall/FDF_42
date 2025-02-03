#include "fdf.h"

void scaler_ofsv (t_fdf *fdf)
{
    fdf->scale.x = (I_H / fdf->height / 2) ;
    fdf->scale.y = (I_W / fdf->width / 2) ;
    fdf->scale.z = fdf->scale.x ;

    if (fdf->scale.x < fdf->scale.y) 
        fdf->scale.y = fdf->scale.x;
    else
        fdf->scale.x = fdf->scale.y;
    
    fdf->ofsset_value.x_min = INT_MAX;
    fdf->ofsset_value.y_min = INT_MAX;
    fdf->ofsset_value.x_max = INT_MIN;
    fdf->ofsset_value.y_max = INT_MIN;
    
}

void  scaling (t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    while (i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            fdf->map[i][j].x = j * fdf->scale.x  -  (fdf->scale.x/10);
            fdf->map[i][j].y = i * fdf->scale.y -  (fdf->scale.y/10);
            fdf->map[i][j].z *= fdf->scale.z /2.7;
            j++;
        }
        i++;
    }
}

void projection (t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    while (i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            if (fdf->projection = PROJ_ISO)
            {
                fdf->map[i][j].x = (fdf->map[i][j].x - fdf->map[i][j].y) * cos(0.523599);
                fdf->map[i][j].y = -fdf->map[i][j].z + (fdf->map[i][j].x + fdf->map[i][j].y) * sin(0.523599);
            }
            else if (fdf->projection = PROJ_FRONT)
                fdf->map[i][j].y = fdf->map[i][j].z;
            else if (fdf->projection = PROJ_SIDE)
                fdf->map[i][j].y = -fdf->map[i][j].z;
            j++;
        }
        i++;
    }
}

void calculate_offsets(t_fdf *fdf) 
{
    int i;
    int j;

    i = 0;
    while  ( i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            fdf->map[i][j].x += fdf->offset.x;
            fdf->map[i][j].y += fdf->offset.y;
            if (i < fdf->ofsset_value.x_min) 
                fdf->ofsset_value.x_min = i;
            if (i > fdf->ofsset_value.x_max) 
                fdf->ofsset_value.x_max = i;
            if (j < fdf->ofsset_value.y_min) 
                fdf->ofsset_value.y_min = j;
            if (j > fdf->ofsset_value.y_max) 
                fdf->ofsset_value.y_max = j;
            j++;
        }
        i++;
    }
    fdf->offset.x = (I_W / 2) - (fdf->ofsset_value.x_max + fdf->ofsset_value.x_min) / 2;
    fdf->offset.y = (I_H / 2) - (fdf->ofsset_value.y_max + fdf->ofsset_value.y_min) / 2;
}

void add_offset(t_fdf *fdf)
{   
    int i;
    int j;

    i = 0;
    while (i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            fdf->map[i][j].x += fdf->offset.x;
            fdf->map[i][j].y += fdf->offset.y;
            j++;
        }
        i++;
    }
}
void calculate_min_max_z(t_fdf *fdf) 
{
    int i;
    int j;

    i = 0;
    fdf->z_min = INT_MAX;
    fdf->z_max = INT_MIN;
    while (i < fdf->height) {
        j = 0;
        while (j < fdf->width) {
            if (fdf->map[i][j].z < fdf->z_min)
                fdf->z_min = fdf->map[i][j].z;
            if (fdf->map[i][j].z > fdf->z_max)
                fdf->z_max = fdf->map[i][j].z;
            j++;
        }
        i++;
    }
}

void coloring(t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    while (i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)

        {   
            if (fdf->map[i][j].color)
                fdf->map[i][j].color = get_color(fdf->map[i][j].z, fdf->z_min, fdf->z_max);
            j++;
        }
        i++;
    }

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
void my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= I_W || y < 0 || y >= I_H)
        return;
    dst = fdf->img.img_data + (y * fdf->img.size_line + x * (fdf->img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

// void draw_lines(t_fdf *fdf)
// {   
//     int i = -1;
//     while (++i < fdf->height) {
//         int j = -1;
//         while (++j < fdf->width) {
//             my_mlx_pixel_put(fdf, fdf->map[i][j].x, fdf->map[i][j].y, 
//                            fdf->map[i][j].color);
            
//             // Horizontal connection
//             if (j+1 < fdf->width)
//                 draw_myline(fdf, fdf->map[i][j], fdf->map[i][j+1]);
            
//             // Vertical connection
//             if (i+1 < fdf->height)
//                 draw_myline(fdf, fdf->map[i][j], fdf->map[i+1][j]);
//         }
//     }
// }

// void draw_myline(t_fdf *fdf, t_point start, t_point end)
// {
//     t_line line;
//     int steep = abs(end.y - start.y) > abs(end.x - start.x);
//     int tmp;
    
//     if (steep) {
//         tmp = start.x; start.x = start.y; start.y = tmp;
//         tmp = end.x; end.x = end.y; end.y = tmp;
//     }
//     if (start.x > end.x) {
//         tmp = start.x; start.x = end.x; end.x = tmp;
//         tmp = start.y; start.y = end.y; end.y = tmp;
//         tmp = start.color; start.color = end.color; end.color = tmp;
//     }

//     line.diff.x = abs(end.x - start.x);
//     line.diff.y = abs(end.y - start.y);
//     int err = line.diff.x / 2;
//     int ystep = (start.y < end.y) ? 1 : -1;
//     int total_steps = line.diff.x;
//     int current_step = 0;

//     while (start.x <= end.x) {
//         float ratio = total_steps ? (float)current_step/total_steps : 0.5f;
//         int color = interpolate_color(start.color, end.color, ratio);
//         if (steep) my_mlx_pixel_put(fdf, start.y, start.x, color);
//         else my_mlx_pixel_put(fdf, start.x, start.y, color);
        
//         err -= line.diff.y;
//         if (err < 0) {
//             start.y += ystep;
//             err += line.diff.x;
//         }
//         start.x++;
//         current_step++;
//     }
// }


int main ()
{
    t_fdf *fdf;
    int fd;

    fd = open("42.fdf", O_RDONLY);
    fdf = malloc(sizeof(t_fdf));
    parse_map(fdf, fd);
    scaler_ofsv(fdf);
    scaling(fdf);
    projection(fdf);
    calculate_offsets(fdf);
    add_offset(fdf);
    for (int i = 0; i < fdf->height; i++)
    calculate_min_max_z(fdf);
    for (int i = 0; i < fdf->height; i++)
    coloring(fdf);







    // for (int i = 0; i < fdf->height; i++)
    // {
    //     for (int j = 0; j < fdf->width; j++)
    //     {
    //         printf("x = %d y = %d z = %d color = %d\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j].z, fdf->map[i][j].color);
    //     }
    // }
    ///////////// i ha ve to free every thing  ======free (fdf->map);
    free(fdf);
    return (0);
}