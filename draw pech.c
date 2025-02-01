
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= I_W || y < 0 || y >= I_H)
        return;
    dst = img->img_data + (y * img->size_line + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

t_step choice(t_pos start, t_pos end)
{
    t_step guid;
    guid.y = 0;
    guid.x = 0;
    if (start.y > end.y)
        guid.y = -1;
    else if (end.y > start.y)
        guid.y = 1;

    if (start.x > end.x)
        guid.x = -1;
    else if (end.x > start.x)
        guid.x = 1;
    return guid;
}

void draw_myline(t_img *img, int x1, int y1, int x2, int y2, int color)
{
    t_line line;

    line.start.x = x1;
    line.start.y = y1;
    line.end.x = x2;
    line.end.y = y2;
    line.diff.x = abs(line.end.x - line.start.x);
    line.diff.y = abs(line.end.y - line.start.y);
    line.step = choice(line.start, line.end);
    line.p = (2 * line.diff.y) - line.diff.x;

    my_mlx_pixel_put(img, line.start.x, line.start.y, color);

    while (line.start.x != line.end.x || line.start.y != line.end.y)
    {
        if (line.diff.x >= line.diff.y)
        {
            if (line.p < 0)
            {
                line.start.x += line.step.x;
                line.p += 2 * line.diff.y;
            }
            else
            {
                line.start.x += line.step.x;
                line.start.y += line.step.y;
                line.p += (2 * line.diff.y) - (2 * line.diff.x);
            }
        }
        else
        {
            if (line.p < 0)
            {
                line.start.y += line.step.y;
                line.p += 2 * line.diff.x;
            }
            else
            {
                line.start.x += line.step.x;
                line.start.y += line.step.y;
                line.p += (2 * line.diff.x) - (2 * line.diff.y);
            }
        }
        my_mlx_pixel_put(img, line.start.x, line.start.y, color);
    }
}