/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:09:37 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 19:14:07 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_key(int keycode, t_env *env)
{
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 65361) // Left
		env->offset_x -= 10;
	if (keycode == 65363) // Right
		env->offset_x += 10;
	if (keycode == 65362) // Up
		env->offset_y -= 10;
	if (keycode == 65364) // Down
		env->offset_y += 10;
	mlx_clear_window(env->mlx, env->win);
	draw_map(env);
	return (0);
}

int	mouse_press(int button, int x, int y, t_env *env)
{
	if (button == 1) // Left click
	{
		env->mouse_pressed = 1;
		env->last_x = x;
		env->last_y = y;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 1)
		env->mouse_pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, t_env *env)
{
	int	dx;
	int	dy;
	
	dx = 0;
	dy = 0;
	if (!env || !env->mlx || !env->win || !env->mouse_pressed)
		return (0);
	dx = x - env->last_x;
	dy = y - env->last_y;
	env->offset_x += dx;
	env->offset_y += dy;
	env->last_x = x;
	env->last_y = y;
	// printf("mouse (x, y): (%d, %d) | offset (x, y): (%d, %d)\n", x, y, env->offset_x, env->offset_y);
	mlx_clear_window(env->mlx, env->win);
	draw_map(env);
	return (0);
}