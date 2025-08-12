/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:34:32 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 14:58:02 by nistanoj         ###   ########.fr       */
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
		return lo;
    if (val > hi)
		return hi;
    return val;
}

void	apply_zoom(t_fdf *fdf, double factor, int pivot_x, int pivot_y)
{
    int old_scale;
    int new_scale;

	old_scale = fdf->view->scale;
	new_scale = clampi((int)round(old_scale * factor), MIN_SCALE, MAX_SCALE); 
    if (new_scale == old_scale)
        return;
    double k = (double)new_scale / (double)old_scale;

    // Ajuste offsets autour d'un pivot (molette sous le curseur ou centre)
    fdf->view->offset_x = pivot_x + (int)round((fdf->view->offset_x - pivot_x) * k);
    fdf->view->offset_y = pivot_y + (int)round((fdf->view->offset_y - pivot_y) * k);

    fdf->view->scale = new_scale;
    // Harmonise l'altitude avec la même proportion
    fdf->view->z_scale = clampi((int)round(fdf->view->z_scale * k), 1, MAX_SCALE);
}
