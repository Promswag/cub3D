/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/11 14:44:58 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	game_terminate(t_game *game)
{
	doorlst_destroy(&game->doors);
	texture_destroy(game->textures);
}

t_game	game_init(char *name)
{
	t_point	coor;
	t_game	game;

	coor = check_coor(name, (t_point){-1, 0});
	game = (t_game){
		.bonus = 1,
		.mlx = 0,
		.map = (t_map){filling_tab(name), tab_row(name), tab_col(name), \
			fc_color(name, 'C'), fc_color(name, 'F'), path_texture(name)},
		.window = 0,
		.textures = 0,
		.player = (t_player){0 - (PI / 2) * check_player(name)
							 , (t_point){(coor.x + 0.5) * TILE_SIZE
									   , (coor.y + 0.5) * TILE_SIZE}},
		.doors = 0,
		.keys = (t_keys){0, 0, 0, 0, 0, 0}
	};
	// if (game.bonus == 0 && pars_bonus(name) && game.map.path[4][1])
	// 	printf("Error\n");
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || parsing(argv[1]))
		return (printf("Error\n"));
	game = game_init(argv[1]);
	door_loader(&game);
	if (load_textures(&game, path_texture(argv[1])))
		return (1);
	game.mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3D", false);
	if (!game.mlx)
		return (1);
	mlx_set_window_pos(game.mlx, (2560 - DISPLAY_WIDTH) >> 1, \
		(1440 - DISPLAY_HEIGHT) >> 1);
	game.window = mlx_new_image(game.mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game.window)
		return (1);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game.mlx, DISPLAY_WIDTH >> 1, DISPLAY_HEIGHT >> 1);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &draw, &game);
	mlx_loop(game.mlx);
	game_terminate(&game);
	mlx_terminate(game.mlx);
	return (0);
}