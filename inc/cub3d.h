/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:00:44 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 19:31:21 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# define WIDTH 1440
# define HEIGHT 810
# define TEX_WIDTH 256
# define TEX_HEIGHT 256

typedef struct s_veci
{
	int	x;
	int	y;
}	t_veci;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_player
{
	t_vec	pos;
	t_vec	viewdir;
	t_vec	plane;
	char	stand;
}	t_player;

typedef struct s_map
{
	size_t		width;
	size_t		height;
	char		**dir;
	t_player	*player;
	char		*whole_map;
	int			line_count;
	int			tex_count;
	int			col_count;
	int			p_count;
	char		**tex;
	int			f_col;
	int			c_col;
}	t_map;

typedef struct s_texture
{
	int		*pixels;
	int		x;
	double	y;
	double	tex_step;
	int		wall_height;
	int		color;
}	t_texture;

typedef struct s_ray
{
	t_vec		angle;
	t_vec		delta_dist;
	t_vec		side_dist;
	t_veci		map_pos;
	t_veci		step_dir;
	int			side;
	double		length;
}	t_ray;

typedef struct s_mlxinfo
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_ray		ray;
	t_texture	*texture;
	t_map		*map;
	double		time;
	double		str_update_time;
	double		old_time;
}	t_mlxinfo;

// bonus.c
void	mouse_rot(void *g);
void	minimap(t_mlxinfo *game);
void	put_square(t_mlxinfo *game, int x, int y, int color);

// control.c
void	rot_fov(t_mlxinfo *game, double rot_val);
void	move_player(t_mlxinfo *game, t_vec axis, double val);
void	ft_controls(void *g);

// draw.c
t_veci	calc_wall_height(int *wall_height, double ray_len);
void	draw_pixel_column(t_mlxinfo *game, int x, t_veci wall, t_texture t);
void	calc_pixel_column(t_mlxinfo *game, int x, t_texture *texture);
int		get_texture_side(t_ray *ray);

// init.c
void	init_player(t_player *player);
void	init_ray(t_ray *ray);
void	init_game(t_mlxinfo *game);
void	init_textures(t_mlxinfo *game);
void	init_map(t_map *map, t_player *player);

// main.c
int		parser(t_map *m, char *file);

// parse_color.c
int		rgb_con(char *r, char *g, char *b);
int		check_split(char **split);
int		color(char *color_str, int *color, t_map *m);
int		valid_char(char c);
int		check_map(char *m);

// parse_map.c
int		space_check(char **s, t_map *m, size_t i, size_t j);
int		check_bounds(char **s, t_map *m);
char	**get_dimensions(t_map *m);
int		get_player_pos(t_map *m);
void	fill_map(char **s, t_map *m);

// parse_util.c
int		filename_error(char *file, char *c);
int		read_check(char *file);
int		file_check(char *file);
char	*skip_empty_lines(int fd, t_map *m);
int		diagnose(t_map *m);

// parser.c
int		texture(char *tex_str, char **tex_path, char *symbol, t_map *m);
int		check_struct(char *line, char *str);
int		color_or_texture(int fd, t_map *m);
int		save_map(int fd, t_map *m);
int		get_map(int fd, t_map *m);

// ray.c
void	update_ray(t_ray *ray, t_player *player, double camera);
void	ray_length(t_ray *ray, t_map *map);
void	ray_direction(t_ray *ray, t_player *player);
void	cast_rays(t_mlxinfo *game);

// util.c
int		*get_pixel_data(char *img_path);
void	clear_screen(void *param);
void	free_string(char **str);
void	cleanup(t_mlxinfo *game);

#endif
