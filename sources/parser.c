/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:52:23 by vegret            #+#    #+#             */
/*   Updated: 2022/12/13 22:20:04 by vegret           ###   ########.fr       */
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
	while (line[i] == ' ')
		i++;
	while (line[i] != '\n' && line[i])
	{
		new = new_point(x, y);
		if (!new)
			return (pointsclear(map), 0);
		new->data.z = parse_coords(line, &i);
		new->data.color = parse_color(line, &i);
		if (*prev)
			(*prev)->next = new;
		else
			*map = new;
		*prev = new;
		while (line[i] == ' ')
			i++;
		y++;
	}
	return (1);
}

static void	assign_nexts(t_points *points)
{
	while (points)
	{
		points->nextx = get_point(
				points->data.x + 1,
				points->data.y,
				points->next);
		points->nexty = get_point(
				points->data.x,
				points->data.y + 1,
				points->next);
		points = points->next;
	}
}

t_points	*parse_map(int fd)
{
	t_points	*points;
	t_points	*prev;
	char		*line;
	int			x;

	x = 0;
	points = NULL;
	prev = NULL;
	line = get_next_line(fd);
	while (line)
	{
		line = uppercase(line);
		if (!parse_line(line, x, &points, &prev))
			return (NULL);
		free(line);
		line = get_next_line(fd);
		x++;
	}
	assign_nexts(points);
	return (points);
}
