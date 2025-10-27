/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:50:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 07:54:43 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	handle_rotation_part1(int key, t_app *a)
{
	if (key == XK_q)
	{
		a->keys.rot_z_plus = 1;
		view_rotate_z(&a->view, ROT_STEP);
	}
	else if (key == XK_e)
	{
		a->keys.rot_z_minus = 1;
		view_rotate_z(&a->view, -ROT_STEP);
	}
	else if (key == XK_i)
	{
		a->keys.rot_x_plus = 1;
		view_rotate_x(&a->view, ROT_STEP);
	}
	else
		return (0);
	return (1);
}

int	handle_rotation_part2(int key, t_app *a)
{
	if (key == XK_k)
	{
		a->keys.rot_x_minus = 1;
		view_rotate_x(&a->view, -ROT_STEP);
	}
	else if (key == XK_j)
	{
		a->keys.rot_y_minus = 1;
		view_rotate_y(&a->view, -ROT_STEP);
	}
	else if (key == XK_l)
	{
		a->keys.rot_y_plus = 1;
		view_rotate_y(&a->view, ROT_STEP);
	}
	else
		return (0);
	return (1);
}

int	handle_rotation(int key, t_app *a)
{
	int	r;

	r = handle_rotation_part1(key, a);
	if (r)
		return (r);
	return (handle_rotation_part2(key, a));
}
