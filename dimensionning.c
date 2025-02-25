/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensionning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:31:31 by root              #+#    #+#             */
/*   Updated: 2025/02/15 00:45:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scaler_ofsv(t_fdf *fdf)
{
	if (fdf->height >= 250 || fdf->width >= 250)
	{
		fdf->scale.x = (I_H / fdf->height / 2);
		fdf->scale.y = (I_W / fdf->width / 2);
	}
	else
	{
		fdf->scale.x = (I_H / fdf->height / 2) / 1.5;
		fdf->scale.y = (I_W / fdf->width / 2) / 1.5;
	}
	if (fdf->scale.x < fdf->scale.y)
		fdf->scale.y = fdf->scale.x;
	else
		fdf->scale.x = fdf->scale.y;
	fdf->scale.final = fdf->scale.x;
}

void	scaling(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			fdf->mapv[i][j].x = fdf->map[i][j].x * fdf->scale.final;
			fdf->mapv[i][j].y = fdf->map[i][j].y * fdf->scale.final;
			fdf->mapv[i][j].z = fdf->map[i][j].z * fdf->scale.final;
			j++;
		}
		i++;
	}
}

void	projection(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->projection == PROJ_ISO)
				iso_projection(fdf, i, j);
			else if (fdf->projection == PROJ_TOP)
				top_projection(fdf, i, j);
			else if (fdf->projection == PROJ_SIDE)
				side_projection(fdf, i, j);
			else if (fdf->projection == PROJ_FRONT)
				front_projection(fdf, i, j);
			j++;
		}
		i++;
	}
}

void	assign_offset(t_fdf *fdf)
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
			if (fdf->mapv[i][j].x < fdf->ofsset_value.x_min)
				fdf->ofsset_value.x_min = fdf->mapv[i][j].x;
			if (fdf->mapv[i][j].x > fdf->ofsset_value.x_max)
				fdf->ofsset_value.x_max = fdf->mapv[i][j].x;
			if (fdf->mapv[i][j].y < fdf->ofsset_value.y_min)
				fdf->ofsset_value.y_min = fdf->mapv[i][j].y;
			if (fdf->mapv[i][j].y > fdf->ofsset_value.y_max)
				fdf->ofsset_value.y_max = fdf->mapv[i][j].y;
			j++;
		}
		i++;
	}
}

void	calculate_min_max_z(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->mapv[i][j].z < fdf->z_min)
				fdf->z_min = fdf->mapv[i][j].z;
			if (fdf->mapv[i][j].z > fdf->z_max)
				fdf->z_max = fdf->mapv[i][j].z;
			j++;
		}
		i++;
	}
}
