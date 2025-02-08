/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:33:03 by root              #+#    #+#             */
/*   Updated: 2025/02/08 23:14:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(char *nptr, int x)
{
	int	signe;
	int	num;

	signe = 1;
	num = 0;
	while (nptr[x] == '\t' || nptr[x] == ' ' || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (nptr[x] == '+' || nptr[x] == '-')
	{
		if (nptr[x] == '-')
		{
			signe *= -1;
		}
		x++;
	}
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		num = (num * 10);
		num = num + (nptr[x] - 48);
		x++;
	}
	return (num * signe);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}

int	ft_isdigit(int x)
{
	if (x >= 48 && x <= 57)
		return (2048);
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*p;
	int		x;

	x = 0;
	p = malloc(ft_strlen((char *)s) + 1);
	if (p == NULL)
		return (NULL);
	while (s[x])
	{
		p[x] = s[x];
		x++;
	}
	p[x] = '\0';
	return (p);
}

void	read_file(t_fdf *fdf)
{
	char	*arr;
	int		fd;

	fd = open(fdf->argv, O_RDONLY);
	fdf->line = 0;
	arr = get_next_line(fd);
	while (arr)
	{
		free(arr);
		arr = get_next_line(fd);
		fdf->line++;
	}
	free(arr);
	fdf->height = fdf->line;
	close(fd);
	return ;
}
