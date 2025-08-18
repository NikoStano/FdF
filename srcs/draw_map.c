/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:49 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/18 22:15:42 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_line(t_fdf *fdf, t_image img)
{	
	img.dx = ft_abs(img.x1 - img.x0);
	img.sx = check_pos_point(img.x0, img.x1);
	img.dy = -ft_abs(img.y1 - img.y0);
	img.sy = check_pos_point(img.y0, img.y1);
	img.err = img.dx + img.dy;
	while (1)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, img.x0, img.y0, 0xFFFFFF);
		if (img.x0 == img.x1 && img.y0 == img.y1)
			break ;
		img.e2 = 2 * img.err;
		if (img.e2 >= img.dy)
		{
			img.err += img.dy;
			img.x0 += img.sx;
		}
		if (img.e2 <= img.dx)
		{
			img.err += img.dx;
			img.y0 += img.sy;
		}
	}
}

static void	draw_shit(t_fdf *fdf, t_image img, int x, int y)
{
	int		z;

	z = fdf->buff[y][x];
	img.x0 = (x - y) * fdf->view->scale + fdf->view->offset_x;
	img.y0 = (x + y) * fdf->view->scale / 2 - z * fdf->view->z_scale + \
		fdf->view->offset_y;
	if (x < img.cols - 1)
	{
		img.z_right = fdf->buff[y][x + 1];
		img.x1 = ((x + 1) - y) * fdf->view->scale + fdf->view->offset_x;
		img.y1 = ((x + 1) + y) * fdf->view->scale / 2 - img.z_right * \
			fdf->view->z_scale + fdf->view->offset_y;
		draw_line(fdf, img);
	}
	if (y < img.rows - 1)
	{
		img.z_down = fdf->buff[y + 1][x];
		img.x1 = (x - (y + 1)) * fdf->view->scale + fdf->view->offset_x;
		img.y1 = (x + (y + 1)) * fdf->view->scale / 2 - img.z_down * \
			fdf->view->z_scale + fdf->view->offset_y;
		draw_line(fdf, img);
	}
}

static void	draw_map_internal(t_fdf *fdf)
{
	int		y;
	int		x;
	t_image	img;

	img.rows = fdf->map->rows;
	img.cols = fdf->map->cols;
	y = 0;
	while (y < img.rows)
	{
		x = 0;
		while (x < img.cols)
		{
			draw_shit(fdf, img, x, y);
			x++;
		}
		y++;
	}
}

void	draw_map_ctx(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	draw_map_internal(fdf);
}
