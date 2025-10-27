/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:03 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 09:46:07 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static long	clamp_toint(long n)
{
	if (n > (long)INT_MAX)
		return ((long)INT_MAX);
	if (n < (long)INT_MIN)
		return ((long)INT_MIN);
	return (n);
}

static long	init_proj(t_v3 p, t_view *v, t_proj *pj)
{
	long	v2;

	pj->sc = (double)v->scale;
	pj->c = cos(v->ang_z);
	pj->s = sin(v->ang_z);
	pj->tx = (double)p.x - v->piv_x;
	pj->ty = (double)p.y - v->piv_y;
	pj->xr = pj->tx * pj->c - pj->ty * pj->s;
	pj->yr = pj->tx * pj->s + pj->ty * pj->c;
	v2 = (pj->xr + pj->yr) * pj->sc / 2;
	return (v2);
}

void	iso_project(t_v3 p, t_view *v, t_v2 *out)
{
	long	u;
	long	v2;
	long	y;
	t_proj	pj;

	v2 = init_proj(p, v, &pj);
	u = clamp_toint((long)((pj.xr - pj.yr) * pj.sc));
	y = clamp_toint((long)(v2 - (double)p.z * v->z_scale));
	out->x = (int)(u + v->off_x);
	out->y = (int)(y + v->off_y);
}
