#ifndef FDF_H
#define FDF_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdbool.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <limits.h>

#define BUFFER_SIZE 1

#define W_W 1920
#define W_H 1040
#define I_W 1920
#define I_H 1040
#define MLX_ERROR 1


typedef struct s_pos
{
    int i;
    int j;
}   t_pos;
typedef struct ofsset_value
{
    int x_min;
    int y_min;
    int x_max;
    int y_max;
}   t_offset_value;
typedef struct s_point
{
    int x;
    int y;
    int z;
    unsigned int color;
    int has_color;

} t_point;
typedef enum e_projection
{
    PROJ_ISO,
    PROJ_TOP,
    PROJ_FRONT,
    PROJ_SIDE
} t_projection;

typedef struct s_img
{
    void    *img_ptr;       
    char    *img_data;      
    int     bits_per_pixel; 
    int     size_line;     
    int     endian;         
} t_img;

typedef struct s_offset
{
    int x;
    int y;
}   t_offset;

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
typedef struct s_index
{
    int index;
    int words;
}   t_index;

typedef struct s_scale
{
    int x;
    int y;
    int z;
}   t_scale;

typedef struct s_fdf
{   
    void *mlx;
    void *win;
    t_img img;
    t_point **map;
    int width;
    int height;
    int z_min;
    int z_max;
    t_projection projection;
    t_offset offset;
    t_scale scale;
    float zoom;
    t_offset_value ofsset_value;
}   t_fdf;


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
int	ft_isdigit(int x);
int	ft_isalpha(int c);
////////////////////// parssing  functions //////////////////////////
void parse_map (t_fdf *fdf, int fd);
void parssing (t_fdf *fdf , char **split_line);
void assigning (t_fdf *fdf, char **ft_split, t_pos *pos, t_index *index);
unsigned int  char_tohex (char *s,int index);
size_t	checker_map(char *str);
///////////////////////////// draw functions //////////////////////////
void  scaling (t_fdf *fdf);
void scaler_ofsv (t_fdf *fdf);
void projection (t_fdf *fdf);
void calculate_offsets(t_fdf *fdf);
void add_offset(t_fdf *fdf);
void calculate_min_max_z(t_fdf *fdf);
void coloring(t_fdf *fdf);
int get_color(int z, int z_min, int z_max);
void my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void draw_lines(t_fdf *fdf);



#endif
