/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/11/26 18:24:38 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_x(t_point point)
{
	double	x;
	double	a;
	double	s;

	s = 1;
	a = 0.8944;
	x = (point.x - point.z) * a * s;
	return ((int) round(x));
}

static int	get_y(t_point point)
{
	double	y;
	double	a;
	double	b;

	b = M_PI / 4;
	a = M_PI / 4;
	y = (point.x + point.z) * 0.4472;
	return ((int) round(y));
}

#define DISTANCE 25

static void	link_points(int x1, int y1, int x2, int y2, t_vars *vars)
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	eps;

	dx = x2 - x1;
	dy = y2 - y1;
	y = y1;
	x = x1;
	eps = 0;
	while (x <= x2)
	{
		mlx_pixel_put(vars->mlx, vars->win, x, y, DEFAULT_POINT_COLOR);
		eps += dy;
		if ((eps << 1) >= dx)
		{
			y++;
			eps -= dx;
		}
		x++;
	}
}

static int	putpoints(t_vars *vars)
{
	t_points	*point;
	int			x;
	int			y;
	int			x2;
	int			y2;

	point = vars->points;
	int min_x = 40;
	int min_y = 40;
	while (point)
	{
		//x = get_x(point->data);
		//y = get_y(point->data);
		x = point->data.x + (x * DISTANCE) + min_x;
		y = point->data.y + (y * DISTANCE) + min_y;
		if (point->next)
		{
			x2 = point->next->data.x;
			y2 = point->next->data.y;
			x2 += x2 * DISTANCE;
			y2 += y2 * DISTANCE;
			link_points(x, y, x2 + min_x, y2 + min_y, vars);
		}
		//mlx_pixel_put(vars->mlx, vars->win, x + (x * DISTANCE) + min_x, y + (y * DISTANCE) + min_y, point->data.color);
		point = point->next;
	}
	return (0);
}

//static void	printtest(t_point content)
//{
//	printf(
//		"x: %d y: %d z: %d color: %x\n",
//		content.x,
//		content.y,
//		content.z,
//		content.color);
//}

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
	fd = open(argv[1], O_RDONLY);
	vars.points = parse_map(fd);
	if (!vars.points)
		return (1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, MLX_WIDTH, MLX_HEIGHT, "Fdf vegret");
	putpoints(&vars);
	//t_point a = {MLX_WIDTH / 2, MLX_HEIGHT / 2, 0};
	//t_point b = {MLX_WIDTH, MLX_HEIGHT, 0};
	//link_points(a, b, &vars);

	mlx_key_hook(vars.win, &key_listener, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, &exit_fdf, &vars);
	mlx_mouse_hook(vars.win, &mouse_listener, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
