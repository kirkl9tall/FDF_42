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
/////////////////////////////////////////////////// draw line.// ///////////////////////

void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 || y1 != y2) {
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
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
        while (t < words)
        {
            printf("%d ",bigloly[c][t].z);
            t++;
        }
        c++;
        printf("\n");
    }
    void * win_ptr;
    void * mlx_ptr;
    void * img_ptr;
    int x_w = 1000;
    int y_w = 800;


    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,x_w,y_w,"test map !");
    //img_ptr = mlx_new_image (mlx_ptr, dims.widht, dims.height );

   // mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );
    //mlx_put_image_to_window ( mlx_ptr, win_ptr, img_ptr, 300, 300);

    t_scale scale;

    scale.x = x_w / dims.widht;   
    scale.y = y_w / dims.height;

    if (scale.x < scale.y) {
        scale.y = scale.x;  
    } 
    else
    {
        scale.x = scale.y;
    }
    for (int i = 1; i <= dims.height; i++) {
    for (int j = 1; j < dims.widht; j++) 
    {

        int x = j * scale.x;
        int y = i * scale.y; 
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
        //////////////////////////////// a faire solo /////////////////////////////
        if (j + 1 < dims.widht) {
            int x2 = (j + 1) * scale.x;
            int y2 = i * scale.x;
            draw_line(mlx_ptr, win_ptr, x, y, x2, y2, 0xFFFFFF); // Draw horizontal line
        }

        // Connect to the bottom neighbor
        if (i + 1 < dims.height) {
            int x2 = j * scale.x;
            int y2 = (i + 1) * scale.y;
            draw_line(mlx_ptr, win_ptr, x, y, x2, y2, 0xFFFFFF); // Draw vertical line
        }
    }
}
//////////////////////////////////////////////////////////////////////////////

    mlx_loop(mlx_ptr);
}