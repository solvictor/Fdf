/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:10:34 by vegret            #+#    #+#             */
/*   Updated: 2022/12/13 18:19:39 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_img(t_fdf_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->data + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

void	display_controls(t_vars *vars)
{
	mlx_string_put(vars->id, vars->win, 0, 10, 0x00FFFFFF,
		"Controls:");
	mlx_string_put(vars->id, vars->win, 0, 10, 0x00FFFFFF,
		"________");
	mlx_string_put(vars->id, vars->win, 0, 22, 0x00FFFFFF,
		"- W A S D, move");
	mlx_string_put(vars->id, vars->win, 0, 34, 0x00FFFFFF,
		"- R, rotate");
	mlx_string_put(vars->id, vars->win, 0, 46, 0x00FFFFFF,
		"- P, change projection");
	mlx_string_put(vars->id, vars->win, 0, 58, 0x00FFFFFF,
		"- Mouse wheel, zoom");
}

t_point	*get_point(int x, int y, t_points *list)
{
	while (list)
	{
		if (list->data.x == x && list->data.y == y)
			return (&list->data);
		list = list->next;
	}
	return (NULL);
}
