/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:46:07 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/11 13:46:07 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_doorlst	*which_door(t_game *game, int x, int y)
{
	t_doorlst	*lst;

	lst = game->doors;
	while (lst)
	{
		if (lst->x == x && lst->y == y)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	door_loader(t_game *game)
{
	t_doorlst	*door;
	char		status;
	int			x;
	int			y;

	y = -1;
	while (++y < game->map.row)
	{
		x = -1;
		while (++x < game->map.col)
		{
			status = game->map.map[y][x];
			if (status == 'D' || status == 'O')
			{
				door = new_doorlst(x, y, status);
				if (!door)
					return (1);
				doorlst_add_back(&game->doors, door);
			}
		}
	}
	return (0);
}

void	door_update(t_game *game)
{
	t_doorlst	*lst;

	lst = game->doors;
	while (lst)
	{
		if (lst->status)
		{
			if (lst->frame < 32)
				lst->frame++;
			else
				game->map.map[lst->y][lst->x] = 'O';
		}
		else
		{
			if (lst->frame > 0)
				lst->frame--;
			game->map.map[lst->y][lst->x] = 'D';
		}
		lst = lst->next;
	}
}

static int	door_check(t_game *game, int x, int y)
{
	t_doorlst	*lst;

	lst = game->doors;
	if (x >= 0 && x < game->map.col && y >= 0 && y < game->map.row && \
		(game->map.map[y][x] == 'D' || game->map.map[y][x] == 'O'))
	{
		while (lst)
		{
			if (lst->x == x && lst->y == y)
			{
				lst->status ^= 1;
				return (1);
			}
			lst = lst->next;
		}
	}
	return (0);
}

void	door_toggle(t_game *game)
{
	int			x;
	int			y;
	int			i;

	if (game->map.map[(int)game->player.coord.y / TILE_SIZE][\
		(int)game->player.coord.x / TILE_SIZE] == 'O')
		return ;
	i = 0;
	while (i < 96)
	{
		x = (game->player.coord.x + cos(game->player.angle) * i) / TILE_SIZE;
		y = (game->player.coord.y + sin(game->player.angle) * i) / TILE_SIZE;
		if (door_check(game, x, y))
			return ;
		i += 4;
	}
}
