/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:15:57 by rhortens          #+#    #+#             */
/*   Updated: 2023/10/21 13:02:31 by rnauke           ###   ########.fr       */
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

void	free_string(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	rgb_con(char *r, char *g, char *b)
{
	int	red;
	int	gre;
	int	blu;
	int	hex;

	red = ft_atoi(r);
	gre = ft_atoi(g);
	blu = ft_atoi(b);
	if (red > 255 || gre > 255 || blu > 255)
		return (1);
	hex = (red << 24) | (gre << 16) | (blu << 8) | 0xff;
	return (hex);
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

int	check_split(char **split)
{
	int	cntr;
	int	cntr2;

	cntr = 0;
	while (split[cntr])
	{
		cntr2 = 0;
		while (split[cntr][cntr2])
		{
			if (!ft_isdigit(split[cntr][cntr2]))
				return (1);
			cntr2++;
		}
		cntr++;
	}
	if (cntr > 3)
		return (1);
	return (0);
}

int	color(char *color_str, int *color)
{
	char	*str;
	char	**split;

	str = ft_strtrim(color_str, "FC \t\n");
	split = ft_split(str, ',');
	if (check_split(split) || !split[0] || !split[1] || !split[2])
	{
		free(str);
		free_string(split);
		return (1);
	}
	*color = rgb_con(split[0], split[1], split[2]);
	free(str);
	free_string(split);
	if (*color == 1)
		return (1);
	return (0);
}

int	texture(char *tex_str, char **tex_path, char *symbol, t_map *m)
{
	char	*str;
	char	*set;

	set = ft_strjoin(symbol, " \t\n");
	str = ft_strtrim(tex_str, set);
	free(set);
	if (!read_check(str))
	{
		free(str);
		return (1);
	}
	*tex_path = ft_strdup(str);
	m->tex_count++;
	return (0);
}

int	check_struct(char *line, char *str)
{
	free(line);
	if (ft_strncmp(str, "F", 1) && ft_strncmp(str, "C", 1)
		&& ft_strncmp(str, "N", 1) && ft_strncmp(str, "S", 1)
		&& ft_strncmp(str, "E", 1) && ft_strncmp(str, "W", 1))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	color_or_texture(int fd, t_map *m)
{
	char	*line;
	char	*str;
	int		ret_val;

	ret_val = 0;
	while (!ret_val && (m->tex_count != 4 || !m->f_col || !m->c_col))
	{
		line = skip_empty_lines(fd, m);
		str = ft_strtrim(line, "\t \n");
		if (!ft_strncmp(str, "F ", 2))
			ret_val = color(str, &m->f_col);
		else if (!ft_strncmp(str, "C ", 2))
			ret_val = color(str, &m->c_col);
		else if (!ft_strncmp(str, "NO ", 3))
			ret_val = texture(str, &m->tex[0], "NO", m);
		else if (!ft_strncmp(str, "SO ", 3))
			ret_val = texture(str, &m->tex[1], "SO", m);
		else if (!ft_strncmp(str, "EA ", 3))
			ret_val = texture(str, &m->tex[2], "EA", m);
		else if (!ft_strncmp(str, "WE ", 3))
			ret_val = texture(str, &m->tex[3], "WE", m);
		if (check_struct(line, str))
			break ;
	}
	return (ret_val);
}

void	save_map(int fd, t_map *m)
{
	char	*line;
	char	*one;

	line = skip_empty_lines(fd, m);
	m->whole_map = ft_strjoin("", line);
	while (line)
	{
		one = m->whole_map;
		m->whole_map = ft_strjoin(one, line);
		free(one);
		free(line);
		line = get_next_line(fd);
	}
}

int	valid_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' )
	{
		return (1);
	}
	return (0);
}

int	space_check(char **s, t_map *m, size_t i, size_t j)
{
	if (i && j && valid_char(s[i][j]))
	{
		if (j < ft_strlen(s[i])	&& (s[i][j + 1] == ' '
			|| s[i][j - 1] == ' '))
			return (1); //printf("end line\n");
		if (i < m->height - 1 && (s[i + 1][j] == ' ' || s[i - 1][j] == ' '))
			return (1); //printf("end line\n");
	}
	return (0);
}

int	check_bounds(char **s, t_map *m)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			if (!i && (s[i][j] != '1' && s[i][j] != ' '))
				return (1); //printf("end line\n");
			else if (i == m->height - 1 && (s[i][j] != '1' && s[i][j] != ' '))
				return (1); //printf("end line\n");
			else if (!j && (s[i][j] != '1' && s[i][j] != ' '))
				return (1); //printf("end line\n");
			else if (!s[i][j] && ft_strlen(s[i]) > j && s[i][j - 1] != '1')
				return (1); //printf("end line\n");
			else if (space_check(s, m, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	**get_dimensions(t_map *m)
{
	char	**split;
	size_t	cntr;
	size_t	wide;

	cntr = 0;
	split = ft_split(m->whole_map, '\n');
	while (split[cntr])
	{
		wide = ft_strlen(split[cntr]);
		if (wide > m->width)
			m->width = wide;
		cntr++;
	}
	m->height = cntr;
	m->dir = ft_calloc(m->height, sizeof(char *));
	cntr = 0;
	while (cntr < m->height)
	{
		m->dir[cntr] = ft_calloc(m->width + 1, sizeof(char));
		cntr++;
	}
	return (split);
}

int	get_player_pos(t_map *m)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (++i < m->height)
	{
		j = -1;
		while (++j < m->width)
		{
			if (m->dir[i][j] == 'N' || m->dir[i][j] == 'E' ||
				m->dir[i][j] == 'S' || m->dir[i][j] == 'W')
			{
				m->player->stand = m->dir[i][j];
				m->player->pos.x = (double)j + 0.5;
				m->player->pos.y = (double)i + 0.5;
				m->dir[i][j] = '0';
				m->p_count++;
			}
		}
	}
	if (m->p_count > 1)
		return (1);
	return (0);
}

void	fill_map(char **s, t_map *m)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (s[i])
	{
		j = 0;
		len = ft_strlen(s[i]);
		while (j < m->width)
		{
			if (j >= len)
				m->dir[i][j] = ' ';
			else
				m->dir[i][j] = s[i][j];
			j++;
		}
		m->dir[i][j] = '\0';
		i++;
	}
}

int	get_map(int fd, t_map *m)
{
	char **s;

	save_map(fd, m);
	s = get_dimensions(m);
	fill_map(s, m);
	if (check_bounds(m->dir, m))
	{
		ft_printf("invalid map\n");
		return (1);
	}
	if (get_player_pos(m))
	{
		ft_printf("only 1 player allowed\n");
		return (1);
	}
	printf("x: %f y: %f", m->player->pos.x, m->player->pos.y);
	return (0);
}

int	diagnose(t_map *m)
{
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

int	parser(t_map *m, char *file)
{
	int		fd;

	if (file_check(file))
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Opening file.\n"), 1);
	if (color_or_texture(fd, m) || diagnose(m))
	{
		close(fd);
		return (1);
	}
	if (get_map(fd, m))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}