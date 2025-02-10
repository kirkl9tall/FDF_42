/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:31:45 by root              #+#    #+#             */
/*   Updated: 2025/02/10 22:58:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 50

# define W_W 1920
# define W_H 1040
# define I_W 1920
# define I_H 1040
# define MLX_ERROR 1

typedef struct s_colors
{
	int				start_r;
	int				start_g;
	int				start_b;
	int				end_r;
	int				end_g;
	int				end_b;
	int				r;
	int				g;
	int				b;
}					t_colors;
typedef struct s_pos
{
	int				i;
	int				j;
}					t_pos;
typedef struct s_line_tools
{
	int				total_steps;
	int				err;
	int				ystep;
	float			ratio;
	int				color;
	int				current_step;
}					t_line_tools;

typedef struct ofsset_value
{
	int				x_min;
	int				y_min;
	int				x_max;
	int				y_max;
}					t_offset_value;
typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
	int				has_color;

}					t_point;
typedef enum e_projection
{
	PROJ_ISO,
	PROJ_TOP,
	PROJ_FRONT,
	PROJ_SIDE
}					t_projection;

typedef struct s_img
{
	void			*img_ptr;
	char			*img_data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_img;

typedef struct s_offset
{
	int				x;
	int				y;
}					t_offset;

typedef struct s_step
{
	int				x;
	int				y;
}					t_step;
typedef struct s_diff
{
	int				x;
	int				y;
}					t_diff;
typedef struct s_line
{
	t_pos			start;
	t_pos			end;
	t_diff			diff;
	t_step			step;
	int				p;
}					t_line;
typedef struct s_index
{
	int				index;
	int				words;
}					t_index;

typedef struct s_scale
{
	float				x;
	float				y;
	float				z;
	float				final;
}					t_scale;

typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_point			**map;
	t_point			**mapv;
	int				width;
	int				height;
	int				z_min;
	int				z_max;
	t_projection	projection;
	t_offset		offset;
	t_scale			scale;
	int				line;
	float			zoom;
	t_offset_value	ofsset_value;
	char			*argv;
	t_line_tools	line_tools;
	t_line			line_pixel;
	float 			rot_x;
	float 			rot_y;
}					t_fdf;

char				*get_next_line(int fd);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlen(char *str);
int					checker(char *str, int c);
char				*ft_strchr(char *str, int c);
char				*ft_strldup(char *s, int i);
int					ft_atoi(char *nptr, int x);
char				**ft_split(char *s, char c);
char				*ft_strdup(char *s);
char				*ft_strjoin(char *s1, char *s2);
int					ft_isdigit(int x);
int					ft_isalpha(int c);
////////////////////// parssing  functions //////////////////////////
void				parse_map(t_fdf *fdf, int fd);
void				parssing(t_fdf *fdf, char **split_line);
void				assigning(t_fdf *fdf, char **ft_split, t_pos *pos,
						t_index *index);
unsigned int		char_tohex(char *s, int index);
size_t				checker_map(char *str);
void				copy_data(t_fdf *fdf);
///////////////////////////// draw functions //////////////////////////
void				scaling(t_fdf *fdf);
void				scaler_ofsv(t_fdf *fdf);
void				projection(t_fdf *fdf);
void				calculate_offsets(t_fdf *fdf);
void				add_offset(t_fdf *fdf);
void				calculate_min_max_z(t_fdf *fdf);
void				coloring(t_fdf *fdf);
int					get_color(int z, int z_min, int z_max);
void				my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void				draw_lines(t_fdf *fdf);
int					interpolate_color(int start_color, int end_color,
						float ratio);
int					clamp(int value);
void				prepare_line_coordinates(t_point *start, t_point *end,
						int *steep);
void				karawatcha(t_point *start, t_point *end, int steep,
						t_fdf *fdf);
void				prepare_line_coordinates(t_point *start, t_point *end,
						int *steep);
void				draw_line_pixel(t_fdf *fdf, t_point start, t_point end,
						int steep);
void				read_file(t_fdf *fdf);
///////////////////// for test ///////
void				dimension_color(t_fdf *fdf);
void				assign_offset(t_fdf *fdf);
int 				is_outside_window(int x, int y, int width, int height);
void 				redraw(t_fdf *fdf);
void				reset_map (t_fdf *fdf);
#endif
