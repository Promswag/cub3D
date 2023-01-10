/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:26:18 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/10 17:00:49 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_pixel_door(t_game *game, int x, t_texture_info ti, t_doorlst *d)
{
	int		i;
	int		j;
	float	o;
	float	t;

	i = -1;
	j = -1;
	t = -1;
	if (ti.x < game->textures[4]->width / 2)
		t = 1;
	while (++i < ti.h)
	{
		if (i % ((int)ti.h / 4) == 0 && j < 3)
			j++;
		o = ti.x;
		if (j == (d->frame / 8))
			o = ti.x + (game->textures[4]->width / 64 * (d->frame - 8 * j) * 4) * t;
		else if (j < (d->frame / 8))
			o = -1;
		if ((t == 1 && o >= 0 && o < game->textures[4]->width / 2) || (t == -1 \
		&& o >= game->textures[4]->width / 2 && o < game->textures[4]->width))
			mlx_put_pixel(game->window, x, ti.o + i, \
			get_color(o, ti.y, game->textures[4]));
		ti.y += ti.r;
	}
}

void	draw_stripe_door(t_game *game, int x, float angle, t_ray ray)
{
	t_texture_info	t;
	int				offset;

	if (ray.distance != 1e9)
	{
		ray.distance *= cos(adjust_angle(game->player.angle - angle));
		t.h = (1.0 * TILE_SIZE * DISPLAY_WIDTH * 60 / FOV) / ray.distance;
		t.r = 1.0 * game->textures[4]->height / t.h;
		offset = 0;
		if (t.h > DISPLAY_HEIGHT)
		{
			offset = (t.h - DISPLAY_HEIGHT) >> 1;
			t.h = DISPLAY_HEIGHT;
		}
		t.o = (DISPLAY_HEIGHT - t.h) >> 1;
		t.y = offset * t.r;
		t.x = (int)(ray.r.x * game->textures[4]->width / TILE_SIZE) \
			% game->textures[4]->width;
		draw_pixel_door(game, x, t, ray.door);
	}
}

void	draw_pixel(t_game *game, int x, t_texture_info ti, t_texture *t)
{
	int		i;

	i = -1;
	while (++i < ti.o)
		mlx_put_pixel(game->window, x, i, game->map.ceiling);
	i = ti.h + ti.o - 1;
	while (++i < DISPLAY_HEIGHT)
		mlx_put_pixel(game->window, x, i, game->map.floor);
	i = -1;
	while (++i < ti.h)
	{
		mlx_put_pixel(game->window, x, ti.o + i, get_color(ti.x, ti.y, t));
		ti.y += ti.r;
	}
}

void	draw_stripe(t_game *game, int x, float angle, t_ray ray)
{
	t_texture_info	t;
	int				offset;

	ray.distance *= cos(adjust_angle(game->player.angle - angle));
	t.h = (1.0 * TILE_SIZE * DISPLAY_WIDTH * 60 / FOV) / ray.distance;
	t.r = 1.0 * game->textures[ray.direction]->height / t.h;
	offset = 0;
	if (t.h > DISPLAY_HEIGHT)
	{
		offset = (t.h - DISPLAY_HEIGHT) >> 1;
		t.h = DISPLAY_HEIGHT;
	}
	t.o = (DISPLAY_HEIGHT - t.h) >> 1;
	t.y = offset * t.r;
	t.x = (int)(ray.r.x * game->textures[ray.direction]->width / TILE_SIZE) \
		% game->textures[ray.direction]->width;
	draw_pixel(game, x, t, game->textures[ray.direction]);
}

void	draw(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	movements_handler(game);
	mlx_delete_image(game->mlx, game->window);
	game->window = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	raycaster(game);
	if (game->bonus)
	{
		draw_minimap(game);
		door_update(game);
	}
	mlx_image_to_window(game->mlx, game->window, 0, 0);
}
