#include "fdf.h"

void init_fdf(t_fdf * fdf,char *title)
{
    fdf->mlx = mlx_init();
    fdf->win = mlx_new_window(fdf->mlx, W_W, W_H, title);
    if (!fdf->mlx) 
        exit(MLX_ERROR);
    if (!fdf->win)
        exit(MLX_ERROR);
    fdf->img.img_ptr = mlx_new_image(fdf->mlx, W_W, W_H);
    fdf->img.img_data = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bits_per_pixel, &fdf->img.size_line, &fdf->img.endian);
    fdf->zoom = 1.0;
    fdf->offset.x = W_W / 2;
    fdf->offset.y = W_H / 2;
    fdf->projection = PROJ_ISO;

}

int	handle_keypress(int keysym, t_fdf *fdf)
{

    if (keysym == XK_Escape)
    {   
        if (fdf->mlx && fdf->img.img_ptr)
            mlx_destroy_image(fdf->mlx,fdf->img.img_ptr);
        if (fdf->mlx && fdf->win)
            mlx_destroy_window(fdf->mlx, fdf->win);
        if (fdf->mlx)
            mlx_destroy_display(fdf->mlx);
        exit(1);
    }
    if (keysym == XK_i)
    {
        fdf->projection = PROJ_ISO;
        dimension_color(fdf);
        mlx_put_image_to_window(fdf->mlx,fdf->win,fdf->img.img_ptr,0,0);

    }
    if (keysym == XK_t)
    {
        fdf->projection = PROJ_TOP;
        dimension_color(fdf);
        mlx_put_image_to_window(fdf->mlx,fdf->win,fdf->img.img_ptr,0,0);   
    }

    return (0);
}

void dimension_color(t_fdf * fdf)
{
    mlx_destroy_image(fdf->mlx, fdf->img.img_ptr);
    fdf->img.img_ptr = mlx_new_image(fdf->mlx, W_W, W_H);
    fdf->img.img_data = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bits_per_pixel, &fdf->img.size_line, &fdf->img.endian);
    scaler_ofsv(fdf);
    scaling(fdf);
    projection(fdf);
    calculate_offsets(fdf);
    calculate_min_max_z(fdf);
    coloring(fdf);
    draw_lines(fdf);
}
int main ()
{
    t_fdf *fdf;
    int fd;

    fd = open("42.fdf", O_RDONLY);
    fdf = malloc(sizeof(t_fdf));
    init_fdf(fdf,"new funky test !");
    mlx_key_hook(fdf->win,handle_keypress,fdf);
    parse_map(fdf, fd);
    dimension_color(fdf);
    // scaler_ofsv(fdf);
    // scaling(fdf);
    // projection(fdf);
    // calculate_offsets(fdf);
    // calculate_min_max_z(fdf);
    // coloring(fdf);
    // draw_lines(fdf);

    mlx_put_image_to_window(fdf->mlx,fdf->win,fdf->img.img_ptr,0,0);
    mlx_loop(fdf->mlx);
    ///////////// i ha ve to free every thing  ======free (fdf->map);
    free(fdf);
    return (0);
}