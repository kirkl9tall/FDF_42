/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:56:49 by abismail          #+#    #+#             */
/*   Updated: 2024/11/06 11:56:49 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strjoin(char  *s1, char *s2)
{
	char	*p;
	int		x;
	int		y;

	x = 0;
	y = 0;
	p = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[x])
		p[y++] = s1[x++];
	x = 0;
	while (s2[x])
		p[y++] = s2[x++];
	p[y] = '\0';
	return (p);
}
/*
int main ()
{
		char *s1 = "abcdefjh" ;
		char *s2 = "ijklmnop";

		printf("%s\n",ft_strjoin(s1,s2));
}*/
