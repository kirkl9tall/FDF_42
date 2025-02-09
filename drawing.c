/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:31:34 by root              #+#    #+#             */
/*   Updated: 2025/02/08 23:18:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	prepare_line_coordinates(t_point *start, t_point *end, int *steep)
{
	int	tmp;

	*steep = abs(end->y - start->y) > abs(end->x - start->x);
	if (*steep)
	{
		tmp = start->x;
		start->x = start->y;
		start->y = tmp;
		tmp = end->x;
		end->x = end->y;
		end->y = tmp;
	}
	if (start->x > end->x)
	{
		tmp = start->x;
		start->x = end->x;
		end->x = tmp;
		tmp = start->y;
		start->y = end->y;
		end->y = tmp;
		tmp = start->color;
		start->color = end->color;
		end->color = tmp;
	}
}

void	karawatcha(t_point *start, t_point *end,
		int steep, t_fdf *fdf)
{
	fdf->line_tools.ratio = (float)fdf->line_tools.current_step
		/ fdf->line_tools.total_steps;
	fdf->line_tools.color = interpolate_color(start->color, end->color,
			fdf->line_tools.ratio);
	if (steep)
		my_mlx_pixel_put(fdf, start->y, start->x, fdf->line_tools.color);
	else
		my_mlx_pixel_put(fdf, start->x, start->y, fdf->line_tools.color);
	fdf->line_tools.err -= fdf->line_pixel.diff.y;
	if (fdf->line_tools.err < 0)
	{
		start->y += fdf->line_tools.ystep;
		fdf->line_tools.err += fdf->line_pixel.diff.x;
	}
	start->x++;
	fdf->line_tools.current_step++;
}

void	draw_line_pixel(t_fdf *fdf, t_point start, t_point end, int steep)
{
	fdf->line_tools.total_steps = fdf->line_pixel.diff.x;
	fdf->line_tools.current_step = 0;
	fdf->line_tools.err = fdf->line_pixel.diff.x / 2;
	if (start.y < end.y)
		fdf->line_tools.ystep = 1;
	else
		fdf->line_tools.ystep = -1;
	while (start.x <= end.x)
	{
		karawatcha(&start, &end, steep, fdf);
	}
}

void	draw_myline(t_fdf *fdf, t_point start, t_point end)
{
	int		steep;

	prepare_line_coordinates(&start, &end, &steep);
	fdf->line_pixel.diff.x = abs(end.x - start.x);
	fdf->line_pixel.diff.y = abs(end.y - start.y);
	draw_line_pixel(fdf, start, end, steep);
}

void	draw_lines(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->height)
	{
		j = -1;
		while (++j < fdf->width)
		{
			my_mlx_pixel_put(fdf, fdf->map[i][j].x, fdf->map[i][j].y,
				fdf->map[i][j].color);
			if (j + 1 < fdf->width)
				draw_myline(fdf, fdf->map[i][j], fdf->map[i][j + 1]);
			if (i + 1 < fdf->height)
				draw_myline(fdf, fdf->map[i][j], fdf->map[i + 1][j]);
		}
	}
}
