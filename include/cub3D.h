/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:01:20 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/23 17:22:05 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include <math.h>

# define TILE_SIZE 64
# define DISPLAY_WIDTH 1600
# define DISPLAY_HEIGHT 900
# define PI 3.14159265359

typedef enum e_keys {
	W = MLX_KEY_W,
	S = MLX_KEY_S,
	A = MLX_KEY_A,
	D = MLX_KEY_D,
	UP = MLX_KEY_UP,
	DO = MLX_KEY_DOWN,
	LE = MLX_KEY_LEFT,
	RI = MLX_KEY_RIGHT,
}	t_enum_keys;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_map
{
	char	**map;
}	t_map;

typedef struct s_player
{
	float	angle;
	t_point	coord;
	t_point	delta;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
}	t_keys;

typedef struct s_game
{
	void			*mlx;
	t_map			map;
	unsigned long	fps;
	unsigned long	start_time;
	unsigned long	last_frame;
	mlx_image_t		*window;
	t_player		player;
	t_keys			keys;
}	t_game;

unsigned long	get_time(void);

#endif