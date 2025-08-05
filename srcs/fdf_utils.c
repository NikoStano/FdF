/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:55:05 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 19:13:58 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	lines = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		lines++;
	}
	close(fd);
	return (lines);
}

char	*ft_strtoq(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*token;

	if (str)
		next_token = str;
	if (!next_token)
		return (0);
	token = next_token;
	while (*next_token && !ft_strchr(delim, *next_token))
		next_token++;
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;
	return (token);
}
