/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:14:31 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/09 17:16:59 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

t_ray	*raycaster_step(t_game *game, t_ray *ray)
{
	int		i;
	int		mx;
	int		my;

	i = -1;
	while (++i < 50)
	{
		mx = (int)ray[0].r.x >> 6;
		my = (int)ray[0].r.y >> 6;
		if (my >= 0 && my < game->map.row && mx >= 0 && mx < game->map.col)
		{
			if (game->map.map[my][mx] == '1')
			{
				ray[0].distance = dist(game->player.coord, ray[0].r);
				break ;
			}
			else if (game->map.map[my][mx] == 'D' || game->map.map[my][mx] == 'O')
			{
				if (ray[1].distance == 1e9)
				{
					ray[1].r = point_add(ray[1].r, (t_point){ray[1].o.x / 2, ray[1].o.y / 2});
					ray[1].distance = dist(game->player.coord, ray[1].r);
				}
			}
		}
		ray[0].r = point_add(ray[0].r, ray[0].o);
		if (ray[1].distance == 1e9)
			ray[1].r = point_add(ray[1].r, ray[1].o);
	}
	return (ray);
}

t_ray	*raycaster_horizontal(t_game *game, float ra, t_ray *ray)
{
	float	atan;

	ray[0].distance = 1e9;
	atan = -1 / tan(ra);
	if (ra > PI)
	{
		ray[0].r.y = (((int)game->player.coord.y >> 6) << 6) - 0.0001;
		ray[0].r.x = (game->player.coord.y - ray[0].r.y) * atan + \
			game->player.coord.x;
		ray[0].o = (t_point){0 -(-TILE_SIZE * atan), -TILE_SIZE};
		ray[0].direction = N;
	}
	if (ra < PI)
	{
		ray[0].r.y = (((int)game->player.coord.y >> 6) << 6) + 64;
		ray[0].r.x = (game->player.coord.y - ray[0].r.y) * atan + \
			game->player.coord.x;
		ray[0].o = (t_point){0 -(TILE_SIZE * atan), TILE_SIZE};
		ray[0].direction = S;
	}
	ray[1] = ray[0];
	return (raycaster_step(game, ray));
}

t_ray	*raycaster_vertical(t_game *game, float ra, t_ray *ray)
{
	float	atan;

	ray[0].distance = 1e9;
	atan = -tan(ra);
	if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		ray[0].r.x = (((int)game->player.coord.x >> 6) << 6) - 0.0001;
		ray[0].r.y = (game->player.coord.x - ray[0].r.x) * atan + \
			game->player.coord.y;
		ray[0].o = (t_point){-TILE_SIZE, -(-TILE_SIZE * atan)};
		ray[0].direction = E;
	}
	if (ra < PI / 2 || ra > 3 * PI / 2)
	{
		ray[0].r.x = (((int)game->player.coord.x >> 6) << 6) + 64;
		ray[0].r.y = (game->player.coord.x - ray[0].r.x) * atan + \
			game->player.coord.y;
		ray[0].o = (t_point){TILE_SIZE, -(TILE_SIZE * atan)};
		ray[0].direction = W;
	}
	ray[1] = ray[0];
	return (raycaster_step(game, ray));
}

t_ray	raycaster_check(t_game *game, t_ray h, t_ray v)
{
	if (v.distance < h.distance)
	{
		if (v.direction == E)
			v.r.y = TILE_SIZE * game->map.row - v.r.y;
		v.r.x = v.r.y;
		return (v);
	}
	else
	{
		if (h.direction == S)
			h.r.x = TILE_SIZE * game->map.col - h.r.x;
		return (h);
	}
}

void	raycaster(t_game *game)
{
	int		pixel;
	float	ra;
	float	step;
	t_ray	ray[2][2];
	t_ray	rayc[2];

	ra = adjust_angle(game->player.angle - PI * FOV / 360);
	step = PI * FOV / 180 / DISPLAY_WIDTH;
	pixel = -1;
	while (++pixel < DISPLAY_WIDTH)
	{
		raycaster_horizontal(game, ra, ray[0]);
		raycaster_vertical(game, ra, ray[1]);
		rayc[0] = raycaster_check(game, ray[0][0], ray[1][0]);
		rayc[1] = raycaster_check(game, ray[0][1], ray[1][1]);
		draw_stripe(game, pixel, ra, rayc[0]);
		if (rayc[0].distance > rayc[1].distance)
			draw_stripe_door(game, pixel, ra, rayc[1]);
		ra = adjust_angle(ra + step);
	}
}
