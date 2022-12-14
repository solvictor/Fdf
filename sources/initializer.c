/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:02:44 by vegret            #+#    #+#             */
/*   Updated: 2022/12/14 18:56:57 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	extremums_init(t_vars *vars)
{
	t_point	*points;

	vars->min.dx = -1;
	vars->min.dy = -1;
	vars->max.dx = -1;
	vars->max.dy = -1;
	points = vars->points;
	while (points)
	{
		if (vars->min.dx == -1 || points->dx < vars->min.dx)
			vars->min.dx = points->dx;
		if (vars->min.dy == -1 || points->dy < vars->min.dy)
			vars->min.dy = points->dy;
		if (vars->max.dx == -1 || points->dx > vars->max.dx)
			vars->max.dx = points->dx;
		if (vars->max.dy == -1 || points->dy > vars->max.dy)
			vars->max.dy = points->dy;
		points = points->next;
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

void	fdf_init(int fd, t_vars *vars)
{
	vars->points = parse_map(fd);
	close(fd);
	if (!vars->points || !vars->title)
		(ft_putendl_fd("No data found.", 1), clean_exit(vars, 0));
	vars->zoom = 1;
	vars->rotation = 0;
	vars->projection = new_proj("Isometric)", &project, 30, 30);
	vars->id = mlx_init();
	if (!vars->id)
		(ft_putendl_fd("MLX initialization failed.", 1), clean_exit(vars, 0));
	mlx_get_screen_size(vars->id, &vars->width, &vars->height);
	vars->height -= 140;
	vars->win = mlx_new_window(
			vars->id,
			vars->width,
			vars->height,
			vars->title);
	vars->center.dx = vars->width / 2;
	vars->center.dy = vars->height / 2;
	if (!vars->win)
		(ft_putendl_fd("Window creation failed.", 1), clean_exit(vars, 0));
	update_display(vars);
}
