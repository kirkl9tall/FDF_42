/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:31:37 by root              #+#    #+#             */
/*   Updated: 2025/02/12 00:52:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= I_W || y < 0 || y >= I_H)
		return ;
	dst = fdf->img.img_data + (y * fdf->img.size_line + x
			* (fdf->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void	put_menu(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= I_W || y < 0 || y >= I_H)
		return ;
	dst = fdf->menu.img_data + (y * fdf->menu.size_line + x
			* (fdf->menu.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	reassign_offset(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			fdf->mapv[i][j].x += fdf->offset.x;
			fdf->mapv[i][j].y += fdf->offset.y;
			j++;
		}
		i++;
	}
}

void	calculate_offsets(t_fdf *fdf)
{
	fdf->ofsset_value.x_min = INT_MAX;
	fdf->ofsset_value.y_min = INT_MAX;
	fdf->ofsset_value.x_max = INT_MIN;
	fdf->ofsset_value.y_max = INT_MIN;
	assign_offset(fdf);
	fdf->offset.x = (I_W / 2) - (fdf->ofsset_value.x_max
			+ fdf->ofsset_value.x_min) / 2 + fdf->trans_x;
	fdf->offset.y = (I_H / 2) - (fdf->ofsset_value.y_max
			+ fdf->ofsset_value.y_min) / 2 + fdf->trans_y;
	reassign_offset(fdf);
}

void	copy_data(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	fdf->mapv = malloc (sizeof (t_point *) * fdf->height);
	if (!fdf->mapv)
		return ;
	while (x < fdf->height)
	{
		y = 0;
		fdf->mapv[x] = malloc(sizeof(t_point) * fdf->width);
		if (!fdf->mapv[x])
			return ;
		while (y < fdf->width)
		{
			fdf->mapv[x][y].z = fdf->map[x][y].z;
			fdf->mapv[x][y].x = fdf->map[x][y].x;
			fdf->mapv[x][y].y = fdf->map[x][y].y;
			fdf->mapv[x][y].color = fdf->map[x][y].color;
			fdf->mapv[x][y].has_color = fdf->map[x][y].has_color;
			y++;
		}
		x++;
	}
}

void	reset_map(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->height)
	{
		y = 0;
		while (y < fdf->width)
		{
			fdf->mapv[x][y].z = fdf->map[x][y].z;
			fdf->mapv[x][y].x = fdf->map[x][y].x;
			fdf->mapv[x][y].y = fdf->map[x][y].y;
			fdf->mapv[x][y].color = fdf->map[x][y].color;
			fdf->mapv[x][y].has_color = fdf->map[x][y].has_color;
			y++;
		}
		x++;
	}
}
