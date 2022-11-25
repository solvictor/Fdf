/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/11/25 17:48:47 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	printtest(void *content)
{
	t_point	*point;

	point = (t_point *) content;
	if (point)
	{
		printf("%d", point->z);
	}
	else
		printf("NULL");
}

/* TODO
Makefile
- enlever les messages quand il va et quitte libft
- message quand ya nothing to do
- Changer les couleurs
*/
int	main(int argc, char const *argv[])
{
	int		fd;
	t_list	*points;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	points = parse_map(fd);
	if (!points)
		return (1);
	ft_lstiter(points, printtest);
	return (0);
}
