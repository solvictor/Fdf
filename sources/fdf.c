/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/12/05 15:07:49 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

/* TODO
Fdf
- abs not from math.h? remove all abs if so
- utiliser une image de mlx pour ameliorer les perfs
- degrade entre les points
- taille de la fenetre adaptative
- centrer la figure
- norme

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
	mlx_key_hook(vars.win, &key_listener, &vars);
	mlx_mouse_hook(vars.win, &mouse_listener, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, &exit_fdf, &vars);
	putpoints(&vars);
	mlx_loop(vars.mlx);
	exit_fdf(&vars);
	return (EXIT_SUCCESS);
}
