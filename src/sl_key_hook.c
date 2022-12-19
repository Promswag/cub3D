/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_key_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:11 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/19 14:44:17 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_movement_handler(int x, int y, t_data *data);
void	sl_map_update(int x, int y, t_data *data);

void	sl_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		sl_close(data);
	if (data->gameover == 0)
	{
		if (keydata.key == MLX_KEY_W)
			sl_movement_handler(0, -1, data);
		if (keydata.key == MLX_KEY_S)
			sl_movement_handler(0, 1, data);
		if (keydata.key == MLX_KEY_A)
			sl_movement_handler(-1, 0, data);
		if (keydata.key == MLX_KEY_D)
			sl_movement_handler(1, 0, data);
	}
	sl_draw(data);
}

void	sl_movement_handler(int x, int y, t_data *data)
{
	char	target;

	target = data->map.map[data->player_pos.y + y][data->player_pos.x + x];
	if (target == 'C')
		data->map.item_c--;
	if (target == 'C' || target == 'E' || target == '0')
	{
		data->moves++;
		sl_map_update(x, y, data);
	}
	if (target == 'E' && data->map.item_c == 0)
		data->gameover = 1;
	if (target == 'E')
	{
		data->tmp_exit++;
		data->tmp_exit_pos.x = data->player_pos.x;
		data->tmp_exit_pos.y = data->player_pos.y;
	}
}

void	sl_map_update(int x, int y, t_data *data)
{
	data->map.map[data->player_pos.y][data->player_pos.x] = '0';
	data->map.map[data->player_pos.y + y][data->player_pos.x + x] = 'P';
	data->player_pos.y += y;
	data->player_pos.x += x;
	if (data->tmp_exit)
	{
		if (data->player_pos.x != data->tmp_exit_pos.x
			|| data->player_pos.y != data->tmp_exit_pos.y)
		{
			data->map.map[data->tmp_exit_pos.y][data->tmp_exit_pos.x] = 'E';
			data->tmp_exit--;
		}
	}
}
