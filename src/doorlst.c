/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:09:46 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/16 15:51:30 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_doorlst	*doorlst_last(t_doorlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	doorlst_add_back(t_doorlst **lst, t_doorlst *elem)
{
	if (*lst == NULL)
		*lst = elem;
	else
		doorlst_last(*lst)->next = elem;
}

t_doorlst	*new_doorlst(unsigned int x, unsigned int y, char status)
{
	t_doorlst	*elem;

	elem = malloc(sizeof(t_doorlst));
	if (!(elem))
		return (NULL);
	elem->x = x;
	elem->y = y;
	if (status == 'D')
	{
		elem->status = 0;
		elem->frame = 0;
	}
	else
	{
		elem->status = 1;
		elem->frame = 31;
	}
	elem->next = NULL;
	return (elem);
}

void	doorlst_destroy(t_doorlst **lst)
{
	t_doorlst	*prev;

	while (*lst)
	{
		prev = *lst;
		*lst = (*lst)->next;
		free(prev);
	}
	lst = NULL;
}
