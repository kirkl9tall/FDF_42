
#include "fdf.h"

char	*bomaamar(int fd, char *boby)
{
	int		a;
	char	*buff;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (boby == NULL)
	{
		boby = malloc(1);
		if (!boby)
			return (NULL);
		boby[0] = '\0';
	}
	buff = malloc(BUFFER_SIZE + 1);
	while (checker(boby, '\n') == 0)
	{
		a = read(fd, buff, BUFFER_SIZE);
		if (a <= 0)
			break ;
		buff[a] = '\0';
		boby = ft_strjoin(boby, buff);
	}
	free(buff);
	return (boby);
}

char	*get_next_line(int fd)
{
	static char	*boby;
	char		*buffreturned;
	char		*tmp;
	int			x;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	boby = bomaamar(fd, boby);
	if (!boby || *boby == '\0')
		return (free(boby), boby = NULL, NULL);
	x = 0;
	while (boby[x] != '\n' && boby[x] != '\0')
		x++;
	if (boby[x] == '\n' && boby[x] != '\0')
		x++;
	buffreturned = ft_strldup(boby, x);
	tmp = boby;
	boby = ft_strchr(tmp, '\n');
	if (!boby || *boby == '\0')
	{
		free(boby); 
		boby = NULL;
	}
	free(tmp);
	if (*buffreturned == '\0')
		return (free(buffreturned), NULL);
	return (buffreturned);
}

// int main ()
// {
// 	int i = open("10-2.fdf",O_CREAT| O_RDWR , 0666);
// 	int **bigloly;

	
// 	char *a;
// 	int l = 0;
//  	while((a = get_next_line(i)) != NULL)
// 	{
		
// 		l++;
// 		free(a);
// 	}
// 	bigloly = malloc(sizeof(char*)* l);
// 	close(i);
// }
// 	/* a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 		a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 		a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 		a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 		a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 		a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 		a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
//     a = get_next_line(i);
// 	printf("%s",a);
// 	free(a);
// 	a = get_next_line(i);
// 	printf("%s",a);
// 	free(a); */
// 	// a = get_next_li ne(i);
// 	//     printf("%s",a);
// 	// free(a);
// //}

// // int main ()
// // {
// // 	int i = open("test.txt",O_CREAT| O_RDWR , 0666);

// // 	char *a;
// //  	a = get_next_line(i);
// 		printf("%s", a);
// 		free(a);
// 	close(i);
// }