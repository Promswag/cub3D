/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:39:46 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/19 13:08:44 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.map.col * TILE_SIZE, \
	data.map.row * TILE_SIZE, "so_long");
	if (sl_img_loader(&data))
	{
		ft_putstr_fd("Error\nMissing tile images.\n");
		sl_close(&data);
	}
	sl_draw(&data);
	mlx_key_hook(data.win, sl_key_hook, &data);
	mlx_hook(data.win, 17, 0, sl_close, &data);
	mlx_loop(data.mlx);
}
