#include "fdf.h"

void redraw(t_fdf *fdf)
 {
    memset(fdf->img.img_data, 0, W_W * W_H * (fdf->img.bits_per_pixel / 8));
	scaling(fdf);
	projection(fdf);
	calculate_offsets(fdf);
	calculate_min_max_z(fdf);
	coloring(fdf);
	draw_lines(fdf);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
}
