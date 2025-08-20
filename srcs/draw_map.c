/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:49 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/20 12:54:22 by nistanoj         ###   ########.fr       */
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
			if (z > 0)
				img->color = 0x309060;
			else if (z < 0)
				img->color = 0x306090;
			else
				img->color = 0x906030;
			draw_shit(fdf, *img, x, y);
			x++;
		}
		y++;
	}
}

void	draw_img(t_image *img)
{
	my_mlx_pixel_put(img, img->x0, img->y0, img->color);
}

void	draw_map_ctx(t_fdf *fdf)
{
	t_image	img;

	mlx_clear_window(fdf->mlx, fdf->win);
	img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	draw_map_internal(fdf, &img);
	mlx_put_image_to_window(fdf->mlx, fdf->win, img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, img.img);
}
