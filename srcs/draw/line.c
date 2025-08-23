/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:08 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/22 01:38:15 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	check_dir(int x, int y)
{
	if (x < y)
		return (1);
	return (-1);
}

static void	bres_init(t_bres *b, t_v2 a, t_v2 b2)
{
	int	tmp;

	tmp = b2.x - a.x;
	b->dx = ft_abs(tmp);
	tmp = b2.y - a.y;
	b->dy = -ft_abs(tmp);
	b->sx = check_dir(a.x, b2.x);
	b->sy = check_dir(a.y, b2.y);
	b->err = b->dx + b->dy;
}

void	draw_line(t_img *img, t_v2 a, t_v2 b2, int color)
{
	t_bres	b;
	int		e2;

	bres_init(&b, a, b2);
	while (1)
	{
		put_px(img, a.x, a.y, color);
		if (a.x == b2.x && a.y == b2.y)
			break ;
		e2 = b.err << 1;
		if (e2 >= b.dy)
		{
			b.err += b.dy;
			a.x += b.sx;
		}
		if (e2 <= b.dx)
		{
			b.err += b.dx;
			a.y += b.sy;
		}
	}
}
