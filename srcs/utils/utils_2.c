/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:34:45 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/21 20:27:33 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	count_cols(const char *s)
{
	int	i;
	int	in;
	int	n;

	i = 0;
	in = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != ' ' && !in)
		{
			in = 1;
			n++;
		}
		else if (s[i] == ' ')
			in = 0;
		i++;
	}
	return (n);
}

void	free_stuff(int **stuff, int rows)
{
	int	i;

	if (!stuff)
		return ;
	i = 0;
	while (i < rows)
	{
		free(stuff[i]);
		stuff[i] = NULL;
		i++;
	}
	free(stuff);
	stuff = NULL;
}

void	map_free(t_map *m)
{
	int	i;

	if (m == NULL)
		return ;
	if (m->pt)
	{
		i = 0;
		while (i < m->rows)
		{
			free(m->pt[i]);
			m->pt[i] = NULL;
			i++;
		}
		free(m->pt);
		m->pt = NULL;
	}
	if (m->zbuf)
		free_stuff(m->zbuf, m->rows);
	if (m->cbuf)
		free_stuff(m->cbuf, m->rows);
	m->rows = 0;
	m->cols = 0;
}

int	base_color(int z)
{
	if (z > 0)
		return (GREEN);
	if (z < 0)
		return (BLUE);
	return (BROWN);
}
