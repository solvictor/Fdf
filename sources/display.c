/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:07:29 by vegret            #+#    #+#             */
/*   Updated: 2022/12/08 23:50:51 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	link_points(t_point src, t_point dst, t_vars *vars)
{
	int				e2;
	int				err;
	const int		dx = ft_abs(dst.dx - src.dx);
	const int		dy = -ft_abs(dst.dy - src.dy);

	err = dx + dy;
	while (1)
	{
		put_pixel_img(&vars->img, src.dx, src.dy, DEFAULT_POINT_COLOR);
		if (src.dx == dst.dx && src.dy == dst.dy)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			src.dx += -1 + 2 * (src.dx < dst.dx);
		}
		if (e2 <= dx)
		{
			err += dx;
			src.dy += -1 + 2 * (src.dy < dst.dy);
		}
	}
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

static int	out_window(t_point *p1, t_point *p2, t_vars *vars)
{
	return ((p1->dx > vars->img.width && p2->dx > vars->img.width)
		|| (p1->dy > vars->img.height && p2->dy > vars->img.height));
}

static int	render_points(t_vars *vars)
{
	t_points	*point;
	t_point		*tmp;

	point = vars->points;
	while (point)
	{
		tmp = get_point(point->data.x + 1, point->data.y, point->next);
		if (tmp && !out_window(tmp, &point->data, vars))
			link_points(*tmp, point->data, vars);
		tmp = get_point(point->data.x, point->data.y + 1, point->next);
		if (tmp && !out_window(tmp, &point->data, vars))
			link_points(*tmp, point->data, vars);
		point = point->next;
	}
	return (0);
}

static void	isometrify(t_points *points, int distance, double angle)
{
	t_points	*last_first;
	t_points	*prec;

	if (!points)
		return ;
	last_first = points;
	prec = points;
	points = points->next;
	while (points)
	{
		if (prec->data.x != points->data.x)
		{
			prec = last_first;
			last_first = points;
			points->data.dy = prec->data.dy + sin(angle) * distance;
		}
		else
			points->data.dy = prec->data.dy - sin(angle) * distance;
		points->data.dx = prec->data.dx + cos(angle) * distance;
		prec = points;
		points = points->next;
	}
}

void	addz(t_vars *vars)
{
	t_points	*point;

	point = vars->points;
	while (point)
	{
		point->data.dy -= point->data.z * vars->distance * vars->zoom;
		point = point->next;
	}
}

void	center(t_vars *vars)
{
	t_points	*point;
	int			x;
	int			y;

	x = (vars->width - vars->max.dx + vars->min.dx) / 2 - vars->min.dx;
	y = (vars->height - vars->max.dy + vars->min.dy) / 2 - vars->min.dy;
	point = vars->points;
	while (point)
	{
		point->data.dx += x;
		point->data.dy += y;
		point = point->next;
	}
}

// First point is start
void	update_display(t_vars *vars)
{
	if (!vars->id)
		return ;
	if (vars->img.id)
		mlx_destroy_image(vars->id, vars->img.id);
	isometrify(vars->points, vars->distance * vars->zoom, 30 * FDF_PI / 180);
	addz(vars);
	extremums_init(vars);
	center(vars);
	image_init(vars);
	render_points(vars);
	mlx_put_image_to_window(vars->id, vars->win, vars->img.id, 0, 0);
}
