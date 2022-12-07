/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:07:29 by vegret            #+#    #+#             */
/*   Updated: 2022/12/07 15:38:56 by vegret           ###   ########.fr       */
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
	dx = ft_abs(x1 - x0);
	dy = -ft_abs(y1 - y0);
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

void	isometrify(t_points *points, int distance, double angle)
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

void	center(t_vars *vars)
{
	t_points	*point;

	point = vars->points;
	while (point)
	{
		point->data.dx += -vars->min.dx;
		point->data.dy += -vars->min.dy;
		point = point->next;
	}
}

void	addz(t_vars *vars)
{
	t_points	*point;

	point = vars->points;
	while (point)
	{
		point->data.dy -= point->data.z * vars->distance;
		point = point->next;
	}
}

#define MIN_X 1
#define MIN_Y 331

// First point is start
void	update_display(t_vars *vars)
{
	if (!vars->id)
		return ;
	if (vars->img.id)
		mlx_destroy_image(vars->id, vars->img.id);
	isometrify(vars->points, vars->distance, 30 * FDF_PI / 180);
	addz(vars);
	extremums_init(vars);
	center(vars);
	extremums_init(vars);
	image_init(vars);
	render_points(vars);
	put_pixel_img(&vars->img, vars->min.dx, vars->min.dy, 0x00FF0000);
	put_pixel_img(&vars->img, vars->max.dx, vars->max.dy, 0x00FF0000);
	mlx_put_image_to_window(vars->id, vars->win, vars->img.id, 0, 0);
}
