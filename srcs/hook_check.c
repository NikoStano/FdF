/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:54:46 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/14 18:59:42 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	on_key(int keycode, t_fdf *fdf)
{
	int	step;

	step = 20;
	if (keycode == XK_Escape)
		return (on_destroy(fdf));
	if (keycode == XK_Left || keycode == XK_a)
		fdf->view->offset_x -= step;
	else if (keycode == XK_Right || keycode == XK_d)
		fdf->view->offset_x += step;
	else if (keycode == XK_Up || keycode == XK_w)
		fdf->view->offset_y -= step;
	else if (keycode == XK_Down || keycode == XK_s)
		fdf->view->offset_y += step;
	else if (keycode == XK_r)
		view_reset(fdf->view);
	else
		return (0);
	draw_map_ctx(fdf);
	return (0);
}

int	on_mouse(int button, int x, int y, t_fdf *fdf)
{
	if (button == BTN_LEFT)
	{
		fdf->view->mouse_pressed = 1;
		fdf->view->last_x = x;
		fdf->view->last_y = y;
	}
	else if (button == BTN_SCROLL_UP)
	{
		apply_zoom(fdf, 1.15, x, y);
		draw_map_ctx(fdf);
	}
	else if (button == BTN_SCROLL_DOWN)
	{
		apply_zoom(fdf, 1.0 / 1.15, x, y);
		draw_map_ctx(fdf);
	}
	return (0);
}

int	on_mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	(void)button;
	fdf->view->mouse_pressed = 0;
	return (0);
}

int	on_motion(int x, int y, t_fdf *fdf)
{
	int	dx;
	int	dy;

	if (!fdf->view->mouse_pressed)
		return (0);
	dx = x - fdf->view->last_x;
	dy = y - fdf->view->last_y;
	fdf->view->offset_x += dx;
	fdf->view->offset_y += dy;
	fdf->view->last_x = x;
	fdf->view->last_y = y;
	draw_map_ctx(fdf);
	return (0);
}

int	on_destroy(t_fdf *fdf)
{
	(void)fdf;
	exit(0);
	return (0);
}
