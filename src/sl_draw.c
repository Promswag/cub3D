/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:03:34 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/19 14:39:36 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		sl_img_loader(t_data *data);
void	sl_draw(t_data *data);
void	sl_draw_tile(char c, int x, int y, t_data *data);

void	sl_draw(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	if (data->gameover == 0)
	{
		while (++i < data->map.row)
		{
			j = -1;
			while (++j < data->map.col)
				sl_draw_tile(data->map.map[i][j], j, i, data);
		}
	}
}

void	sl_draw_tile(char c, int x, int y, t_data *data)
{
	if (c == '1')
		mlx_image_to_window(\
		data->mlx, data->wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == '0')
		mlx_image_to_window(\
		data->mlx, data->bg, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'C')
		mlx_image_to_window(\
		data->mlx, data->item, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'E')
		mlx_image_to_window(\
		data->mlx, data->exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'P')
		mlx_image_to_window(\
		data->mlx, data->player, x * TILE_SIZE, y * TILE_SIZE);
}

int	sl_img_loader(t_data *data)
{
	data->bg = mlx_texture_to_image(data->mlx, mlx_load_png("img/background.png"));
	data->wall = mlx_texture_to_image(data->mlx, mlx_load_png("img/wall.png"));
	data->item = mlx_texture_to_image(data->mlx, mlx_load_png("img/collectible.png"));
	data->exit = mlx_texture_to_image(data->mlx, mlx_load_png("img/exit.png"));
	data->player = mlx_texture_to_image(data->mlx, mlx_load_png("img/player.png"));
	if (!data->bg || !data->wall || !data->item || !data->exit || !data->player)
		return (-1);
	return (0);
}
