/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:01:20 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/06 15:49:30 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include <math.h>
# include "cub3d_parsing.h"

# define TILE_SIZE 64
# define DISPLAY_WIDTH 1600
# define DISPLAY_HEIGHT 900
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
	char			**map;
	int				row;
	int				col;
	unsigned int	ceiling;
	unsigned int	floor;
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

typedef struct s_texture
{
	unsigned int	*pixels;
	unsigned int	height;
	unsigned int	width;
}	t_texture;

typedef struct s_game
{
	int				bonus;
	void			*mlx;
	t_map			map;
	mlx_image_t		*window;
	t_texture		**textures;
	t_player		player;
	t_keys			keys;
}	t_game;

typedef struct s_ray
{
	float			distance;
	t_point			r;
	t_point			o;
	unsigned int	direction;
}	t_ray;

typedef struct s_texture_info
{
	int		h;
	int		o;
	float	r;
	float	x;
	float	y;
}	t_texture_info;

//	inputs.c
void			key_handler(mlx_key_data_t k, void *param);

//	movements.c
void			movements_handler(t_game *game);

//	textures.c
int				load_textures(t_game *game, char **path);

//	minimap.c
void			draw_minimap(t_game *game);

//	draw.c
void			draw(void *param);
void			draw_stripe(t_game *game, int x, float angle, t_ray ray);

//	raycaster.c
void			raycaster(t_game *game);

//	utils.c
float			adjust_angle(float angle);
t_point			point_add(t_point a, t_point b);
float			dist(t_point a, t_point b);

#endif