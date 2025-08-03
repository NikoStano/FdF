/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:47:02 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/03 14:35:46 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int find_height(char *filename)
{
    int     fd;
    int     height;
    char    *line;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (write(1, "Open ERROR !\n", 13), 0);
    height = 0;
    while (get_next_line(fd, &line) >= 0 && *line != '\0')
    {
        height++;
        free(line);
    }
    free(line);
    if (close(fd) == -1)
        return (write(1, "Close ERROR !\n", 14), 0);
    return (height);

}

int find_width(char *filename)
{
    int     fd;
    int     width;
    char    *line;
    int     i;

    i = -1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (write(1, "Open ERROR !\n", 13), 0);
    width = 0;
    get_next_line(fd, &line);
    if (*line == '\0')
        return (write(1, "Invalid map (empty) !\n", 13), 0);
    while (line[++i])
		if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			width++;
	free(line);
	while (get_next_line(fd, &line))
		free(line);
    free(line);
    if (close(fd) == -1)
        return (write(1, "Close ERROR !\n", 14), 0);
    return (width);
}

void    ft_fill_tab(int **n, char *line, int width)
{
    char    **num;
    int     i;
    int     j;

    num = ft_split(line, ' ');
    i = -1;
    while (num[++i] && i < width)
    {
        n[i] = malloc(sizeof(int) * 2);
        if (!n[i])
            return ;
        n[i][0] = ft_atoi(num[i]);
        j = 0;
        while (num[i][j] && num[i][j] != ',')
            j++;
        if (num[i][j] == ',')
            n[i][1] = ft_atoi_base(&num[i][++j], "0123456789ABCDEF");
        else
            n[i][1] = -1;
        free(num[i]);
    }
    if (i != width || num[i])
        return ;
    free(num);
}

void	ft_check_valid(char *filename, char *buff)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	i = -1;
	while (get_next_line(fd, &line) >= 0 && *line != '\0')
	{
		buff[i++] = malloc(sizeof(int *) * line[i++]);
		if (!line[i])
			return ;
		ft_fill_tab(buff[i], line, filename[i]);
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return ;
}
