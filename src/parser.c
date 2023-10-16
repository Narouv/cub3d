/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhortens <rhortens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:15:57 by rhortens          #+#    #+#             */
/*   Updated: 2023/10/16 11:41:20 by rhortens         ###   ########.fr       */
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

	fd = open(file, 0_RDONLY);
	if (fd < 0)
	{
		close(fd);
		printf("Error: File can't be read.\n");
	}
	close(fd);
	return (1);
}

int	file_check(char *file)
{
	if (filename_error(file, ".cub") < 0)
		return (1);
	if (!read_check(file));
		return (1);
	return (0);
}

void	map_dir(t_map *m, int fd)
{
	int		i;
	char	*line;

	i = 0;
	m->height = 2;
	m->width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > m->width)
			m->width = ft_strlen(line);
		free(line);
		m->height++;
	}
	m->width += 2;
	m->dir = malloc (m->height * sizeof(char));
	while (i < m->height)
	{
		m->dir[i] = malloc((m->width + 1) * sizeof(char));
		m->dir[i++][m->width] = '\0';
	}
}

int	no_content(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (i == j)
		return (1);
	return (0);
}

void	map_fill(t_map *m, int fd)
{
	int		i;
	int		j;
	char	*line;

	i = 1;
	j = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (m->line_count)
			m->line_count--;
		else if (!no_content(line))
		{
			m->dir[i][j] = ' ';
			while (++j < (ft_strlen(line) + 1))
				m->dir[i][j] = line[j - 1];
			//fill spaces
		}
		else if (i > 0)
			//fill spaces
		free(line);
	}
}

int	map_check(t_map *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < m->height)
	{
		while (j < m->width)
		{
			if (m->dir[i][j] != 'N' && m->dir[i][j] != 'E' && m->dir[i][j] != 'S' &&
				m->dir[i][j] != 'W' && m->dir[i][j] != '0' && m->dir[i][j] != '1' && m->dir[i][j] != ' ')
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	dir_check(t_map *m)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (i < m->height)
	{
		while (j < m->width)
		{
			if (m->dir[i][j] == 'N' || m->dir[i][j] == 'E' || m->dir[i][j] == 'S' || m->dir[i][j] == 'W')
			{
				m->player.pos.x = j;
				m->player.pos.y = i;
				n++;
			}
			j++;
		}
		i++;
	}
	if (n != 1)
	{
		printf ("Error: Please use exactly one spawn point.\n");
		return (1);
	}
	return (0);
}

int	space_check(t_map *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < m->height)
	{
		while (j < m->width)
		{
			if (m->dir[i][j] == '0' || m->dir[i][j] == 'N' || m->dir[i][j] == 'E' ||
				m->dir[i][j] == 'S' || m->dir[i][j] == 'W')
			{
				if (m->dir[i + 1][j] == ' ' || m->dir[i - 1][j] == ' ' ||
					m->dir[i][j + 1] == ' ' || m->dir[i][j - 1] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_validation(t_map *m, int fd, char *file)
{
	map_dir(m, fd);
	close (fd);
	fd = open(file, 0_RDONLY);
	//fill spaces
	map_fill(m, fd);
	//fill spaces
	if (map_check(m) || dir_check(m) || space_check(m))
	{
		printf("Error: Map not valid.\n");
		//free
		return (1);
	}
	//initialize stuff
}

int	cond_check(int i, int n, int status)
{
	if (i < 4 || !n)
	{
		if (status == 1)
			printf("Error: Wrong texture input.\n");
		return (1);
	}
	return (0);
}

int	dirtex_check(char *line, int i, int status)
{
	if (i == 0 && ft_strcmp(line, "NO")) //ft_strcmp!!
		return (1);
	else if (i == 1 && ft_strcmp(line, "SO")) //ft_strcmp!!
		return (1);
	else if (i == 2 && ft_strcmp(line, "WE")) //ft_strcmp!!
		return (1);
	else if (i == 3 && ft_strcmp(line, "EA")) //ft_strcmp!!
		return (1);
	if (status == 1)
		printf("Error: Texture not correct.\n");
	return (0);
}

int	line_check(char **split, int i, int status)
{
	if (!read_check(split[1]))
		return (0);
	if (!dirtex_check(split[0], i, status))
		return (0);
	return (1);
}

int	format_check(char *line, int i, int status)
{
	int		j;
	int		n;
	char	**split;

	j = 0;
	n = 0;
	split = ft_split(line, ' ');
	while(split[j])
		j++;
	if (j != 2)
	{
		//free
		return (0);
	}
	n = line_check(split, i, status);
	//free
	if (!n)
		return (0);
	return (1);
}

int	wrong_texture(t_map *m, int fd, int status)
{
	int		i;
	int		n;
	char	*line;

	i = 0;
	n = 1;
	while (n && i < 4)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		m->line_count++;
		if (!no_content(line))
			n = format_check(line, i++, status);
		free(line);
	}
	return (cond_check(i, n, status));
}

int	texture_check(t_map *m, int fd, char *file)
{
	int	i;
	int	tmp;

	i = 0;
	m->line_count = 0;
	m->tex_count = 0;
	tmp = open(file, 0_RDONLY);
	while (!wrong_texture(m, tmp, 0))
		m->tex_count++;
	close(tmp);
	if (m->tex_count == 0)
	{
		while (!wrong_texture(m, tmp, 1))
			m->tex_count++;
		return (1);
	}
	m->line_count = 0;
	while (i < m->tex_count)
	{
		texture_check(m, fd, 1);
		i++;
	}
	return (0);
}

int	col_comma_check(char *line)
{
	int	i;
	int	n;
	
	i = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == ',')
			n++;
		i++;
	}
	if (n != 2)
		return (0);
	return (1);
}

int	cf_check(char **col, int n, int i)
{
	if (i == 0)
	{
		if (ft_strcmp(col[0], "F"))
			return (1);
	}
	if (i == 1)
	{
		if (ft_strcmp(col[0], "C"))
			return (1);
	}
	printf("Error: Ceiling/Floor color not correct.\n");
	//free
	return (0);
}

int	rgb_check(char **num, int n)
{
	int	i;
	int	tmp;
	int	count;

	i = 0;
	tmp = 0;
	count = 0;
	if (ft_isdigit(num[1]) && ft_isdigit(num[3]) && ft_isdigit(num[5]))
	{
		while (i < n)
		{
			if (i % 2 == 1)
			{
				tmp = ft_atoi(num[i]);
				if (tmp > -1 && tmp < 256)
					count++;
			}
			i++;
		}
		if (count == 3)
			return (1);
	}
	//free
	return (printf("Error: RGB colors wrong.\n"), 0);
}

int	col_format_check(char *line, int i)
{
	int		n;
	char	**split;

	if (!col_comma_check(line))
		return (0);
	//split input and check for a total of exactly 6 elements?
	if (!cf_check(split, n, i))
		return (0);
	if (!rgb_check(split, n))
		return (0);
	//free
	return (1);
}

int	color_check(t_map *m, int fd)
{
	int		i;
	int		n;
	char	*line;

	i = 0;
	n = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		m->line_count++;
		if (!no_content(line))
			n = col_format_check(line, i++);
		free(line);
		if (i > 1 || !n)
			break ;
	}
	if (i < 2 || !n)
	{
		printf("Error: Color input wrong.\n");
		return (1);
	}
	return (0);
}

void	tex_store(t_map *m, int fd)
{
	int		i;
	char	**tmp;
	char	*line;

	i = 0;
	m->tex = malloc((m->tex_count * 4) * sizeof(char *));
	while (i < m->tex_count * 4)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_split(line, ' ');
		if (!no_content(line))
			m->tex = ft_strdup(tmp[1]);
		free(line);
		//free array
	}
}

void	col_store(t_map *m, int fd)
{
	int		i;
	int		c;
	char	**tmp;
	char	*line;

	i = 0;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		//tmp = split like col_format_check
		if (!no_content(line))
		{
			//c = rgb to hex
			if (i == 0)
				m->f_col = c;
			else
				m->c_col = c;
			i++;
		}
		free(line);
		//free array
	}
}

int	parser(t_map *m, char *file)
{
	int	fd;

	if (file_check(file))
		return (1);
	fd = open(file, 0_RDONLY);
	if (texture_check(m, fd, file) || color_check(m, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(file, 0_RDONLY);
	tex_store(m, fd);
	col_store(m, fd);
	if (map_validatiton(m, fd, file))
	{
		close(fd);
		return (1);
	}
	close (fd);
	return (0);
}
