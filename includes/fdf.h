/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:56 by vegret            #+#    #+#             */
/*   Updated: 2022/12/19 13:57:11 by vegret           ###   ########.fr       */
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
# define DISTANCE 16.0

/*	t_point:	Stores a point

	x:			Line
	y:			Column
	z:			Height
	dx:			Display x
	dy:			Display y
	color:		RGB color
	next:		Next point in the list
	nextx:		Poit at x + 1 coordinates
	nexty:		Poit at y + 1 coordinates
*/
typedef struct s_point {
	int				x;
	int				y;
	int				z;
	double			dx;
	double			dy;
	unsigned int	color;
	struct s_point	*next;
	struct s_point	*nextx;
	struct s_point	*nexty;
}				t_point;

/*	t_fdf_img:	Stores the image the map is written in

	id:			MLX image instance
	data:		Image pixel informations
	bpp:		Bits per pixels
*/
typedef struct s_fdf_img {
	void	*id;
	char	*data;
	int		bpp;
	int		width;
	int		height;
	int		endian;
	int		line_size;
}				t_fdf_img;

/*	t_projection:	Stores a render mode

	name:			Projection display name
	f:				Function used for projection
	angle1:			Left angle used for projection (degree)
	angle2:			Right angle used for projection (degree)
*/
typedef struct s_projection {
	char	*name;
	void	(*f)(void *);
	double	angle1;
	double	angle2;
}				t_projection;

/*	t_vars:		Stores all data needed for the project

	id:			MLX instance
	win:		Window's instance
	title:		Window's title
	rotation:	Current angle of rotation (degrees)
	width:		Window's width
	height:		Window's height
	zoom:		Current zoom multiplier
	zhight:		Current z height multiplier
	min:		Coordinates of the minimum point
	max:		Coordinates of the maximum point
	center:		Coordinates of the point at the center of the map
	points:		Point list parsed from the map file
	img:		Image used for map rendering
	projection:	Current render mode
*/
typedef struct s_vars {
	void			*id;
	void			*win;
	char			*title;
	int				rotation;
	int				width;
	int				height;
	double			zoom;
	double			zhight;
	t_point			min;
	t_point			max;
	t_point			center;
	t_point			*points;
	t_fdf_img		img;
	t_projection	proj;
}				t_vars;

/* Initialisers */
void			image_init(t_vars *vars);
void			extremums_init(t_vars *vars);
void			fdf_init(int fd, char *file_name, t_vars *vars);

/* Parsing stuff */
t_point			*parse_map(int fd);
t_point			*new_point(int x, int y);
t_point			*get_point(int x, int y, t_point *list);
char			*uppercase(char *str);

/* Projections stuff */
double			dabs(double d);
void			project(t_vars *vars);
void			update_projection(t_vars *vars);
void			center(t_vars *vars, int x, int y);
void			rotate(t_point *points, double angle);
t_projection	new_proj(
					char *name, void (*f)(t_vars *),
					double angle1, double angle2
					);

/* Listeners */
int				on_destroy(void *p);
int				on_key(int key, void *p);
int				on_mouse(int button, int x, int y, void *p);

/* Display functions */
void			show_controls(t_vars *vars);
void			update_display(t_vars *vars);
void			put_pixel_img(t_fdf_img *img, int x, int y, unsigned int color);

/* Memory clearing functions */
void			pointsclear(t_point **lst);
void			clean_exit(t_vars *vars, int status);

#endif