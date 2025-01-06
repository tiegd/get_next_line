/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:13:46 by gaducurt          #+#    #+#             */
/*   Updated: 2024/12/10 16:13:48 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Return the total number of char in a list.
*/

int	ft_lst_size(t_list *lst)
{
	int	size;

	size = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

/*
**	Free a linked list.
*/

void	ft_lstfree(t_list **lst)
{
	t_list	*buffer;

	if (lst)
	{
		while (*lst)
		{
			buffer = (*lst)->next;
			free((*lst)->content);
			free(*lst);
			*lst = buffer;
		}
	}
}

int	ft_checklst(t_list *lst)
{
	int		i;
	t_list	*element;

	i = 0;
	if (!lst)
		return (0);
	element = ft_lstlast(lst);
	while (element->content[i])
	{
		if (element->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
**	Creat a new element of list with a content in parameter.
*/

void	ft_lstnew_back(t_list **lst, char *str, int len)
{
	t_list	*new;
	t_list	*last;
	int		i;

	new = malloc(sizeof(t_list));
	if (!new)
		return (ft_lstfree(lst));
	new->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new->content)
	{
		free(new);
		return (ft_lstfree(lst));
	}
	i = -1;
	while (++i < len)
		new->content[i] = str[i];
	new->content[i] = '\0';
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

/*
**	Add an element at the end of list.
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
