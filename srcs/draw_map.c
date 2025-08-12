/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:49 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:30 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_line(int x0, int y0, int x1, int y1)
{
	t_fdf	*fdf;
	int	err;
	int	e2;

	err = ft_abs(x1 - x0) + ft_abs(x1 - x0);
	while (x0 >= 0 && y0 >= 0 && x0 < WIDTH && y0 < HEIGHT)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
	}
}

void	find_it(int y0, int x0, int y1, int x1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;

	dx = ft_abs(x1 - x0);
	sx = check_pos_point(x0, x1);
	dy = -ft_abs(y1 - y0);
	sy = check_pos_point(y0, y1);

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

static void draw_map_internal(t_fdf *fdf, int offx, int offy, int sc, int zsc)
{
	int y;
	int x;
	int rows;
	int cols;
	int	z;
	int	z_right;
	int	z_down;
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	y = 0;
	rows = fdf->map->rows;
	cols = fdf->map->cols;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			z = fdf->buff[y][x];
			x0 = (x - y) * sc + offx;
			y0 = (x + y) * sc / 2 - z * zsc + offy;
			if (x < cols - 1)
			{
				z_right = fdf->buff[y][x + 1];
				x1 = ((x + 1) - y) * sc + offx;
				y1 = ((x + 1) + y) * sc / 2 - z_right * zsc + offy;
				draw_line(fdf->mlx, fdf->win, x0, y0, x1, y1);
			}
			if (y < rows - 1)
			{
				z_down = fdf->buff[y + 1][x];
				x1 = (x - (y + 1)) * sc + offx;
				y1 = (x + (y + 1)) * sc / 2 - z_down * zsc + offy;
				draw_line(fdf->mlx, fdf->win, x0, y0, x1, y1);
			}
			x++;
		}
		y++;
	}
}

void	draw_map_ctx(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	draw_map_internal(fdf, fdf->view->offset_x, fdf->view->offset_y, fdf->view->scale, fdf->view->z_scale);
}
