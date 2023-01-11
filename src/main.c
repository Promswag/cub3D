/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/11 16:29:59 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_terminate(t_game *game, int i)
{
	if (i)
		printf("Error\n");
	doorlst_destroy(&game->doors);
	texture_destroy(game->textures);
	ft_erase(game->map.map);
	// ft_erase(game->map.path);
	return (1);
}

t_game	game_init(char *name)
{
	t_point	coor;
	t_game	game;

	coor = (t_point){0, 0};
	coor = check_coor(name, (t_point){-1, -1});
	game = (t_game){
		.bonus = 0,
		.mlx = 0,
		.map = (t_map){filling_tab(name), tab_row(name), tab_col(name), \
			fc_color(name, 'C'), fc_color(name, 'F'), path_texture(name)},
		.window = 0,
		.textures = 0,
		.player = (t_player){0 - (PI / 2) * check_player(name), \
			(t_point){(coor.x + 0.5) * TILE_SIZE, (coor.y + 0.5) * TILE_SIZE}},
		.doors = 0,
		.keys = (t_keys){0, 0, 0, 0, 0, 0}
	};
	bonus_toggler(&game);
	if (game.bonus == 0 && (pars_bonus(name)))
	{
		game_terminate(&game, 0);
		pars_end();
	}
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || parsing(argv[1]))
		return (printf("Error\n"));
	game = game_init(argv[1]);
	door_loader(&game);
	if (load_textures(&game, game.map.path))
		return (game_terminate(&game, 1));
	game.mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3D", true);
	if (!game.mlx)
		return (game_terminate(&game, 1));
	mlx_set_window_pos(game.mlx, (2560 - DISPLAY_WIDTH) >> 1, \
		(1440 - DISPLAY_HEIGHT) >> 1);
	game.window = mlx_new_image(game.mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game.window)
		return (game_terminate(&game, 1));
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game.mlx, DISPLAY_WIDTH >> 1, DISPLAY_HEIGHT >> 1);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &draw, &game);
	mlx_loop(game.mlx);
	game_terminate(&game, 0);
	mlx_terminate(game.mlx);
	return (0);
}
