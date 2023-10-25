/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:59:35 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/25 02:17:16 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	update_ray(t_ray *ray, t_player *player, double camera)
{
	ray->angle.x = player->viewdir.x + player->plane.x * camera;
	ray->angle.y = player->viewdir.y + player->plane.y * camera;
	ray->delta_dist.x = fabs(1 / ray->angle.x);
	if (ray->angle.x == 0)
		ray->delta_dist.x = INFINITY;
	ray->delta_dist.y = fabs(1 / ray->angle.y);
	if (ray->angle.y == 0)
		ray->delta_dist.y = INFINITY;
	ray->map_pos.x = (int)player->pos.x;
	ray->map_pos.y = (int)player->pos.y;
}

void	ray_length(t_ray *ray, t_map *map)
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
		if (map->dir[ray->map_pos.x][ray->map_pos.y] == '1')
			hit = 1;
	}
	if (!ray->side)
		ray->length = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->length = (ray->side_dist.y - ray->delta_dist.y);
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
		ray_length(ray, game->map);
		calc_pixel_column(game, x, &game->texture[get_texture_side(ray)]);
		x++;
	}
}
