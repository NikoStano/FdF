/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:19 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 08:31:13 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	first_pass(int fd, t_map *m)
{
	char	*ln;
	int		r;

	m->rows = 0;
	m->cols = 0;
	ln = NULL;
	r = get_next_line(fd, &ln);
	if (r <= 0)
	{
		if (ln)
			free(ln);
		return (1);
	}
	m->cols = count_cols(ln);
	m->rows = 1;
	free(ln);
	return (count_rows_from_fd(fd, m));
}

static int	alloc_zbuf(t_map *m)
{
	int	y;

	m->zbuf = (int **)malloc(sizeof(int *) * m->rows);
	if (!m->zbuf)
		return (1);
	y = 0;
	while (y < m->rows)
	{
		m->zbuf[y] = (int *)malloc(sizeof(int) * m->cols);
		if (!m->zbuf[y])
		{
			free_zbuf_rows(m->zbuf, y);
			m->zbuf = NULL;
			return (1);
		}
		y++;
	}
	return (0);
}

static int	alloc_cbuf(t_map *m)
{
	int	y;

	m->cbuf = (int **)malloc(sizeof(int *) * m->rows);
	if (!m->cbuf)
		return (1);
	y = 0;
	while (y < m->rows)
	{
		m->cbuf[y] = (int *)malloc(sizeof(int) * m->cols);
		if (!m->cbuf[y])
		{
			free_stuff(m->cbuf, y);
			m->cbuf = NULL;
			return (1);
		}
		init_cbuf_row(m->cbuf[y], m->cols);
		y++;
	}
	return (0);
}

static int	fill_row(int fd, t_map *m)
{
	char		*ln;
	int			y;
	int			r;

	y = 0;
	r = get_next_line(fd, &ln);
	while (r > 0)
	{
		if (parse_line_into(m->zbuf[y], m->cbuf[y], ln, m->cols))
			return (free(ln), 1);
		free(ln);
		ln = NULL;
		r = get_next_line(fd, &ln);
		y++;
		if (r <= 0)
			break ;
	}
	return (0);
}

int	map_load(t_map *m, const char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (first_pass(fd, m))
		return (close(fd), 1);
	lseek(fd, 0, SEEK_SET);
	if (alloc_zbuf(m))
		return (close(fd), 1);
	if (alloc_cbuf(m))
		return (close(fd), map_free(m), 1);
	if (fill_row(fd, m))
		return (close(fd), map_free(m), 1);
	close(fd);
	return (0);
}
