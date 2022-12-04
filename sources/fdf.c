/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/12/04 23:46:48 by vegret           ###   ########.fr       */
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
	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = -1 + 2 * (x0 < x1);
	sy = -1 + 2 * (y0 < y1);
	err = dx + dy;
	while (1)
	{
		mlx_pixel_put(vars->mlx, vars->win, x0, y0, color);
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

void	corrector(t_point *point)
{
	point->dy += MIN_Y;
	point->dx += MIN_X;
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

static int	putpoints(t_vars *vars)
{
	t_points	*point;
	t_point		*tmp;

	point = vars->points;
	while (point)
	{
		tmp = get_point(point->data.x + 1, point->data.y, vars->points);
		if (tmp)
			link_points(tmp, point, vars);
		tmp = get_point(point->data.x, point->data.y + 1, vars->points);
		if (tmp)
			link_points(tmp, point, vars);
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

static void	fdf_init(int fd, t_vars *vars)
{
	vars->points = parse_map(fd);
	if (!vars->points)
		(ft_putendl_fd("No data found.", 1), exit(EXIT_FAILURE));
	vars->distance = 20;
	vars->width = MLX_WIDTH;
	vars->height = MLX_HEIGHT;
	isometrify(vars->points, vars->distance, 30 * FDF_PI / 180);
	lstiter(vars->points, &corrector);
	init_extremums(vars);
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
	mlx_hook(vars->win, DestroyNotify, StructureNotifyMask, &exit_fdf, vars);
}

/* TODO
Fdf
- abs not from math.h? remove all abs if so
- utiliser une image de mlx pour ameliorer les perfs
- degrade entre les points
- taille de la fenetre adaptative
- centrer la figure

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
	exit_fdf(&vars);
	return (EXIT_SUCCESS);
}
