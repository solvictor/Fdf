/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:02:44 by vegret            #+#    #+#             */
/*   Updated: 2022/12/06 17:08:15 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define MIN_X 1
#define MIN_Y 331

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

// First point is start
void	init_fdf(int fd, t_vars *vars)
{
	vars->points = parse_map(fd);
	if (!vars->points)
		(ft_putendl_fd("No data found.", 1), clean_exit(vars, 0));
	vars->distance = 20;
	vars->points->data.dx = MIN_X;
	vars->points->data.dy = MIN_Y;
	vars->id = mlx_init();
	if (!vars->id)
		(ft_putendl_fd("MLX initialization failed.", 1), clean_exit(vars, 0));
	mlx_get_screen_size(vars->id, &vars->width, &vars->height);
	//vars->width = ft_min(ft_abs(vars->max.dx - vars->min.dx) + 3, vars->width);
	//vars->height = ft_min(ft_abs(vars->max.dy - vars->min.dy) + 3, vars->height);
	vars->win = mlx_new_window(
			vars->id,
			vars->width,
			vars->height,
			"Fdf vegret");
	if (!vars->win)
		(ft_putendl_fd("Window creation failed.", 1), clean_exit(vars, 0));
	update_display(vars);
}
