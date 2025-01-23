#ifndef FDF_H
#define FDF_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <stdbool.h>

typedef struct  s_pos
{
    int x;
    int y;
}   t_pos;
typedef struct s_step
{
    int x;
    int y;
}   t_step;
typedef struct s_diff
{
    int  x;
    int y;
}t_diff;

typedef struct s_line {
    t_pos start; 
    t_pos end;   
    t_diff diff; 
    t_step step; 
    int p;
} t_line;

typedef struct s_map
{
    int x;
    int y;
    int z;
    unsigned int colors;
    int xc;
    int yc;
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
t_step choice (t_pos start, t_pos end);
void initial_step(void *mlx_ptr,void *win_ptr,t_pos start,int p,t_step step,int color);
void nega_decision(void *mlx_ptr,void *win_ptr,t_line line,int color);
void posi_decision(void *mlx_ptr,void *win_ptr,t_line line,int color);
void draw_myline (void *win_ptr, void *mlx_ptr ,int x1,int y1,int x2,int y2,int color);
/// ////////////
unsigned int  char_tohex (char *s,int index);
size_t	checker_map(char *str);
int parssing (int fd);
#endif