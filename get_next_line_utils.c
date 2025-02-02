
#include "fdf.h"

size_t	ft_strlen(char *str)
{
	size_t	x;

	if (!str)
		return (0);
	x = 0;
	while (str[x])
		x++;
	return (x);
}

int	checker(char *str, int c)
{
	int	x;

	if (str == NULL)
		return (0);
	x = 0;
	if (c == '\0')
		return (0);
	while (str[x])
	{
		if (str[x] == (char)c)
			return (1);
		x++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!s2)
		return (free(s1), NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[x])
		p[y++] = s1[x++];
	x = 0;
	while (s2[x])
		p[y++] = s2[x++];
	p[y] = '\0';
	free(s1);
	return (p);
}

char	*ft_strldup(char *s, int i)
{
	char	*p;
	int		x;

	if (s == NULL)
	{
		s = malloc(1);
		if (!s)
			return (NULL);
		s[0] = '\0';
	}
	x = 0;
	p = malloc(i + 1);
	if (p == NULL)
		return (NULL);
	while (i--)
	{
		p[x] = s[x];
		x++;
	}
	p[x] = '\0';
	return (p);
}

char	*ft_strchr(char *str, int c)
{
	int	x;

	x = 0;
	if (c == '\0')
		return (NULL);
	while (str[x])
	{
		if (str[x] == (char)c)
			return (ft_strdup(str + x + 1));
		x++;
	}
	return (NULL);
}
