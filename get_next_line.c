/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:13:31 by gaducurt          #+#    #+#             */
/*   Updated: 2024/12/10 16:13:32 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->str = content;
	new->next = NULL;
	return (new);
}

char	*newtab(char *buffer, t_list *lst)
{
	int	len;
	int	i;

	i = 0;
	len = ft_lstsize(lst);
	buffer = malloc(len * sizeof(char));
}

char	*get_next_line(int fd)
{
    static char	*stock;
	char		*buffer;
	char		*result;
	t_list		lst;
	int			rd;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	rd = read(fd, buffer, BUFFER_SIZE);
	if (fd < 0)
		return (NULL);
	if (rd < 0)
		return (NULL);
	ft_lstnew(buffer);
	while (buffer != '\n' && buffer != '\0')
	{

		buffer++;
	}
	return (result);
}
