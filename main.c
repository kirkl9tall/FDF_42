#include "fdf.h"


unsigned int  char_tohex (char *s,int index)
{
    int x;
    unsigned int result;

    x = index;
    result = 0;

    if (s[x] == '0' && (s[x+1] == 'x' || s[1] == 'X'))
        x = 2;
    while (s[x] ||s[x] != ' ')
    {
        if (s[x] >= '0' && s[x] <= '9')
            result += s[x] - 48;
        else if (s[x]>='A' && s[x]<='Z')
            result += s[x] - ('A'+10);
        else if (s[x]>='a' && s[x]<='z')
            result += s[x] - ('a'+10);
        else 
        {
            printf ("Hexa error !");
            return (0);
        }
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

int main (void)
{
	int i = open("10-4.fdf", O_RDWR , 0666);
	t_map **bigloly;
    char *loly;
    char **bigo;
    int q = 0;
	char *a;

    loly = malloc (4000);
 	while((a = get_next_line(i)) != NULL)
	{
        loly = ft_strjoin(loly,a);
        q++;
		free(a);
	}
    
    bigo = ft_split(loly,'\n');
    bigloly = malloc (q * sizeof(t_map*));
    int f = 0;
    int words;
    int index = 0;
    int at = 0;
    int pars = 0;

    //------------------------------ width ==================
    
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
                
                bigloly[pars][index].colors = 0;
                index++;
                while (bigo[pars][f] != ' ' && bigo[pars][f] != '\0')
                    f++;    
            }
            else if (bigo[pars][f] == ',' )
            {
                f++;
                bigloly[pars][index].colors = char_tohex(bigo[pars],f);
                bigloly[pars][index].x = index;
                bigloly[pars][index].y = pars;
                while (bigo[pars][f] != ' ' && bigo[pars][f] != '\0');
                f++;
            }
            f++;    
        }
        pars++;
    }
    int c = 0;
    while (c < 9)
    {
        int t = 0;
        while (t <= 9)
        {
            printf("%d ",bigloly[c][t].colors);
            t++;
        }
        c++;
        printf("\n");
    }
}

