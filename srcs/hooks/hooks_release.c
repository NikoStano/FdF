/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:30:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 07:51:19 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	release_movement_keys(int key, t_app *a)
{
	if (key == XK_Left || key == XK_a)
		a->keys.left = 0;
	else if (key == XK_Right || key == XK_d)
		a->keys.right = 0;
	else if (key == XK_Up || key == XK_w)
		a->keys.up = 0;
	else if (key == XK_Down || key == XK_s)
		a->keys.down = 0;
}

static void	release_rotation_keys(int key, t_app *a)
{
	if (key == XK_q)
		a->keys.rot_z_plus = 0;
	else if (key == XK_e)
		a->keys.rot_z_minus = 0;
	else if (key == XK_i)
		a->keys.rot_x_plus = 0;
	else if (key == XK_k)
		a->keys.rot_x_minus = 0;
	else if (key == XK_j)
		a->keys.rot_y_minus = 0;
	else if (key == XK_l)
		a->keys.rot_y_plus = 0;
}

static void	release_zoom_keys(int key, t_app *a)
{
	if (key == XK_Shift_L)
		a->keys.z_plus = 0;
	else if (key == XK_Control_L)
		a->keys.z_minus = 0;
	else if (key == XK_plus || key == XK_KP_Add)
		a->keys.zoom_in = 0;
	else if (key == XK_minus || key == XK_KP_Subtract)
		a->keys.zoom_out = 0;
}

int	on_key_release(int key, t_app *a)
{
	release_movement_keys(key, a);
	release_rotation_keys(key, a);
	release_zoom_keys(key, a);
	render(a);
	return (0);
}
