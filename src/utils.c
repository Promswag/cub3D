/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:52:23 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/12 11:00:34 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	get_color(int x, int y, t_texture *t)
{
	return (t->pixels[y * t->width + x]);
}

float	adjust_angle(float angle)
{
	if (angle < 0)
		return (angle + 2 * PI);
	else if (angle > 2 * PI)
		return (angle - 2 * PI);
	else
		return (angle);
}

t_point	point_add(t_point a, t_point b)
{
	return ((t_point){a.x + b.x, a.y + b.y});
}

float	dist(t_point a, t_point b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

t_doordata	setup_door(t_game *game, t_tinfo t)
{
	t_doordata	data;

	data.o = 0;
	data.r = t.dh / 4;
	data.j = 0;
	if (t.dh > t.h)
	{
		data.o = ((t.dh - DISPLAY_HEIGHT) >> 1);
		data.j = (data.o / data.r);
	}
	data.t = -1;
	if (t.x < game->textures[4]->width / 2)
		data.t = 1;
	return (data);
}
