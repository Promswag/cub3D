/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:31:46 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/11 10:33:04 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	raycaster_door(t_game *game, t_ray *ray, int mx, int my)
{
	if (ray->distance == 1e9)
	{
		ray->r = point_add(ray->r, (t_point){ray->o.x / 2, ray->o.y / 2});
		ray->distance = dist(game->player.coord, ray->r);
		ray->door = which_door(game, mx, my);
	}
}
