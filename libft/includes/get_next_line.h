/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:56 by vegret            #+#    #+#             */
/*   Updated: 2022/11/20 20:43:17 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif
# ifndef MAX_FILES
#  define MAX_FILES 1024
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			content[BUFFER_SIZE + 1];
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*get_line(t_list *stash, int len);
int		strindex(char *str, char c);
int		ft_strlstlen(t_list *stash);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void);
void	ft_lstclear(t_list **lst);

#endif
