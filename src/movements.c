/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:43:47 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/11 11:21:38 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

static void	mouse_handler(t_game *game)
{
	int	x;
	int	y;
	int	d;

	d = DISPLAY_WIDTH >> 1;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x != d)
	{
		if (x > d)
			game->player.angle = adjust_angle(\
				game->player.angle + 2 * PI / 360);
		if (x < d)
			game->player.angle = adjust_angle(\
				game->player.angle - 2 * PI / 360);
		mlx_set_mouse_pos(game->mlx, d, DISPLAY_HEIGHT >> 1);
	}
}

static t_point	move_point(t_game *game, float angle, float step)
{
	t_point	p;
	int		x;
	int		y;

	p.x = game->player.coord.x + cos(game->player.angle + angle) * step;
	p.y = game->player.coord.y + sin(game->player.angle + angle) * step;
	x = p.x / TILE_SIZE;
	y = p.y / TILE_SIZE;
	if (x >= 0 && x < game->map.col && y >= 0 && y < game->map.row)
	{
		if (game->map.map[y][x] == '1' || \
			(game->map.map[\
				(int)(game->player.coord.y / TILE_SIZE)][x] == '1' \
			&& game->map.map[y][\
				(int)(game->player.coord.x / TILE_SIZE)] == '1'))
			p = game->player.coord;
		if (game->map.map[y][x] == 'D' || \
			(game->map.map[\
				(int)(game->player.coord.y / TILE_SIZE)][x] == 'D' \
			&& game->map.map[y][\
				(int)(game->player.coord.x / TILE_SIZE)] == 'D'))
			p = game->player.coord;
	}
	return (p);
}

void	movements_handler(t_game *game)
{
	if (game->keys.w)
		game->player.coord = move_point(game, 0, 5);
	if (game->keys.s)
		game->player.coord = move_point(game, PI, 5);
	if (game->keys.a)
		game->player.coord = move_point(game, -(PI / 2), 5);
	if (game->keys.d)
		game->player.coord = move_point(game, PI / 2, 5);
	if (game->keys.q)
		game->player.angle = adjust_angle(game->player.angle - 2 * PI / 72);
	if (game->keys.e)
		game->player.angle = adjust_angle(game->player.angle + 2 * PI / 72);
	if (game->bonus)
		mouse_handler(game);
}
