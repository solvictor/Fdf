/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:56 by vegret            #+#    #+#             */
/*   Updated: 2022/12/06 18:47:04 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# define DEFAULT_POINT_COLOR	0x00FFFFFF
# define FDF_PI					3.14159265358979323846

/*
x: Line
y: Column
z: Height
dx: Display x
dy: Display y
*/
typedef struct s_point {
	int				x;
	int				y;
	int				z;
	int				dx;
	int				dy;
	unsigned int	color;
}				t_point;

typedef struct s_points {
	t_point			data;
	struct s_points	*next;
}				t_points;

typedef struct s_fdf_img {
	void	*id;
	char	*data;
	int		bpp;
	int		width;
	int		height;
	int		endian;
	int		line_size;
}				t_fdf_img;

typedef struct s_vars {
	void		*id;
	void		*win;
	int			distance;
	int			height;
	int			width;
	t_point		min;
	t_point		max;
	t_fdf_img	img;
	t_points	*points;
}				t_vars;

int			test_listener(void *p);
int			key_listener(int key, void *p);
int			mouse_listener(int button, int x, int y, void *p);
int			destroy_listener(void *p);
int			render_points(t_vars *vars);
void		pointsclear(t_points **lst);
void		clean_exit(t_vars *vars, int status);
void		init_fdf(int fd, t_vars *vars);
t_points	*parse_map(int fd);
t_points	*new_point(int x, int y);
char		*uppercase(char *str);
void		image_init(t_vars *vars);
void		update_display(t_vars *vars);
void		isometrify(t_points *points, int distance, double angle);
void		init_extremums(t_vars *vars);
void		put_pixel_img(t_fdf_img *img, int x, int y, unsigned int color);

#endif