/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:16 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 17:07:08 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	init_view_defaults(t_view *v)
{
	v->off_x = OFF_X_DEFAULT;
	v->off_y = OFF_Y_DEFAULT;
	v->scale = SCALE_DEFAULT;
	v->z_scale = ZS_DEFAULT;
	v->mouse_down = 0;
	v->last_x = 0;
	v->last_y = 0;
	v->ang_x = 0.0;
	v->ang_y = 0.0;
	v->ang_z = 0.0;
	v->projection = PROJ_ISO;
	v->auto_rotate = 0;
	v->color_mode = COLOR_AUTO;
}

int	win_init(t_app *a, const char *path)
{
	int	err;

	err = 0;
	ft_bzero(a, sizeof(*a));
	if (map_load(&a->map, path))
		return (1);
	init_view_defaults(&a->view);
	a->view.piv_x = (a->map.cols - 1) / 2.0;
	a->view.piv_y = (a->map.rows - 1) / 2.0;
	a->mlx = mlx_init();
	if (!a->mlx)
		return (1);
	a->win = mlx_new_window(a->mlx, WIDTH, HEIGHT, NAME);
	if (!a->win)
		return (1);
	img_create(a, &a->fb, WIDTH, HEIGHT);
	return (err);
}

void	win_destroy(t_app *a)
{
	if (!a)
		return ;
	if (a->mlx && a->fb.img)
		img_destroy(a, &a->fb);
	map_free(&a->map);
	if (a->mlx && a->win)
	{
		mlx_destroy_window(a->mlx, a->win);
		a->win = NULL;
	}
	if (a->mlx)
	{
		mlx_destroy_display(a->mlx);
		free(a->mlx);
		a->mlx = NULL;
	}
}

int	win_run(t_app *a)
{
	mlx_hook(a->win, 17, 0, on_destroy, a);
	mlx_key_hook(a->win, on_key, a);
	mlx_mouse_hook(a->win, on_mouse, a);
	mlx_hook(a->win, 5, 1L << 3, on_mouse_release, a);
	mlx_hook(a->win, 6, 1L << 6, on_motion, a);
	mlx_loop_hook(a->mlx, auto_rotate_loop, a);
	render(a);
	mlx_loop(a->mlx);
	return (0);
}
