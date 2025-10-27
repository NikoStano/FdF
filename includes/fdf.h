/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:36:42 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 05:01:32 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* LIBRARIES */
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/keysym.h>
# include <math.h>

# include "define.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

/* STRUCT */
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}			t_point;

typedef struct s_map
{
	int		rows;
	int		cols;
	int		**zbuf;
	int		**cbuf;
	t_point	**pt;
}			t_map;

typedef struct s_bres
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}			t_bres;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}			t_img;

typedef struct s_view
{
	int		off_x;
	int		off_y;
	int		scale;
	int		z_scale;
	int		mouse_down;
	int		last_x;
	int		last_y;
	int		projection;
	int		auto_rotate;
	int		color_mode;
	double	ang_x;
	double	ang_y;
	double	ang_z;
	double	piv_x;
	double	piv_y;
}			t_view;

typedef struct s_v2
{
	int	x;
	int	y;
}			t_v2;

typedef struct s_v3
{
	int	x;
	int	y;
	int	z;
}			t_v3;

typedef struct s_proj
{
	long	sc;
	double	c;
	double	s;
	double	tx;
	double	ty;
	double	xr;
	double	yr;
}			t_proj;

typedef struct s_rot
{
	double	c;
	double	s;
	double	xr;
	double	yr;
	double	zr;
	double	cx;
	double	sx;
	double	cy;
	double	sy;
	double	cz;
	double	sz;
}			t_rot;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	fb;
	t_map	map;
	t_view	view;
}			t_app;

/* DRAW */
/* image.c */
void	img_create(t_app *a, t_img *img, int w, int h);
void	img_destroy(t_app *a, t_img *img);
void	img_clear(t_img *img);
void	put_px(t_img *img, int x, int y, int color);

/* line.c */
void	draw_line(t_img *img, t_v2 a, t_v2 b, int color);

/* render.c */
void	render(t_app *a);

/* PARSE */
/* parse.c */
int		map_load(t_map *m, const char *path);

/* parse_util.c */
int		parse_line_into(int *dst_z, int *dst_c, char *line, int cols);

/* PROJECT */
/* project.c */
void	iso_project(t_v3 p, t_view *v, t_v2 *out);

/* project2.c */
void	parallel_project(t_v3 p, t_view *v, t_v2 *out);
void	conic_project(t_v3 p, t_view *v, t_v2 *out);
void	project(t_v3 p, t_view *v, t_v2 *out);

/* project3.c */
void	parallel_project_3d(t_v3 p, t_view *v, t_v2 *out);
void	conic_project_3d(t_v3 p, t_view *v, t_v2 *out);

/* project4.c */
void	iso_project_3d(t_v3 p, t_view *v, t_v2 *out);

/* UTILS */
/* utils_1.c */
int		clampi(int v, int lo, int hi);
int		ft_abs(int n);
int		word_count(const char *s);
int		safe_atoi(const char *s, int *out);
void	ft_split_free(char **sp);

/* utils_2.c*/
int		count_cols(const char *s);
void	free_stuff(int **stuff, int rows);
void	map_free(t_map *m);
int		base_color(int z);

/* VIEW */
/* hooks */
int		on_key(int key, t_app *a);
int		on_mouse(int btn, int x, int y, t_app *a);
int		on_mouse_release(int btn, int x, int y, t_app *a);
int		on_motion(int x, int y, t_app *a);
int		on_destroy(t_app *a);

/* view.c */
void	view_reset(t_view *v);
void	view_zoom(t_view *v, t_v2 pivot, int num, int den);
void	view_rotate_z(t_view *v, double delta);
void	view_rotate_x(t_view *v, double delta);
void	view_rotate_y(t_view *v, double delta);
void	draw_hud(t_app *a);
int		interpolate_color(int c1, int c2, float ratio);
int		get_color(t_app *a, int x, int y, int z);
int		auto_rotate_loop(t_app *a);

/* init.c */
int		win_init(t_app *a, const char *path);
void	win_destroy(t_app *a);
int		win_run(t_app *a);

#endif
