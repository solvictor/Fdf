/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:27:41 by vegret            #+#    #+#             */
/*   Updated: 2022/12/14 18:56:57 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_projection	new_proj(
				char *name, void (*f)(t_vars *),
				double angle1, double angle2
				)
{
	t_projection	new;

	new.name = name;
	new.f = (void *) f;
	new.angle1 = angle1;
	new.angle2 = angle2;
	return (new);
}

void	update_projection(t_vars *vars)
{
	if (vars->projection.f == (void *) &project)
	{
		if (!ft_strncmp(vars->projection.name, "Isometric)", 11))
			vars->projection = new_proj("Military)", &project, 45, 45);
		else if (!ft_strncmp(vars->projection.name, "Military)", 10))
			vars->projection = new_proj("Dimetric)", &project, 15, 15);
		else if (!ft_strncmp(vars->projection.name, "Dimetric)", 10))
			vars->projection = new_proj("Trimetric)", &project, 15, 45);
		else if (!ft_strncmp(vars->projection.name, "Trimetric)", 11))
			vars->projection = new_proj("Cavalier)", &project, 0, 45);
		else
			vars->projection = new_proj("Isometric)", &project, 30, 30);
	}
}

void	project(t_vars *vars)
{
	t_point			*points;
	t_point			*last_first;
	t_point			*prec;
	const double	angle1 = vars->projection.angle1 * M_PI / 180;
	const double	angle2 = vars->projection.angle2 * M_PI / 180;

	points = vars->points;
	last_first = points;
	prec = points;
	points = points->next;
	while (points)
	{
		if (prec->x != points->x)
		{
			prec = last_first;
			last_first = points;
			points->dy = prec->dy + sin(angle1) * DISTANCE * vars->zoom;
		}
		else
			points->dy = prec->dy - sin(angle2) * DISTANCE * vars->zoom;
		points->dx = prec->dx + cos(angle2) * DISTANCE * vars->zoom;
		prec = points;
		points = points->next;
	}
}
