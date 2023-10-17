/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:00:44 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/17 15:44:27 by rnauke           ###   ########.fr       */
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
}	t_player;

typedef struct s_map
{
	int				map_fd;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	char			*floor;
	char			*ceil;
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
	t_texture	**texture;
	// t_map		map;
	double		time;
	double		str_update_time;
	double		old_time;
}	t_mlxinfo;

int	verify_input(t_map *m);

#endif
