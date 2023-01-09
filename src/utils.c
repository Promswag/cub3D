/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:52:23 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/09 14:06:04 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

t_ray	raycaster_supercheck(t_ray rays[4])
{
	t_ray	ray;
	int		i;

	ray = rays[0];
	i = -1;
	while (++i < 4)
	{
		if (rays[i].distance < ray.distance)
		{
			ray.distance = rays[i].distance;
			i = -1;
		}
	}
	return (ray);
}

