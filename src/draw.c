/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:26:18 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/06 15:48:12 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	get_color(int x, int y, t_texture *t)
{
	return (t->pixels[y * t->width + x]);
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
		draw_minimap(game);
	mlx_image_to_window(game->mlx, game->window, 0, 0);
}
