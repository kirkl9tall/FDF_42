#include "fdf.h"

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
    fdf->map[pos->i][index->index].has_color = 1;
    while (ft_isdigit(ft_split[pos->i][pos->j]) || ft_split[pos->i][pos->j] == '-')
        pos->j++;
    if (ft_split[pos->i][pos->j] == ',')
    {
        pos->j++;
        fdf->map[pos->i][index->index].color = char_tohex(ft_split[pos->i], pos->j);
        fdf->map[pos->i][index->index].has_color = 0;
        while (ft_isdigit(ft_split[pos->i][pos->j]) || ft_isalpha(ft_split[pos->i][pos->j]))
            pos->j++;
    }
    index->index++;
}
void copy_data (t_fdf *fdf)
{
    int x;
    int y;

    x= 0;
    fdf->mapv = malloc (sizeof (t_point *)*fdf->height);
    if (!fdf->mapv)
        return;
    while (x < fdf->height)
    {
        y = 0;
        fdf->mapv[x]= malloc(sizeof(t_point) * fdf->width);

        if (!fdf->mapv[x])
            return;

        while (y < fdf->width)
        {
            fdf->mapv[x][y].z = fdf->map[x][y].z;
            fdf->mapv[x][y].x = fdf->map[x][y].x;
            fdf->mapv[x][y].y = fdf->map[x][y].y;
            fdf->mapv[x][y].color = fdf->map[x][y].color;
            fdf->mapv[x][y].has_color = fdf->map[x][y].has_color;
            y++;
        }
        x++;
    }
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
void read_file(t_fdf *fdf)
{
    char *arr;
    int fd;

    fd = open(fdf->argv, O_RDONLY);
    fdf->line = 0;
    arr = get_next_line(fd);
    while (arr)
    {
        free(arr);
        arr = get_next_line(fd);
        fdf->line++;
    }
    free(arr);
    fdf->height = fdf->line;
    close(fd);
    return ;
}
void parse_map (t_fdf *fdf, int fd)
{
    char *container;
    char * buffer;
    char **split_line;

    container = ft_strdup("");
    read_file(fdf);
    while (fdf->line--)
    {
        buffer = get_next_line(fd);
        container = ft_strjoin(container, buffer);
        free(buffer);
    }
    split_line = ft_split(container, '\n');
    free(container);
    fdf->line = fdf->height;
    fdf->map = malloc(sizeof(t_point *) * fdf->height );
    if (!fdf->map)
        return;
    parssing (fdf, split_line);
    copy_data(fdf);
        while (fdf->line--)
            free(split_line[fdf->line]);
    free(split_line);
}