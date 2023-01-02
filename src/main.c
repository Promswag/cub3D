/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/02 16:57:34 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

float	dist(t_point a, t_point b, float angle)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void	adjust_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

void	map_length(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map && game->map.map[i])
		i++;
	game->map.row = i;
}

char	*g_map[] = {
	(char []){'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', \
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', \
	'1', '1', '1', '1', '1', '1', '1', '1', '1', 0},
	(char []){'1', '0', '1', '0', '0', '0', '0', '1', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '1', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '1', '1', '1', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '1', '1', '1', '1', '1', '1', '1', '1', 0},
	(char []){'1', 0},
	(char []){'1', 0},
	(char []){'1', 0},
	(char []){'1', 0},
	(char []){'1', 0},
	0
};

void	prepare_image(t_game *game, int x, float distance, float angle)
{
	float	height;
	float	fish_angle;
	int		i;
	int		offset;

	fish_angle = game->player.angle - angle;
	adjust_angle(&fish_angle);
	distance *= cos(fish_angle);
	height = (TILE_SIZE * DISPLAY_HEIGHT * DISPLAY_WIDTH / DISPLAY_HEIGHT * 60 / FOV) / distance;
	if (height > DISPLAY_HEIGHT)
		height = DISPLAY_HEIGHT;
	offset = (DISPLAY_HEIGHT - height) / 2;
	i = 0;
	while (i < height)
		mlx_put_pixel(game->window, x, offset + i++, 0xFFFFFFFF);
}

void	cub3d_raycaster(t_game *game)
{
	int		r;
	int		wall;
	int		mx;
	int		my;
	int		hit;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	atan;
	float	step;
	float	disth;
	float	distv;
	float	distt;
	float	hx;
	float	hy;
	float	vx;
	float	vy;

	ra = game->player.angle - PI * FOV / 360;
	adjust_angle(&ra);
	step = PI * FOV / 180 / DISPLAY_WIDTH;
	r = -1;
	printf("%f\n", step);
	while (++r < DISPLAY_WIDTH)
	{
		hit = 0;
		//HORIZONTAL
		disth = 1000000;
		hx = game->player.coord.x;
		hy = game->player.coord.y;
		wall = 0;
		atan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int)game->player.coord.y >> 6) << 6) - 0.0001;
			rx = (game->player.coord.y - ry) * atan + game->player.coord.x;
			yo = -TILE_SIZE;
			xo = -yo * atan;
		}
		if (ra < PI)
		{
			ry = (((int)game->player.coord.y >> 6) << 6) + 64;
			rx = (game->player.coord.y - ry) * atan + game->player.coord.x;
			yo = TILE_SIZE;
			xo = -yo * atan;
		}
		if (ra == 0 || ra == PI)
		{
			ry = game->player.coord.y;
			rx = game->player.coord.x;
			wall = 8;
		}
		while (wall++ < 25)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if (my >= 0 && my < game->map.row \
				&& mx >= 0 && mx < (int)ft_strlen(game->map.map[my]) \
				&& game->map.map[my][mx] == '1')
			{
				wall = 25;
				hx = rx;
				hy = ry;
				disth = dist(game->player.coord, (t_point){rx, ry}, game->player.angle);
				hit = 1;
			}
			else
			{
				ry += yo;
				rx += xo;
			}
		}

		distv = 1000000;
		vx = game->player.coord.x;
		vy = game->player.coord.y;
		wall = 0;
		atan = -tan(ra);
		if (ra > PI / 2 && ra < 3 * PI / 2)
		{
			rx = (((int)game->player.coord.x >> 6) << 6) - 0.0001;
			ry = (game->player.coord.x - rx) * atan + game->player.coord.y;
			xo = -TILE_SIZE;
			yo = -(xo * atan);
		}
		if (ra < PI / 2 || ra > 3 * PI / 2)
		{
			rx = (((int)game->player.coord.x >> 6) << 6) + 64;
			ry = (game->player.coord.x - rx) * atan + game->player.coord.y;
			xo = TILE_SIZE;
			yo = -(xo * atan);
		}
		if (ra == PI / 2 || ra == 3 * PI / 2)
		{
			ry = game->player.coord.y;
			rx = game->player.coord.x;
			wall = 8;
		}
		while (wall++ < 25)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if (my >= 0 && my < game->map.row \
				&& mx >= 0 && mx < (int)ft_strlen(game->map.map[my]) \
				&& game->map.map[my][mx] == '1')
			{
				wall = 25;
				vx = rx;
				vy = ry;
				distv = dist(game->player.coord, (t_point){rx, ry}, game->player.angle);
				hit = 1;
			}
			else
			{
				ry += yo;
				rx += xo;
			}
		}
		if (distv < disth)
		{
			rx = vx;
			ry = vy;
			distt = distv;
		}
		if (disth < distv)
		{
			rx = hx;
			ry = hy;
			distt = disth;
		}
		if (hit && rx >= 0 && rx < DISPLAY_WIDTH && ry >= 0 && ry < DISPLAY_HEIGHT)
			mlx_put_pixel(game->window, rx, ry, 0x00FF00FF);
		ra += step;
		prepare_image(game, r, distt, ra);
		adjust_angle(&ra);
	}
}

void	draw(t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	mlx_delete_image(game->mlx, game->window);
	game->window = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	cub3d_draw_minimap(game);
	x = game->player.coord.x - 4;
	y = game->player.coord.y - 4;

	i = -1;
	while (++i < 9)
	{
		j = -1;
		while (++j < 9)
			if (y + i >= 0 && y + i < DISPLAY_HEIGHT \
				&& x + j >= 0 && x + j < DISPLAY_WIDTH)
				mlx_put_pixel(game->window, x + j, y + i, 0xFFFFFFFF);
	}
	i = -1;
	while (++i < 15)
	{
		x = game->player.coord.x + cos(game->player.angle) * i;
		y = game->player.coord.y + sin(game->player.angle) * i;
		if (y >= 0 && y < DISPLAY_HEIGHT && x >= 0 && x < DISPLAY_WIDTH)
			mlx_put_pixel(game->window, x, y, 0xFFFFFFFF);
	}
	cub3d_raycaster(game);
	mlx_image_to_window(game->mlx, game->window, 0, 0);
}

void	update_game(t_game *game)
{
	if (game->keys.w)
	{
		game->player.coord.x += game->player.delta.x;
		game->player.coord.y += game->player.delta.y;
	}
	if (game->keys.s)
	{
		game->player.coord.x -= game->player.delta.x;
		game->player.coord.y -= game->player.delta.y;
	}
	if (game->keys.a)
	{
		game->player.angle -= 2 * PI / 72;
		adjust_angle(&game->player.angle);
		game->player.delta.x = cos(game->player.angle) * 5;
		game->player.delta.y = sin(game->player.angle) * 5;
	}
	if (game->keys.d)
	{
		game->player.angle += 2 * PI / 72;
		adjust_angle(&game->player.angle);
		game->player.delta.x = cos(game->player.angle) * 5;
		game->player.delta.y = sin(game->player.angle) * 5;
	}
}

void	draw_60fps(void *param)
{
	t_game			*game;
	unsigned long	time;

	game = (t_game *)param;
	time = get_time();
	// if (time - game->last_frame > 100000)
	if (time - game->last_frame > 16666)
	{
		game->last_frame = time;
		game->fps++;
		update_game(game);
		draw(game);
	}
}

void	key_handler(mlx_key_data_t k, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (k.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if ((k.key == W || k.key == UP) && k.action == MLX_PRESS)
		game->keys.w = 1;
	if ((k.key == W || k.key == UP) && k.action == MLX_RELEASE)
		game->keys.w = 0;
	if ((k.key == S || k.key == DO) && k.action == MLX_PRESS)
		game->keys.s = 1;
	if ((k.key == S || k.key == DO) && k.action == MLX_RELEASE)
		game->keys.s = 0;
	if ((k.key == A || k.key == LE) && k.action == MLX_PRESS)
		game->keys.a = 1;
	if ((k.key == A || k.key == LE) && k.action == MLX_RELEASE)
		game->keys.a = 0;
	if ((k.key == D || k.key == RI) && k.action == MLX_PRESS)
		game->keys.d = 1;
	if ((k.key == D || k.key == RI) && k.action == MLX_RELEASE)
		game->keys.d = 0;
}

t_game	game_init(void)
{
	t_game	game;

	game = (t_game){
		.mlx = 0,
		.map = {0},
		.fps = 0,
		.start_time = 0,
		.last_frame = 0,
		.window = 0,
		.player = (t_player){\
			.angle = PI / 2, \
			.coord = (t_point){.x = 50, .y = 50}, \
			.delta = (t_point){.x = cos(PI / 2) * 5, .y = sin(PI / 2) * 5}},
		.keys = (t_keys){.w = 0, .a = 0, .s = 0, .d = 0}
	};
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game = game_init();

	(void)argc;
	(void)argv;
	game.mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3D", true);
	if (!game.mlx)
		;
	game.window = mlx_new_image(game.mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game.window)
		;
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &draw_60fps, &game);
	game.start_time = get_time();
	game.map.map = g_map;
	map_length(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
