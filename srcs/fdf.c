/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:02 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 09:56:09 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// static int	ft_init(char *file)
// {
// 	t_fdf	env;
// 	int		lines;

// 	if (!file)
// 		return (1);
// 	lines = count_lines(file);
// 	if (lines <= 0)
// 		return (ft_printf("Error: Invalid file or empty file.\n"), 1);
// 	env.buff = malloc(sizeof(int *) * lines);
// 	if (!env.buff)
// 		return (ft_printf("Error: Memory allocation failed.\n"), 1);
// 	if (read_map(file, env.buff, &lines) != 0)
// 		return (free(env.buff), ft_printf("Error: Could not read map.\n"), 1);
// 	env.mlx = mlx_init();
// 	if (!env.mlx)
// 		return (free(env.buff), ft_printf("Error: Could not initialize mlx.\n"), 1);
// 	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "FdF");
// 	if (!env.win)
// 		return (free(env.buff), ft_printf("Error: Could not create window.\n"), 1);
// 	draw_map(&env);
// 	return (0);
// }

int main(int argc, char **argv)
{
	// Contexte global
	t_fdf   fdf;
	t_map   map;
	t_view  view;

	int     **buff;
	int     rows;
	int     cols;
	int     i;

	if (argc != 2)
		return (ft_printf("Usage: %s <filename>\n", argv[0]), 1);

	// Allocation simple (peut être remplacée par un comptage de lignes préalable)
	buff = malloc(sizeof(int *) * 100);
	if (!buff)
		return (perror("malloc failed"), 1);

	if (ft_check_valid(argv[1], buff, &rows, &cols) != 0)
		return (ft_printf("Erreur: lecture du fichier %s\n", argv[1]), 1);

	// Grille de points à partir de buff
	map.rows = rows;
	map.cols = cols;
	map.point = alloc_points_grid(rows, cols);
	if (!map.point)
		return (perror("alloc points"), 1);
	fill_points_from_buff(map.point, buff, rows, cols);

	// Vue initiale
	view.offset_x = OFFSET_X;
	view.offset_y = OFFSET_Y;
	view.last_x = 0;
	view.last_y = 0;
	view.mouse_pressed = 0;
	view.map = map; // copie par valeur

	// Contexte FDF
	fdf.buff  = buff;
	fdf.point = map.point;
	fdf.map   = &map;
	fdf.view  = &view;

	// Init MLX & fenêtre
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
		return (ft_printf("Erreur: mlx_init()\n"), 1);
	fdf.win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "FdF simple");
	if (!fdf.win)
		return (ft_printf("Erreur: mlx_new_window()\n"), 1);

	// Premier dessin
	draw_map_ctx(&fdf);

	// Hooks
	mlx_key_hook(fdf.win, on_key, &fdf);                 // clavier (appui)
	mlx_mouse_hook(fdf.win, on_mouse, &fdf);             // souris (appui)
	mlx_hook(fdf.win, 5, 1L<<3, on_mouse_release, &fdf); // ButtonRelease
	mlx_hook(fdf.win, 6, 1L<<6, on_motion, &fdf);        // MotionNotify
	mlx_hook(fdf.win, 17, 0, on_destroy, &fdf);          // croix de fenêtre

	// Boucle d'événements
	mlx_loop(fdf.mlx);

	// Libérations (jamais atteintes si exit() dans on_destroy)
	for (i = 0; i < rows; i++)
		free(buff[i]);
	free(buff);
	free_points_grid(map.point, rows);
	return (0);
}
