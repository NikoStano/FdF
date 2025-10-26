/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:12 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 15:54:44 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	img_create(t_app *a, t_img *img, int w, int h)
{
	img->w = w;
	img->h = h;
	img->img = mlx_new_image(a->mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
}

void	img_destroy(t_app *a, t_img *img)
{
	if (!img || !img->img)
		return ;
	mlx_destroy_image(a->mlx, img->img);
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->w = 0;
	img->h = 0;
}

void	img_clear(t_img *img)
{
	ft_bzero(img->addr, img->line_len * img->h);
}

void	put_px(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}
