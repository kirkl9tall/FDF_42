/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_press.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:09:17 by root              #+#    #+#             */
/*   Updated: 2025/02/12 16:09:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_key(int keysym, t_fdf *fdf)
{
	if (keysym == XK_a)
		fdf->rot_y -= 0.1;
	if (keysym == XK_d)
		fdf->rot_y += 0.1;
	if (keysym == XK_w)
		fdf->rot_x -= 0.1f;
	if (keysym == XK_s)
		fdf->rot_x += 0.1f;
}

void	proj_key(int keysym, t_fdf *fdf)
{
	if (keysym == XK_i)
		fdf->projection = PROJ_ISO;
	if (keysym == XK_f)
		fdf->projection = PROJ_FRONT;
	if (keysym == XK_t)
		fdf->projection = PROJ_TOP;
	if (keysym == XK_c)
		fdf->projection = PROJ_SIDE;
}

void	trans_key(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Left)
		fdf->trans_x -= 10;
	if (keysym == XK_Right)
		fdf->trans_x += 10;
	if (keysym == XK_Up)
		fdf->trans_y -= 10;
	if (keysym == XK_Down)
		fdf->trans_y += 10;
}
