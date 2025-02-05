#include "fdf.h"
void my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= I_W || y < 0 || y >= I_H)
        return;
    dst = fdf->img.img_data + (y * fdf->img.size_line + x * (fdf->img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
// kanchkrouk 
