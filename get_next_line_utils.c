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

static int	ft_lstsize(t_list *lst)
{
	int	size;
	int	i;

	size = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		i = 0;
		while (lst->content[i] != '\0' || lst->content[i] != '\n')
		{
			size++;
			i++;
		}
		lst = lst->next;
	}
	return (size);
}

// char    *print_lst(t_list)
