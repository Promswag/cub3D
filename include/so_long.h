/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:40:26 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/19 14:43:10 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 32

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>

# include "get_next_line.h"
# include "../libft/include/libft.h"

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	char	**map;
	int		col;
	int		row;
	int		item_c;
	int		item_e;
	int		item_p;
}	t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			gameover;
	int			moves;
	int			valid_item;
	int			valid_exit;
	int			tmp_exit;
	t_pos		tmp_exit_pos;
	t_map		map;
	mlx_image_t	*bg;
	mlx_image_t	*wall;
	mlx_image_t	*item;
	mlx_image_t	*exit;
	mlx_image_t	*player;
	t_pos		player_pos;
}	t_data;

void	sl_game_init(t_data *data);
int		sl_close(t_data *data);
char	*sl_strjoin(char *s1, char *s2);
int		sl_args_handler(int argc, char **argv);
int		sl_error_handler(int error);
int		sl_map_handler(char *path, t_data *data);
void	sl_draw(t_data *data);
int		sl_img_loader(t_data *data);
void	sl_key_hook(mlx_key_data_t keydata, void *param);
int		sl_path_check(t_data *data);
void	sl_map_free(t_data *data);

#endif
