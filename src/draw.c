/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:26:18 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/16 15:00:53 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel_door(t_game *game, int x, t_tinfo ti, t_ray ray)
{
	t_doordata	z;
	int			i;
	float		o;

	z = setup_door(game, ti);
	i = -1;
	while (++i < ti.h)
	{
		z.j = (i + z.o) / z.r;
		if (z.j > 3)
			z.j = 3;
		o = ti.x;
		if (z.j == (ray.door->frame >> 3))
			o = ti.x + ((double)ray.t->width / 64 * \
			(ray.door->frame - 8 * z.j) * 4) * z.t;
		else if (z.j < (ray.door->frame >> 3))
			o = -1;
		if ((z.t == 1 && o >= 0 && o < ray.t->width >> 1) || \
		(z.t == -1 && o >= ray.t->width >> 1 && \
		o < ray.t->width))
			mlx_put_pixel(game->window, x, ti.o + i, \
			get_color(o, ti.y, ray.t));
		ti.y += ti.r;
	}
}

void	draw_stripe_door(t_game *game, int x, float angle, t_ray ray)
{
	t_tinfo	t;
	int		offset;

	if (ray.distance != 1e9)
	{
		ray.distance *= cos(adjust_angle(game->player.angle - angle));
		t.h = (1.0 * TILE_SIZE * DISPLAY_WIDTH * 60 / FOV) / ray.distance;
		t.dh = t.h;
		t.r = 1.0 * ray.t->height / t.h;
		offset = 0;
		if (t.h > DISPLAY_HEIGHT)
		{
			offset = (t.h - DISPLAY_HEIGHT) >> 1;
			t.h = DISPLAY_HEIGHT;
		}
		t.o = (DISPLAY_HEIGHT - t.h) >> 1;
		t.y = offset * t.r;
		t.x = (int)(ray.r.x * ray.t->width / TILE_SIZE) \
			% ray.t->width;
		draw_pixel_door(game, x, t, ray);
	}
}

static void	draw_pixel(t_game *game, int x, t_tinfo ti, t_ray ray)
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
		mlx_put_pixel(game->window, x, ti.o + i, get_color(ti.x, ti.y, ray.t));
		ti.y += ti.r;
	}
}

void	draw_stripe(t_game *game, int x, float angle, t_ray ray)
{
	t_tinfo	t;
	int		offset;

	ray.distance *= cos(adjust_angle(game->player.angle - angle));
	t.h = (1.0 * TILE_SIZE * DISPLAY_WIDTH * 60 / FOV) / ray.distance;
	t.r = 1.0 * ray.t->height / t.h;
	offset = 0;
	if (t.h > DISPLAY_HEIGHT)
	{
		offset = (t.h - DISPLAY_HEIGHT) >> 1;
		t.h = DISPLAY_HEIGHT;
	}
	t.o = (DISPLAY_HEIGHT - t.h) >> 1;
	t.y = offset * t.r;
	t.x = (int)(ray.r.x * ray.t->width / TILE_SIZE) \
		% ray.t->width;
	draw_pixel(game, x, t, ray);
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
