
#include "fdf.h"

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
/*
int main ()
{
	char  *arr = "abdcefghijk";

	//printf("%s\n",arr);
	printf("%s\n",ft_strdup(arr));


}*/
