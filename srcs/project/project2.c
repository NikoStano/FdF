/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:20:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 16:34:59 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	apply_rotation(t_v3 *p, t_view *v, t_rot *r)
{
	double	tx;
	double	ty;

	r->c = cos(v->ang_z);
	r->s = sin(v->ang_z);
	tx = (double)p->x - v->piv_x;
	ty = (double)p->y - v->piv_y;
	r->xr = tx * r->c - ty * r->s;
	r->yr = tx * r->s + ty * r->c;
}

void	parallel_project(t_v3 p, t_view *v, t_v2 *out)
{
	t_rot	r;

	apply_rotation(&p, v, &r);
	out->x = (int)(r.xr * v->scale + v->off_x);
	out->y = (int)(r.yr * v->scale + v->off_y - p.z * v->z_scale);
}

void	conic_project(t_v3 p, t_view *v, t_v2 *out)
{
	t_rot	r;
	double	fov;
	double	z_dist;

	apply_rotation(&p, v, &r);
	fov = 500.0;
	z_dist = fov / (fov + p.z);
	out->x = (int)((r.xr * z_dist) * v->scale + v->off_x);
	out->y = (int)((r.yr * z_dist) * v->scale + v->off_y - p.z * v->z_scale);
}

void	project(t_v3 p, t_view *v, t_v2 *out)
{
	if (v->ang_x != 0.0 || v->ang_y != 0.0)
	{
		if (v->projection == PROJ_ISO)
			iso_project_3d(p, v, out);
		else if (v->projection == PROJ_PARALLEL)
			parallel_project_3d(p, v, out);
		else if (v->projection == PROJ_CONIC)
			conic_project_3d(p, v, out);
	}
	else
	{
		if (v->projection == PROJ_ISO)
			iso_project(p, v, out);
		else if (v->projection == PROJ_PARALLEL)
			parallel_project(p, v, out);
		else if (v->projection == PROJ_CONIC)
			conic_project(p, v, out);
	}
}
