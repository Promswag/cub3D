/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/23 17:26:18 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

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
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.delta.x = cos(game->player.angle) * 5;
		game->player.delta.y = sin(game->player.angle) * 5;
	}
	if (game->keys.d)
	{
		game->player.angle += 2 * PI / 72;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
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
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
