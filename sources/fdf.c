/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/11/29 17:56:53 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	link_points(int x0, int y0, int x1, int y1, t_vars *vars)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	e2;
	int	err;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_pixel_put(vars->mlx, vars->win, x0, y0, DEFAULT_POINT_COLOR);
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

#define MIN_X 300
#define MIN_Y 300
#define DISTANCE 20

void	calibrate(t_point *point)
{
	point->x = point->x * DISTANCE + MIN_X;
	point->y = point->y * DISTANCE + MIN_Y;
}

static void	printtest(t_point *content)
{
	printf(
		"x: %d y: %d z: %d color: %x\n",
		content->x,
		content->y,
		content->z,
		content->color);
}

static void	get_coords(int x0, int y0, t_point *point)
{
	point->x = x0 + 0.86602540378 * DISTANCE;
	point->y = y0 + DISTANCE / 2;
}

static void	make_x(t_points *points)
{
	t_points	*point;
	t_points	*tmp;
	int			x0;
	int			y0;
	int			currx;
	int			i;

	x0 = MIN_X;
	currx = MIN_X;
	y0 = MIN_Y;
	point = points;
	i = 1;
	while (point)
	{
		get_coords(x0, y0, point);
		if (point->next && point->next->data.x != currx)
		{
			currx = point->next->data.x;
			x0 = MIN_X;
			y0 = MIN_Y;
			i++;
		}
		else
		{
			x0 = point->data.x;
			y0 = point->data.y;
		}
		point = point->next;
	}
}

static int	putpoints(t_vars *vars)
{
	t_points	*point;
	t_points	*tmp;

	lstiter(vars->points, &calibrate);
	make_x(vars->points);
	lstiter(vars->points, &printtest);
	point = vars->points;
	while (point)
	{
		mlx_pixel_put(vars->mlx, vars->win, point->data.x, point->data.y, DEFAULT_POINT_COLOR);
		//if (point->next /*&& point->next->data.x == point->data.x*/)
		//	link_points(point->next->data.x, point->next->data.y, point->data.x, point->data.y, vars);
		//tmp = point->next;
		//while (tmp)
		//{
		//	if (tmp->data.y == point->data.y)
		//		link_points(tmp->data.x, tmp->data.y, point->data.x, point->data.y, vars);
		//	tmp = tmp->next;
		//}
		point = point->next;
	}
	return (0);
}

/* TODO
Makefile
- message quand ya nothing to do
- Changer les couleurs
*/
int	main(int argc, char *argv[])
{
	int		fd;
	t_vars	vars;

	if (argc != 2)
	{
		ft_putstr_fd("Usage : ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putendl_fd(" <filename>", 1);
		return (1);
	}
	// Check if path endswith .fdf
	fd = open(argv[1], O_RDONLY);
	vars.points = parse_map(fd);
	if (!vars.points)
		return (1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, MLX_WIDTH, MLX_HEIGHT, "Fdf vegret");
	putpoints(&vars);
	mlx_key_hook(vars.win, &key_listener, &vars);
	mlx_hook(vars.win, DestroyNotify, NoEventMask, &exit_fdf, &vars);
	mlx_mouse_hook(vars.win, &mouse_listener, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
