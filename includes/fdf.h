/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:50:56 by vegret            #+#    #+#             */
/*   Updated: 2022/11/30 17:58:01 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MLX_WIDTH				800
# define MLX_HEIGHT				600
# define DEFAULT_POINT_COLOR	0x00FFFFFF
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

/*
x: Line
y: Column
z: Height
*/
typedef struct s_point {
	int				x;
	int				y;
	int				z;
	int				basex;
	int				basey;
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
	int			mins[2];
	int			maxs[2];
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