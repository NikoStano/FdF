/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:55:13 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/14 18:35:04 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	**alloc_points_grid(int rows, int cols)
{
	int		y;
	t_point	**grid;

	grid = (t_point **)malloc(sizeof(t_point *) * rows);
	if (!grid)
		return (NULL);
	y = 0;
	while (y < rows)
	{
		grid[y] = (t_point *)malloc(sizeof(t_point) * cols);
		if (!grid[y])
		{
			while (y-- > 0)
				free(grid[y]);
			free(grid);
			return (NULL);
		}
		y++;
	}
	return (grid);
}

void	free_points_grid(t_point **grid, int rows)
{
	int	y;

	y = 0;
	while (y < rows)
		free(grid[y++]);
	free(grid);
}

void	fill_points_from_buff(t_point **pts, int **buff, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			pts[y][x].x = x;
			pts[y][x].y = y;
			pts[y][x].z = buff[y][x];
			x++;
		}
		y++;
	}
}
