/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:10:34 by vegret            #+#    #+#             */
/*   Updated: 2022/12/05 18:41:50 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	put_pixel_img(t_fdf_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->data + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}
