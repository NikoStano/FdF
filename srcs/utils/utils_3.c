/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:50:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 17:12:48 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	get_channel(int color, int shift)
{
	return ((color >> shift) & 0xFF);
}

static int	make_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	interpolate_color(int c1, int c2, float ratio)
{
	int		r;
	int		g;
	int		b;
	int		r1;
	int		r2;

	if (ratio < 0.0f)
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;
	r1 = get_channel(c1, 16);
	r2 = get_channel(c2, 16);
	r = r1 + (int)((r2 - r1) * ratio);
	r1 = get_channel(c1, 8);
	r2 = get_channel(c2, 8);
	g = r1 + (int)((r2 - r1) * ratio);
	r1 = get_channel(c1, 0);
	r2 = get_channel(c2, 0);
	b = r1 + (int)((r2 - r1) * ratio);
	return (make_color(r, g, b));
}

int	get_color(t_app *a, int x, int y, int z)
{
	float	ratio;
	int		map_color;

	if (a->view.color_mode == COLOR_AUTO)
	{
		if (a->map.cbuf && y < a->map.rows && x < a->map.cols)
		{
			map_color = a->map.cbuf[y][x];
			if (map_color != -1)
				return (map_color);
		}
		return (WHITE);
	}
	if (z > 0)
		ratio = (float)z / 50.0f;
	else
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;
	return (interpolate_color(COLOR_LOW, COLOR_HIGH, ratio));
}

int	auto_rotate_loop(t_app *a)
{
	if (a->view.auto_rotate)
	{
		view_rotate_y(&a->view, 0.01);
		render(a);
	}
	return (0);
}
