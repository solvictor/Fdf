/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:56 by vegret            #+#    #+#             */
/*   Updated: 2022/12/01 22:03:22 by vegret           ###   ########.fr       */
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
# define MLX_WIDTH				1600
# define MLX_HEIGHT				900
# define DEFAULT_POINT_COLOR	0x00FFFFFF

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

typedef struct s_vars {
	void		*mlx;
	void		*win;
	int			distance;
	int			height;
	int			width;
	t_point		min;
	t_point		max;
	t_points	*points;
}				t_vars;

t_points	*parse_map(int fd);
t_points	*new_point(int x, int y);
void		lstiter(t_points *lst, void (*f)(t_point *));
void		pointsclear(t_points **lst);
char		*uppercase(char *str);
int			exit_fdf(void *p);
int			key_listener(int key, void *p);
int			test_listener(void *p);
int			mouse_listener(int button, int x, int y, void *p);

#endif