/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:58 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/06 17:05:13 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_length(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map && game->map.map[i])
		i++;
	game->map.ceiling = 0x1C2E50FF;
	game->map.floor = 0x7F7F7FFF;
}

char	*g_map[] = {
	(char []){'1', '1', '1', '1', '1', '1', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'0', '0', '0', '0', '1', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '1', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '0', '0', '0', '1', 0},
	(char []){'1', '0', '0', '1', '0', '0', '1', 0},
	(char []){'1', '0', '1', '1', '1', '0', '1', 0},
	(char []){'1', '0', '0', '1', '0', '0', '1', 0},
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
	(char []){"./img/wall_03.png"},
	(char []){"./img/wall_03.png"},
	(char []){"./img/wall_03.png"},
	(char []){"./img/wall_03.png"},
	0
};

t_game	game_init(char *name)
{
	return ((t_game){
		.bonus = 1,
		.mlx = 0,
		.map = (t_map){filling_tab(name), tab_row(name), tab_col(name), 0, 0},
		.window = 0,
		.textures = 0,
		.player = (t_player){(0 - (PI / 2)) * check_player(name), (t_point){0, 0}},
		.keys = (t_keys){0, 0, 0, 0, 0, 0}
	});
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || parsing(argv[1]))
	{
		printf("Error\n");
		return (0);
	}
	game = game_init(argv[1]);
	game.player.coord = (t_point){(5 + 0.5) * TILE_SIZE, (5 + 0.5) * TILE_SIZE};
	map_length(&game);
	if (load_textures(&game, g_textures_path))
		return (1);
	game.mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3D", true);
	if (!game.mlx)
		return (1);
	game.window = mlx_new_image(game.mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game.window)
		return (1);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game.mlx, DISPLAY_WIDTH >> 1, DISPLAY_HEIGHT >> 1);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &draw, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
