/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:00:44 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/19 21:27:53 by rnauke           ###   ########.fr       */
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
# define WIDTH 640
# define HEIGHT 480
# define TEX_WIDTH 256
# define TEX_HEIGHT 256
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

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
	int			width;
	int			height;
	char		**dir;
	t_player	*player;
	int			line_count;
	int			tex_count;
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
	mlx_image_t *img;
	t_player	player;
	t_ray		ray;
	t_texture	*texture;
	t_map		*map;
	double		time;
	double		str_update_time;
	double		old_time;
}	t_mlxinfo;

void	cast_rays(t_mlxinfo *game);
void	clear_screen(void *param);

void	rot_fov(t_mlxinfo *game, double rot_val);
void	move_player(t_mlxinfo *game, t_vec axis, double val);
void	ft_controls(void *g);

void	update_ray(t_ray *ray, t_player *player, double camera);
void	ray_length(t_ray *ray, t_map *map);
void	ray_direction(t_ray *ray, t_player *player);

int	parser(t_map *m, char *file);

#endif
