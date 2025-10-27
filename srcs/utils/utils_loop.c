/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:30:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 08:23:24 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	process_movement_keys(t_app *a)
{
	int	changed;

	changed = 0;
	if (a->keys.left)
	{
		a->view.off_x -= STEP / 4;
		changed = 1;
	}
	if (a->keys.right)
	{
		a->view.off_x += STEP / 4;
		changed = 1;
	}
	if (a->keys.up)
	{
		a->view.off_y -= STEP / 4;
		changed = 1;
	}
	if (a->keys.down)
	{
		a->view.off_y += STEP / 4;
		changed = 1;
	}
	return (changed);
}

static int	process_rotation_x_y(t_app *a, int changed)
{
	if (a->keys.rot_x_plus)
	{
		view_rotate_x(&a->view, ROT_STEP / 4);
		changed = 1;
	}
	if (a->keys.rot_x_minus)
	{
		view_rotate_x(&a->view, -ROT_STEP / 4);
		changed = 1;
	}
	if (a->keys.rot_y_plus)
	{
		view_rotate_y(&a->view, ROT_STEP / 4);
		changed = 1;
	}
	if (a->keys.rot_y_minus)
	{
		view_rotate_y(&a->view, -ROT_STEP / 4);
		changed = 1;
	}
	return (changed);
}

static int	process_rotation_keys(t_app *a)
{
	int	changed;

	changed = 0;
	changed = process_rotation_x_y(a, changed);
	if (a->keys.rot_z_plus)
		view_rotate_z(&a->view, ROT_STEP / 4);
	if (a->keys.rot_z_minus)
		view_rotate_z(&a->view, -ROT_STEP / 4);
	return (changed);
}

static int	process_zoom_keys(t_app *a)
{
	int	changed;

	changed = 0;
	if (a->keys.zoom_in && a->view.scale < MAX_SCALE)
	{
		a->view.scale += 1;
		changed = 1;
	}
	if (a->keys.zoom_out && a->view.scale > MIN_SCALE)
	{
		a->view.scale -= 1;
		changed = 1;
	}
	if (a->keys.z_plus && a->view.z_scale < 15)
	{
		a->view.z_scale += 1;
		changed = 1;
	}
	if (a->keys.z_minus && a->view.z_scale > 1)
	{
		a->view.z_scale -= 1;
		changed = 1;
	}
	return (changed);
}

int	auto_rotate_loop(t_app *a)
{
	int	changed;

	changed = 0;
	a->keys.frame_count++;
	if (a->view.auto_rotate)
	{
		view_rotate_y(&a->view, 0.01);
		changed = 1;
	}
	if (a->keys.frame_count % 3 != 0)
		return (0);
	changed |= process_movement_keys(a);
	changed |= process_rotation_keys(a);
	changed |= process_zoom_keys(a);
	if (changed)
		render(a);
	return (0);
}
