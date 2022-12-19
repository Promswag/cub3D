/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_path_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:25:51 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/09/28 12:12:39 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		sl_path_check(t_data *data);
int		sl_find_player(t_data *data, int x, int y, char **map);
char	**sl_map_copy(t_data *data, char **map);
int		sl_map_destroy(t_data *data, char **map, int r);
void	sl_map_free(t_data *data);

int	sl_path_check(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.row)
	{
		j = -1;
		while (++j < data->map.col)
		{
			if (data->map.map[i][j] == 'E')
				if (sl_find_player(data, j, i, data->map.map))
					data->valid_exit++;
			if (data->map.map[i][j] == 'C')
			{
				if (sl_find_player(data, j, i, data->map.map))
					data->valid_item++;
				else
					return (0);
			}
		}
	}
	if ((data->valid_item == data->map.item_c) && data->valid_exit)
		return (1);
	return (0);
}

int	sl_find_player(t_data *data, int x, int y, char **tmp)
{
	char	**map;

	map = sl_map_copy(data, tmp);
	if (map[y][x] == 'P')
		return (sl_map_destroy(data, map, 1));
	map[y][x] = '1';
	if (x < data->map.col && map[y][x + 1] != '1')
		if (sl_find_player(data, x + 1, y, map))
			return (sl_map_destroy(data, map, 1));
	if (x > 0 && map[y][x - 1] != '1')
		if (sl_find_player(data, x - 1, y, map))
			return (sl_map_destroy(data, map, 1));
	if (y < data->map.row && map[y + 1][x] != '1')
		if (sl_find_player(data, x, y + 1, map))
			return (sl_map_destroy(data, map, 1));
	if (y > 0 && map[y - 1][x] != '1')
		if (sl_find_player(data, x, y - 1, map))
			return (sl_map_destroy(data, map, 1));
	return (sl_map_destroy(data, map, 0));
}

char	**sl_map_copy(t_data *data, char **tmp)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * data->map.row);
	i = -1;
	while (++i < data->map.row)
	{
		map[i] = malloc(sizeof(char) * data->map.col);
		j = -1;
		while (++j < data->map.col)
			map[i][j] = tmp[i][j];
	}
	return (map);
}

int	sl_map_destroy(t_data *data, char **map, int r)
{
	int	i;

	i = -1;
	while (++i < data->map.row)
		free(map[i]);
	free(map);
	if (r)
		return (1);
	return (0);
}

void	sl_map_free(t_data *data)
{
	int	i;

	i = -1;
	while (data->map.map[++i])
		free(data->map.map[i]);
	free(data->map.map);
}
