#ifndef FDF_H
#define FDF_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <stdbool.h>

typedef struct s_img
{
    void    *img_ptr;       
    char    *img_data;      
    int     bits_per_pixel; 
    int     size_line;     
    int     endian;         
} t_img;
typedef struct s_map
{
    int x;
    int y;
    int z;
    unsigned int colors;
}   t_map;
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


typedef struct s_dim
{
    int width;
    int height;
}   t_dim;
typedef struct s_map_p
{
    t_map **map;
    t_dim dims; 
}   t_map_p;

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
void draw_myline (t_img *img ,int x1,int y1,int x2,int y2,int color)
///////////////////./././/?////////////////////////////////////////////////////////

void put_pixel_to_img(t_img *img, int x, int y, int color);
void draw_mylinee(t_img *img, int x1, int y1, int x2, int y2, int color);
/// ////////////
unsigned int  char_tohex (char *s,int index);
size_t	checker_map(char *str);
t_map_p parssing (int fd);

#endif