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
# define BUFFER_SIZE 25
#endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;


char	*get_next_line(int fd);
t_list	*ft_lstnew(void *buffer);
int		ft_lstsize(t_list *lst);

#endif