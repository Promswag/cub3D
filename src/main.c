/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/19 14:46:49 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;

	sl_game_init(&data);
	if (sl_args_handler(argc, argv))
		return (-1);
	if (sl_map_handler(argv[1], &data))
	{
		sl_map_free(&data);
		return (-1);
	}
	data.mlx = mlx_init(data.map.col * TILE_SIZE, data.map.row * TILE_SIZE, "so_long", true);
	if (sl_img_loader(&data))
	{
		ft_putstr_fd("Error\nMissing tile images.\n", 2);
		sl_close(&data);
	}
	sl_draw(&data);
	mlx_key_hook(data.mlx, &sl_key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
