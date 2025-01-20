#ifndef FDF_H
#define FDF_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <stdbool.h>

typedef struct s_map
{
    int x;
    int y;
    int z;
    unsigned int colors;
}   t_map;

typedef struct s_dim
{
    int widht;
    int height;
}   t_dim;

typedef struct s_scale
{
    int x;
    int y;
}   t_scale;

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);
int		checker(char *str, int c);
char	*ft_strchr(char *str, int c);
char	*ft_strldup(char *s, int i);
int	ft_atoi(char *nptr,int x);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char  *s1, char *s2);
/////
void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color);

#endif