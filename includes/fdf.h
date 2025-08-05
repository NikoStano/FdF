/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:37:58 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 03:01:40 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1000
# define HEIGHT 800

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "mlx.h"

int		ft_check_valid(char *filename, int **buff, int *rows, int *cols);
char	*ft_strtoq(char *str, const char *delim);
void	ft_fill_tab(int *tab, char *line, int width);
void	draw_map(void *mlx, void *win, int **buff, int rows, int cols);
void	draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1);

#endif
