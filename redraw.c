/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:11:21 by root              #+#    #+#             */
/*   Updated: 2025/02/11 23:52:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw(t_fdf *fdf)
{
	memset(fdf->img.img_data, 0, W_W * W_H * (fdf->img.bits_per_pixel / 8));
	scaling(fdf);
	apply_rotation(fdf);
	projection(fdf);
	calculate_offsets(fdf);
	calculate_min_max_z(fdf);
	coloring(fdf);
	draw_lines(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
}

void	rotate_x(t_point *point, float angle)
{
	float	y;
	float	z;
	
	y = point->y;
	z = point->z;
	point->y = y * cos(angle) - z * sin(angle);
	point->z = y * sin(angle) + z * cos(angle);
}

void rotate_y(t_point *point, float angle)
{
	float x;
	float z;
	
	x = point->x;
	z = point->z;
	point->x = x * cos(angle) + z * sin(angle);
	point->z = -x * sin(angle) + z * cos(angle);
}

void apply_rotation(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			rotate_x(&fdf->mapv[i][j], fdf->rot_x);
			rotate_y(&fdf->mapv[i][j], fdf->rot_y);
			j++;
		}
		i++;
	}
}
