/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:27:41 by vegret            #+#    #+#             */
/*   Updated: 2022/12/19 16:20:58 by vegret           ###   ########.fr       */
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
	new.angle1 = angle1 * M_PI / 180;
	new.angle2 = angle2 * M_PI / 180;
	return (new);
}

void	update_projection(t_vars *vars)
{
	if (vars->proj.f == (void *) &project)
	{
		if (!ft_strncmp(vars->proj.name, "Isometric)", 11))
			vars->proj = new_proj("Military)", &project, 45, 45);
		else if (!ft_strncmp(vars->proj.name, "Military)", 10))
			vars->proj = new_proj("Dimetric)", &project, 15, 15);
		else if (!ft_strncmp(vars->proj.name, "Dimetric)", 10))
			vars->proj = new_proj("Trimetric)", &project, 15, 45);
		else if (!ft_strncmp(vars->proj.name, "Trimetric)", 11))
			vars->proj = new_proj("Cavalier)", &project, 0, 45);
		else
			vars->proj = new_proj("Isometric)", &project, 30, 30);
	}
}

void	project(t_vars *vars)
{
	t_point			*prec;
	t_point			*points;
	t_point			*last_first;
	const double	angles[3] = {sin(vars->proj.angle1) * DISTANCE * vars->zoom,
		sin(vars->proj.angle2) * DISTANCE * vars->zoom,
		cos(vars->proj.angle2) * DISTANCE * vars->zoom};

	points = vars->points;
	last_first = points;
	prec = points;
	points = points->next;
	while (points)
	{
		if (points->y)
			points->dy = prec->dy - angles[1];
		else
		{
			prec = last_first;
			last_first = points;
			points->dy = prec->dy + angles[0];
		}
		points->dx = prec->dx + angles[2];
		prec = points;
		points = points->next;
	}
}
