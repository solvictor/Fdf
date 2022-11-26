/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:59:00 by vegret            #+#    #+#             */
/*   Updated: 2022/11/26 05:41:09 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_listener(int key, void *p)
{
	if (key == XK_Escape)
		exit_fdf(p);
	printf("KEY\n%d (%c)\n\n", key, key);
	return (0);
}

int	test_listener(void *p)
{
	t_vars	*vars;

	vars = (t_vars *) p;
	printf("TEST_LISTENER\nMlx: %p Window: %p\n\n", vars->mlx, vars->win);
	return (0);
}

int	mouse_listener(int button, int x, int y, void *p)
{
	t_vars	*vars;

	vars = (t_vars *) p;
	printf("MOUSE\nbutton: %d x: %d y: %d\n\n", button, x, y);
	if (button == Button1)
		mlx_pixel_put(vars->mlx, vars->win, x, y, 0xffffff);
	return (0);
}
