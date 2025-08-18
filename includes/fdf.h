/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:46:36 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/18 22:37:48 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// Includes //
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "../lib/minilibx/mlx.h"
# include <X11/keysym.h>

// Constantes //
# define WIDTH 1000
# define HEIGHT 800
# define SCALE 20
# define Z_SCALE 5
# define OFFSET_X 500
# define OFFSET_Y 400
# define MIN_SCALE 2
# define MAX_SCALE 200

// Souris //
# define BTN_LEFT 1
# define BTN_SCROLL_UP 4
# define BTN_SCROLL_DOWN 5

// Structures de données //
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}				t_point;

typedef struct s_valid
{
	int		fd;
	char	*line;
	int		width;
}				t_valid;

typedef struct s_image
{
	int	rows;
	int	cols;
	int	z_right;
	int	z_down;
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
}				t_image;

typedef struct s_map
{
	int		rows;
	int		cols;
	t_point	**point;
}				t_map;

typedef struct s_view
{
	int		offset_x;
	int		offset_y;
	int		last_x;
	int		last_y;
	int		mouse_pressed;
	int		scale;
	int		z_scale;
	t_map	map;
}				t_view;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	int		**buff;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	t_point	**point;
	t_map	*map;
	t_view	*view;
}				t_fdf;

// Prototypes //
int		ft_check_valid(char *filename, int **buff, int *rows, int *cols);
char	*ft_strtok(char *str, const char *delim);
void	ft_fill_tab(int *tab, char *line, int width);

// Dessin //
void	draw_line(t_fdf *fdf, t_image img);
void	draw_map_ctx(t_fdf *fdf);

// Hooks //
int		on_key(int keycode, t_fdf *fdf);
int		on_mouse(int button, int x, int y, t_fdf *fdf);
int		on_mouse_release(int button, int x, int y, t_fdf *fdf);
int		on_motion(int x, int y, t_fdf *fdf);
int		on_destroy(t_fdf *fdf);

// Zoom //
void	view_reset(t_view *v);
void	apply_zoom(t_fdf *fdf, double factor, int pivot_x, int pivot_y);

// Utils //
int		ft_abs(int n);
int		check_pos_point(int x0, int x1);
int		ft_count_words(char *str);
char	*ft_strtok(char *str, const char *delim);

// Points //
t_point	**alloc_points_grid(int rows, int cols);
void	free_points_grid(t_point **grid, int rows);
void	fill_points_from_buff(t_point **pts, int **buff, int rows, int cols);

#endif
