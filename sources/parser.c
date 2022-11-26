/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:52:23 by vegret            #+#    #+#             */
/*   Updated: 2022/11/26 07:28:16 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	parse_color(char *str, int *i)
{
	unsigned int	color;

	if (str[*i] != ',')
		return (DEFAULT_POINT_COLOR);
	(*i) += 3;
	color = 0;
	while ((str[*i] >= '0' && str[*i] <= '9')
		|| (str[*i] >= 'A' && str[*i] <= 'F'))
	{
		color = color * 16 + str[*i];
		if (str[*i] >= '0' && str[*i] <= '9')
			color -= '0';
		else
			color -= 'A' - 10;
		(*i)++;
	}
	return (color);
}

static int	parse_coords(char *str, int *i)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + str[*i] - '0';
		(*i)++;
	}
	return (result * sign);
}

static int	parse_line(char *line, int x, t_points	**map, t_points	**prev)
{
	t_points	*new;
	int			i;
	int			y;

	i = 0;
	y = 0;
	while (line[i] != '\n' && line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\n' || !line[i])
			break ;
		new = new_point(x, y);
		if (!new)
			return (pointsclear(map), 0);
		new->content.z = parse_coords(line, &i);
		new->content.color = parse_color(line, &i);
		if (*prev)
			(*prev)->next = new;
		else
			*map = new;
		*prev = new;
		y++;
	}
	return (1);
}

t_points	*parse_map(int fd)
{
	t_points	*map;
	t_points	*prev;
	char		*line;
	int			x;

	map = NULL;
	prev = NULL;
	x = 0;
	line = get_next_line(fd);
	while (line)
	{
		line = uppercase(line);
		if (!parse_line(line, x, &map, &prev))
			return (NULL);
		free(line);
		line = get_next_line(fd);
		x++;
	}
	return (map);
}
