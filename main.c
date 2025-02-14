/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:32:51 by root              #+#    #+#             */
/*   Updated: 2025/02/12 16:09:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_cleanup(t_fdf *fdf)
{
	int	i;

	if (fdf->map)
	{
		i = 0;
		while (i < fdf->height)
		{
			free(fdf->map[i]);
			free(fdf->mapv[i]);
			i++;
		}
		free(fdf->map);
		free(fdf->mapv);
	}
	free(fdf->argv);
	if (fdf->mlx)
	{
		if (fdf->img.img_ptr)
			mlx_destroy_image(fdf->mlx, fdf->img.img_ptr);
		if (fdf->menu.img_ptr)
            mlx_destroy_image(fdf->mlx, fdf->menu.img_ptr);
        if (fdf->logo.img_ptr)
            mlx_destroy_image(fdf->mlx, fdf->logo.img_ptr);
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		mlx_destroy_display(fdf->mlx);
	}
	free(fdf->mlx);
}

void	init_fdf(t_fdf *fdf, char *title)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, W_W, W_H, title);
	if (!fdf->mlx)
		exit(MLX_ERROR);
	if (!fdf->win)
		exit(MLX_ERROR);
	fdf->img.img_ptr = mlx_new_image(fdf->mlx, W_W, W_H);
	fdf->img.img_data = mlx_get_data_addr(fdf->img.img_ptr,
			&fdf->img.bits_per_pixel, &fdf->img.size_line, &fdf->img.endian);
	fdf->menu.img_ptr = mlx_new_image(fdf->mlx, 400, W_H);
	fdf->menu.img_data = mlx_get_data_addr(fdf->menu.img_ptr,
			&fdf->menu.bits_per_pixel, &fdf->menu.size_line, &fdf->menu.endian);
	fdf->offset.x = W_W / 2;
	fdf->offset.y = W_H / 2;
	fdf->projection = PROJ_ISO;
	fdf->rot_x = 0.0f;
	fdf->rot_y = 0.0f;
	fdf->trans_x = 0;
	fdf->trans_y = 0;
	draw_menu_background(fdf);
    load_menu_image(fdf);
}

int	handle_keypress(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
	{
		ft_cleanup(fdf);
		free(fdf);
		exit(0);
	}
	if (keysym == XK_p)
		fdf->scale.final *= 1.2;
	if (keysym == XK_m)
		fdf->scale.final /= 1.2;
	if (keysym == XK_a || keysym == XK_d || keysym == XK_w || keysym == XK_s )
		rot_key(keysym,fdf);
	if (keysym == XK_i || keysym == XK_f || keysym == XK_t || keysym == XK_c)
		proj_key(keysym,fdf);
	if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up || keysym == XK_Down) 
		trans_key(keysym,fdf);
	if (keysym == XK_r)
		reset(fdf);
	reset_map(fdf);
	redraw(fdf);
	return(0);
}

void	dimension_color(t_fdf *fdf)
{
	scaler_ofsv(fdf);
	scaling(fdf);
	projection(fdf);
	calculate_offsets(fdf);
	calculate_min_max_z(fdf);
	coloring(fdf);
	draw_lines(fdf);
}

int close_window (t_fdf *fdf)
{
	ft_cleanup(fdf);
	free(fdf);
	exit(0);
}

void load_menu_image(t_fdf *fdf) {
    int width, height;
    fdf->logo.img_ptr = mlx_xpm_file_to_image(fdf->mlx, "iso.xpm", &width, &height);
    if (!fdf->logo.img_ptr) {
        exit(1);
    }
}

void draw_menu_image(t_fdf *fdf) {
    if (fdf->logo.img_ptr) 
        mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->logo.img_ptr, 0, 0);
} 

void draw_menu_background(t_fdf *fdf) 
{
    for (int y = 0; y < 1040; y++) {
        for (int x = 0; x < 300; x++) {
            put_menu(fdf, x, y, 0x2A2A2A);
        }
    }
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->menu.img_ptr, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;
	int		fd;
	
	if (argc == 2)
	{
		fdf = malloc(sizeof(t_fdf));
		fdf->argv = ft_strdup(argv[1]);
		fd = open(fdf->argv, O_RDONLY);
		init_fdf(fdf, "FDF");
		draw_menu_background(fdf);
		draw_menu_image(fdf);
		mlx_key_hook(fdf->win, handle_keypress, fdf);
		mlx_hook(fdf->win, 17, 0,close_window,fdf);
		parse_map(fdf, fd);
		dimension_color(fdf);
		//mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->menu.img_ptr, 0, 0);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
		mlx_loop(fdf->mlx);
		ft_cleanup(fdf);
		free(fdf);
	}
	return (0);
}

