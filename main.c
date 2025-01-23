#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
t_map  isometric(int x, int y, t_map point)
{
 point.x = (x - y) * cos(0.523599);
 point.y = (x + y) * sin(0.523599) - point.z;
 return (point);
}

int main ()
{

    void * win_ptr;
    void * mlx_ptr;
    void * img_ptr;
    int x_w = 1000;
    int y_w = 800;


    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr,x_w,y_w,"test map !");

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
    t_map lala;

    for (int i = 1; i <= dims.height -1; i++) {
    for (int j = 1; j <= dims.widht -1; j++) 
    {
        bigloly[i][j].x = j * scale.x;
        bigloly[i][j].y = i * scale.y; 
        //lala = isometric(bigloly[i][j].x, bigloly[i][j].y, bigloly[i][j]);
        mlx_pixel_put(mlx_ptr, win_ptr, bigloly[i][j].x, bigloly[i][j].y, 0xFFFFFF);

        //////////////////////////// a faire solo /////////////////////////////
        if (j + 1 < dims.widht) {
            int x2 = (j + 1) * scale.x;
            int y2 = i * scale.x;

            draw_myline(win_ptr,mlx_ptr,bigloly[i][j].x,bigloly[i][j].y,x2,y2,0xFFFFFF); // Draw horizontal line
        }

        // Connect to the bottom neighbor
        if (i + 1 < dims.height) {
            int x2 = j * scale.x;
            int y2 = (i + 1) * scale.y;
            draw_myline(win_ptr,mlx_ptr,bigloly[i][j].x,bigloly[i][j].y,x2,y2,0xFFFFFF); // Draw vertical line
        }
    }
}
//////////////////////////////////////////////////////////////////////////////

    mlx_loop(mlx_ptr);

}