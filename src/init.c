/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:51:14 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 19:18:34 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_player *player)
{
	player->viewdir.x = 0;
	player->viewdir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (player->stand == 'W')
	{
		player->viewdir.x = -1;
		player->plane.y = 0.66;
	}
	else if (player->stand == 'S')
	{
		player->viewdir.y = 1;
		player->plane.x = 0.66;
	}
	else if (player->stand == 'E')
	{
		player->viewdir.x = 1;
		player->plane.y = -0.66;
	}
	else
	{
		player->viewdir.y = -1;
		player->plane.x = -0.66;
	}
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
	game->map = ft_calloc(1, sizeof(t_map));
}

void	init_textures(t_mlxinfo *game)
{
	game->texture = malloc(4 * sizeof(t_texture));
	game->texture[0].pixels = get_pixel_data(game->map->tex[0]);
	game->texture[1].pixels = get_pixel_data(game->map->tex[1]);
	game->texture[2].pixels = get_pixel_data(game->map->tex[3]);
	game->texture[3].pixels = get_pixel_data(game->map->tex[2]);
}

// void	cleanup(t_mlxinfo *game)
// {
// 	free(&game);
// }

void	init_map(t_map *map, t_player *player)
{
	map->player = player;
	map->tex_count = 0;
	map->p_count = 0;
	map->line_count = 0;
	map->col_count = 0;
	map->f_col = 0;
	map->c_col = 0;
	map->tex = ft_calloc(4, sizeof(char *));
}
