/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:07:29 by vegret            #+#    #+#             */
/*   Updated: 2022/12/05 18:40:49 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	link_points(t_point *src, t_point *dst, t_vars *vars)
{
	int				e2;
	int				err;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	unsigned int	color;

	x0 = src->dx;
	y0 = src->dy;
	x1 = dst->dx;
	y1 = dst->dy;
	color = src->color;
	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = -1 + 2 * (x0 < x1);
	sy = -1 + 2 * (y0 < y1);
	err = dx + dy;
	while (1)
	{
		put_pixel_img(&vars->img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	printtest(t_point *content)
{
	printf(
		"x: %d (%d) y: %d (%d) z: %d color: %x\n",
		content->dx,
		content->x,
		content->dy,
		content->y,
		content->z,
		content->color);
}

static t_point	*get_point(int x, int y, t_points *list)
{
	while (list)
	{
		if (list->data.x == x && list->data.y == y)
			return (&list->data);
		list = list->next;
	}
	return (NULL);
}

int	render_points(t_vars *vars)
{
	t_points	*point;
	t_point		*tmp;

	point = vars->points;
	while (point)
	{
		tmp = get_point(point->data.x + 1, point->data.y, point->next);
		if (tmp)
			link_points(tmp, &point->data, vars);
		tmp = get_point(point->data.x, point->data.y + 1, point->next);
		if (tmp)
			link_points(tmp, &point->data, vars);
		point = point->next;
	}
	return (0);
}
