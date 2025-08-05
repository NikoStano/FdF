/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:02 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 19:03:32 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_env	env;
	int		line;
	int		i;

	if (argc != 2)
		return (ft_printf("Usage: %s <filename>\n", argv[0]), 1);
	line = count_lines(argv[1]);
	if (line <= 0)
		return (ft_printf("Error: Invalid file or empty file.\n"), 1);
	env.buff = malloc(sizeof(int *) * line);
	if (!env.buff)
		return (ft_printf("Error: Memory allocation failed.\n"), 1);
	if (read_map(argv[1], env.buff, &env.cols) != 0)
	{
		free(env.buff);
		return (ft_printf("Error: Could not read map.\n"), 1);
	}
	env.rows = line;
	env.offset_x = WIDTH / 2;
	env.offset_y = HEIGHT / 2;
	env.mlx = mlx_init();
	if (!env.mlx)
	{
		free(env.buff);
		return (ft_printf("Error: Could not initialize mlx.\n"), 1);
	}
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "FdF");
	if (!env.win)
	{
		free(env.buff);
		return (ft_printf("Error: Could not create window.\n"), 1);
	}
	draw_map(&env);
	mlx_key_hook(env.win, handle_key, &env);

	env.mouse_pressed = 0;
	env.last_x = 0;
	env.last_y = 0;
	mlx_hook(env.win, 4, 1L<<2, mouse_press, &env);     // bouton press
	mlx_hook(env.win, 6, 1L<<6, mouse_move, &env);      // mouvement
	mlx_hook(env.win, 5, 1L<<3, mouse_release, &env);   // bouton release

	mlx_loop(env.mlx);
	i = -1;
	while (i++ < env.rows - 1)
		free(env.buff[i]);
	free(env.buff);
	mlx_destroy_window(env.mlx, env.win);
	free(env.mlx);
	return (0);
}