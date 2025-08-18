/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:34:32 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/18 22:25:57 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	view_reset(t_view *v)
{
	v->offset_x = OFFSET_X;
	v->offset_y = OFFSET_Y;
	v->scale = SCALE;
	v->z_scale = Z_SCALE;
}

static int	clampi(int val, int lo, int hi)
{
	if (val < lo)
		return (lo);
	if (val > hi)
		return (hi);
	return (val);
}

void	apply_zoom(t_fdf *fdf, double factor, int p_x, int p_y)
{
	int		old;
	int		new;
	double	k;

	old = fdf->view->scale;
	new = clampi((int)round(old * factor), MIN_SCALE, MAX_SCALE);
	if (new == old)
		return ;
	k = (double)new / (double)old;
	fdf->view->offset_x = p_x + (int)round((fdf->view->offset_x - p_x) * k);
	fdf->view->offset_y = p_y + (int)round((fdf->view->offset_y - p_y) * k);
	fdf->view->scale = new;
	fdf->view->z_scale = clampi((int)round(fdf->view->z_scale * k-1), \
		MIN_SCALE, MAX_SCALE);
}
