/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:17:51 by vegret            #+#    #+#             */
/*   Updated: 2022/12/14 17:47:53 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	pointsclear(t_point **lst)
{
	t_point	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

t_point	*new_point(int x, int y)
{
	t_point	*new;

	new = malloc(sizeof(t_point));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = 0;
	new->dx = x;
	new->dy = y;
	new->color = DEFAULT_POINT_COLOR;
	new->nextx = NULL;
	new->nexty = NULL;
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

void	clean_exit(t_vars *vars, int status)
{
	if (vars)
	{
		if (vars->points)
			pointsclear(&vars->points);
		if (vars->title)
			free(vars->title);
		if (vars->img.id)
			mlx_destroy_image(vars->id, vars->img.id);
		if (vars->win)
			mlx_destroy_window(vars->id, vars->win);
		if (vars->id)
		{
			mlx_destroy_display(vars->id);
			free(vars->id);
		}
	}
	exit(status);
}
