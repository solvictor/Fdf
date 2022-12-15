/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:56 by vegret            #+#    #+#             */
/*   Updated: 2022/12/15 12:56:02 by vegret           ###   ########.fr       */
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
# define DISTANCE 20.0

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
	struct s_point	*next;
	struct s_point	*nextx;
	struct s_point	*nexty;
}				t_point;

typedef struct s_fdf_img {
	void	*id;
	char	*data;
	int		bpp;
	int		width;
	int		height;
	int		endian;
	int		line_size;
}				t_fdf_img;

typedef struct s_projection {
	char	*name;
	void	(*f)(void *);
	double	angle1;
	double	angle2;
}				t_projection;

typedef struct s_vars {
	void			*id;
	void			*win;
	char			*title;
	int				rotation;
	int				width;
	int				height;
	double			zoom;
	t_point			min;
	t_point			max;
	t_point			center;
	t_point			*points;
	t_fdf_img		img;
	t_projection	projection;
}				t_vars;

char			*uppercase(char *str);
t_point			*parse_map(int fd);
t_point			*new_point(int x, int y);
t_point			*get_point(int x, int y, t_point *list);
int				ft_abs(int n);
void			pointsclear(t_point **lst);
void			show_controls(t_vars *vars);
void			update_display(t_vars *vars);
void			clean_exit(t_vars *vars, int status);
void			put_pixel_img(t_fdf_img *img, int x, int y, unsigned int color);
void			rotate(t_point *points, t_point *center, double angle);
void			center(t_vars *vars, int x, int y);

/* Initialisers */
void			image_init(t_vars *vars);
void			extremums_init(t_vars *vars);
void			fdf_init(int fd, char *file_name, t_vars *vars);

/* Listeners */
int				on_destroy(void *p);
int				on_key(int key, void *p);
int				on_mouse(int button, int x, int y, void *p);

/* Projections stuff */
void			project(t_vars *vars);
void			update_projection(t_vars *vars);
t_projection	new_proj(
					char *name, void (*f)(t_vars *),
					double angle1, double angle2
					);

#endif