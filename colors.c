#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <limits.h>


// void my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
//     char *dst;
//     // if (x < 0 || x >= I_W || y < 0 || y >= I_H)
//     //     return;
//     dst = img->img_data + (y * img->size_line + x * (img->bits_per_pixel / 8));
//     *(unsigned int *)dst = color;
// }
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
    printf("%d %d %d %d \n",R,G,B,T);

    int trgb = create_trgb(T,R,G,B);

    my_mlx_pixel_put(fdf.img,x0,y0,trgb);
    my_mlx_pixel_put(fdf.img,y0,y1,trgb);

    draw_myline(fdf.img,x0,y0,x1,y1,trgb);

    mlx_put_image_to_window (fdf.mlx_ptr,fdf.win_ptr,fdf.img->img_ptr,0,0);


    mlx_key_hook(fdf.win_ptr,handle_keypress,&fdf);
    mlx_loop(fdf.mlx_ptr);
    mlx_destroy_display(fdf.mlx_ptr);
    free(fdf.mlx_ptr);
}