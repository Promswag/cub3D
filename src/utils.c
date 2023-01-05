/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:52:23 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/05 16:06:35 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <sys/time.h>

// unsigned long	get_time(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec * 1000000 + time.tv_usec);
// }

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