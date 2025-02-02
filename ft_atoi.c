#include "fdf.h"

int	ft_atoi(char *nptr,int x)
{
	//int	x;
	int	signe;
	int	num;

	//x = 0;
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
/*
int main ()
{
	char s1[] = "    65654";

	printf("%d\n",ft_atoi(s1));

}*/
