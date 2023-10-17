/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:58:05 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/17 16:55:50 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

char	map[MAP_WIDTH][MAP_HEIGHT] = { 
{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '1', '1', '0', '1', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' },
{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' }
};

void	init_player(t_player *player)
{
	// east = viewdir x: 0 y: 1, plane x: 0.66 y: 0
	// south = viewdir x: 1 y: 0, plane x: 0 y: -0.66
	// west = viewdir x: 0 y: -1, plane x: -0.66 y: 0
	player->pos.x = 5;
	player->pos.y = 5;
	player->viewdir.x = -1;
	player->viewdir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0.66;
}

void	init_ray(t_ray *ray)
{
	ray->angle.x = 0;
	ray->angle.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->map_pos.x = 0;
	ray->map_pos.y = 0;
	ray->side = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
}

void	init_game(t_mlxinfo *game)
{
	game->time = 0;
	game->str_update_time = 0;
	game->old_time = 0;
}

// only works for square textures (same width and height)
int	*get_pixel_data(char *img_path)
{
	int				*txt_arr;
	uint8_t			p;
	size_t			tx;
	size_t			ty;
	mlx_texture_t	*t;

	t = mlx_load_png(img_path);
	p = t->bytes_per_pixel;
	ty = 0;
	txt_arr = malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
	while (ty < TEX_WIDTH)
	{
		tx = 0;
		while (tx < TEX_WIDTH)
		{
			txt_arr[TEX_WIDTH * ty + tx]
				= t->pixels[TEX_WIDTH * tx * p + ty * p] << 24
				| t->pixels[TEX_WIDTH * tx * p + ty * p + 1] << 16
				| t->pixels[TEX_WIDTH * tx * p + ty * p + 2] << 8
				| t->pixels[TEX_WIDTH * tx * p + ty * p + 3];
			tx++;
		}
		ty++;
	}
	return (txt_arr);
}

void	ray_direction(t_ray *ray, t_player *player)
{
	if (ray->angle.x < 0)
	{
		ray->step_dir.x = -1;
		ray->side_dist.x
			= (player->pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_dir.x = 1;
		ray->side_dist.x
			= (ray->map_pos.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	}
	if (ray->angle.y < 0)
	{
		ray->step_dir.y = -1;
		ray->side_dist.y
			= (player->pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_dir.y = 1;
		ray->side_dist.y
			= (ray->map_pos.y + 1.0 - player->pos.y) * ray->delta_dist.y;
	}
}

void	ray_length(t_ray *ray)
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
		if (map[ray->map_pos.x][ray->map_pos.y] == '1')
			hit = 1;
	}
	if (!ray->side)
		ray->length = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->length = (ray->side_dist.y - ray->delta_dist.y);
}

void	update_ray(t_ray *ray, t_player *player, double camera)
{
	ray->angle.x = player->viewdir.x + player->plane.x * camera;
	ray->angle.y = player->viewdir.y + player->plane.y * camera;
	ray->delta_dist.x = fabs(1 / ray->angle.x);
	ray->delta_dist.y = fabs(1 / ray->angle.y);
	ray->map_pos.x = (int)player->pos.x;
	ray->map_pos.y = (int)player->pos.y;
}

void	draw_pixel_column(t_mlxinfo *game, int x, t_texture *texture)
{
	int			y;
	double		wall_hit;
	int			start; // remove
	int			end; // remove
	t_ray		ray;
	t_player	player;

	ray = game->ray;
	player = game->player;
	texture->wall_height = (int)(HEIGHT / game->ray.length);
	start = (-texture->wall_height / 2) + (HEIGHT / 2);
	if (start < 0)
		start = 0;
	end = (texture->wall_height / 2) + (HEIGHT / 2);
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	if (ray.side == 0)
		wall_hit = player.pos.y + game->ray.length * ray.angle.y;
	else
		wall_hit = player.pos.x + game->ray.length * ray.angle.x;
	wall_hit -= floor((wall_hit));
	//x coordinate on the texture
	texture->x = wall_hit * (double)TEX_WIDTH;
	if (ray.side == 0 && ray.angle.x > 0)
		texture->x = TEX_WIDTH - texture->x - 1;
	if (ray.side == 1 && ray.angle.y < 0)
		texture->x = TEX_WIDTH - texture->x - 1;
	// How much to increase the texture coordinate per screen pixel
	texture->tex_step = 1.0 * (double)TEX_HEIGHT / texture->wall_height;
	// Starting texture coordinate
	texture->y
		= ((double)start - (double)HEIGHT
			/ 2 + (double)texture->wall_height / 2)
		* texture->tex_step;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < start)
			mlx_put_pixel(game->img, x, y, 0x520575FF);
		else if (y >= start && y < end)
		{
			texture->color
				= texture->pixels[(TEX_HEIGHT * texture->x + (int)texture->y)];
			mlx_put_pixel(game->img, x, y, texture->color);
			texture->y += texture->tex_step;
		}
		else
			mlx_put_pixel(game->img, x, y, 0x32a852FF);
		y++;
	}
}

int	get_texture_side(t_ray *ray)
{
	if (ray->side == 0 && ray->step_dir.x < 0)
		return (0);
	if (ray->side == 0 && ray->step_dir.x > 0)
		return (1);
	if (ray->side == 1 && ray->step_dir.y < 0)
		return (2);
	if (ray->side == 1 && ray->step_dir.y > 0)
		return (3);
	return (0);
}

void	cast_rays(t_mlxinfo *game)
{
	size_t		x;
	double		camera;
	t_player	*player;
	t_ray		*ray;

	x = 0;
	player = &game->player;
	ray = &game->ray;
	while (x < WIDTH)
	{
		camera = 2 * x / (double)WIDTH - 1;
		update_ray(ray, player, camera);
		ray_direction(ray, player);
		ray_length(ray);
		draw_pixel_column(game, x, game->texture[get_texture_side(ray)]);
		x++;
	}
}

void	clear_screen(void *param)
{
	mlx_image_t	*image;
	uint32_t	i;
	uint32_t	y;

	image = param;
	i = 0;
	while (i < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			mlx_put_pixel(image, i, y, 0x000000FF);
			y++;
		}
		i++;
	}
}

void	rot_fov(t_mlxinfo *game, double rot_val)
{
	double		odx;
	double		ody;
	double		rs;
	t_player	p;

	p = game->player;
	rs = (game->time - game->old_time) * rot_val;
	odx = p.viewdir.x;
	p.viewdir.x = p.viewdir.x * cos(rs) - p.viewdir.y * sin(rs);
	p.viewdir.y = odx * sin(rs) + p.viewdir.y * cos(rs);
	ody = p.plane.x;
	p.plane.x = p.plane.x * cos(rs) - p.plane.y * sin(rs);
	p.plane.y = ody * sin(rs) + p.plane.y * cos(rs);
}

void	move_player(t_mlxinfo *game, t_vec axis, double val)
{
	double	move_speed;

	move_speed = (game->time - game->old_time) * val;
	game->player.pos.x += axis.x * move_speed;
	game->player.pos.y += axis.y * move_speed;
}

void	ft_controls(void *g)
{
	t_mlxinfo	*game;

	game = g;
	game->old_time = game->time;
	game->time = mlx_get_time();
	clear_screen(game->img);
	cast_rays(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, game->player.viewdir, 5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, game->player.viewdir, -5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, game->player.plane, 5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, game->player.plane, -5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rot_fov(game, -3.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rot_fov(game, 3.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	init_textures(t_mlxinfo *game)
{
	game->texture = malloc(4 * sizeof(t_texture));
	game->texture[0] = malloc(sizeof(t_texture));
	game->texture[1] = malloc(sizeof(t_texture));
	game->texture[2] = malloc(sizeof(t_texture));
	game->texture[3] = malloc(sizeof(t_texture));
	game->texture[0]->pixels = get_pixel_data("./assets/mc_cave.png"/*game->map.north*/);
	game->texture[1]->pixels = get_pixel_data("./assets/mc_desert.png"/*game->map.south*/);
	game->texture[2]->pixels = get_pixel_data("./assets/mc_house.png"/*game->map.east*/);
	game->texture[3]->pixels = get_pixel_data("./assets/mc_nether.png"/*game->map.west*/);
}

int	main(void)
{
	t_mlxinfo	*game;
	mlx_t		*mlx;

	game = malloc(sizeof(t_mlxinfo));
	init_game(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx = game->mlx;
	game->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	init_player(&game->player);
	init_ray(&game->ray);
	init_textures(game);
	mlx_image_to_window(mlx, game->img, 0, 0);
	mlx_loop_hook(mlx, ft_controls, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	system("leaks cub3d");
	return (0);
}
