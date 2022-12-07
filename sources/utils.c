/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:17:51 by vegret            #+#    #+#             */
/*   Updated: 2022/12/07 13:47:05 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

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
	new->data.x = x;
	new->data.y = y;
	new->data.z = 0;
	new->data.dx = x;
	new->data.dy = y;
	new->data.color = DEFAULT_POINT_COLOR;
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
