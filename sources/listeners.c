/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:59:00 by vegret            #+#    #+#             */
/*   Updated: 2022/12/13 22:19:50 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_move(int key, t_vars *vars)
{
	if (key == XK_w)
		vars->center.dy -= 20;
	else if (key == XK_a)
		vars->center.dx -= 20;
	else if (key == XK_s)
		vars->center.dy += 20;
	else if (key == XK_d)
		vars->center.dx += 20;
	else if (key == XK_r)
	{
		vars->rotation += 2;
		if (vars->rotation == 360)
			vars->rotation = 0;
	}
	else if (key == XK_p)
	{
		//vars->projection;
		update_display(vars);
	}
	else
		return ;
	update_display(vars);
}

int	key_listener(int key, void *p)
{
	t_vars	*vars;

	vars = (t_vars *) p;
	if (key == XK_Escape)
		destroy_listener(p);
	handle_move(key, vars);
	printf("KEY\n%d (%c)\n\n", key, key);
	return (0);
}

// Button 4 zoom in, 5 zoom out
int	mouse_listener(int button, int x, int y, void *p)
{
	t_vars	*vars;

	vars = (t_vars *) p;
	if (button == 4 && vars->zoom < 20)
	{
		vars->zoom += 0.1;
		update_display(vars);
	}
	else if (button == 5 && vars->zoom > 0.2)
	{
		vars->zoom -= 0.1;
		update_display(vars);
	}
	printf("MOUSE\nbutton: %d x: %d y: %d\n\n", button, x, y);
	return (0);
}

int	destroy_listener(void *p)
{
	clean_exit((t_vars *) p, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
