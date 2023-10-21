/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:45:51 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 18:27:47 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// only works for square textures (same width and height)
int	*get_pixel_data(char *img_path)
{
	int				*txt_arr;
	uint8_t			p;
	t_veci			i;
	mlx_texture_t	*t;

	t = mlx_load_png(img_path);
	p = t->bytes_per_pixel;
	i.y = 0;
	txt_arr = malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
	while (i.y < TEX_WIDTH)
	{
		i.x = 0;
		while (i.x < TEX_WIDTH)
		{
			txt_arr[TEX_WIDTH * i.y + i.x]
				= t->pixels[TEX_WIDTH * i.x * p + i.y * p] << 24
				| t->pixels[TEX_WIDTH * i.x * p + i.y * p + 1] << 16
				| t->pixels[TEX_WIDTH * i.x * p + i.y * p + 2] << 8
				| t->pixels[TEX_WIDTH * i.x * p + i.y * p + 3];
			i.x++;
		}
		i.y++;
	}
	mlx_delete_texture(t);
	return (txt_arr);
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
