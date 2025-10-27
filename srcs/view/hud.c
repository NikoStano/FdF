/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:55:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 07:47:46 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	draw_proj_info(t_app *a, int y)
{
	char	*proj;

	if (a->view.projection == PROJ_ISO)
		proj = "Projection: Isometrique";
	else if (a->view.projection == PROJ_PARALLEL)
		proj = "Projection: Parallele";
	else
		proj = "Projection: Conique";
	mlx_string_put(a->mlx, a->win, 10, y, 0xFFFFFF, proj);
}

static void	draw_rotation_info(t_app *a, int y)
{
	char	*rot;

	rot = ft_itoa((int)(a->view.ang_x * 180 / PI));
	mlx_string_put(a->mlx, a->win, 10, y, 0xFFFFFF, "Rot X: ");
	mlx_string_put(a->mlx, a->win, 70, y, 0xFFFFFF, rot);
	free(rot);
	rot = ft_itoa((int)(a->view.ang_y * 180 / PI));
	mlx_string_put(a->mlx, a->win, 120, y, 0xFFFFFF, "Y: ");
	mlx_string_put(a->mlx, a->win, 145, y, 0xFFFFFF, rot);
	free(rot);
	rot = ft_itoa((int)(a->view.ang_z * 180 / PI));
	mlx_string_put(a->mlx, a->win, 190, y, 0xFFFFFF, "Z: ");
	mlx_string_put(a->mlx, a->win, 215, y, 0xFFFFFF, rot);
	free(rot);
}

static void	draw_scale_info(t_app *a, int y)
{
	char	*scale;

	scale = ft_itoa(a->view.scale);
	mlx_string_put(a->mlx, a->win, 10, y, 0xFFFFFF, "Scale: ");
	mlx_string_put(a->mlx, a->win, 70, y, 0xFFFFFF, scale);
	free(scale);
	scale = ft_itoa(a->view.z_scale);
	mlx_string_put(a->mlx, a->win, 120, y, 0xFFFFFF, "Z: ");
	mlx_string_put(a->mlx, a->win, 145, y, 0xFFFFFF, scale);
	free(scale);
}

static void	draw_color_mode(t_app *a, int y)
{
	char	*mode;

	if (a->view.color_mode == COLOR_AUTO)
		mode = "Color: Auto";
	else
		mode = "Color: Custom";
	mlx_string_put(a->mlx, a->win, 10, y, 0xFFFFFF, mode);
}

void	draw_hud(t_app *a)
{
	draw_proj_info(a, 20);
	draw_rotation_info(a, 40);
	draw_scale_info(a, 60);
	draw_color_mode(a, 80);
	if (a->view.auto_rotate)
		mlx_string_put(a->mlx, a->win, 10, 100, 0x00FF00, "[AUTO-ROTATE ON]");
	draw_keys_status(a);
}
