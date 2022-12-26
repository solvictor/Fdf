/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:27:41 by vegret            #+#    #+#             */
/*   Updated: 2022/12/27 00:37:44 by vegret           ###   ########.fr       */
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
		else
			vars->proj = new_proj("Isometric)", &project, 30, 30);
	}
}

void	project(t_vars *vars)
{
	t_point			*points;
	const double	angles[4] = {
		sin(vars->proj.angle1) * DISTANCE * vars->zoom,
		cos(vars->proj.angle2) * DISTANCE * vars->zoom,
		cos(vars->rotation * M_PI / 180),
		sin(vars->rotation * M_PI / 180)
	};
	double			x;
	double			y;

	points = vars->points;
	while (points)
	{
		x = points->x + points->y;
		y = points->x - points->y;
		points->dx = x * angles[2] - y * angles[3];
		points->dy = x * angles[3] + y * angles[2];
		points->dx = points->dx * angles[1];
		points->dy = points->dy * angles[0];
		points->dy -= points->z * vars->zhight * vars->zoom;
		points = points->next;
	}
}
