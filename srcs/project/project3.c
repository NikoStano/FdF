/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:35:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 16:34:26 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	init_rotation_3d(t_view *v, t_rot *r)
{
	r->cx = cos(v->ang_x);
	r->sx = sin(v->ang_x);
	r->cy = cos(v->ang_y);
	r->sy = sin(v->ang_y);
	r->cz = cos(v->ang_z);
	r->sz = sin(v->ang_z);
}

static void	apply_rotation_3d(t_v3 *p, t_view *v, t_rot *r)
{
	double	tx;
	double	ty;
	double	tz;
	double	x2;
	double	y2;

	init_rotation_3d(v, r);
	tx = (double)p->x - v->piv_x;
	ty = (double)p->y - v->piv_y;
	tz = (double)p->z;
	y2 = ty * r->cx - tz * r->sx;
	tz = ty * r->sx + tz * r->cx;
	ty = y2;
	r->xr = tx * r->cy + tz * r->sy;
	tz = -tx * r->sy + tz * r->cy;
	x2 = r->xr * r->cz - ty * r->sz;
	r->yr = r->xr * r->sz + ty * r->cz;
	r->xr = x2;
	r->zr = tz;
}

void	parallel_project_3d(t_v3 p, t_view *v, t_v2 *out)
{
	t_rot	r;

	apply_rotation_3d(&p, v, &r);
	out->x = (int)(r.xr * v->scale + v->off_x);
	out->y = (int)(r.yr * v->scale + v->off_y - r.zr * v->z_scale);
}

void	conic_project_3d(t_v3 p, t_view *v, t_v2 *out)
{
	t_rot	r;
	double	fov;
	double	z_dist;

	apply_rotation_3d(&p, v, &r);
	fov = 500.0;
	z_dist = fov / (fov + r.zr);
	out->x = (int)((r.xr * z_dist) * v->scale + v->off_x);
	out->y = (int)((r.yr * z_dist) * v->scale + v->off_y);
}
