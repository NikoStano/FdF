/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:58:48 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/13 12:43:02 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
    while (get_next_line(fd, &line) > 0 && line)
	{
		if (i == 0)
		{
			width = ft_count_words(line);
			*cols = width;
		}
		else if (ft_count_words(line) != width)
		{
			free(line);
			close(fd);
			return (-1); // lignes de longueurs différentes
		}
		buff[i] = malloc(sizeof(int) * width);
		if (!buff[i])
		{
			free(line);
			close(fd);
			return (-1); // échec d'allocation
		}
		ft_fill_tab(buff[i], line, width);
		free(line);
		i++;
	}
	*rows = i;
	close(fd);
	return (0);
	// Si on a lu au moins une ligne, on retourne 0
	if (i > 0)
		return (0);
	return (-1); // fichier vide ou erreur de lecture
	// Si on n'a pas lu de lignes, on retourne -1
	// (fichier vide ou erreur de lecture)
	// Si on a lu au moins une ligne, on retourne 0
	// (buff rempli, rows et cols définis)
	// On suppose que buff est déjà alloué avec une taille suffisante
	// (par exemple, malloc(sizeof(int *) * 100) pour 100 lignes max)
	// et que les lignes sont toutes de même longueur.
}

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
