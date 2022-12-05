/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:02:44 by vegret            #+#    #+#             */
/*   Updated: 2022/12/05 15:59:20 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define MIN_X 1
#define MIN_Y 331
#define DISTANCE 20

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	corrector(t_point *point)
{
	point->dy += MIN_Y;
	point->dx += MIN_X;
	point->dy -= point->z * DISTANCE;
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

static void	init_extremums(t_vars *vars)
{
	t_points	*list;

	vars->min.dx = -1;
	vars->min.dy = -1;
	vars->max.dx = -1;
	vars->max.dy = -1;
	list = vars->points;
	while (list)
	{
		if (vars->min.dx == -1 || list->data.dx < vars->min.dx)
			vars->min.dx = list->data.dx;
		if (vars->min.dy == -1 || list->data.dy < vars->min.dy)
			vars->min.dy = list->data.dy;
		if (vars->max.dx == -1 || list->data.dx > vars->max.dx)
			vars->max.dx = list->data.dx;
		if (vars->max.dy == -1 || list->data.dy > vars->max.dy)
			vars->max.dy = list->data.dy;
		list = list->next;
	}
}

void	fdf_init(int fd, t_vars *vars)
{
	vars->points = parse_map(fd);
	if (!vars->points)
		(ft_putendl_fd("No data found.", 1), clean_exit(vars, 0));
	vars->distance = 20;
	isometrify(vars->points, vars->distance, 50 * FDF_PI / 180);
	lstiter(vars->points, &corrector);
	init_extremums(vars);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		(ft_putendl_fd("MLX initialization failed.", 1), clean_exit(vars, 0));
	mlx_get_screen_size(vars->mlx, &vars->width, &vars->height);
	//vars->width = ft_min(abs(vars->max.dx - vars->min.dx) + 3, vars->width);
	//vars->height = ft_min(abs(vars->max.dy - vars->min.dy) + 3, vars->height);
	vars->img = mlx_new_image(vars->mlx, vars->width, vars->height);
	if (!vars->img)
		(ft_putendl_fd("Image creation failed.", 1), clean_exit(vars, 0));
	vars->win = mlx_new_window(
			vars->mlx,
			vars->width,
			vars->height,
			"Fdf vegret");
	if (!vars->win)
		(ft_putendl_fd("Window creation failed.", 1), clean_exit(vars, 0));
}