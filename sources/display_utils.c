/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:10:34 by vegret            #+#    #+#             */
/*   Updated: 2022/12/16 18:47:27 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WHITE 0x00FFFFFF

void	put_pixel_img(t_fdf_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->data + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

void	show_controls(t_vars *vars)
{
	mlx_string_put(vars->id, vars->win, 0, 10, WHITE, "Controls:");
	mlx_string_put(vars->id, vars->win, 0, 12, WHITE, "________");
	mlx_string_put(vars->id, vars->win, 0, 24, WHITE, "- W A S D, move");
	mlx_string_put(vars->id, vars->win, 0, 36, WHITE, "- L R, rotate");
	mlx_string_put(vars->id, vars->win, 0, 48, WHITE,
		"- + -, change z axis multiplier");
	mlx_string_put(vars->id, vars->win, 0, 60, WHITE,
		"- P, change projection (current: ");
	mlx_string_put(vars->id, vars->win, 196, 60, WHITE, vars->proj.name);
	mlx_string_put(vars->id, vars->win, 0, 72, WHITE, "- Mouse wheel, zoom");
}

t_point	*get_point(int x, int y, t_point *points)
{
	while (points)
	{
		if (points->x == x && points->y == y)
			return (points);
		points = points->next;
	}
	return (NULL);
}

void	center(t_vars *vars, int x, int y)
{
	t_point	*point;

	y = y - (vars->max.dy - vars->min.dy) / 2 - vars->min.dy;
	x = x - (vars->max.dx - vars->min.dx) / 2 - vars->min.dx;
	point = vars->points;
	while (point)
	{
		point->dx += x;
		point->dy += y;
		point = point->next;
	}
}

void	rotate(t_point *points, t_point *center, double angle)
{
	double	x;
	double	y;

	while (points)
	{
		x = points->dx;
		y = points->dy;
		points->dx = (x - center->dx) * cos(angle)
			- (y - center->dy) * sin(angle) + center->dx;
		points->dy = (x - center->dx) * sin(angle)
			+ (y - center->dy) * cos(angle) + center->dy;
		points = points->next;
	}
}
