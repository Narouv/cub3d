/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:55:53 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 19:29:47 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	filename_error(char *file, char *c)
{
	int	i;
	int	j;
	int	n;

	i = ft_strlen(file) - 4;
	j = 0;
	n = 1;
	if (ft_strlen(file) < 5 || i < 0)
		n = -1;
	while (file[i])
	{
		if (file[i++] != c[j++])
			n = -1;
	}
	if (n < 0)
		printf("Error: Invalid file name.\n");
	return (n);
}

int	read_check(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		printf("Error: File can't be read.\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	file_check(char *file)
{
	if (filename_error(file, ".cub") < 0)
		return (1);
	if (!read_check(file))
		return (1);
	return (0);
}

char	*skip_empty_lines(int fd, t_map *m)
{
	char	*line;
	size_t	cntr;

	line = get_next_line(fd);
	while (line)
	{
		cntr = 0;
		if (!line)
			break ;
		while (line[cntr] == '\t' || line[cntr] == ' ')
			cntr++;
		if (line[cntr] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			m->line_count++;
		}
		else
			return (line);
	}
	return (NULL);
}

int	diagnose(t_map *m)
{
	if (m->tex_count > 4 || m->col_count > 2)
	{
		ft_printf("double keys\n");
		return (1);
	}
	if (!m->tex[0] || !m->tex[1] || !m->tex[2] || !m->tex[3])
	{
		printf("missing texture\n");
		return (1);
	}
	if (!m->f_col)
	{
		printf("missing floor color\n");
		return (1);
	}
	if (!m->c_col)
	{
		printf("missing ceiling color\n");
		return (1);
	}
	return (0);
}
