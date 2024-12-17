/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:13:40 by gaducurt          #+#    #+#             */
/*   Updated: 2024/12/10 16:13:41 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 16
#endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew_content(t_list **lst, char *str);
void	ft_lstaddback(t_list **lst, t_list *new);
char	**ft_free_buff(char **buffer);
char	*ft_lstfree(t_list **lst);
int		ft_stock(char *buff, char *stock);
void	ft_new_line(t_list **lst, int fd, char *stock);
void	ft_add_stock(t_list **lst, char *stock);
char	*newtab(t_list **lst);
int		ft_lstsizechar(t_list **lst);
char	*get_next_line(int fd);

#endif