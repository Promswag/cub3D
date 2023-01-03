/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/03 17:50:11 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

float	dist(t_point a, t_point b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
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
	(char []){'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 0},
	(char []){'1', '0', '1', '0', '0', '0', '0', '1', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '1', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '1', 0, 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '1', '1', '1', '1', 0, 0},
	(char []){'1', '0', '0', '0', '0', '0', '0', '0', '1', 0, 0},
	(char []){'1', '1', '1', '1', '1', '1', '1', '1', '1', 0, 0},
	0
};

void	load_textures(t_game *game)
{
	game->wall = mlx_load_png("./img/wall_01.png");
	printf("%p\n", game->wall);
	printf("%p\n", game->wall->pixels);
	printf("%d\n", game->wall->height);
	printf("%d\n", game->wall->width);
	printf("%d\n", game->wall->bytes_per_pixel);
	
}

unsigned int	get_color(int x, int y, mlx_texture_t *texture, int height)
{
	float	ratio;

	ratio = height / texture->height;
	return (texture->pixels[(int)((y / ratio + x) * 4)] << 24\
		| texture->pixels[(int)((y / ratio + x) * 4) + 1] << 16 \
		| texture->pixels[(int)((y / ratio + x) * 4) + 2] << 8\
		| texture->pixels[(int)((y / ratio + x) * 4) + 3]);
}

void	prepare_image(t_game *game, int x, float distance, float angle, int color, t_point coord)
{
	float	height;
	float	fish_angle;
	int		i;
	int		offset;

	fish_angle = adjust_angle(game->player.angle - angle);
	distance *= cos(fish_angle);
	height = (TILE_SIZE * DISPLAY_HEIGHT * DISPLAY_WIDTH / DISPLAY_HEIGHT * 60 / FOV) / distance;
	if (height > DISPLAY_HEIGHT)
		height = DISPLAY_HEIGHT;
	offset = (DISPLAY_HEIGHT - height) / 2;
	i = 0;
	while (i < height)
	{
		if (color == 0)
		{
			if (game->wall)
			{
				mlx_put_pixel(game->window, x, offset + i, get_color(coord.x, i, game->wall, height));
				i++;
			}
			else
				mlx_put_pixel(game->window, x, offset + i++, color);
		}
		else
			mlx_put_pixel(game->window, x, offset + i++, color);
	}
}

void	draw_section(t_game *game, t_point start, t_point end, int color)
{
	int	x;

	while (start.y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			mlx_put_pixel(game->window, x, start.y, color);
			x++;
		}
		start.y++;
	}
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
	int		color;
	int		colorh;
	int		colorv;

	ra = adjust_angle(game->player.angle - PI * FOV / 360);
	step = PI * FOV / 180 / DISPLAY_WIDTH;
	r = -1;
	// printf("%f\n", step);
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
			colorh = 0;
		}
		if (ra < PI)
		{
			ry = (((int)game->player.coord.y >> 6) << 6) + 64;
			rx = (game->player.coord.y - ry) * atan + game->player.coord.x;
			yo = TILE_SIZE;
			xo = -yo * atan;
			colorh = 0x00FF00FF;
		}
		// if (ra == 0 || ra == PI)
		// {
		// 	ry = game->player.coord.y;
		// 	rx = game->player.coord.x;
		// 	wall = 8;
		// }
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
				disth = dist(game->player.coord, (t_point){rx, ry});
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
			colorv = 0x0000FFFF;
		}
		if (ra < PI / 2 || ra > 3 * PI / 2)
		{
			rx = (((int)game->player.coord.x >> 6) << 6) + 64;
			ry = (game->player.coord.x - rx) * atan + game->player.coord.y;
			xo = TILE_SIZE;
			yo = -(xo * atan);
			colorv = 0xFFFF00FF;
		}
		// if (ra == PI / 2 || ra == 3 * PI / 2)
		// {
		// 	ry = game->player.coord.y;
		// 	rx = game->player.coord.x;
		// 	wall = 8;
		// }
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
				distv = dist(game->player.coord, (t_point){rx, ry});
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
			color = colorv;
		}
		if (disth < distv)
		{
			rx = hx;
			ry = hy;
			distt = disth;
			color = colorh;
		}
		if (hit && rx >= 0 && rx < DISPLAY_WIDTH && ry >= 0 && ry < DISPLAY_HEIGHT)
			mlx_put_pixel(game->window, rx, ry, 0x00FF00FF);
		if (hit)
			prepare_image(game, r, distt, ra, color, (t_point){(int)rx % TILE_SIZE, (int)ry % TILE_SIZE});
		ra = adjust_angle(ra + step);
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
	draw_section(game, (t_point){0, 0}, (t_point){DISPLAY_WIDTH, DISPLAY_HEIGHT / 2}, 0x7F7F7FFF);
	draw_section(game, (t_point){0, DISPLAY_HEIGHT / 2}, (t_point){DISPLAY_WIDTH, DISPLAY_HEIGHT}, 0x1C2E50FF);
	cub3d_raycaster(game);
	mlx_image_to_window(game->mlx, game->window, 0, 0);
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
		// update_game(game);
		movements_handler(game);
		draw(game);
	}
}

t_game	game_init(void)
{
	return ((t_game){
		.mlx = 0,
		.map = (t_map){0, 0},
		.fps = 0,
		.start_time = 0,
		.last_frame = 0,
		.window = 0,
		.wall = 0,
		.player = (t_player){\
			.angle = PI / 2, \
			.coord = (t_point){.x = 92, .y = 92}},
		.keys = (t_keys){.w = 0, .a = 0, .s = 0, .d = 0, .q = 0, .e = 0}
	});
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
	load_textures(&game);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &draw_60fps, &game);
	game.start_time = get_time();
	game.map.map = g_map;
	map_length(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
