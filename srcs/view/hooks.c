/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:34:50 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 17:07:41 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	print_projection(int proj)
{
	if (proj == PROJ_ISO)
		ft_printf("Projection: Isométrique\n");
	else if (proj == PROJ_PARALLEL)
		ft_printf("Projection: Parallèle\n");
	else
		ft_printf("Projection: Conique\n");
}

static int	handle_movement(int key, t_app *a)
{
	if (key == XK_Left || key == XK_a)
		a->view.off_x -= STEP;
	else if (key == XK_Right || key == XK_d)
		a->view.off_x += STEP;
	else if (key == XK_Up || key == XK_w)
		a->view.off_y -= STEP;
	else if (key == XK_Down || key == XK_s)
		a->view.off_y += STEP;
	else
		return (0);
	return (1);
}

static int	handle_rotation(int key, t_app *a)
{
	if (key == XK_q)
		view_rotate_z(&a->view, ROT_STEP);
	else if (key == XK_e)
		view_rotate_z(&a->view, -ROT_STEP);
	else if (key == XK_i)
		view_rotate_x(&a->view, ROT_STEP);
	else if (key == XK_k)
		view_rotate_x(&a->view, -ROT_STEP);
	else if (key == XK_j)
		view_rotate_y(&a->view, -ROT_STEP);
	else if (key == XK_l)
		view_rotate_y(&a->view, ROT_STEP);
	else
		return (0);
	return (1);
}

static int	handle_view(int key, t_app *a)
{
	if (key == XK_r)
		view_reset(&a->view);
	else if (key == XK_p)
	{
		a->view.projection = (a->view.projection + 1) % 3;
		print_projection(a->view.projection);
	}
	else if (key == XK_c)
		a->view.color_mode = (a->view.color_mode + 1) % 2;
	else if (key == XK_space)
		a->view.auto_rotate = !a->view.auto_rotate;
	else if (key == XK_Shift_L && a->view.z_scale <= 15)
		a->view.z_scale += 1;
	else if (key == XK_Control_L && a->view.z_scale > 1)
		a->view.z_scale -= 1;
	else
		return (0);
	return (1);
}

int	on_key(int key, t_app *a)
{
	int	handled;

	if (key == XK_Escape)
		return (on_destroy(a));
	handled = handle_movement(key, a);
	handled = handled || handle_view(key, a);
	handled = handled || handle_rotation(key, a);
	if (handled)
	{
		render(a);
		return (0);
	}
	return (0);
}
