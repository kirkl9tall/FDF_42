#include "fdf.h"

void scaler_ofsv (t_fdf *fdf)
{
    fdf->scale.x = (I_H / fdf->height / 2) / 2 ;
    fdf->scale.y = (I_W / fdf->width / 2)  / 2;
    fdf->scale.z = fdf->scale.x ;
    
    if (fdf->scale.x < fdf->scale.y) 
        fdf->scale.y = fdf->scale.x;
    else
        fdf->scale.x = fdf->scale.y;
    fdf->ofsset_value.x_min = INT_MAX;
    fdf->ofsset_value.y_min = INT_MAX;
    fdf->ofsset_value.x_max = INT_MIN;
    fdf->ofsset_value.y_max = INT_MIN;
}

void  scaling (t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    while (i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            fdf->map[i][j].x *= fdf->scale.x;
            fdf->map[i][j].y *= fdf->scale.y;
            fdf->map[i][j].z *= (fdf->scale.x);
            j++;
        }
        i++;
    }
}

void projection (t_fdf *fdf)
{
    int i;
    int j;
    int origin_x;

    i = 0;
    while (i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            if (fdf->projection == PROJ_ISO)
            {   
                origin_x = fdf->map[i][j].x;
                fdf->map[i][j].x = (fdf->map[i][j].x  - fdf->map[i][j].y ) * cos(0.523599);
                fdf->map[i][j].y = (origin_x + fdf->map[i][j].y) * sin(0.523599) -fdf->map[i][j].z;
            }
            else if (fdf->projection == PROJ_FRONT)
                fdf->map[i][j].y = fdf->map[i][j].z;
            else if (fdf->projection == PROJ_SIDE)
                fdf->map[i][j].y = -fdf->map[i][j].z;
            j++;
        }
        i++;
    }
}

void calculate_offsets(t_fdf *fdf) 
{
    int i;
    int j;
    i = 0;
    while  ( i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            fdf->map[i][j].x += fdf->offset.x;
            fdf->map[i][j].y += fdf->offset.y;

            if (fdf->map[i][j].x < fdf->ofsset_value.x_min)
                fdf->ofsset_value.x_min = fdf->map[i][j].x;
            if (fdf->map[i][j].x > fdf->ofsset_value.x_max)
                fdf->ofsset_value.x_max = fdf->map[i][j].x;
            if (fdf->map[i][j].y < fdf->ofsset_value.y_min)
                fdf->ofsset_value.y_min = fdf->map[i][j].y;
            if (fdf->map[i][j].y > fdf->ofsset_value.y_max)
                fdf->ofsset_value.y_max = fdf->map[i][j].y;
            j++;
        }
        i++;
    }
    fdf->offset.x = (I_W / 2) - (fdf->ofsset_value.x_max + fdf->ofsset_value.x_min) / 2;
    fdf->offset.y = (I_H / 2) - (fdf->ofsset_value.y_max + fdf->ofsset_value.y_min) / 2;
}

void calculate_min_max_z(t_fdf *fdf) 
{
    int i;
    int j;

    i = 0;
    fdf->z_min = INT_MAX;
    fdf->z_max = INT_MIN;
    while (i < fdf->height) 
    {
        j = 0;
        while (j < fdf->width) {
            if (fdf->map[i][j].z < fdf->z_min)
                fdf->z_min = fdf->map[i][j].z;
            if (fdf->map[i][j].z > fdf->z_max)
                fdf->z_max = fdf->map[i][j].z;
            j++;
        }
        i++;
    }
}