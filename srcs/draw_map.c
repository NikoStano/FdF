/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:49 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/13 12:41:12 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1)
    {
        mlx_pixel_put(mlx, win, x0, y0, 0xFFFFFF);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

static void draw_map_internal(t_fdf *fdf, int offx, int offy, int sc, int zsc)
{
    int y;
    int x;
    int rows = fdf->map->rows;
    int cols = fdf->map->cols;

    y = 0;
    while (y < rows)
    {
        x = 0;
        while (x < cols)
        {
            int z = fdf->buff[y][x];
            int x0 = (x - y) * sc + offx;
            int y0 = (x + y) * sc / 2 - z * zsc + offy;
            if (x < cols - 1)
            {
                int z_right = fdf->buff[y][x + 1];
                int x1 = ((x + 1) - y) * sc + offx;
                int y1 = ((x + 1) + y) * sc / 2 - z_right * zsc + offy;
                draw_line(fdf->mlx, fdf->win, x0, y0, x1, y1);
            }
            if (y < rows - 1)
            {
                int z_down = fdf->buff[y + 1][x];
                int x1 = (x - (y + 1)) * sc + offx;
                int y1 = (x + (y + 1)) * sc / 2 - z_down * zsc + offy;
                draw_line(fdf->mlx, fdf->win, x0, y0, x1, y1);
            }
            x++;
        }
        y++;
    }
}

void draw_map_ctx(t_fdf *fdf)
{
    mlx_clear_window(fdf->mlx, fdf->win);
    draw_map_internal(
        fdf,
        fdf->view->offset_x,
        fdf->view->offset_y,
        fdf->view->scale,
        fdf->view->z_scale
    );
}
