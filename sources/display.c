/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:07:29 by vegret            #+#    #+#             */
/*   Updated: 2022/12/16 19:08:29 by vegret           ###   ########.fr       */
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

static void	link_points(t_point src, t_point dst, t_vars *vars)
{
	int				e2;
	int				err;
	const int		dx = ft_abs(dst.dx - src.dx);
	const int		dy = -ft_abs(dst.dy - src.dy);

	err = dx + dy;
	while (1)
	{
		put_pixel_img(&vars->img, src.dx, src.dy, src.color);
		if (round(src.dx) == round(dst.dx) && round(src.dy) == round(dst.dy))
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
	t_point	*tmp;

	point = vars->points;
	while (point)
	{
		tmp = point->nextx;
		if (tmp)
			link_points(*tmp, *point, vars);
		tmp = point->nexty;
		if (tmp)
			link_points(*tmp, *point, vars);
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

void	update_display(t_vars *vars)
{
	if (!vars->id)
		return ;
	if (vars->img.id)
		mlx_destroy_image(vars->id, vars->img.id);
	if (vars->proj.f)
		vars->proj.f(vars);
	rotate(vars->points, &vars->center, vars->rotation * M_PI / 180);
	addz(vars);
	extremums_init(vars);
	center(vars, vars->center.dx, vars->center.dy);
	image_init(vars);
	render_points(vars);
	mlx_put_image_to_window(vars->id, vars->win, vars->img.id, 0, 0);
	show_controls(vars);
}
