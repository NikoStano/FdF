#ifndef FDF_H
# define FDF_H

  //////////////
 // Includes //
//////////////
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
# include <X11/keysym.h>

  ////////////////
 // Constantes //
////////////////
# define NAME "FdF"
# define TITLE "FdF simple"
# define WIDTH 1000
# define HEIGHT 800
# define SCALE 20       // échelle par défaut (plan)
# define Z_SCALE 5      // échelle par défaut (altitude)
# define OFFSET_X 500   // offsets par défaut
# define OFFSET_Y 400
# define MIN_SCALE 2
# define MAX_SCALE 200

  ////////////
 // Souris //
////////////
# define BTN_LEFT         1
# define BTN_SCROLL_UP    4
# define BTN_SCROLL_DOWN  5

  ///////////////////////////
 // Structures de données //
///////////////////////////
typedef struct s_point
{
    int x;
    int y;
    int z;
}               t_point;

typedef struct s_map
{
    int     rows;
    int     cols;
    t_point **point;
}               t_map;

typedef struct s_view
{
    int     offset_x;
    int     offset_y;
    int     last_x;
    int     last_y;
    int     mouse_pressed;
    int     scale;      // dynamique (zoom)
    int     z_scale;    // dynamique (zoom)
    t_map   map;
}               t_view;

typedef struct s_fdf
{
    void    *mlx;
    void    *win;
    int     **buff;     // grille d'altitudes brute
    t_point **point;    // grille de points enrichis (x,y,z)
    t_map   *map;
    t_view  *view;
}               t_fdf;

  ////////////////
 // Prototypes //
////////////////
int     ft_check_valid(char *filename, int **buff, int *rows, int *cols);
char    *ft_strtok(char *str, const char *delim);
void    ft_fill_tab(int *tab, char *line, int width);

  ////////////
 // Dessin //
////////////
void    draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1);
void    draw_map_ctx(t_fdf *fdf);

  ///////////
 // Hooks //
///////////
int     on_key(int keycode, t_fdf *fdf);
int     on_mouse(int button, int x, int y, t_fdf *fdf);
int     on_mouse_release(int button, int x, int y, t_fdf *fdf);
int     on_motion(int x, int y, t_fdf *fdf);
int     on_destroy(t_fdf *fdf);

  //////////
 // Zoom //
//////////
void    view_reset(t_view *v);
void    apply_zoom(t_fdf *fdf, double factor, int pivot_x, int pivot_y);

  ///////////
 // Utils //
///////////
int     ft_abs(int n);
int     check_pos_point(int x0, int x1);
int     ft_count_words(char *str);
char    *ft_strtok(char *str, const char *delim);

  ///////////
 // Points //
////////////
t_point **alloc_points_grid(int rows, int cols);
void    free_points_grid(t_point **grid, int rows);
void    fill_points_from_buff(t_point **pts, int **buff, int rows, int cols);


#endif