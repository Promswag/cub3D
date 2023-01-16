/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:31:46 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/16 15:15:31 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	raycaster_loop(t_game *game, t_ray *ray, t_point p, int *door)
{
	if (game->map.map[(int)p.y][(int)p.x] == '1')
	{
		ray->distance = dist(game->player.coord, ray->r);
		ray->t = game->textures[ray->direction];
		return (1);
	}
	else if ((game->map.map[(int)p.y][(int)p.x] == 'D' && *door == 1))
	{
		ray->r = point_add(ray->r, (t_point){ray->o.x / 2, ray->o.y / 2});
		ray->distance = dist(game->player.coord, ray->r);
		ray->t = game->textures[4];
		return (1);
	}
	else if (game->map.map[(int)p.y][(int)p.x] == 'D' && *door == 0)
	{
		(ray + 1)->r = point_add((ray + 1)->r, \
			(t_point){(ray + 1)->o.x / 2, (ray + 1)->o.y / 2});
		(ray + 1)->distance = dist(game->player.coord, (ray + 1)->r);
		(ray + 1)->door = which_door(game, p.x, p.y);
		(ray + 1)->t = game->textures[4];
		*door = 1;
	}
	return (0);
}
