/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:12:26 by root              #+#    #+#             */
/*   Updated: 2025/02/12 00:34:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void iso_projection (t_fdf *fdf, int i, int j)
{
    int	x;
	int	y;
    
    x = fdf->mapv[i][j].x;
    y = fdf->mapv[i][j].y;
    fdf->mapv[i][j].x = (x - y) * cos(0.523599);
    fdf->mapv[i][j].y = (x + y) * sin(0.523599) - fdf->mapv[i][j].z;
}

void front_projection(t_fdf *fdf, int i, int j)
{
    fdf->mapv[i][j].x = fdf->mapv[i][j].x;
    fdf->mapv[i][j].y = fdf->mapv[i][j].z;
}

void top_projection(t_fdf *fdf, int i, int j)
{
    fdf->mapv[i][j].x = fdf->mapv[i][j].x;
    fdf->mapv[i][j].y = fdf->mapv[i][j].y;
}
void side_projection(t_fdf *fdf, int i, int j)
{
    fdf->mapv[i][j].x = fdf->mapv[i][j].y;
    fdf->mapv[i][j].y = -fdf->mapv[i][j].z;
}

void	reset(t_fdf *fdf)
{
	memset(fdf->img.img_data, 0, W_W * W_H * (fdf->img.bits_per_pixel / 8));
    scaler_ofsv(fdf);
	scaling(fdf);
    fdf->rot_x = 0.0f;
	fdf->rot_y = 0.0f;
	apply_rotation(fdf);
	projection(fdf);
	calculate_offsets(fdf);
	calculate_min_max_z(fdf);
	coloring(fdf);
	draw_lines(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
}