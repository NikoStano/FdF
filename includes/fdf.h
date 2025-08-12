/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:37:58 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 11:31:54 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <X11/keysym.h>

# define WIDTH 1000
# define HEIGHT 800
# define SCALE 20
# define Z_SCALE 5
# define OFFSET_X 500
# define OFFSET_Y 400

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

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}			t_point;

typedef struct s_map
{
	int		rows;
	int		cols;
	t_point	**point;
}			t_map;

typedef	struct s_view
{
	int		offset_x;
	int		offset_y;
	int		last_x;
	int		last_y;
	int		mouse_pressed;
	t_map	map;
}			t_view;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	int		**buff;
	t_point	**point;
	t_map	*map;
	t_view	*view;
}			t_fdf;


// temp
void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1);
void draw_map_ctx(t_fdf *fdf);
int on_key(int keycode, t_fdf *fdf);
int on_mouse(int button, int x, int y, t_fdf *fdf);
int on_mouse_release(int button, int x, int y, t_fdf *fdf);
int on_motion(int x, int y, t_fdf *fdf);
int on_destroy(t_fdf *fdf);
t_point **alloc_points_grid(int rows, int cols);
void free_points_grid(t_point **grid, int rows);
void fill_points_from_buff(t_point **pts, int **buff, int rows, int cols);
int	ft_abs(int n);
int	check_pos_point(int x0, int x1);

/* PARSE.C */

int		ft_check_valid(char *filename, int **buff, int *rows, int *cols);
void	ft_fill_tab(int *tab, char *line, int width);

// void	draw_map(void *mlx, void *win, int **buff, int rows, int cols);
// void	draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1);


// int		on_key(int keycode, t_fdf *fdf);
// int		on_mouse(int button, int x, int y, t_fdf *fdf);
// int		on_mouse_release(int button, int x, int y, t_fdf *fdf);
// int		on_motion(int x, int y, t_fdf *fdf);
// int		on_destroy(t_fdf *fdf);


#endif
