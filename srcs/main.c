/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:57:36 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 19:03:27 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// int	main(int argc, char **argv)
// {
// 	int		**buff;
// 	void	*mlx;
// 	void	*win;
// 	int		rows;
// 	int		cols;
// 	int		i;

// 	if (argc != 2)
// 		return (ft_printf("Usage: %s <filename>\n", argv[0]), 1);
// 	buff = malloc(sizeof(int *) * 100);
// 	if (!buff)
// 		return (perror("malloc failed"), 1);
// 	ft_check_valid(argv[1], buff, &rows, &cols);
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, WIDTH, HEIGHT, "FdF simple");
// 	draw_map(mlx, win, buff, rows, cols);
// 	mlx_loop(mlx);
// 	for (i = 0; i < rows; i++)
// 		free(buff[i]);
// 	free(buff);
// 	return (0);
// }


// #include "fdf.h"

// int	ft_check_valid(char *filename, int **buff, int *rows, int *cols)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;
// 	int		width;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	i = 0;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		width = ft_count_words(line);
// 		if (i == 0)
// 			*cols = width;
// 		buff[i] = malloc(sizeof(int) * width);
// 		if (!buff[i])
// 		{
// 			free(line);
// 			while (i-- > 0)
// 				free(buff[i]);
// 			close(fd);
// 			return (-1);
// 		}
// 		ft_fill_tab(buff[i], line, width);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	*rows = i;
// 	return (0);
// }

// char	*ft_strtoq(char *str, const char *delim)
// {
// 	static char	*next_token = NULL;
// 	char		*token;

// 	if (str)
// 		next_token = str;
// 	if (!next_token)
// 		return (0);
// 	token = next_token;
// 	while (*next_token && !ft_strchr(delim, *next_token))
// 		next_token++;
// 	if (*next_token)
// 	{
// 		*next_token = '\0';
// 		next_token++;
// 	}
// 	else
// 		next_token = NULL;
// 	return (token);
// }

// void	ft_fill_tab(int *tab, char *line, int width)
// {
// 	int		i = 0;
// 	char	*token;
	
// 	token = ft_strtoq(line, " ");
// 	while (i < width && token)
// 	{
// 		tab[i] = ft_atoi(token);
// 		i++;
// 		token = ft_strtoq(NULL, " ");
// 	}
// }

// void	draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
// {
// 	int dx = abs(x1 - x0);
// 	int sx = x0 < x1 ? 1 : -1;
// 	int dy = -abs(y1 - y0);
// 	int sy = y0 < y1 ? 1 : -1;
// 	int err = dx + dy;

// 	while (1)
// 	{
// 		mlx_pixel_put(mlx, win, x0, y0, 0xFFFFFF);
// 		if (x0 == x1 && y0 == y1)
// 			break;
// 		int e2 = 2 * err;
// 		if (e2 >= dy)
// 		{
// 			err += dy;
// 			x0 += sx;
// 		}
// 		if (e2 <= dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// void	draw_map(void *mlx, void *win, int **buff, int rows, int cols)
// {
// 	int	scale = 20;
// 	int	z_scale = 2;
// 	int	offset_x = 500;
// 	int	offset_y = 300;

// 	for (int y = 0; y < rows; y++)
// 	{
// 		for (int x = 0; x < cols; x++)
// 		{
// 			int z = buff[y][x];
// 			int x0 = (x - y) * scale + offset_x;
// 			int y0 = (x + y) * scale / 2 - z * z_scale + offset_y;

// 			if (x < cols - 1)
// 			{
// 				int z_right = buff[y][x + 1];
// 				int x1 = ((x + 1) - y) * scale + offset_x;
// 				int y1 = ((x + 1) + y) * scale / 2 - z_right * z_scale + offset_y;
// 				draw_line(mlx, win, x0, y0, x1, y1);
// 			}
// 			if (y < rows - 1)
// 			{
// 				int z_down = buff[y + 1][x];
// 				int x1 = (x - (y + 1)) * scale + offset_x;
// 				int y1 = (x + (y + 1)) * scale / 2 - z_down * z_scale + offset_y;
// 				draw_line(mlx, win, x0, y0, x1, y1);
// 			}
// 		}
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	int		**buff;
// 	void	*mlx;
// 	void	*win;
// 	int		rows;
// 	int		cols;

// 	if (argc != 2)
// 	{
// 		ft_printf("Usage: %s <filename>\n", argv[0]);
// 		return (EXIT_FAILURE);
// 	}
// 	buff = malloc(sizeof(int *) * 100); // 100 lignes max
// 	if (!buff)
// 	{
// 		perror("malloc failed");
// 		return (EXIT_FAILURE);
// 	}
// 	ft_check_valid(argv[1], buff, &rows, &cols);

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, WIDTH, HEIGHT, "FdF simple");

// 	draw_map(mlx, win, buff, rows, cols);

// 	mlx_loop(mlx);

// 	for (int i = 0; i < 100; i++)
// 		if (buff[i]) free(buff[i]);
// 	free(buff);
// 	return (EXIT_SUCCESS);
// }