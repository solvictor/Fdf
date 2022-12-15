/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:07:29 by vegret            #+#    #+#             */
/*   Updated: 2022/12/15 15:49:03 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	get_color(t_point *src, t_point *dst)
{
	unsigned int		color;
	const int			sr = (src->color & 0xFF0000) >> 16;
	const int			sg = (src->color & 0xFF00) >> 8;
	const int			sb = (src->color & 0xFF);
	const int			dr = (dst->color & 0xFF0000) >> 16;
	const int			dg = (dst->color & 0xFF00) >> 8;
	const int			db = (dst->color & 0xFF);

	if (src->color == dst->color)
		return (src->color);
	color = 0;
	color |= (sr + dr) / 2 << 16;
	color |= (sg + dg) / 2 << 8;
	color |= (sb + db) / 2;
	return (color);
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
		point->dy -= point->z * DISTANCE * vars->zoom;
		point = point->next;
	}
}

void	update_display(t_vars *vars)
{
	if (!vars->id)
		return ;
	if (vars->img.id)
		mlx_destroy_image(vars->id, vars->img.id);
	if (vars->projection.f)
		vars->projection.f(vars);
	rotate(vars->points, &vars->center, vars->rotation * M_PI / 180);
	addz(vars);
	extremums_init(vars);
	printf("%d %d\n", vars->center.dx, vars->center.dy);
	center(vars, vars->center.dx, vars->center.dy);
	image_init(vars);
	render_points(vars);
	mlx_put_image_to_window(vars->id, vars->win, vars->img.id, 0, 0);
	show_controls(vars);
}
