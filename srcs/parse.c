/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:58:48 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/14 18:56:20 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_check_valid(char *filename, int **buff, int *rows, int *cols)
{
	t_valid	v;
	int		i;

	v.fd = open(filename, O_RDONLY);
	if (v.fd == -1)
		return (-1);
	i = 0;
	while (get_next_line(v.fd, &(v.line)) > 0 && v.line)
	{
		if (i == 0)
		{
			v.width = ft_count_words(v.line);
			*cols = v.width;
		}
		else if (ft_count_words(v.line) != v.width)
			return (free(v.line), close(v.fd), -1);
		buff[i] = malloc(sizeof(int) * v.width);
		if (!buff[i])
			return (free(v.line), close(v.fd), -1);
		ft_fill_tab(buff[i++], v.line, v.width);
		free(v.line);
	}
	*rows = i;
	return (close(v.fd), 0);
}

void	ft_fill_tab(int *tab, char *line, int width)
{
	int		i;
	char	*token;

	token = ft_strtok(line, " ");
	i = 0;
	while (i < width && token)
	{
		tab[i] = ft_atoi(token);
		i++;
		token = ft_strtok(NULL, " ");
	}
}
