/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:25:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 16:50:06 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

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
		view_zoom(&a->view, p, 120, 100);
		render(a);
	}
	else if (btn == BTN_MDN)
	{
		view_zoom(&a->view, p, 100, 120);
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
