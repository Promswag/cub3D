/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:11:37 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/05 14:46:14 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_handler(mlx_key_data_t k, void *param)
{
	t_game	*game;

	game = param;
	if (k.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (k.key == MLX_KEY_SPACE)
		mlx_close_window(game->mlx);
	if (k.action == MLX_PRESS || k.action == MLX_RELEASE)
	{
		if (k.key == MLX_KEY_W || k.key == MLX_KEY_UP)
			game->keys.w ^= 1;
		if (k.key == MLX_KEY_S || k.key == MLX_KEY_DOWN)
			game->keys.s ^= 1;
		if (k.key == MLX_KEY_A)
			game->keys.a ^= 1;
		if (k.key == MLX_KEY_D)
			game->keys.d ^= 1;
		if (k.key == MLX_KEY_Q || k.key == MLX_KEY_LEFT)
			game->keys.q ^= 1;
		if (k.key == MLX_KEY_E || k.key == MLX_KEY_RIGHT)
			game->keys.e ^= 1;
	}
}
