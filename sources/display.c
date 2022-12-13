/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:07:29 by vegret            #+#    #+#             */
/*   Updated: 2022/12/13 22:19:29 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	get_color(t_point *src, t_point *dst)
{
	const unsigned int	color = 0;
	const int			n = ft_abs(src->color - dst->color);

	if (src->color == dst->color)
		return (src->color);
	
	return (src->color);
}

static void	link_points(t_point src, t_point dst, t_vars *vars)
{
	int				e2;
	int				err;
	const int		dx = ft_abs(dst.dx - src.dx);
	const int		dy = -ft_abs(dst.dy - src.dy);

	err = dx + dy;
	while (1)
	{
		put_pixel_img(&vars->img, src.dx, src.dy, get_color(&src, &dst));
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

static int	render_points(t_vars *vars)
{
	t_points	*point;
	t_point		*tmp;

	point = vars->points;
	while (point)
	{
		tmp = point->nextx;
		if (tmp)
			link_points(*tmp, point->data, vars);
		tmp = point->nexty;
		if (tmp)
			link_points(*tmp, point->data, vars);
		point = point->next;
	}
	return (0);
}

static void	isometric(t_points *points, double distance, double angle)
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

static void	addz(t_vars *vars)
{
	t_points	*point;

	point = vars->points;
	while (point)
	{
		point->data.dy -= point->data.z * DISTANCE * vars->zoom;
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
	isometric(vars->points, DISTANCE * vars->zoom, 30 * M_PI / 180);
	rotate(vars->points, &vars->center, vars->rotation * M_PI / 180);
	addz(vars);
	extremums_init(vars);
	center(vars, vars->center.dx, vars->center.dy);
	image_init(vars);
	render_points(vars);
	mlx_put_image_to_window(vars->id, vars->win, vars->img.id, 0, 0);
	display_controls(vars);
}
