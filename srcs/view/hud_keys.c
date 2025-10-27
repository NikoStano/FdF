/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:00:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 08:20:08 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	draw_movement_keys(t_app *a, int x, int y)
{
	int	color;

	mlx_string_put(a->mlx, a->win, x, y, 0xFFFFFF, "Mouvement:");
	if (a->keys.up)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 20, color, "[W/Up]");
	if (a->keys.left)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 40, color, "[A/Left]");
	if (a->keys.down)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 60, color, "[S/Down]");
	if (a->keys.right)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 80, color, "[D/Right]");
}

static void	draw_rotation_keys_part1(t_app *a, int x, int y)
{
	int	color;

	mlx_string_put(a->mlx, a->win, x, y, 0xFFFFFF, "Rotation:");
	if (a->keys.rot_x_plus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 20, color, "[I] X+");
	if (a->keys.rot_x_minus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 40, color, "[K] X-");
	if (a->keys.rot_y_plus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 60, color, "[L] Y+");
}

static void	draw_rotation_keys_part2(t_app *a, int x, int y)
{
	int	color;

	if (a->keys.rot_y_minus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 80, color, "[J] Y-");
	if (a->keys.rot_z_plus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 100, color, "[Q] Z+");
	if (a->keys.rot_z_minus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 120, color, "[E] Z-");
}

void	draw_rotation_keys(t_app *a, int x, int y)
{
	draw_rotation_keys_part1(a, x, y);
	draw_rotation_keys_part2(a, x, y);
}

void	draw_zoom_keys(t_app *a, int x, int y)
{
	int	color;

	mlx_string_put(a->mlx, a->win, x, y, 0xFFFFFF, "Zoom:");
	if (a->keys.zoom_in)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 20, color, "[+]");
	if (a->keys.zoom_out)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 40, color, "[-]");
	if (a->keys.z_plus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 60, color, "[Shift] Z+");
	if (a->keys.z_minus)
		color = 0x00FF00;
	else
		color = 0x808080;
	mlx_string_put(a->mlx, a->win, x, y + 80, color, "[Ctrl] Z-");
}
