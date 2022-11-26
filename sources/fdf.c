/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/11/26 16:07:36 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_x(t_point point)
{
	double	x;
	double	b;

	b = M_PI / 4;
	x = cos(b) * point.x
		- sin(b) * point.z;
	return ((int) round(x));
}

static int	get_y(t_point point)
{
	double	y;
	double	a;
	double	b;

	b = M_PI / 4;
	a = M_PI / 4;
	y = sin(a) * sin(b) * point.x
		+ cos(a) * point.y
		+ sin(a) * cos(b) * point.z;
	return ((int) round(y));
}

static int	putpoints(t_vars *vars)
{
	t_points	*point;
	int			x;
	int			y;

	point = vars->points;
	while (point)
	{
		x = get_x(point->data) * DISTANCE;
		y = get_y(point->data) * DISTANCE;
		//ft_putstr_fd("(", 1);
		//ft_putnbr_fd(x, 1);
		//ft_putstr_fd(", ", 1);
		//ft_putnbr_fd(y, 1);
		//ft_putendl_fd(")", 1);
		mlx_pixel_put(vars->mlx, vars->win, x, y, point->data.color);
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
- enlever les messages quand il va et quitte libft
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
	mlx_key_hook(vars.win, &key_listener, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, &exit_fdf, &vars);
	mlx_mouse_hook(vars.win, &mouse_listener, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
