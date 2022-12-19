/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:43:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/19 14:43:55 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <stdio.h>

int	sl_map_handler(char *path, t_data *data);
int	sl_map_reader(char *path, t_data *data);
int	sl_map_shape_checker(t_data *data);
int	sl_map_enclosure_checker(t_data *data);
int	sl_map_char_checker(t_data *data);

int	sl_map_handler(char *path, t_data *data)
{
	if (sl_map_reader(path, data))
		return (sl_error_handler(10));
	if (sl_map_shape_checker(data))
		return (sl_error_handler(11));
	if (sl_map_enclosure_checker(data))
		return (sl_error_handler(12));
	if (sl_map_char_checker(data))
		return (sl_error_handler(13));
	if (data->map.item_p != 1)
		return (sl_error_handler(14));
	if (data->map.item_c == 0)
		return (sl_error_handler(15));
	if (data->map.item_e == 0)
		return (sl_error_handler(16));
	if (sl_path_check(data) == 0)
		return (sl_error_handler(17));
	return (0);
}

int	sl_map_reader(char *path, t_data *data)
{
	int		file;
	char	*read;
	char	*map;

	file = open(path, O_RDONLY);
	if (file >= 0)
	{
		map = malloc(sizeof(char) * 1);
		map[0] = '\0';
		read = get_next_line(file);
		while (read)
		{
			map = sl_strjoin(map, read);
			data->map.row++;
			read = get_next_line(file);
		}
		data->map.map = ft_split(map, '\n');
		free(map);
		free(read);
		if ((data->map.map[0]))
			data->map.col = ft_strlen(data->map.map[0]);
		return (0);
	}
	return (1);
}

int	sl_map_shape_checker(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->map.row)
		if (data->map.col != (int)ft_strlen(data->map.map[i]))
			return (1);
	return (0);
}

int	sl_map_enclosure_checker(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->map.col)
		if (data->map.map[0][i] != '1' ||
				data->map.map[data->map.row - 1][i] != '1')
			return (1);
	i = -1;
	while (++i < data->map.row)
		if (data->map.map[i][0] != '1' ||
				data->map.map[i][data->map.col - 1] != '1')
			return (1);
	return (0);
}

int	sl_map_char_checker(t_data *data)
{
	t_pos	i;

	i.y = -1;
	while (++i.y < data->map.row)
	{
		i.x = -1;
		while (++i.x < data->map.col)
		{
			if (data->map.map[i.y][i.x] != '1' && data->map.map[i.y][i.x] != '0'\
			&& data->map.map[i.y][i.x] != 'C' && data->map.map[i.y][i.x] != 'E'\
			&& data->map.map[i.y][i.x] != 'P')
				return (1);
			if (data->map.map[i.y][i.x] == 'P')
			{
				data->player_pos.x = i.x;
				data->player_pos.y = i.y;
				data->map.item_p++;
			}
			if (data->map.map[i.y][i.x] == 'C')
				data->map.item_c++;
			if (data->map.map[i.y][i.x] == 'E')
				data->map.item_e++;
		}
	}
	return (0);
}
