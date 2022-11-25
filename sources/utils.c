/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:17:51 by vegret            #+#    #+#             */
/*   Updated: 2022/11/25 23:36:36 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pointsclear(t_points **lst)
{
	t_points	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

t_points	*new_point(int x, int y)
{
	t_points	*new;

	new = malloc(sizeof(t_points));
	if (!new)
		return (NULL);
	new->content.x = x;
	new->content.y = y;
	new->content.z = 0;
	new->content.color = 0x00FFFFFF;
	new->next = NULL;
	return (new);
}

char	*uppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}
