/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:56:18 by abismail          #+#    #+#             */
/*   Updated: 2025/02/14 22:37:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	ft_cleanup(fdf);
	free(fdf);
	exit(0);
}

void	load_menu_image(t_fdf *fdf)
{
	int	width;
	int	height;

	fdf->logo.img_ptr = mlx_xpm_file_to_image(fdf->mlx, "Guid-Keys.xpm", &width,
			&height);
	if (!fdf->logo.img_ptr)
	{
		exit(1);
	}
}

void	draw_menu_image(t_fdf *fdf)
{
	if (fdf->logo.img_ptr)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->logo.img_ptr, 0, 0);
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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n)
	{
		((unsigned char *)s)[x] = (unsigned char)c;
		x++;
	}
	return (s);
}
