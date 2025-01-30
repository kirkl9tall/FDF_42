#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <limits.h>


int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b );
} 

int	handle_keypress(int keysym, t_fdf *fdf)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
        fdf->win_ptr = NULL;
    }
    return (0);
}
int main ()
{
    t_fdf fdf;

    fdf.mlx_ptr = mlx_init();
    fdf.wind.x = 1200;
    fdf.wind.y = 900;

    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr,fdf.wind.x,fdf.wind.y,"gradient colors !");
    fdf.img = (t_img *)malloc(sizeof(t_img));
    fdf.img->img_ptr = mlx_new_image(fdf.mlx_ptr,fdf.wind.x,fdf.wind.y);
    fdf.img->img_data = mlx_get_data_addr(fdf.img->img_ptr, &fdf.img->bits_per_pixel, &fdf.img->size_line, &fdf.img->endian);

    int x0,x1,y0,y1;
    x0 = 300;
    x1 = 600;
    y0 = 300; 
    y1 = 600;
    int color = 0xAF00FF;
    int R = get_r(color);
    int G = get_g(color) ;
    int B = get_b(color) ;
    int T = get_t(color) ;
    int trgb = create_trgb(T,R,G,B);

    my_mlx_pixel_put(fdf.img,x0,y0,0x00FF00);
    my_mlx_pixel_put(fdf.img,y0,y1,0x00FF00);

   draw_myline(fdf.img,x0,y0,x1,y1,trgb);

    mlx_put_image_to_window(fdf.mlx_ptr,fdf.win_ptr,fdf.img->img_ptr,0,0);


    mlx_key_hook(fdf.win_ptr,handle_keypress,&fdf);
    mlx_loop(fdf.mlx_ptr);

    mlx_destroy_display(fdf.mlx_ptr);
    free(fdf.mlx_ptr);
}

/////////////////////////////////////////////////////////////////////////////////////
#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

void draw_myline(t_img *img, int x1, int y1, int x2, int y2, int color_start, int color_end) {
    t_line line;
    int steep = abs(y2 - y1) > abs(x2 - x1);

    if (steep) {
        int tmp;
        tmp = x1; x1 = y1; y1 = tmp;
        tmp = x2; x2 = y2; y2 = tmp;
    }

    if (x1 > x2) {
        int tmp;
        tmp = x1; x1 = x2; x2 = tmp;
        tmp = y1; y1 = y2; y2 = tmp;
    }

    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    line.diff.x = abs(line.end.x - line.start.x);
    line.diff.y = abs(line.end.y - line.start.y);
    int err = line.diff.x / 2;
    int ystep = (y1 < y2) ? 1 : -1;

    int length = sqrt(line.diff.x * line.diff.x + line.diff.y * line.diff.y);
    int i = 0;
    while (line.start.x <= line.end.x) {
        float t = (float)i / length; 
         // Calculate the fraction of the line's total length
        int color = color_lerp(color_start, color_end, t);

        if (steep) {
            my_mlx_pixel_put(img, line.start.y, line.start.x, color);
        } else {
            my_mlx_pixel_put(img, line.start.x, line.start.y, color);
        }

        err -= line.diff.y;
        if (err < 0) {
            line.start.y += ystep;
            err += line.diff.x;
        }
        line.start.x++;
        i++;
    }
}