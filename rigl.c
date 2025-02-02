#include "fdf.h"

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error\n");
        exit(1);
    }
    int fd = open(argv[1],O_RDONLY | 0666);
     if (fd == -1)
    {
        printf("Error\n");
        exit(1);
    }
    holishiiit(fd);
}

#include "fdf.h"

void initialize_data(t_data *data)
{
    data->mlx_ptr = mlx_init();

    if (data->mlx_ptr == NULL)
    {
        data->error = MLX_ERROR;
        return ;
    }
    data->win_ptr = mlx_new_window(data->mlx_ptr, W_W, W_H, "My window");
            if (data->win_ptr == NULL)
        {
            free(data->win_ptr);
            data->error = MLX_ERROR;
            return ;
        }
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, I_W, I_H);
    data->img.img_data = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.size_line, &data->img.endian);
    return;
}
void scaler (t_scale *scale, t_map_p *s)
{
    scale->x = (I_H / s->dims.height / 2) ;
    scale->y = (I_W / s->dims.width / 2) ;
    scale->z = scale->x ;

    if (scale->x < scale->y) 
        scale->y = scale->x;
    else
        scale->x = scale->y;
}

void iso (t_map_p *s)
{
    for (int i = 0; i < s->dims.height; i++)
    {
        for (int j = 0; j < s->dims.width; j++)
        {
            s->map[i][j] = isometric(s->map[i][j].x,s->map[i][j].y,s->map[i][j].z,s->map[i][j].colors, s->map[i][j].no_color);
        }
    }
}
t_map front_view(int x, int z, int color, int no_color) {
    t_map point;

    point.x = x;           
    point.y = -z;          
    point.z = z;           
    point.colors = color;
    point.no_color = no_color;

    return point;
}
void front (t_map_p *s)
{
    for (int i = 0; i < s->dims.height; i++)
    {
        for (int j = 0; j < s->dims.width; j++)
        {
            s->map[i][j] = front_view(s->map[i][j].x,s->map[i][j].z,s->map[i][j].colors, s->map[i][j].no_color);
        }
    }
}
void add_offset(t_map_p *s, t_offset *offsets)
{
    for (int i = 0; i < s->dims.height; i++)
    {
        for (int j = 0; j < s->dims.width; j++)
        {
            s->map[i][j].x += offsets->x;
            s->map[i][j].y += offsets->y;
        }
    }
}
void free_map (t_map_p *s)
{
    int i;

    i = 0;
    if (!s || !s->map) 
        return;
    while(i<s-> dims.height)
    {
        if (s->map[i])
            free (s->map[i]);
        i++;
    }
     free(s->map);
    s->map = NULL;
}

void holishiiit (int fd)
{
    t_data data;
    //t_map_p s;
    t_scale scale;
    t_offset offsets;
    t_z z_values ;

    data.sa = parssing(fd);

    initialize_data(&data);
    mlx_key_hook(data.win_ptr,handle_keypress,&data);
    
    scaler(&scale, &data.sa);
    scaling(&data.sa,scale); 
    iso(&data.sa);
    //front(&s);
    calculate_offsets(&data.sa, &offsets);
    add_offset(&data.sa, &offsets);
    calculate_min_max_z(&data.sa, &z_values);
    coloring(&data.sa, &z_values);
    draw_lines(&data, &data.sa);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 0, 0);
    free_map(&data.sa);
    mlx_loop(data.mlx_ptr);
    free(data.mlx_ptr);
}

#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

unsigned int  char_tohex (char *s,int index)
{
    int x;
    unsigned int result;

    result = 0;
    x = index;
    if (s[x] == '0' && (s[x + 1] == 'x' || s[x + 1] == 'X'))
        x = index + 2;

    while ((s[x] >= '0' && s[x] <= '9') || (s[x] >= 'a' && s[x] <= 'f') || (s[x] >= 'A' && s[x] <= 'F'))
    {
        result *= 16;
        if (s[x] >= '0' && s[x] <= '9')
            result += s[x] - 48;
        else if (s[x]>='A' && s[x]<='F')
            result += s[x] - 'A'+ 10;
        else if (s[x]>='a' && s[x]<='f')
            result += s[x] - 'a'+ 10;
        x++;
    }
    return (result);
}
size_t	checker_map(char *str)
{
	size_t	x;
    size_t count;
    
    count  = 0;
	x = 0;
        while (str[x] == ' ')
            x++;
	while (str[x])
    {
        if(str[x] != ' ')
        {
            if  (str[x+1] == '\0')
            {
                count++;
            }
            x++;
        }
        else
        {
            if (str[x+1] != ' ')
                count++;
            x++;
        }
    }
	return (count);
}
///////////////////////////////////////////////////  isometric projection ////////////////////////////////////
void free_bigo(char **s,t_map_p bigloly)
{
    int i;
    i = 0;
        while (i < bigloly.dims.height)
        {
            if (s[i])
                free (s[i]);
            i++;
        }
        free(s);
}
t_map_p parssing (int fd)
{
    if (fd == -1)
    {
        printf("Error in Map ! \n");
        exit(1);
    }
	t_map_p bigloly;
    char *loly;
    char **bigo;
    int q = 0;
	char *a;
    loly = ft_strdup("");
    ////////////////////////////////////// read from  a file   and calculate  the  height ////////////////////////////////////////
 	while((a = get_next_line(fd)) != NULL)
	{
        loly = ft_strjoin(loly,a);
        q++;
		free(a);
	}
    ///////////////////////////////////////////// split    to a  2D array  type char  //////////////////////////////////////
    bigo = ft_split(loly,'\n');

    ////////////////////////// create a 2 arrays of  the struct that have x,y,z,colors ////////////////////////////////////
    bigloly.map = malloc (q * sizeof(t_map*));
    if (!bigloly.map)
    {
        printf("Error\n");
        exit(1);
    }

    int f;
    int words;
    int index;
    int line = 0;
    /////////////////////////////////////////////////  convert the char  2D array to  the struct  2 D array ///////////////////    
    while (line < q)
    {
        words = checker_map(bigo[line]);
        bigloly.map[line] = malloc(words*(sizeof(t_map)));
        f = 0;
        index = 0;
        while  (bigo[line][f])
        {
            if (bigo[line][f] == '-' || (bigo[line][f] <= '9' && bigo[line][f] >='0'))
            {
                bigloly.map[line][index].z =ft_atoi(bigo[line],f);
                bigloly.map[line][index].x = index;
                bigloly.map[line][index].y = line;
                bigloly.map[line][index].colors = 0xFFFFFF;
                bigloly.map[line][index].no_color = 1;
                while (bigo[line][f] >= '0'  && bigo[line][f] <= '9')
                    f++;
                if (bigo[line][f] == ',')
                {
                    f++;
                    bigloly.map[line][index].colors = char_tohex(bigo[line],f);
                    bigloly.map[line][index].no_color = 0;
                    while ((bigo[line][f] >= '0' && bigo[line][f] <= '9') ||(bigo[line][f] >= 'a' && bigo[line][f] <= 'f') ||(bigo[line][f] >= 'A' && bigo[line][f] <= 'F'))
                        f++;
                }
                index++;
                while (bigo[line][f] != ' ' && bigo[line][f] != '\0')
                    f++;    
            }
            while (bigo[line][f] == ' ')
                f++;   
        }
        line++;
    }

    bigloly.dims.height = line;
    bigloly.dims.width = words;
    free(loly);
    free_bigo(bigo,bigloly);
    return (bigloly);
}
#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

int clamp(int value) {
    return (value < 0) ? 0 : (value > 255) ? 255 : value;
}

int interpolate_color(int start_color, int end_color, float ratio) {
    int start_r = (start_color >> 16) & 0xFF;
    int start_g = (start_color >> 8) & 0xFF;
    int start_b = start_color & 0xFF;

    int end_r = (end_color >> 16) & 0xFF;
    int end_g = (end_color >> 8) & 0xFF;
    int end_b = end_color & 0xFF;

    int r = clamp(start_r + (int)(ratio * (end_r - start_r)));
    int g = clamp(start_g + (int)(ratio * (end_g - start_g)));
    int b = clamp(start_b + (int)(ratio * (end_b - start_b)));

    return (r << 16) | (g << 8) | b;
} 

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= I_W || y < 0 || y >= I_H)
        return;
    dst = img->img_data + (y * img->size_line + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

t_step choice(t_pos start, t_pos end)
{
    t_step guid;
    guid.y = 0;
    guid.x = 0;
    if (start.y > end.y)
        guid.y = -1;
    else if (end.y > start.y)
        guid.y = 1;

    if (start.x > end.x)
        guid.x = -1;
    else if (end.x > start.x)
        guid.x = 1;
    return guid;
}

void draw_myline(t_img *img, int x1, int y1, int x2, int y2, int color_start,int color_end)
{
    t_line line;
    int steep = abs(y2 - y1) > abs(x2 - x1);

    if (steep) {
        // Swap x and y coordinates
        int tmp;
        tmp = x1; x1 = y1; y1 = tmp;
        tmp = x2; x2 = y2; y2 = tmp;
        tmp = color_start; color_start = color_end; color_end = tmp;
    }

    if (x1 > x2) {
        // Swap start and end points
        int tmp;
        tmp = x1; x1 = x2; x2 = tmp;
        tmp = y1; y1 = y2; y2 = tmp;
        tmp = color_start; color_start = color_end; color_end = tmp; 
    }

    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    line.diff.x = abs(line.end.x - line.start.x);
    line.diff.y = abs(line.end.y - line.start.y);
    line.step = choice(line.start, line.end);
    int err = line.diff.x / 2;
    int ystep = (y1 < y2) ? 1 : -1;
    int total_steps = line.diff.x;
    int current_step = 0;


    while (line.start.x <= line.end.x) {
        /// color progression 
        float ratio = total_steps == 0 ? 0.5 : (float)current_step / total_steps;
        int color = interpolate_color(color_start, color_end, ratio);
        if (steep) {
            my_mlx_pixel_put(img, line.start.y, line.start.x, color);
        } else {
            my_mlx_pixel_put(img, line.start.x, line.start.y, color);
        }

        err -= line.diff.y;
        if (err < 0) {
            line.start.y += ystep;
            err += line.diff.x;
        }
        line.start.x++;
        current_step++;
    }
}

#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

int clamp(int value) {
    return (value < 0) ? 0 : (value > 255) ? 255 : value;
}

int interpolate_color(int start_color, int end_color, float ratio) {
    int start_r = (start_color >> 16) & 0xFF;
    int start_g = (start_color >> 8) & 0xFF;
    int start_b = start_color & 0xFF;

    int end_r = (end_color >> 16) & 0xFF;
    int end_g = (end_color >> 8) & 0xFF;
    int end_b = end_color & 0xFF;

    int r = clamp(start_r + (int)(ratio * (end_r - start_r)));
    int g = clamp(start_g + (int)(ratio * (end_g - start_g)));
    int b = clamp(start_b + (int)(ratio * (end_b - start_b)));

    return (r << 16) | (g << 8) | b;
} 

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= I_W || y < 0 || y >= I_H)
        return;
    dst = img->img_data + (y * img->size_line + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

t_step choice(t_pos start, t_pos end)
{
    t_step guid;
    guid.y = 0;
    guid.x = 0;
    if (start.y > end.y)
        guid.y = -1;
    else if (end.y > start.y)
        guid.y = 1;

    if (start.x > end.x)
        guid.x = -1;
    else if (end.x > start.x)
        guid.x = 1;
    return guid;
}

void draw_myline(t_img *img, int x1, int y1, int x2, int y2, int color_start,int color_end)
{
    t_line line;
    int steep = abs(y2 - y1) > abs(x2 - x1);

    if (steep) {
        // Swap x and y coordinates
        int tmp;
        tmp = x1; x1 = y1; y1 = tmp;
        tmp = x2; x2 = y2; y2 = tmp;
        tmp = color_start; color_start = color_end; color_end = tmp;
    }

    if (x1 > x2) {
        // Swap start and end points
        int tmp;
        tmp = x1; x1 = x2; x2 = tmp;
        tmp = y1; y1 = y2; y2 = tmp;
        tmp = color_start; color_start = color_end; color_end = tmp; 
    }

    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    line.diff.x = abs(line.end.x - line.start.x);
    line.diff.y = abs(line.end.y - line.start.y);
    line.step = choice(line.start, line.end);
    int err = line.diff.x / 2;
    int ystep = (y1 < y2) ? 1 : -1;
    int total_steps = line.diff.x;
    int current_step = 0;


    while (line.start.x <= line.end.x) {
        /// color progression 
        float ratio = total_steps == 0 ? 0.5 : (float)current_step / total_steps;
        int color = interpolate_color(color_start, color_end, ratio);
        if (steep) {
            my_mlx_pixel_put(img, line.start.y, line.start.x, color);
        } else {
            my_mlx_pixel_put(img, line.start.x, line.start.y, color);
        }

        err -= line.diff.y;
        if (err < 0) {
            line.start.y += ystep;
            err += line.diff.x;
        }
        line.start.x++;
        current_step++;
    }
}



#include "fdf.h"

// char	*ft_strdup(char *s)
// {
// 	char	*p;
// 	int		x;

// 	x = 0;
// 	p = malloc(ft_strlen((char *)s) + 1);
// 	if (p == NULL)
// 		return (NULL);
// 	while (s[x])
// 	{
// 		p[x] = s[x];
// 		x++;
// 	}
// 	p[x] = '\0';
// 	return (p);
// }

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

