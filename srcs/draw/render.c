/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:34:59 by nistanoj          #+#    #+#             */
/*   Updated: 2025/09/03 16:10:43 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static t_v3	v3_of(int x, int y, int z)
{
	t_v3	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

static void	draw_right_neighbor(t_app *a, int x, int y)
{
	t_v2	s;
	t_v2	t;
	t_v3	p;
	int		z1;
	int		z2;

	z1 = a->map.zbuf[y][x];
	z2 = a->map.zbuf[y][x + 1];
	p = v3_of(x, y, z1);
	iso_project(p, &a->view, &s);
	p = v3_of(x + 1, y, z2);
	iso_project(p, &a->view, &t);
	draw_line(&a->fb, s, t, base_color(z1));
}

static void	draw_bottom_neighbor(t_app *a, int x, int y)
{
	t_v2	s;
	t_v2	t;
	t_v3	p;
	int		z1;
	int		z2;

	z1 = a->map.zbuf[y][x];
	z2 = a->map.zbuf[y + 1][x];
	p = v3_of(x, y, z1);
	iso_project(p, &a->view, &s);
	p = v3_of(x, y + 1, z2);
	iso_project(p, &a->view, &t);
	draw_line(&a->fb, s, t, base_color(z1));
}

void	render(t_app *a)
{
	int	y;
	int	x;

	img_clear(&a->fb);
	y = 0;
	while (y < a->map.rows)
	{
		x = 0;
		while (x < a->map.cols)
		{
			if (x + 1 < a->map.cols)
				draw_right_neighbor(a, x, y);
			if (y + 1 < a->map.rows)
				draw_bottom_neighbor(a, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->fb.img, 0, 0);
}
