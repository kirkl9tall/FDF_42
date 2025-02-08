/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:31:26 by root              #+#    #+#             */
/*   Updated: 2025/02/08 22:01:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(int z, int z_min, int z_max)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	if (z_min == z_max)
		return (0xFFFFFF);
	ratio = (double)(z - z_min) / (z_max - z_min);
	red = (int)(255 * ratio);
	green = (int)(255 * (1 - ratio));
	blue = 200;
	return ((red << 16) | (green << 8) | blue);
}

void	coloring(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->mapv[i][j].has_color)
				fdf->mapv[i][j].color = get_color(fdf->mapv[i][j].z, fdf->z_min,
						fdf->z_max);
			j++;
		}
		i++;
	}
}

int	clamp(int value)
{
	if (value < 0)
	{
		return (0);
	}
	else if (value > 255)
	{
		return (255);
	}
	else
	{
		return (value);
	}
}

int	interpolate_color(int start_color, int end_color, float ratio)
{
	t_colors	colors;

	colors.start_r = (start_color >> 16) & 0xFF;
	colors.start_g = (start_color >> 8) & 0xFF;
	colors.start_b = start_color & 0xFF;
	colors.end_r = (end_color >> 16) & 0xFF;
	colors.end_g = (end_color >> 8) & 0xFF;
	colors.end_b = end_color & 0xFF;
	colors.r = clamp(colors.start_r
			+(int)(ratio * (colors.end_r - colors.start_r)));
	colors.g = clamp(colors.start_g
			+(int)(ratio * (colors.end_g - colors.start_g)));
	colors.b = clamp(colors.start_b
			+ (int)(ratio * (colors.end_b - colors.start_b)));
	return ((colors.r << 16) | (colors.g << 8) | colors.b);
}
