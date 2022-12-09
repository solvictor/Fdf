/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:02:44 by vegret            #+#    #+#             */
/*   Updated: 2022/12/09 13:53:42 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	extremums_init(t_vars *vars)
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

void	image_init(t_vars *vars)
{
	vars->img.width = vars->width;
	vars->img.height = vars->height;
	vars->img.id = mlx_new_image(vars->id, vars->img.width, vars->img.height);
	if (!vars->img.id)
		(ft_putendl_fd("Image creation failed.", 1), clean_exit(vars, 0));
	vars->img.data = mlx_get_data_addr(
			vars->img.id,
			&vars->img.bpp,
			&vars->img.line_size,
			&vars->img.endian);
}

void	init_fdf(int fd, t_vars *vars)
{
	vars->points = parse_map(fd);
	close(fd);
	if (!vars->points)
		(ft_putendl_fd("No data found.", 1), clean_exit(vars, 0));
	vars->distance = 20;
	vars->zoom = 1;
	vars->id = mlx_init();
	if (!vars->id)
		(ft_putendl_fd("MLX initialization failed.", 1), clean_exit(vars, 0));
	mlx_get_screen_size(vars->id, &vars->width, &vars->height);
	vars->win = mlx_new_window(
			vars->id,
			vars->width,
			vars->height - 140,
			"Fdf vegret");
	vars->center.dx = vars->width / 2;
	vars->center.dy = vars->height / 2;
	if (!vars->win)
		(ft_putendl_fd("Window creation failed.", 1), clean_exit(vars, 0));
	update_display(vars);
}
