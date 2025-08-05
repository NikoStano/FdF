/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:58:48 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 19:00:36 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_fill_tab(int *tab, char *line, int width)
{
	int		i = 0;
	char	*token;
	
	token = ft_strtoq(line, " ");
	while (i < width && token)
	{
		tab[i] = ft_atoi(token);
		i++;
		token = ft_strtoq(NULL, " ");
	}
}

int	read_map(char *filename, int **buff, int *cols)
{
	int		fd;
	char	*line;
	int		i = 0;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		width = ft_count_words(line);
		if (i == 0)
			*cols = width;
		buff[i] = malloc(sizeof(int) * width);
		if (!buff[i])
			return (free(line), close(fd), -1);
		ft_fill_tab(buff[i], line, width);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
