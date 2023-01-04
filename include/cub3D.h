/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:01:20 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/04 14:12:55 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include <math.h>

# define TILE_SIZE 64
# define DISPLAY_WIDTH 1500
# define DISPLAY_HEIGHT 1000
# define PI 3.14159265359
# define FOV 60

typedef enum e_direction {
	E = 0,
	N,
	W,
	S
}	t_enum_direction;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_map
{
	char	**map;
	int		row;
	int		col;
}	t_map;

typedef struct s_player
{
	float	angle;
	t_point	coord;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	q;
	int	e;
}	t_keys;

typedef struct s_game
{
	void			*mlx;
	t_map			map;
	unsigned long	fps;
	unsigned long	start_time;
	unsigned long	last_frame;
	mlx_image_t		*window;
	mlx_texture_t	**textures;
	t_player		player;
	t_keys			keys;
}	t_game;


//	inputs.c
void			key_handler(mlx_key_data_t k, void *param);

//	movements.c
void			movements_handler(t_game *game);

//	cub3d_minimap.c
void			cub3d_draw_minimap(t_game *game);

//	utils.c
unsigned long	get_time(void);
float			adjust_angle(float angle);
t_point			point_add(t_point a, t_point b);

#endif