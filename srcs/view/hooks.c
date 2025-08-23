/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:34:50 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/22 03:39:57 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	on_key(int key, t_app *a)
{
	if (key == XK_Escape)
		return (on_destroy(a));
	if (key == XK_Left || key == XK_a)
		a->view.off_x -= STEP;
	else if (key == XK_Right || key == XK_d)
		a->view.off_x += STEP;
	else if (key == XK_Up || key == XK_w)
		a->view.off_y -= STEP;
	else if (key == XK_Down || key == XK_s)
		a->view.off_y += STEP;
	else if (key == XK_r)
		view_reset(&a->view);
	else if (key == XK_q)
		view_rotate_z(&a->view, ROT_STEP);
	else if (key == XK_e)
		view_rotate_z(&a->view, -ROT_STEP);
	else
		return (0);
	render(a);
	return (0);
}

int	on_mouse(int btn, int x, int y, t_app *a)
{
	t_v2	p;

	p.x = x;
	p.y = y;
	if (btn == BTN_LEFT)
	{
		a->view.mouse_down = 1;
		a->view.last_x = x;
		a->view.last_y = y;
	}
	else if (btn == BTN_MUP)
	{
		view_zoom(&a->view, p, 115, 100);
		render(a);
	}
	else if (btn == BTN_MDN)
	{
		view_zoom(&a->view, p, 100, 115);
		render(a);
	}
	return (0);
}

int	on_mouse_release(int btn, int x, int y, t_app *a)
{
	if (btn == BTN_LEFT)
	{
		a->view.mouse_down = 0;
		a->view.last_x = x;
		a->view.last_y = y;
	}
	return (0);
}

int	on_motion(int x, int y, t_app *a)
{
	t_bres	b;

	if (!a->view.mouse_down)
		return (0);
	b.dx = x - a->view.last_x;
	b.dy = y - a->view.last_y;
	a->view.off_x += b.dx;
	a->view.off_y += b.dy;
	a->view.last_x = x;
	a->view.last_y = y;
	render(a);
	return (0);
}

int	on_destroy(t_app *a)
{
	win_destroy(a);
	exit(0);
	return (0);
}
