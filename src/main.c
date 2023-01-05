/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/05 17:13:26 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>


void	map_length(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map && game->map.map[i])
		i++;
	game->map.row = 30;
	game->map.col = 7;
}

char	*g_map[] = {
	(char []){'1', '1', '1', '1', '1', '1', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '1', '1', '1', '1', '1', '1', 0},
	0
};

char	*g_textures_path[] = {
	(char []){"/Users/gbaumgar/Cursus/cub3D/img/wall_03.png"},
	(char []){"/Users/gbaumgar/Cursus/cub3D/img/wall_03.png"},
	(char []){"/Users/gbaumgar/Cursus/cub3D/img/wall_03.png"},
	(char []){"/Users/gbaumgar/Cursus/cub3D/img/wall_03.png"},
	0
};


unsigned int	get_color(int x, int y, t_texture *t)
{
	return (t->pixels[y * t->width + x]);
}

// void	prepare_image(t_game *game, int x, float angle, float distance, float rx, int nesw)
// {
// 	int		height;
// 	float	fish_angle;
// 	int		i;
// 	int		offset;

// 	fish_angle = adjust_angle(game->player.angle - angle);
// 	distance *= cos(fish_angle);
// 	height = (1.0 * TILE_SIZE * DISPLAY_WIDTH * 60 / FOV) / distance;
// 	float	ratio = 1.0 * game->textures[nesw]->height / height;
// 	int	ty_off = 0;
// 	if (height > DISPLAY_HEIGHT)
// 	{
// 		ty_off = (height - DISPLAY_HEIGHT) >> 1;
// 		height = DISPLAY_HEIGHT;
// 	}
// 	offset = (DISPLAY_HEIGHT - height) >> 1;

// 	float ty = ty_off*ratio;
// 	float ratio2;

// 	ratio2 = 1.0 * game->textures[nesw]->width / TILE_SIZE;
// 	i = -1;
// 	while (++i < offset)
// 		mlx_put_pixel(game->window, x, i, 0x1C2E50FF);
// 	i = height + offset - 1;
// 	while (++i < DISPLAY_HEIGHT)
// 		mlx_put_pixel(game->window, x, i, 0x7F7F7FFF);
// 	i = -1;
// 	while (++i < height)
// 	{
// 		// mlx_put_pixel(game->window, x, offset + i, get_color((int)(rx * ratio2) % game->textures[nesw]->width, ty, game->textures[nesw]));
// 		unsigned int color = game->textures[nesw]->pixels[(int)ty * game->textures[nesw]->width + (int)(rx * ratio2) % game->textures[nesw]->width];
// 		mlx_put_pixel(game->window, x, offset + i, color);
// 		ty += ratio;
// 	}
// }

void	prepare_image(t_game *game, int x, float angle, t_ray ray)
{
	int		height;
	float	fish_angle;
	int		i;
	int		offset;

	fish_angle = adjust_angle(game->player.angle - angle);
	ray.distance *= cos(fish_angle);
	height = (1.0 * TILE_SIZE * DISPLAY_WIDTH * 60 / FOV) / ray.distance;
	float	ratio = 1.0 * game->textures[ray.direction]->height / height;
	int	ty_off = 0;
	if (height > DISPLAY_HEIGHT)
	{
		ty_off = (height - DISPLAY_HEIGHT) >> 1;
		height = DISPLAY_HEIGHT;
	}
	offset = (DISPLAY_HEIGHT - height) >> 1;

	float ty = ty_off*ratio;
	float ratio2;

	ratio2 = 1.0 * game->textures[ray.direction]->width / TILE_SIZE;
	i = -1;
	while (++i < offset)
		mlx_put_pixel(game->window, x, i, 0x1C2E50FF);
	i = height + offset - 1;
	while (++i < DISPLAY_HEIGHT)
		mlx_put_pixel(game->window, x, i, 0x7F7F7FFF);
	i = -1;
	while (++i < height)
	{
		// mlx_put_pixel(game->window, x, offset + i, get_color((int)(rx * ratio2) % game->textures[ray.direction]->width, ty, game->textures[ray.direction]));
		unsigned int color = game->textures[ray.direction]->pixels[(int)ty * game->textures[ray.direction]->width + (int)(ray.r.x * ratio2) % game->textures[ray.direction]->width];
		mlx_put_pixel(game->window, x, offset + i, color);
		ty += ratio;
	}
}

// void	raycaster(t_game *game)
// {
// 	int		angle;
// 	int		wall;
// 	int		mx;
// 	int		my;
// 	t_point	r;
// 	t_point	o;
// 	float	ra;
// 	float	atan;
// 	float	step;
// 	t_point	d;
// 	t_point	h;
// 	t_point	v;
// 	int		color;
// 	int		colorh;
// 	int		colorv;

// 	ra = adjust_angle(game->player.angle - PI * FOV / 360);
// 	step = PI * FOV / 180 / DISPLAY_WIDTH;
// 	angle = -1;
// 	while (++angle < DISPLAY_WIDTH)
// 	{
// 		d = (t_point){1e6, 1e6};
// 		h.x = game->player.coord.x;
// 		h.y = game->player.coord.y;
// 		wall = 0;
// 		atan = -1 / tan(ra);
// 		if (ra > PI)
// 		{
// 			r.y = (((int)game->player.coord.y >> 6) << 6) - 0.0001;
// 			r.x = (game->player.coord.y - r.y) * atan + game->player.coord.x;
// 			o.y = -TILE_SIZE;
// 			o.x = -(o.y * atan);
// 			colorh = N;
// 		}
// 		if (ra < PI)
// 		{
// 			r.y = (((int)game->player.coord.y >> 6) << 6) + 64;
// 			r.x = (game->player.coord.y - r.y) * atan + game->player.coord.x;
// 			o.y = TILE_SIZE;
// 			o.x = -(o.y * atan);
// 			colorh = S;
// 		}
// 		// if (ra == 0 || ra == PI)
// 		// {
// 		// 	r.y = game->player.coord.y;
// 		// 	rx = game->player.coord.x;
// 		// 	wall = 8;
// 		// }
// 		while (wall++ < 50)
// 		{
// 			mx = (int)r.x >> 6;
// 			my = (int)r.y >> 6;
// 			if (my >= 0 && my < game->map.row \
// 				&& mx >= 0 && mx < (int)ft_strlen(game->map.map[my]) \
// 				&& game->map.map[my][mx] == '1')
// 			{
// 				wall = 50;
// 				h = r;
// 				d.x = dist(game->player.coord, (t_point){r.x, r.y});
// 			}
// 			else
// 				r = point_add(r, o);
// 		}

// 		v.x = game->player.coord.x;
// 		v.y = game->player.coord.y;
// 		wall = 0;
// 		atan = -tan(ra);
// 		if (ra > PI / 2 && ra < 3 * PI / 2)
// 		{
// 			r.x = (((int)game->player.coord.x >> 6) << 6) - 0.0001;
// 			r.y = (game->player.coord.x - r.x) * atan + game->player.coord.y;
// 			o.x = -TILE_SIZE;
// 			o.y = -(o.x * atan);
// 			colorv = E;
// 		}
// 		if (ra < PI / 2 || ra > 3 * PI / 2)
// 		{
// 			r.x = (((int)game->player.coord.x >> 6) << 6) + 64;
// 			r.y = (game->player.coord.x - r.x) * atan + game->player.coord.y;
// 			o.x = TILE_SIZE;
// 			o.y = -(o.x * atan);
// 			colorv = W;
// 		}
// 		// if (ra == PI / 2 || ra == 3 * PI / 2)
// 		// {
// 		// 	r.y = game->player.coord.y;
// 		// 	r.x = game->player.coord.x;
// 		// 	wall = 8;
// 		// }
// 		while (wall++ < 50)
// 		{
// 			mx = (int)r.x >> 6;
// 			my = (int)r.y >> 6;
// 			if (my >= 0 && my < game->map.row \
// 				&& mx >= 0 && mx < game->map.col\
// 				&& game->map.map[my][mx] == '1')
// 			{
// 				wall = 50;
// 				v = r;
// 				d.y = dist(game->player.coord, (t_point){r.x, r.y});
// 			}
// 			else
// 				r = point_add(r, o);
// 		}
// 		if (d.y < d.x)
// 		{
// 			r = v;
// 			color = colorv;
// 			if (color == E)
// 				r.y = TILE_SIZE * game->map.row - r.y;
// 			prepare_image(game, angle, ra, (t_ray){d.y, {r.y, 0}, {0}, color});
// 		}
// 		if (d.x < d.y)
// 		{
// 			r = h;
// 			color = colorh;
// 			if (color == S)
// 				r.x = TILE_SIZE * game->map.col - r.x;
// 			prepare_image(game, angle, ra, (t_ray){d.x, {r.x, 0}, {0}, color});
// 		}
// 		ra = adjust_angle(ra + step);
// 	}
// }

void	draw(t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	mlx_delete_image(game->mlx, game->window);
	game->window = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	x = game->player.coord.x - 4;
	y = game->player.coord.y - 4;

	i = -1;
	raycaster(game);
	// draw_minimap(game);
	// while (++i < 9)
	// {
	// 	j = -1;
	// 	while (++j < 9)
	// 		if (y + i >= 0 && y + i < DISPLAY_HEIGHT \
	// 			&& x + j >= 0 && x + j < DISPLAY_WIDTH)
	// 			mlx_put_pixel(game->window, x + j, y + i, 0xFFFFFFFF);
	// }
	// i = -1;
	// while (++i < 15)
	// {
	// 	x = game->player.coord.x + cos(game->player.angle) * i;
	// 	y = game->player.coord.y + sin(game->player.angle) * i;
	// 	if (y >= 0 && y < DISPLAY_HEIGHT && x >= 0 && x < DISPLAY_WIDTH)
	// 		mlx_put_pixel(game->window, x, y, 0xFFFFFFFF);
	// }
	mlx_image_to_window(game->mlx, game->window, 0, 0);
}

void	draw_60fps(void *param)
{
	t_game			*game;
	// unsigned long	time;

	game = (t_game *)param;
	// time = get_time();
	// if (time - game->last_frame > 100000)
	// if (time - game->last_frame > 16666)
	// {
	// 	game->last_frame = time;
	// 	game->fps++;
	// 	if (game->fps == 60)
	// 	{
	// 		game->fps = 1;
	// 		game->start_time = time;
	// 	}
		// update_game(game);
	movements_handler(game);
	draw(game);
		// printf("%ld, %ld\n", game->fps, time - game->start_time);
		// printf("\033[A%f\n", 1.0 * game->fps / ((time - game->start_time) / 1e6));
	// }
}

t_game	game_init(void)
{
	return ((t_game){
		.mlx = 0,
		.map = (t_map){0, 0, 0, 0, 0},
		.fps = 0,
		.start_time = 0,
		.last_frame = 0,
		.window = 0,
		.textures = 0,
		.player = (t_player){-(PI / 2), (t_point){0, 0}},
		.keys = (t_keys){0, 0, 0, 0, 0, 0}
	});
}

int	main(int argc, char **argv)
{
	t_game	game;

	printf("\n\n\n");
	game = game_init();
	game.player.angle *= S;
	game.player.coord = (t_point){(5 + 0.5) * TILE_SIZE, (5 + 0.5) * TILE_SIZE};
	if (load_textures(&game, g_textures_path))
		return (1);
	game.mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3D", true);
	if (!game.mlx)
		;
	game.window = mlx_new_image(game.mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game.window)
		;
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &draw_60fps, &game);
	// game.start_time = get_time();
	game.map.map = g_map;
	map_length(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
