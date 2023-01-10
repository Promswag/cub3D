/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:43:24 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/09 15:36:36 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

int	adjust_yx(float a, int b)
{
	int	r;

	r = a - 5 * TILE_SIZE + b * 2;
	if (r < 0)
		r -= TILE_SIZE;
	r /= TILE_SIZE;
	return (r);
}

void	draw_blocs(t_game *game)
{
	int		x;
	int		y;
	int		i;
	int		j;

	i = -1;
	while (++i < 320)
	{
		y = adjust_yx(game->player.coord.y, i);
		j = -1;
		while (++j < 320)
		{
			x = adjust_yx(game->player.coord.x, j);
			if (x >= 0 && x < game->map.col && y >= 0 && y < game->map.row)
			{
				if (game->map.map[y][x] == '0')
					mlx_put_pixel(game->window, j + 2, i + 2, 0xB0B0B0FF);
				else if (game->map.map[y][x] == 0)
					mlx_put_pixel(game->window, j + 2, i + 2, 0x333333FF);
				else
					mlx_put_pixel(game->window, j + 2, i + 2, 0x777777FF);
			}
			else
				mlx_put_pixel(game->window, j + 2, i + 2, 0x333333FF);
		}
	}
}

void	draw_boundaries(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 324)
	{
		x = -1;
		while (++x < 324)
		{
			if (y == 0 || y == 1 || y == 323 || y == 322)
				mlx_put_pixel(game->window, x, y, 0x000000FF);
			if (x == 0 || x == 1 || x == 323 || x == 322)
				mlx_put_pixel(game->window, x, y, 0x000000FF);
		}
	}
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		y;

	draw_boundaries(game);
	draw_blocs(game);
	x = 162;
	y = 162;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			mlx_put_pixel(game->window, x + j - 5, y + i - 5, 0xFFFFFFFF);
	}
	i = -1;
	while (++i < 15)
		mlx_put_pixel(game->window, x + cos(game->player.angle) * i, \
			y + sin(game->player.angle) * i, 0xFFFFFFFF);
}
