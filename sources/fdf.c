/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/12/15 12:59:51 by vegret           ###   ########.fr       */
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
- degrade entre les points
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
	vars.id = NULL;
	vars.img.id = NULL;
	vars.win = NULL;
	vars.title = NULL;
	fdf_init(fd, argv[1], &vars);
	mlx_mouse_hook(vars.win, &on_mouse, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, &on_destroy, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, &on_key, &vars);
	mlx_loop(vars.id);
	clean_exit(&vars, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
