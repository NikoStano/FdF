/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:58:48 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 11:33:10 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
