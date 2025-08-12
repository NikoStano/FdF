/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:02 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 15:43:12 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int main(int argc, char **argv)
{
	t_fdf   fdf;
	t_map   map;
	t_view  view;
	int     **buff;
	int     rows;
	int     cols;
	int     i;

	if (argc != 2)
		return (ft_printf("Usage: %s <filename>\n", argv[0]), 1);
	buff = malloc(sizeof(int *) * 100);
	if (!buff)
		return (perror("malloc failed"), 1);

	if (ft_check_valid(argv[1], buff, &rows, &cols) != 0)
		return (ft_printf("Erreur: lecture du fichier %s\n", argv[1]), 1);
	map.rows = rows;
	map.cols = cols;
	map.point = alloc_points_grid(rows, cols);
	if (!map.point)
		return (perror("alloc points"), 1);
	fill_points_from_buff(map.point, buff, rows, cols);
	view.offset_x = OFFSET_X;
	view.offset_y = OFFSET_Y;
	view.last_x = 0;
	view.last_y = 0;
	view.mouse_pressed = 0;
	view.map = map;
	fdf.buff  = buff;
	fdf.point = map.point;
	fdf.map   = &map;
	fdf.view  = &view;
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
		return (ft_printf("Erreur: mlx_init()\n"), 1);
	fdf.win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "FdF simple");
	if (!fdf.win)
		return (ft_printf("Erreur: mlx_new_window()\n"), 1);
	draw_map_ctx(&fdf);
	mlx_key_hook(fdf.win, on_key, &fdf);
	mlx_mouse_hook(fdf.win, on_mouse, &fdf);
	mlx_hook(fdf.win, 5, 1L<<3, on_mouse_release, &fdf);
	mlx_hook(fdf.win, 6, 1L<<6, on_motion, &fdf);
	mlx_hook(fdf.win, 17, 0, on_destroy, &fdf);
	mlx_loop(fdf.mlx);
	i = -1;
	while  (i++ < rows)
		free(buff[i]);
	free(buff);
	free_points_grid(map.point, rows);
	return (0);
}
