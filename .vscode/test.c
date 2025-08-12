/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 03:01:48 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 10:50:31 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

// ------------------------------------------------------------
// Parsing minimal — remplit buff et rows/cols
// ------------------------------------------------------------
int ft_check_valid(char *filename, int **buff, int *rows, int *cols)
{
	int     fd;
	char    *line;
	int     i;
	int     width;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	while ((get_next_line(fd, &line)) >= 0 && *line)
	{
		width = ft_count_words(line);
		if (i == 0)
			*cols = width;
		buff[i] = malloc(sizeof(int) * width);
		if (!buff[i])
		{
			free(line);
			while (i-- > 0)
				free(buff[i]);
			close(fd);
			return (-1);
		}
		ft_fill_tab(buff[i], line, width);
		free(line);
		i++;
	}
	close(fd);
	*rows = i;
	return (0);
}

void ft_fill_tab(int *tab, char *line, int width)
{
	int     i = 0;
	char    *token;

	token = ft_strtok(line, " ");
	while (i < width && token)
	{
		tab[i] = ft_atoi(token);
		i++;
		token = ft_strtok(NULL, " ");
	}
}

// ------------------------------------------------------------
// Utilitaires points
// ------------------------------------------------------------
static t_point **alloc_points_grid(int rows, int cols)
{
	int      y;
	t_point **grid;

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

static void free_points_grid(t_point **grid, int rows)
{
	int y = 0;
	while (y < rows)
		free(grid[y++]);
	free(grid);
}

static void fill_points_from_buff(t_point **pts, int **buff, int rows, int cols)
{
	int y, x;
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

// ------------------------------------------------------------
// Dessin
// ------------------------------------------------------------
void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while (1)
	{
		mlx_pixel_put(mlx, win, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void draw_map_internal(t_fdf *fdf, int offx, int offy)
{
	int y;
	int x;
	int rows = fdf->map->rows;
	int cols = fdf->map->cols;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			int z = fdf->buff[y][x];
			int x0 = (x - y) * SCALE + offx;
			int y0 = (x + y) * SCALE / 2 - z * Z_SCALE + offy;
			if (x < cols - 1)
			{
				int z_right = fdf->buff[y][x + 1];
				int x1 = ((x + 1) - y) * SCALE + offx;
				int y1 = ((x + 1) + y) * SCALE / 2 - z_right * Z_SCALE + offy;
				draw_line(fdf->mlx, fdf->win, x0, y0, x1, y1);
			}
			if (y < rows - 1)
			{
				int z_down = fdf->buff[y + 1][x];
				int x1 = (x - (y + 1)) * SCALE + offx;
				int y1 = (x + (y + 1)) * SCALE / 2 - z_down * Z_SCALE + offy;
				draw_line(fdf->mlx, fdf->win, x0, y0, x1, y1);
			}
			x++;
		}
		y++;
	}
}

void draw_map_ctx(t_fdf *fdf)
{
	// Efface et redessine en utilisant les offsets de la vue
	mlx_clear_window(fdf->mlx, fdf->win);
	draw_map_internal(fdf, fdf->view->offset_x, fdf->view->offset_y);
}

// ------------------------------------------------------------
// Hooks clavier/souris
// ------------------------------------------------------------
static int is_key(int key, int a, int b)
{
	return (key == a || key == b);
}

int on_key(int keycode, t_fdf *fdf)
{
	int step = 20; // vitesse de déplacement au clavier

	if (is_key(keycode, KEY_ESC_MAC, KEY_ESC_X11))
		return (on_destroy(fdf));
	if (is_key(keycode, KEY_LEFT_MAC, KEY_LEFT_X11) || is_key(keycode, KEY_A_MAC, KEY_A_X11))
		fdf->view->offset_x -= step;
	else if (is_key(keycode, KEY_RIGHT_MAC, KEY_RIGHT_X11) || is_key(keycode, KEY_D_MAC, KEY_D_X11))
		fdf->view->offset_x += step;
	else if (is_key(keycode, KEY_UP_MAC, KEY_UP_X11) || is_key(keycode, KEY_W_MAC, KEY_W_X11))
		fdf->view->offset_y -= step;
	else if (is_key(keycode, KEY_DOWN_MAC, KEY_DOWN_X11) || is_key(keycode, KEY_S_MAC, KEY_S_X11))
		fdf->view->offset_y += step;
	else
		return (0);
	draw_map_ctx(fdf);
	return (0);
}

int on_mouse(int button, int x, int y, t_fdf *fdf)
{
	(void)x; (void)y;
	// bouton gauche (1) — fonctionne sur mac & linux en général
	if (button == 1)
	{
		fdf->view->mouse_pressed = 1;
		fdf->view->last_x = x;
		fdf->view->last_y = y;
	}
	return (0);
}

int on_mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x; (void)y; (void)button;
	fdf->view->mouse_pressed = 0;
	return (0);
}

int on_motion(int x, int y, t_fdf *fdf)
{
	if (!fdf->view->mouse_pressed)
		return (0);
	int dx = x - fdf->view->last_x;
	int dy = y - fdf->view->last_y;
	fdf->view->offset_x += dx;
	fdf->view->offset_y += dy;
	fdf->view->last_x = x;
	fdf->view->last_y = y;
	draw_map_ctx(fdf);
	return (0);
}

int on_destroy(t_fdf *fdf)
{
	// Petit helper pour quitter proprement via ESC ou croix
	(void)fdf;
	exit(0);
	return (0);
}

// ------------------------------------------------------------
// Entrée du programme — avec t_fdf / t_map / t_view + hooks
// ------------------------------------------------------------
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
