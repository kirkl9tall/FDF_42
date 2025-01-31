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
t_map_p parssing (int fd)
{
    if (fd == -1)
    {
        printf("Error\n");
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
    free(loly);

    ////////////////////////// create a 2 arrays of  the struct that have x,y,z,colors ////////////////////////////////////
    bigloly.map = malloc (q * sizeof(t_map_p*));
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
        bigloly.map[line] = malloc(words*(sizeof(t_map_p)));
        f = 0;
        index = 0;
        unsigned int color = 0;
        while  (bigo[line][f])
        {
            // if (bigo[line][f] == ' ') 
            //     f++;
            if (bigo[line][f] == '-' || bigo[line][f] <= '9' && bigo[line][f] >='0' )
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
    // for (int i = 0; i < line; i++)
    // {
    //     for (int j = 0; j < words; j++)
    //     {
    //         printf("%d ",bigloly.map[i][j].colors);
    //     }
    //     printf("\n");
    // }
    bigloly.dims.height = line;
    bigloly.dims.width = words;
    free(bigo);
    // printf("%d\n",bigloly.dims.height);
    // printf("%d\n",bigloly.dims.width);
    return (bigloly);
}