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

int main (void)
{
	int i = open("10-2.fdf", O_RDWR , 0666);
	int **bigloly;
    char *loly;
    char **bigo;
    int q = 0;
	char *a;

    loly = malloc (500);
 	while((a = get_next_line(i)) != NULL)
	{
        loly = ft_strjoin(loly,a);
        q++;
		free(a);
	}
    bigo = ft_split(loly,'\n');

    bigloly = malloc (q * sizeof(int*));
    printf("%s\n",bigo[0]);
    int f = 0;
    int words;

    int index = 0;
    int at = 0;
    int pars = 0;
    while (pars < q)
        {
        words = checker_map(bigo[pars]);
        bigloly[pars] = malloc(words*(sizeof(int)));
        f = 0;
        while  (bigo[pars][f])
        {
            if (bigo[pars][f] == ' ') 
                f++;

            else if (bigo[pars][f] == '-')
            {
                at = ft_atoi(bigo[pars],f); 
                bigloly[pars][index] = at;
                //printf("minus %d\n",at);
                index++;
                while (bigo[pars][f] != ' ')
                    f++;    
            }
            else if (bigo[pars][f] <= '9' && bigo[pars][f] >='0' )
            {
                at = ft_atoi(bigo[pars],f); 
               // printf("number %d\n",at);
                bigloly[pars][index] = at;
                index++;
                while (bigo[pars][f] != ' ' && bigo[pars][f] != '\0' )
                    f++;   
            }
            f++;    
        }
        pars++;
    }
    int t = 0;
    while (t <= 9)
    {
        printf("%d\n",bigloly[0][t]);
        t++;
    }
   // printf("%ld\n", sizeof((bigloly[0]) ) / sizeof(bigloly[0][0]));

    // printf("%d\n",at);
	close(i);
}