/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:02 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/04 17:00:22 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_check_valid(char *filename, char *buff)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	i = 0;
	while (get_next_line(fd, &line) >= 0 && *line != '\0')
	{
		buff[i] = malloc(sizeof(int *) * line[i]);
		if (!line[i])
			return ;
		ft_fill_tab(buff[i], line, filename[i]);
		free(line);
        i++;
	}
	free(line);
	if (close(fd) == -1)
		return ;
}
