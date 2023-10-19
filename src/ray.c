/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:59:35 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/19 21:27:45 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	update_ray(t_ray *ray, t_player *player, double camera)
{
	ray->angle.x = player->viewdir.x + player->plane.x * camera;
	ray->angle.y = player->viewdir.y + player->plane.y * camera;
	ray->delta_dist.x = fabs(1 / ray->angle.x);
	ray->delta_dist.y = fabs(1 / ray->angle.y);
	ray->map_pos.x = (int)player->pos.x;
	ray->map_pos.y = (int)player->pos.y;
}

void	ray_length(t_ray *ray, t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->map_pos.x >= map->width || ray->map_pos.y >= map->height)
			hit = 1;
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
		// put protection for outide of map
		if (map->dir[ray->map_pos.y][ray->map_pos.x] == '1')
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
