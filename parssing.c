#include "fdf.h"

// void init_fdf(t_fdf * fdf,char *title)
// {
//     fdf->mlx = mlx_init();
//     fdf->win = mlx_new_window(fdf->mlx, W_W, W_H, title);
//     if (!fdf->mlx) 
//         exit(MLX_ERROR);
//     if (!fdf->win)
//         exit(MLX_ERROR);
//     fdf->img.img_ptr = mlx_new_image(fdf->mlx, I_W, I_H);
//     fdf->img.img_data = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bits_per_pixel, &fdf->img.size_line, &fdf->img.endian);
//     fdf->zoom = 1.0;
//     fdf->offset.x = W_W / 2;
//     fdf->offset.y = W_H / 2;
//     fdf->projection = PROJ_ISO;

// }
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
void assigning (t_fdf *fdf, char **ft_split, t_pos *pos, t_index *index)
{
    fdf->map[pos->i][index->index].z = ft_atoi(ft_split[pos->i], pos->j);
    fdf->map[pos->i][index->index].x = index->index;
    fdf->map[pos->i][index->index].y = pos->i;
    fdf->map[pos->i][index->index].color = 0xFFFFFF;
    fdf->map[pos->i][index->index].has_color = 0;
    while (ft_isdigit(ft_split[pos->i][pos->j]) || ft_split[pos->i][pos->j] == '-')
        pos->j++;
    if (ft_split[pos->i][pos->j] == ',')
    {
        pos->j++;
        fdf->map[pos->i][index->index].color = char_tohex(ft_split[pos->i], pos->j);
        fdf->map[pos->i][index->index].has_color = 1;
        while (ft_isdigit(ft_split[pos->i][pos->j]) || ft_isalpha(ft_split[pos->i][pos->j]))
            pos->j++;
    }
    index->index++;
}

void parssing (t_fdf *fdf , char **split_line)
{
    t_pos pos;
    t_index index;

    pos.i = 0;
    while (pos.i < fdf->height)
    {
        index.words = checker_map(split_line[pos.i]);
        fdf->map[pos.i] = malloc(sizeof(t_point) * index.words);
        index.index = 0;
        pos.j = 0;
        while (split_line[pos.i][pos.j])
        {
            if (split_line[pos.i][pos.j] == '-' || ft_isdigit(split_line[pos.i][pos.j]))
            {
                assigning(fdf, split_line, &pos, &index);
            }
            else
                pos.j++;
        }
        pos.i++;
    }
    fdf->width = index.words;
}
void parse_map (t_fdf *fdf, int fd)
{
    char *container;
    char * buffer;
    char **split_line;
    int lines;

    lines = 0;
    container = ft_strdup("");
    while ((buffer = get_next_line(fd)) != NULL)
    {
        container = ft_strjoin(container, buffer);
        lines++;
        free(buffer);
    }
    split_line = ft_split(container, '\n');
    free(container);
    fdf->map = malloc(sizeof(t_point *) * lines );
    if (!fdf->map)
        exit(1);
    fdf->height = lines;
    parssing (fdf, split_line);
    for (int i = 0; i < fdf->height; i++)
    free(split_line[i]);
    free(split_line);
}
