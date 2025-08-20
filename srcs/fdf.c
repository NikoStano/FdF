/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:02 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/20 11:56:26 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	init(t_fdf *fdf, char **av)
{
	fdf->buff = malloc(sizeof(int *) * 1000);
	if (!fdf->buff)
		return (perror("Error: malloc failed on buff"), 1);
	fdf->view = malloc(sizeof(t_view));
	if (!fdf->view)
		return (perror("Error: malloc failed on struct view"), 1);
	fdf->view->map.cols = 0;
	fdf->view->map.rows = 0;
	if (ft_check_valid(av[1], fdf->buff, &(fdf->view->map.rows), \
		&(fdf->view->map.cols)) != 0)
		return (ft_printf("Error: lecture du fichier %s\n", av[1]), 1);
	fdf->view->map.point = alloc_points_grid(fdf->view->map.rows, \
		fdf->view->map.cols);
	if (!fdf->view->map.point)
		return (perror("Error: allocation on grid point !"), 1);
	return (0);
}

static int	launch(t_fdf *fdf)
{
	fill_points_from_buff(fdf->view->map.point, fdf->buff, fdf->view->map.rows, \
		fdf->view->map.cols);
	fdf->view->last_x = 0;
	fdf->view->last_y = 0;
	fdf->view->mouse_pressed = 0;
	view_reset(fdf->view);
	fdf->point = fdf->view->map.point;
	fdf->map = &(fdf->view->map);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (perror("Erreur: mlx_init()"), 1);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF simple");
	if (!fdf->win)
		return (perror("Erreur: mlx_new_window()"), 1);
	draw_map_ctx(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	int		i;

	if (argc != 2)
		return (ft_printf("Usage: %s <filename>\n", argv[0]), 1);
	if (init(&fdf, argv))
		return (1);
	if (launch(&fdf))
		return (1);
	mlx_key_hook(fdf.win, on_key, &fdf);
	mlx_mouse_hook(fdf.win, on_mouse, &fdf);
	mlx_hook(fdf.win, 5, 1L << 3, on_mouse_release, &fdf);
	mlx_hook(fdf.win, 6, 1L << 6, on_motion, &fdf);
	mlx_hook(fdf.win, 17, 0, on_destroy, &fdf);
	mlx_loop(fdf.mlx);
	i = -1;
	while (i++ < fdf.view->map.rows)
		free(fdf.buff[i]);
	free(fdf.buff);
	free_points_grid(fdf.view->map.point, fdf.view->map.rows);
	return (0);
}
