#include "fdf.h"
#include "minilibx-linux/mlx.h"

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

int main (int argc ,char *argv[])
{
	int i = open("10-2.fdf", O_RDONLY , 0666);
        if (i < 0) return 1;
	t_map **bigloly;
    char *loly;
    char **bigo;
    int q = 0;
	char *a;
    loly = malloc (4000);
    ////////////////////////////////////// read from  a file   and calculate  the  height ////////////////////////////////////////
 	while((a = get_next_line(i)) != NULL)
	{
        loly = ft_strjoin(loly,a);
        q++;
		free(a);
	}
    ///////////////////////////////////////////// split    to a  2D array  type char  //////////////////////////////////////
    bigo = ft_split(loly,'\n');

    ////////////////////////// create a 2 arrays of  the struct that have x,y,z,colors ////////////////////////////////////
    bigloly = malloc (q * sizeof(t_map*));
    int f = 0;
    int words;
    int index = 0;
    int at = 0;
    int pars = 0;

    /////////////////////////////////////////////////  convert the char  2D array to  the struct  2 D array ///////////////////    
    while (pars < q)
    {
        words = checker_map(bigo[pars]);
        bigloly[pars] = malloc(words*(sizeof(t_map)));
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
                bigloly[pars][index].z = at;
                bigloly[pars][index].x = index;
                bigloly[pars][index].y = pars;
                bigloly[pars][index].colors = 0x000000;
                while (bigo[pars][f] >= '0'  && bigo[pars][f] <= '9')
                    f++;
                if (bigo[pars][f] == ',')
                {
                    f++;
                    bigloly[pars][index].colors = char_tohex(bigo[pars],f);
                }
                index++;
                while (bigo[pars][f] != ' ' && bigo[pars][f] != '\0')
                    f++;    
            }
            f++;    
        }
        pars++;
    }

    ////////////////////////////////////////// struct dimensions  done ////////////////////////////////////////////
    t_dim dims;
    dims.height = pars;
    dims.widht = words;
///////////////////////////////////////// open a window   of mlx--- ///////////////////////////////////////////////////////

    int c = 0;
    while (c < pars)
    {
        int t = 0;
        while (t <= 9)
        {
            printf("%d ",bigloly[c][t].z);
            t++;
        }
        c++;
        printf("\n");
    }
    void * win_ptr;
    void * mlx_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,700,700,"test map !");

    mlx_loop(mlx_ptr);

}