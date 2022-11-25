/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:52:23 by vegret            #+#    #+#             */
/*   Updated: 2022/11/25 17:52:49 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*new_point(void)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = 0;
	point->y = 0;
	point->z = 0;
	point->color = 0x00FFFFFF;
	return (ft_lstnew(point));
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

static unsigned int	parse_color(char *line, int *i)
{
	unsigned int	color;

	if (line[*i] != ',')
		return (0);
	(*i)++;
	color = 0;
	return (color);
}

static t_list	*parse_line(char *line, int x)
{
	t_list	*points;
	t_list	*new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	points = NULL;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		new = new_point();
		if (!new)
			return (ft_lstclear(&points, &free), NULL);
		((t_point *) new->content)->x = x;
		((t_point *) new->content)->y = y;
		((t_point *) new->content)->z = parse_coords(line, &i);
		((t_point *) new->content)->color = parse_color(line, &i);
		ft_lstadd_front(&points, new);
		y++;
	}
	return (points);
}

t_list	*parse_map(int fd)
{
	t_list	*map;
	t_list	*curr;
	char	*line;
	int		x;

	map = NULL;
	x = 0;
	line = get_next_line(fd);
	while (line)
	{
		curr = parse_line(line, x);
		if (!curr)
			return (ft_lstclear(&map, &free), NULL);
		ft_lstadd_back(&map, curr);
		free(line);
		line = get_next_line(fd);
		x++;
	}
	
	return (map);
}
