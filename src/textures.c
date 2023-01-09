/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:53:33 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/09 12:09:42 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_texture_pixels(t_texture *texture, mlx_texture_t *t)
{
	unsigned int	*h;
	unsigned int	*w;
	unsigned int	b;

	b = t->bytes_per_pixel;
	texture->pixels = 0;
	texture->pixels = malloc(sizeof(unsigned int) * (t->height * t->width));
	if (!texture->pixels)
		return (1);
	h = &texture->height;
	w = &texture->width;
	*h = -1;
	while (++*h < t->height)
	{
		*w = -1;
		while (++*w < t->width)
			texture->pixels[*h * t->width + *w] = \
				t->pixels[((*h * t->width) + *w) * b + 0] << 24 | \
				t->pixels[((*h * t->width) + *w) * b + 1] << 16 | \
				t->pixels[((*h * t->width) + *w) * b + 2] << 8 | \
				t->pixels[((*h * t->width) + *w) * b + 3];
	}
	mlx_delete_texture(t);
	return (0);
}

int	load_texture_placeholder(t_texture *texture)
{
	texture->height = 1;
	texture->width = 1;
	texture->pixels = malloc(sizeof(unsigned int));
	if (!texture->pixels)
		return (1);
	*texture->pixels = 0x666666FF;
	return (0);
}

int	load_textures(t_game *game, char **path)
{
	int				i;
	mlx_texture_t	*texture;

	game->textures = malloc(sizeof(t_texture *) * 5);
	if (!game->textures)
		return (1);
	i = -1;
	while (++i < 5)
	{
		game->textures[i] = malloc(sizeof(t_texture));
		if (!game->textures[i])
			return (1);
		texture = mlx_load_png(path[i]);
		if (texture)
		{
			if (load_texture_pixels(game->textures[i], texture))
				return (1);
		}
		else
		{
			if (load_texture_placeholder(game->textures[i]))
				return (1);
		}
	}
	return (0);
}
