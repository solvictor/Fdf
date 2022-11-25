/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:15 by vegret            #+#    #+#             */
/*   Updated: 2022/11/26 00:03:53 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	lstiter(t_points *lst, void (*f)(t_point content))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

/* TODO
Makefile
- enlever les messages quand il va et quitte libft
- message quand ya nothing to do
- Changer les couleurs
*/
int	main(int argc, char const *argv[])
{
	int			fd;
	t_points	*points;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	points = parse_map(fd);
	if (!points)
		return (1);
	pointsclear(&points);
	return (0);
}
