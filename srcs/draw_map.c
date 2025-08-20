/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:49 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/20 11:58:24 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static inline void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_img(t_image *img)
{
	my_mlx_pixel_put(img, img->x0, img->y0, img->color);
}

void	draw_line(t_image img)
{	
	img.dx = ft_abs(img.x1 - img.x0);
	img.sx = check_pos_point(img.x0, img.x1);
	img.dy = -ft_abs(img.y1 - img.y0);
	img.sy = check_pos_point(img.y0, img.y1);
	img.err = img.dx + img.dy;
	while (1)
	{
		draw_img(&img);
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
		draw_line(img);
	}
	if (y < img.rows - 1)
	{
		img.z_down = fdf->buff[y + 1][x];
		img.x1 = (x - (y + 1)) * fdf->view->scale + fdf->view->offset_x;
		img.y1 = (x + (y + 1)) * fdf->view->scale / 2 - img.z_down * \
			fdf->view->z_scale + fdf->view->offset_y;
		draw_line(img);
	}
}

static void	draw_map_internal(t_fdf *fdf, t_image *img)
{
	int		y;
	int		x;
	int		z;

	img->rows = fdf->map->rows;
	img->cols = fdf->map->cols;
	y = 0;
	while (y < img->rows)
	{
		x = 0;
		z = 0;
		while (x < img->cols)
		{
			z = fdf->buff[y][x];
			if (z != 0)
				img->color = 0xFFAA33;
			else
				img->color = 0xFFFFFF;
			draw_shit(fdf, *img, x, y);
			x++;
		}
		y++;
	}
}
