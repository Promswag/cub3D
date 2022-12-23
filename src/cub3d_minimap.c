/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:43:24 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/23 13:15:38 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub3d_draw_minimap(t_game *game)
{
	t_point		player_index;
	mlx_image_t	*img;
	int			i;
	int			j;

	player_index.x = game->player.coord.x / 64 - 4;
	player_index.y = game->player.coord.y / 64 - 4;
	img = mlx_new_image(game->mlx, 10, 10);
	i = -1;
	while (++i < 9)
	{
		j = -1;
		while (++j < 9)
		{
			if ()
			mlx_image_to_window(game->mlx, img, 10 * j, 10 * i);
		}
	}
}
