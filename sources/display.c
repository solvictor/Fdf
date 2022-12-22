/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:07:29 by vegret            #+#    #+#             */
/*   Updated: 2022/12/22 16:52:25 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define RED		0xFF0000
#define GREEN	0x00FF00
#define BLUE	0x0000FF

static void	change_color(t_point *src, t_point *dst)
{
	if (src->color == dst->color)
		return ;
	if (((dst->color & RED) >> 16) > ((src->color & RED) >> 16))
		src->color += 1 << 16;
	else if ((src->color & RED) > 0)
		src->color -= 1 << 16;
	if (((dst->color & GREEN) >> 8) > ((src->color & GREEN) >> 8))
		src->color += 1 << 8;
	else if ((src->color & GREEN) > 0)
		src->color -= 1 << 8;
	if ((dst->color & BLUE) > (src->color & BLUE))
		src->color += 1;
	else if ((src->color & BLUE) > 0)
		src->color -= 1;
}

static int	is_out(t_vars *vars, t_point *v0, t_point *v1)
{
	if ((v0->dx < 0 && v1->dx < 0)
		|| (v0->dx >= vars->width && v1->dx >= vars->width))
		return (1);
	if ((v0->dy < 0 && v1->dy < 0)
		|| (v0->dy >= vars->height && v1->dy >= vars->height))
		return (1);
	return (0);
}

static void	link_points(t_point src, t_point dst, t_vars *vars)
{
	double			e2;
	double			err;
	const double	dx = dabs(dst.dx - src.dx);
	const double	dy = -dabs(dst.dy - src.dy);

	err = dx + dy;
	while (1)
	{
		put_pixel_img(&vars->img, src.dx, src.dy, src.color);
		if (dabs(src.dx - dst.dx) <= 1 && dabs(src.dy - dst.dy) <= 1)
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
		change_color(&src, &dst);
	}
}

static int	render_points(t_vars *vars)
{
	t_point	*point;

	point = vars->points;
	while (point)
	{
		if (point->nextx && !is_out(vars, point, point->nextx))
			link_points(*point->nextx, *point, vars);
		if (point->nexty && !is_out(vars, point, point->nexty))
			link_points(*point->nexty, *point, vars);
		point = point->next;
	}
	return (0);
}

static void	addz(t_vars *vars)
{
	t_point	*point;

	point = vars->points;
	while (point)
	{
		point->dy -= point->z * vars->zhight * vars->zoom;
		point = point->next;
	}
}

//void	project2(t_vars *vars)
//{
//	t_point			*points;
//	t_point			*tmp;
//	const double	angles[3] = {sin(vars->proj.angle1) * DISTANCE * vars->zoom,
//		sin(vars->proj.angle2) * DISTANCE * vars->zoom,
//		cos(vars->proj.angle2) * DISTANCE * vars->zoom};

//	points = vars->points;
//	while (points)
//	{
//		tmp = points;
//		while (tmp)
//		{
//			tmp->dx = (tmp->dx) + tmp->dy * angles[2];
//			tmp->dy = (tmp->dy);
//			//tmp->dx = 20 + tmp->x * 20;
//			//tmp->dy = 20 + tmp->y * 20;
//			tmp = tmp->nextx;
//		}
//		points = points->nexty;
//	}
//}

void	update_display(t_vars *vars)
{
	if (!vars->id)
		return ;
	if (vars->img.id)
		mlx_destroy_image(vars->id, vars->img.id);
	if (vars->proj.f)
		vars->proj.f(vars);
	rotate(vars->points, vars->rotation * M_PI / 180);
	addz(vars);
	extremums_init(vars);
	center(vars, vars->center.dx, vars->center.dy);
	project(vars);
	image_init(vars);
	render_points(vars);
	mlx_put_image_to_window(vars->id, vars->win, vars->img.id, 0, 0);
	show_controls(vars);
}
