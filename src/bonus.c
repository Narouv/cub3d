/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:01:11 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/16 05:11:18 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	put_square(mlx_image_t *img, int x, int y, int color)
{
	int scale = 10; // replace with some sort of scale in the struct
	for (int xs = 0; xs < scale; xs++)
		for (int ys = 0; ys < scale; ys++)
			if (!xs || !ys)
				mlx_put_pixel(img, x+xs, y+ys, 0x000000FF);
			else if (xs == scale -1 || ys == scale -1)
				mlx_put_pixel(img, x+xs, y+ys, 0x000000FF);
			else
				mlx_put_pixel(img, x+xs, y+ys, color);
}

void minimap(void *i/*char **map*/)
{
	mlx_image_t *img = i;
	int scale = 10; // replace with some sort of scale in the struct
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] == '1')
				put_square(img, x*scale, y*scale, 0xFFFFFFFF);
			else if (map[y][x] == '0')
				put_square(img, x*scale, y*scale, 0xCCCCCCFF);
			else
				put_square(img, x*scale, y*scale, 0x0);
		}	
	}
}

void	check_door(t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step_dir.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step_dir.y;
			ray->side = 1;
		}
		if (map[ray->map_pos.x][ray->map_pos.y] == '2')
		{
			ray->door = 1;
			hit = 1;
		}
		else if (map[ray->map_pos.x][ray->map_pos.y] == '1')
		{
			ray->door = 0;
			hit = 1;
		}
	}
	if (!ray->side)
		ray->length = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->length = (ray->side_dist.y - ray->delta_dist.y);
}

void	rot_fov(t_mlxinfo *game, double rot_val)
{
	double	old_dir_x;
	double	old_dir_y;
	double	rot_speed;

	rot_speed = game->time - game->old_time * rot_val;
	old_dir_x = game->player.viewdir.x;
	game->player.viewdir.x = game->player.viewdir.x * cos(rot_speed) - game->player.viewdir.y * sin(rot_speed);
	game->player.viewdir.y = old_dir_x * sin(rot_speed) + game->player.viewdir.y * cos(rot_speed);
	old_dir_y = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(rot_speed) - game->player.plane.y * sin(rot_speed);
	game->player.plane.y = old_dir_y * sin(rot_speed) + game->player.plane.y * cos(rot_speed);
}

void	mouse_rot(void *g)
{
	t_player	*player;
	int			*x;
	int			*y;

	player = &((t_mlxinfo *)g)->player;
	mlx_get_mouse_pos(((t_mlxinfo *)g)->mlx, x, y);
	rot_fov(game, (((double)x - (double)WIDTH) * 0.5);
	mlx_set_mouse_pos(((t_mlxinfo *)g)->mlx, WIDTH / 2, HEIGHT / 2);
}


void	ft_controls_bonus(void *g)
{
	t_mlxinfo	*game;

	game = g;
	game->old_time = game->time;
	game->time = mlx_get_time();
	clear_screen(game->img);
	cast_rays(game);
	minimap(game->img);
	
	double	frame_time = game->time - game->old_time;
	double	move_speed = frame_time * 5.0;
	double	rot_speed = frame_time * 3.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.pos.x += game->player.viewdir.x * move_speed;
		game->player.pos.y += game->player.viewdir.y * move_speed;
	}
	//move backwards
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.pos.x -= game->player.viewdir.x * move_speed;
		game->player.pos.y -= game->player.viewdir.y * move_speed;
	}
	//rotate to the right
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		rot_fov(game, -3.0);
	//rotate to the left
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		rot_fov(game, 3.0);
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		toggle_door(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	toggle_door(t_mlxinfo *game)
{
	double	l;
	int		x;
	double	camera;

	x = WIDTH / 2;
	camera = 2 * x / (double)WIDTH - 1;
	update_ray(&game->ray, &game->player, camera);
	ray_direction(&game->ray, &game->player);
	l = check_door(&game->ray);
	if (game->ray.door)
		map[game->ray.map_pos.x][game->ray.map_pos.y] = '1';
	else
		map[game->ray.map_pos.x][game->ray.map_pos.y] = '2';
}
