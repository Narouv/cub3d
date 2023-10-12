/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:58:05 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/12 04:35:33 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

char map[MAP_WIDTH][MAP_HEIGHT] = {
  {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','1','1','1','1','1','0','0','0','0','1','0','1','0','1','0','0','0','1'},
  {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','1','0','0','0','1','0','0','0','1'},
  {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','1','1','0','1','1','0','0','0','0','1','0','1','0','1','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','0','0','0','0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','0','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
};

void put_square(mlx_image_t *img, int x, int y, int color)
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

void init_player(t_player *player)
{
	player->pos.x = 5;
	player->pos.y = 5;
	player->viewdir.x = -1;
	player->viewdir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0.66;
}

void	ray_init(t_ray *ray)
{
	ray->angle.x = 1337;
	ray->angle.y = 42069;
	ray->delta_dist.x = 1337;
	ray->delta_dist.y = 1337;
	ray->map_pos.x = 0;
	ray->map_pos.y = 0;
	ray->side = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
}

void init_game(t_mlxinfo *game)
{
	game->time = 0;
	game->str_update_time = 0;
	game->old_time = 0;
}

void	fps_cntr(void *g) // string on screen very blurry therefor bad
{
	t_mlxinfo	*game;
	char *fps; // fps char
	int i; // fps int

	game = g;
	if (game->time - game->str_update_time > 0.5)
	{
		game->str_update_time = game->time;
		i = 1 / (game->time - game->old_time);
		fps = ft_itoa(i);
		mlx_put_string(game->mlx, fps, 10, 10);
		free(fps);
	}
}

// only works for square textures (same width and height)
int	*get_pixel_data(char *img_path)
{
	int	*txt_arr;
	uint8_t	p;
	size_t s;
	mlx_texture_t *t = mlx_load_png(img_path);

	if (!t)
		exit(1);
	p = t->bytes_per_pixel;
	s = TEX_WIDTH;
	txt_arr = malloc(sizeof(int) * s * s);
	for (size_t ty = 0; ty < s; ty++)
		for (size_t tx = 0; tx < s; tx++)	
			txt_arr[s * ty + tx] = t->pixels[s * tx * p + ty * p] << 24 |
							t->pixels[s * tx * p + ty * p + 1] << 16 |
							t->pixels[s * tx * p + ty * p + 2] << 8 |
							t->pixels[s * tx * p + ty * p + 3];
	return (txt_arr);
}

void	ray_direction(t_ray *ray, t_player *player)
{
	if (ray->angle.x < 0)
	{
		ray->step_dir.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_dir.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	}
	if (ray->angle.y < 0)
	{
		ray->step_dir.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_dir.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - player->pos.y) * ray->delta_dist.y;
	}
}

double	ray_length(t_ray *ray)
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
		if (map[(int)ray->map_pos.x][(int)ray->map_pos.y] == '1')
			hit = 1;
	}
	if (!ray->side)
		return (ray->side_dist.x - ray->delta_dist.x);
	return (ray->side_dist.y - ray->delta_dist.y);
}

void	init_ray(t_ray *ray, t_player *player, double camera)
{
	ray->angle.x = player->viewdir.x + player->plane.x * camera;
	ray->angle.y = player->viewdir.y + player->plane.y * camera;
	// ray travel from x side to next x side and same for y
	if (ray->angle.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1 / ray->angle.x);
	if (ray->angle.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->angle.y);
	// which map tile player is in
	ray->map_pos.x = (int)player->pos.x;
	ray->map_pos.y = (int)player->pos.y;
}

void	draw_pixel_column(t_mlxinfo *game, int x, double wall_dist, int *texture)
{
	int	y;
	double	wall_hit;
	int	wall_height;
	int	start;
	int	end;

	t_ray ray = game->ray;
	t_player player = game->player;
	
	wall_height = (int)(HEIGHT / wall_dist);
	start = (-wall_height / 2) + (HEIGHT / 2);
	if(start < 0)
		start = 0;
	end = (wall_height / 2) + (HEIGHT / 2);
	if(end >= HEIGHT)
		end = HEIGHT - 1;

	if (ray.side == 0)
		wall_hit = player.pos.y + wall_dist * ray.angle.y;
	else
		wall_hit = player.pos.x + wall_dist * ray.angle.x;
	wall_hit -= floor((wall_hit));

	//x coordinate on the texture
	ray.texture.wall_pos.x = wall_hit * (double)TEX_WIDTH;
	if(ray.side == 0 && ray.angle.x > 0)
		ray.texture.wall_pos.x = TEX_WIDTH - ray.texture.wall_pos.x - 1;
	if(ray.side == 1 && ray.angle.y < 0)
		ray.texture.wall_pos.x = TEX_WIDTH - ray.texture.wall_pos.x - 1;
	// How much to increase the texture coordinate per screen pixel
	ray.texture.tex_step = 1.0 * (double)TEX_HEIGHT / wall_height;
	// Starting texture coordinate
	ray.texture.wall_pos.y = ((double)start - (double)HEIGHT / 2 + (double)wall_height / 2) * ray.texture.tex_step;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < start)
			mlx_put_pixel(game->img, x, y, 0x520575FF);
		else if (y >= start && y < end)
		{
			ray.texture.color = texture[(TEX_HEIGHT * (int)ray.texture.wall_pos.x + (int)ray.texture.wall_pos.y)];
			mlx_put_pixel(game->img, x, y, ray.texture.color);
			ray.texture.wall_pos.y += ray.texture.tex_step;
		}
		else
			mlx_put_pixel(game->img, x, y, 0x32a852FF);
		y++;
	}
}

void	lazertag(t_mlxinfo *game)
{
	size_t x;
	double camera;
	t_player	player;
	t_ray		ray;
	
	// mlx_image_t *img = game->img;
	// double perp_wall_dist;

	x = 0;
	player = game->player;
	ray = game->ray;
	int *txt_arr[1];
	txt_arr[0] = get_pixel_data("cat.png");
	while (x < WIDTH)
	{
		camera = ((2 * x) / (double)WIDTH) - 1;
		init_ray(&ray, &player, camera);
		//decide ray step direction
		ray_direction(&ray, &player);
		//dda
		// perp_wall_dist = ray_length(&ray);
		draw_pixel_column(game, x, ray_length(&ray), txt_arr[0]);
		// determine wall height
		// int lineHeight = (int)(HEIGHT / perp_wall_dist);
		// int start = (-lineHeight / 2) + (HEIGHT / 2);
		// if(start < 0)
		// 	start = 0;
		// int end = (lineHeight / 2) + (HEIGHT / 2);
		// if(end >= HEIGHT)
		// 	end = HEIGHT - 1;
		// // choose color/texture
		// //texturing calculations
		// // int texNum = 0; //usually supposed to indicate which texture to use, i only use 1 atm so initialze to 0

		// //calculate value of wallX
		// double wallX; //where exactly the wall was hit
		// if (ray.side == 0) wallX = player.pos.y + perp_wall_dist * ray.angle.y;
		// else           wallX = player.pos.x + perp_wall_dist * ray.angle.x;
		// wallX -= floor((wallX));

		// //x coordinate on the texture
		// int texX = wallX * (double)TEX_WIDTH;
		// if(ray.side == 0 && ray.angle.x > 0)
		// 	texX = TEX_WIDTH - texX - 1;
		// if(ray.side == 1 && ray.angle.y < 0)
		// 	texX = TEX_WIDTH - texX - 1;
		// // How much to increase the texture coordinate per screen pixel
		// double txt_step = 1.0 * (double)TEX_HEIGHT / lineHeight;
		// // Starting texture coordinate
		// double texPos = ((double)start - (double)HEIGHT / 2 + (double)lineHeight / 2) * txt_step;
		// for(int y = 0; y < HEIGHT; y++)
		// {
		// 	if (y < start)
		// 		mlx_put_pixel(img, x, y, 0x520575FF);
		// 	else if (y >= start && y < end)
		// 	{
		// 		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		// 		int texY = (int)texPos & (TEX_HEIGHT - 1);
		// 		texPos += txt_step;
		// 		int color = txt_arr[0][TEX_HEIGHT * texX + texY];
		// 		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// 		// if(side == 1) color = (color >> 1) & 8355711;
		// 		mlx_put_pixel(img, x, y, color);
		// 	}
		// 	else
		// 		mlx_put_pixel(img, x, y, 0x32a852FF);
		// }
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

void	ft_controls(void* g)
{
	t_mlxinfo	*game;

	game = g;
	game->old_time = game->time;
	game->time = mlx_get_time();
	clear_screen(game->img);
	lazertag(game);
	
	double frame_time = (game->time - game->old_time);
	double moveSpeed = frame_time * 5.0;
	double rotSpeed = frame_time * 3.0; 
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.pos.x += game->player.viewdir.x * moveSpeed;
		game->player.pos.y += game->player.viewdir.y * moveSpeed;
	}
	//move backwards
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.pos.x -= game->player.viewdir.x * moveSpeed;
		game->player.pos.y -= game->player.viewdir.y * moveSpeed;
	}
	//rotate to the right
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
	  double oldDirX = game->player.viewdir.x;
	  game->player.viewdir.x = game->player.viewdir.x * cos(-rotSpeed) - game->player.viewdir.y * sin(-rotSpeed);
	  game->player.viewdir.y = oldDirX * sin(-rotSpeed) + game->player.viewdir.y * cos(-rotSpeed);
	  double oldPlaneX = game->player.plane.x;
	  game->player.plane.x = game->player.plane.x * cos(-rotSpeed) - game->player.plane.y * sin(-rotSpeed);
	  game->player.plane.y = oldPlaneX * sin(-rotSpeed) + game->player.plane.y * cos(-rotSpeed);
	}
	//rotate to the left
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
	  double oldDirX = game->player.viewdir.x;
	  game->player.viewdir.x = game->player.viewdir.x * cos(rotSpeed) - game->player.viewdir.y * sin(rotSpeed);
	  game->player.viewdir.y = oldDirX * sin(rotSpeed) + game->player.viewdir.y * cos(rotSpeed);
	  double oldPlaneX = game->player.plane.x;
	  game->player.plane.x = game->player.plane.x * cos(rotSpeed) - game->player.plane.y * sin(rotSpeed);
	  game->player.plane.y = oldPlaneX * sin(rotSpeed) + game->player.plane.y * cos(rotSpeed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}



int	main()
{
	t_mlxinfo *game;
	mlx_t *mlx;
	
	game = malloc(sizeof(t_mlxinfo));
	init_game(game);
	init_player(&game->player);
	ray_init(&game->ray);
	
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx = game->mlx;
	game->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	
	// mlx_texture_t *txt = mlx_load_png("pic.png");
	
	// for (size_t i = 0; i < (225 * 225) * 4; i+=4)
	// {
	// 	printf("%zu ", i);
	// 	printf("%X", txt->pixels[i]);
	// 	printf("%X", txt->pixels[i + 1]);
	// 	printf("%X", txt->pixels[i + 2]);
	// 	printf("%X", txt->pixels[i + 3]);
	// 	printf("\n");
	// }

	lazertag(game);
	minimap(game->img);
	mlx_image_to_window(mlx, game->img, 0, 0);
	mlx_loop_hook(mlx, ft_controls, game);
	// mlx_loop_hook(mlx, fps_cntr, game);
	mlx_loop(mlx);
	

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

