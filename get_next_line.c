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

t_list	*ft_lstnew_back(t_list *lst, void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->str = content;
	new->next = NULL;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (lst);
}

char	*newtab(t_list *lst, char *stock)
{
	char	*result;
	int		sizelst;
	int		i;
	int		j;
	
	sizelst = ft_lstsize(&lst);
	result = malloc(sizelst * sizeof(char));
	i = 0;
	while (lst->next)
	{
		j = 0;
		if (lst->str == '\n')
		{
			result[i] = '\n';
			while (lst->str != '/0')
			{
				*stock = lst->str[j];
				j++;
				*stock++;
			}
		}
		result[i] = lst->str[j];
		result++;
	}
	return (result);
}

char	*ft_free_all(char *buffer)
{
	int	i;

	i = 0;
	while (*buffer)
	{
		free(buffer[i]);
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
    static char	*stock;
	char		*buffer;
	char		*result;
	t_list		lst;
	int			rd;
	int			i;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	rd = read(fd, buffer, BUFFER_SIZE);
	i = 0;
	if (fd < 0)
		return (NULL);
	while (i <= rd)
	{
		ft_lstnew_back(&lst, buffer);
	}
	newtab(&lst, stock);
	ft_free_all(buffer);
	return (result);
}
