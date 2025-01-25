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
    loly = malloc (4000);
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
    bigloly.map = malloc (q * sizeof(t_map_p*));
    int f = 0;
    int words;
    int index = 0;
    int at = 0;
    int pars = 0;

    /////////////////////////////////////////////////  convert the char  2D array to  the struct  2 D array ///////////////////    
    while (pars < q)
    {
        words = checker_map(bigo[pars]);
        bigloly.map[pars] = malloc(words*(sizeof(t_map_p)));
        f = 0;
        index = 0;
        unsigned int color = 0;
        while  (bigo[pars][f])
        {
            if (bigo[pars][f] == ' ') 
                f++;
            else if (bigo[pars][f] == '-' || bigo[pars][f] <= '9' && bigo[pars][f] >='0' )
            {
                at = ft_atoi(bigo[pars],f); 
                bigloly.map[pars][index].z = at;
                bigloly.map[pars][index].x = index;
                bigloly.map[pars][index].y = pars;
                bigloly.map[pars][index].colors = 0x000000;
                while (bigo[pars][f] >= '0'  && bigo[pars][f] <= '9')
                    f++;
                if (bigo[pars][f] == ',')
                {
                    f++;
                    bigloly.map[pars][index].colors = char_tohex(bigo[pars],f);
                }
                index++;
                while (bigo[pars][f] != ' ' && bigo[pars][f] != '\0')
                    f++;    
            }
            f++;    
        }
        pars++;
    }
    bigloly.dims.height = pars;
    bigloly.dims.width = words;
    return (bigloly);
}