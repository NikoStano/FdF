/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:49 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 19:00:57 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
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

void	draw_map(t_env *env)
{
	int scale = SCALE;
	int z_scale = Z_SCALE;
	int offset_x = env->offset_x;
	int offset_y = env->offset_y;
	int y, x;

	y = 0;
	while (y < env->rows)
	{
		x = 0;
		while (x < env->cols)
		{
			int z = env->buff[y][x];
			int x0 = (x - y) * scale + offset_x;
			int y0 = (x + y) * scale / 2 - z * z_scale + offset_y;
			if (x < env->cols - 1)
			{
				int z_right = env->buff[y][x + 1];
				int x1 = ((x + 1) - y) * scale + offset_x;
				int y1 = ((x + 1) + y) * scale / 2 - z_right * z_scale + offset_y;
				draw_line(env->mlx, env->win, x0, y0, x1, y1);
			}
			if (y < env->rows - 1)
			{
				int z_down = env->buff[y + 1][x];
				int x1 = (x - (y + 1)) * scale + offset_x;
				int y1 = (x + (y + 1)) * scale / 2 - z_down * z_scale + offset_y;
				draw_line(env->mlx, env->win, x0, y0, x1, y1);
			}
			x++;
		}
		y++;
	}
}
