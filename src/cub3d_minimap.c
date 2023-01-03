/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:43:24 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/02 11:15:59 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub3d_draw_bloc(t_game *game, int y, int x)
{
	int	i;
	int	j;
	int	posy;
	int	posx;

	i = 0;
	while (++i < TILE_SIZE - 1)
	{
		j = 0;
		while (++j < TILE_SIZE - 1)
		{
			posy = y * TILE_SIZE + i;
			posx = x * TILE_SIZE + j;
			if (posy >= 0 && posy < DISPLAY_HEIGHT
				&& posx >= 0 && posx < DISPLAY_WIDTH)
			{
				if (game->map.map[y][x] == '1')	
					mlx_put_pixel(game->window, posx, posy, 0xFFFFFFFF);
			}
		}
	}
}

void	cub3d_draw_minimap(t_game *game)
{
	t_point		player_index;
	// mlx_image_t	*img;
	int			i;
	int			j;

	player_index.x = game->player.coord.x / 64 - 4;
	player_index.y = game->player.coord.y / 64 - 4;
	// img = mlx_new_image(game->mlx, 10, 10);
	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
			cub3d_draw_bloc(game, i, j);
	}
	// while (++i < 9)
	// {
	// 	j = -1;
	// 	while (++j < 9)
	// 	{
	// 		mlx_image_to_window(game->mlx, img, 10 * j, 10 * i);
	// 	}
	// }
}
