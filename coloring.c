#include "fdf.h"

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
            if (fdf->mapv[i][j].has_color)
                fdf->mapv[i][j].color = get_color(fdf->mapv[i][j].z, fdf->z_min, fdf->z_max);
            j++;
        }
        i++;
    }

}

int clamp(int value) 
{
    if (value < 0) {
        return 0;
    } else if (value > 255) {
        return 255;
    } else {
        return value;
    }
}

int interpolate_color(int start_color, int end_color, float ratio) {
    int start_r = (start_color >> 16) & 0xFF;
    int start_g = (start_color >> 8) & 0xFF;
    int start_b = start_color & 0xFF;

    int end_r = (end_color >> 16) & 0xFF;
    int end_g = (end_color >> 8) & 0xFF;
    int end_b = end_color & 0xFF;

    int r = clamp(start_r + (int)(ratio * (end_r - start_r)));
    int g = clamp(start_g + (int)(ratio * (end_g - start_g)));
    int b = clamp(start_b + (int)(ratio * (end_b - start_b)));

    return (r << 16) | (g << 8) | b;
} 

