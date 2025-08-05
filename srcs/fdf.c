/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:02 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/05 02:43:42 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_check_valid(char *filename, int **buff, int *rows, int *cols)
{
	int		fd;
	char	*line;
	int		i;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
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

// int main(int argc, char **argv)
// {
// 	int		**buff;

// 	if (argc != 2)
// 	{
// 		ft_printf("Usage: %s <filename>\n", argv[0]);
// 		return (EXIT_FAILURE);
// 	}
// 	buff = malloc(sizeof(int *) * 100); // Allocate memory for 100 lines
// 	if (!buff)
// 	{
// 		perror("Memory allocation failed");
// 		return (EXIT_FAILURE);
// 	}
// 	ft_check_valid(argv[1], buff);
// 	// Free each allocated line
// 	for (int i = 0; i < 100; i++)
// 	{
// 		if (buff[i])
// 			free(buff[i]);
// 	}
// 	free(buff);
// 	return (EXIT_SUCCESS);
// }
