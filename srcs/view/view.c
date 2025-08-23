/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:34:54 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/22 03:37:47 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	view_reset(t_view *v)
{
	v->off_x = OFF_X_DEFAULT;
	v->off_y = OFF_Y_DEFAULT;
	v->scale = SCALE_DEFAULT;
	v->z_scale = ZS_DEFAULT;
	v->ang_z = 0.0;
}

void	view_zoom(t_view *v, t_v2 pivot, int num, int den)
{
	int	old;
	int	neu;

	old = v->scale;
	neu = clampi((old * num) / den, MIN_SCALE, MAX_SCALE);
	if (neu == old)
		return ;
	v->off_x = pivot.x + ((v->off_x - pivot.x) * neu) / old;
	v->off_y = pivot.y + ((v->off_y - pivot.y) * neu) / old;
	v->scale = neu;
	v->z_scale = clampi((v->z_scale * neu) / old, MIN_SCALE, MAX_SCALE);
}

void	view_rotate_z(t_view *v, double delta)
{
	v->ang_z += delta;
	while (v->ang_z > 3.141592653589793)
		v->ang_z -= 6.283185307179586;
	while (v->ang_z < -3.141592653589793)
		v->ang_z += 6.283185307179586;
}
