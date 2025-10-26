/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:40:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 16:34:44 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	init_rot_3d(t_view *v, t_rot *r)
{
	r->cx = cos(v->ang_x);
	r->sx = sin(v->ang_x);
	r->cy = cos(v->ang_y);
	r->sy = sin(v->ang_y);
	r->cz = cos(v->ang_z);
	r->sz = sin(v->ang_z);
}

static void	rotate_3d(t_v3 *p, t_view *v, t_rot *r)
{
	double	tx;
	double	ty;
	double	tz;
	double	tmp;

	init_rot_3d(v, r);
	tx = (double)p->x - v->piv_x;
	ty = (double)p->y - v->piv_y;
	tz = (double)p->z;
	tmp = ty * r->cx - tz * r->sx;
	tz = ty * r->sx + tz * r->cx;
	ty = tmp;
	r->xr = tx * r->cy + tz * r->sy;
	r->zr = -tx * r->sy + tz * r->cy;
	tmp = r->xr * r->cz - ty * r->sz;
	r->yr = r->xr * r->sz + ty * r->cz;
	r->xr = tmp;
}

void	iso_project_3d(t_v3 p, t_view *v, t_v2 *out)
{
	t_rot	r;
	long	u;
	long	v2;

	rotate_3d(&p, v, &r);
	u = (r.xr - r.yr) * v->scale;
	v2 = (r.xr + r.yr) * v->scale / 2 - r.zr * v->z_scale;
	out->x = (int)(u + v->off_x);
	out->y = (int)(v2 + v->off_y);
}
