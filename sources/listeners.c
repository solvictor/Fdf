/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:59:00 by vegret            #+#    #+#             */
/*   Updated: 2022/12/19 16:15:40 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_move(int key, t_vars *vars)
{
	if (key == XK_w)
		vars->center.dy += 20;
	else if (key == XK_a)
		vars->center.dx += 20;
	else if (key == XK_s)
		vars->center.dy -= 20;
	else if (key == XK_d)
		vars->center.dx -= 20;
	else if (key == XK_r)
	{
		if (vars->rotation == 360)
			vars->rotation = -2;
		vars->rotation += 2;
	}
	else if (key == XK_l)
	{
		if (vars->rotation == 0)
			vars->rotation = 360;
		vars->rotation -= 2;
	}
	else if (key == XK_p)
		update_projection(vars);
	else
		return ;
	update_display(vars);
}

int	on_key(int key, void *p)
{
	t_vars	*vars;

	vars = (t_vars *) p;
	handle_move(key, vars);
	if (key == XK_Escape)
		on_destroy(p);
	else if (key == XK_equal)
		vars->zhight++;
	else if (key == XK_minus)
		vars->zhight--;
	else
		return (0);
	update_display(vars);
	return (0);
}

int	on_mouse(int button, int x, int y, void *p)
{
	t_vars	*vars;

	(void) x, (void) y;
	vars = (t_vars *) p;
	if (button == 4 && vars->zoom < 20)
		vars->zoom += 0.1;
	else if (button == 5 && vars->zoom > 0.2)
		vars->zoom -= 0.1;
	else
		return (0);
	update_display(vars);
	return (0);
}

int	on_destroy(void *p)
{
	clean_exit((t_vars *) p, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
