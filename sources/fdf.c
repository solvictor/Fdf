/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/12/01 22:03:04 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	link_points(int x0, int y0, int x1, int y1, t_vars *vars)
{
	int			e2;
	int			err;
	const int	dx = abs(x1 - x0);
	const int	dy = -abs(y1 - y0);
	const int	sx = -1 + 2 * (x0 < x1);
	const int	sy = -1 + 2 * (y0 < y1);

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

#define MIN_X 100
#define MIN_Y 500
#define DISTANCE 20

void	addz(t_point *point)
{
	point->dy -= point->z * DISTANCE;
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

static void	isometrify(t_points *points, int distance)
{
	int	x0;
	int	y0;
	int	lasty;
	int	lastx;

	x0 = MIN_X;
	lastx = MIN_X;
	y0 = MIN_Y;
	lasty = MIN_Y;
	while (points)
	{
		points->data.dx = x0 + 0.86602540378 * distance;
		points->data.dy = y0 - distance / 2;
		if (points->next && points->data.x != points->next->data.x)
		{
			lastx += 0.86602540378 * distance;
			lasty += distance / 2;
			x0 = lastx;
			y0 = lasty;
		}
		else
		{
			x0 = points->data.dx;
			y0 = points->data.dy;
		}
		points = points->next;
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

static void	compute_points(t_vars *vars)
{
	isometrify(vars->points, vars->distance);
	lstiter(vars->points, &addz); // trouver un autre moyen d'ajouter z
	init_extremums(vars);
}

static int	putpoints(t_vars *vars)
{
	t_points	*point;
	t_point		*tmp;

	point = vars->points;
	while (point)
	{
		mlx_pixel_put(
			vars->mlx,
			vars->win,
			point->data.dx,
			point->data.dy,
			point->data.color);
		tmp = get_point(point->data.x + 1, point->data.y, vars->points);
		if (tmp)
			link_points(tmp->dx, tmp->dy, point->data.dx, point->data.dy, vars);
		tmp = get_point(point->data.x, point->data.y + 1, vars->points);
		if (tmp)
			link_points(tmp->dx, tmp->dy, point->data.dx, point->data.dy, vars);
		point = point->next;
	}
	return (0);
}

static int	fdf_open(int argc, char *argv[])
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Usage : ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putendl_fd(" <filename>", 1);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("No file ", 1);
		ft_putendl_fd(argv[1], 1);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	fdf_init(int fd, t_vars *vars)
{
	vars->points = parse_map(fd);
	if (!vars->points)
		(ft_putendl_fd("No data found.", 1), exit(EXIT_FAILURE));
	vars->distance = 20;
	vars->width = MLX_WIDTH;
	vars->height = MLX_HEIGHT;
	compute_points(vars);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		(ft_putendl_fd("MLX initialization failed.", 1), exit(EXIT_FAILURE));
	vars->win = mlx_new_window(
			vars->mlx,
			vars->width,
			vars->height,
			"Fdf vegret");
	if (!vars->win)
		(ft_putendl_fd("Window creation failed.", 1), exit(EXIT_FAILURE));
}

static void	setup_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win, &key_listener, vars);
	mlx_mouse_hook(vars->win, &mouse_listener, vars);
	mlx_hook(vars->win, DestroyNotify, NoEventMask, &exit_fdf, vars);
}

/* TODO
Fdf
- abs not from math.h? remove all abs if so

Makefile
- Message quand ya nothing to do
- Changer les couleurs
*/
int	main(int argc, char *argv[])
{
	int		fd;
	t_vars	vars;

	fd = fdf_open(argc, argv);
	fdf_init(fd, &vars);
	mlx_pixel_put(vars.mlx, vars.win, vars.min.dx, vars.min.dy, 0x00FF0000);
	mlx_pixel_put(vars.mlx, vars.win, vars.max.dx, vars.max.dy, 0x00FF0000);
	setup_hooks(&vars);
	putpoints(&vars);
	mlx_loop(vars.mlx);
	return (EXIT_SUCCESS);
}
