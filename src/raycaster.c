/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:14:31 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/06 15:33:48 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_ray	raycaster_step(t_game *game, t_ray ray)
{
	int		i;
	int		mx;
	int		my;

	i = -1;
	ray.distance = 1e9;
	while (++i < 50)
	{
		mx = (int)ray.r.x >> 6;
		my = (int)ray.r.y >> 6;
		if (my >= 0 && my < game->map.row && mx >= 0 && mx < game->map.col \
			&& game->map.map[my][mx] == '1')
		{
			ray.distance = dist(game->player.coord, ray.r);
			break ;
		}
		else
			ray.r = point_add(ray.r, ray.o);
	}
	return (ray);
}

t_ray	raycaster_horizontal(t_game *game, float ra)
{
	t_ray	ray;
	float	atan;

	atan = -1 / tan(ra);
	if (ra > PI)
	{
		ray.r.y = (((int)game->player.coord.y >> 6) << 6) - 0.0001;
		ray.r.x = (game->player.coord.y - ray.r.y) * atan + \
			game->player.coord.x;
		ray.o = (t_point){0 -(-TILE_SIZE * atan), -TILE_SIZE};
		ray.direction = N;
	}
	if (ra < PI)
	{
		ray.r.y = (((int)game->player.coord.y >> 6) << 6) + 64;
		ray.r.x = (game->player.coord.y - ray.r.y) * atan + \
			game->player.coord.x;
		ray.o = (t_point){0 -(TILE_SIZE * atan), TILE_SIZE};
		ray.direction = S;
	}
	return (raycaster_step(game, ray));
}

t_ray	raycaster_vertical(t_game *game, float ra)
{
	t_ray	ray;
	float	atan;

	atan = -tan(ra);
	if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		ray.r.x = (((int)game->player.coord.x >> 6) << 6) - 0.0001;
		ray.r.y = (game->player.coord.x - ray.r.x) * atan + \
			game->player.coord.y;
		ray.o = (t_point){-TILE_SIZE, -(-TILE_SIZE * atan)};
		ray.direction = E;
	}
	if (ra < PI / 2 || ra > 3 * PI / 2)
	{
		ray.r.x = (((int)game->player.coord.x >> 6) << 6) + 64;
		ray.r.y = (game->player.coord.x - ray.r.x) * atan + \
			game->player.coord.y;
		ray.o = (t_point){TILE_SIZE, -(TILE_SIZE * atan)};
		ray.direction = W;
	}
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
	t_ray	ray;

	ra = adjust_angle(game->player.angle - PI * FOV / 360);
	step = PI * FOV / 180 / DISPLAY_WIDTH;
	pixel = -1;
	while (++pixel < DISPLAY_WIDTH)
	{
		ray = raycaster_check(game, \
			raycaster_horizontal(game, ra), \
			raycaster_vertical(game, ra));
		draw_stripe(game, pixel, ra, ray);
		ra = adjust_angle(ra + step);
	}
}
