/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:00:51 by abismail          #+#    #+#             */
/*   Updated: 2025/02/14 23:35:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initial_fdf(char *argv)
{
	int	i;
	int	dot_pos;

	i = 0;
	dot_pos = -1;
	while (argv[i])
	{
		if (argv[i] == '.')
			dot_pos = i;
		i++;
	}
	if (dot_pos == -1 || dot_pos == 0 || argv[dot_pos + 1] != 'f'
		|| argv[dot_pos + 2] != 'd' || argv[dot_pos + 3] != 'f' || argv[dot_pos
			+ 4] != '\0')
	{
		write(2, "Error: Invalid .fdf file \n", 27);
		exit(1);
	}
}
