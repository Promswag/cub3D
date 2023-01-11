/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_inspect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:24:47 by aho               #+#    #+#             */
/*   Updated: 2022/12/23 15:24:49 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	wall_inspect_right(char *str, int *x)
{
	int	stat;

	stat = 1;
	while (str[*x] != '\n' && str[*x] != '\0')
	{
		if (str[*x] == ' ')
			stat = 1;
		else if (str[*x] == '1')
			stat = 0;
		else if (str[*x] != ' ' && str[*x] != '1' && stat == 1)
			return (1);
		(*x)++;
	}
	return (0);
}

int	wall_inspect_left(char *str, int *x)
{
	int	stat;

	stat = 1;
	while (*x >= 0)
	{
		if (str[*x] == ' ')
			stat = 1;
		else if (str[*x] == '1')
			stat = 0;
		else if (str[*x] != ' ' && str[*x] != '1' && stat == 1)
			return (1);
		(*x)--;
	}
	return (0);
}

int	wall_inspect_down(char **tab, int line, int x)
{
	int	stat;
	int	j;

	j = 0;
	stat = 1;
	while (j < line)
	{
		if (tab[j][x] == ' ')
			stat = 1;
		else if (tab[j][x] == '1')
			stat = 0;
		else if (tab[j][x] != ' ' && tab[j][x] != '1' && stat == 1)
			return (1);
		j++;
	}
	return (0);
}

int	wall_inspect_up(char **tab, int line, int x)
{
	int	stat;

	line--;
	stat = 1;
	while (line >= 0)
	{
		if (tab[line][x] == ' ')
			stat = 1;
		else if (tab[line][x] == '1')
			stat = 0;
		else if (tab[line][x] != ' ' && tab[line][x] != '1' && stat == 1)
			return (1);
		line--;
	}
	return (0);
}

int	wall_inspect(char **tab, int line)
{
	int	x;
	int	j;

	x = 0;
	j = 0;
	while (j < line)
	{
		if (wall_inspect_right(tab[j], &x))
			return (1);
		x--;
		if (wall_inspect_left(tab[j], &x))
			return (1);
		x++;
		j++;
	}
	while (tab[x])
	{
		if (wall_inspect_down(tab, line, x))
			return (1);
		if (wall_inspect_up(tab, line, x))
			return (1);
		x++;
	}
	return (0);
}
