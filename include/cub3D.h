/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:01:20 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/11 13:21:34 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include <math.h>
# include "cub3d_parsing.h"
# include <stdio.h>

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
	char			**path;
}	t_map;

typedef struct s_player
{
	float	angle;
	t_point	coord;
}	t_player;

typedef struct s_doorlst
{
	int					x;
	int					y;
	int					frame;
	int					status;
	struct s_doorlst	*next;
}	t_doorlst;

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
	t_doorlst		*doors;
	t_keys			keys;
}	t_game;

typedef struct s_ray
{
	float			distance;
	t_point			r;
	t_point			o;
	t_doorlst		*door;
	unsigned int	direction;
}	t_ray;

typedef struct s_tinfo
{
	int		dh;
	int		h;
	int		o;
	float	r;
	float	x;
	float	y;
}	t_tinfo;

//	inputs.c
void			key_handler(mlx_key_data_t k, void *param);

//	movements.c
void			movements_handler(t_game *game);

//	textures.c
int				load_textures(t_game *game, char **path);
void			texture_destroy(t_texture **textures);

//	minimap.c
void			draw_minimap(t_game *game);

//	draw.c
void			draw(void *param);
void			draw_stripe(t_game *game, int x, float angle, t_ray ray);
void			draw_stripe_door(t_game *game, int x, float angle, t_ray ray);

//	raycaster.c
void			raycaster(t_game *game);

//	raycaster_utils.c
void			raycaster_door(t_game *game, t_ray *ray, int mx, int my);

//	door.c
int				door_loader(t_game *game);
void			door_toggle(t_game *game);
void			door_update(t_game *game);
t_doorlst		*which_door(t_game *game, int x, int y);

//	doorlst.c
t_doorlst		*new_doorlst(unsigned int x, unsigned int y, char status);
void			doorlst_add_back(t_doorlst **lst, t_doorlst *new);
void			doorlst_destroy(t_doorlst **lst);

//	utils.c
unsigned int	get_color(int x, int y, t_texture *t);
float			adjust_angle(float angle);
t_point			point_add(t_point a, t_point b);
float			dist(t_point a, t_point b);

#endif