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

/*
**	Copy the characters after '\n', in stock.
*/

static char	*ft_stock(t_list **lst, char stock[BUFFER_SIZE + 1])
{
	t_list	*last;
	int		i;
	int		j;

	i = 0;
	while (i < BUFFER_SIZE)
		stock[i++] = '\0';
	i = 0;
	j = 0;
	if (!(*lst))
		return (NULL);
	last = ft_lstlast(*lst);
	if (!last->content || !ft_checklst(last))
		return (NULL);
	while (last->content[i])
	{
		if (last->content[i++] == '\n')
			break ;
	}
	if (last->content[i] != '\0')
	{
		while (last->content[i] != '\0')
			stock[j++] = last->content[i++];
	}
	return (stock);
}

/*
**	Read n elements of the first line with read() and copy in buff[].
*/

static void	ft_new_line(t_list **lst, int fd, char *stock)
{
	int		rd;
	char	*buff;

	rd = 1;
	while (ft_checklst(*lst) == 0 && (rd != 0))
	{
		buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (ft_lstfree(lst));
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0 || (rd == 0 && !(*lst)))
		{
			free(buff);
			ft_lstfree(lst);
			stock[0] = '\0';
			return ;
		}
		buff[rd] = '\0';
		ft_lstnew_back(lst, buff, rd);
		free(buff);
		if (!*lst)
			return (ft_lstfree(lst));
	}
}

/*
**	Copy stock in the first list element.
*/

static void	ft_add_stock(t_list **lst, char *stock)
{
	int	i;

	i = 0;
	if (!*lst)
		return ;
	(*lst)->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(*lst)->content)
		return (ft_lstfree(lst));
	while (i < BUFFER_SIZE && stock[i])
	{
		(*lst)->content[i] = stock[i];
		i++;
	}
	(*lst)->content[i] = '\0';
	(*lst)->next = NULL;
}

/*
**	Copy each list element in the result tab.
*/

static char	*ft_newtab(t_list **lst)
{
	t_list	*tmp;
	char	*result;
	int		i;
	int		j;

	tmp = *lst;
	result = malloc(((ft_lst_size(tmp) * BUFFER_SIZE) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (tmp)
	{
		j = 0;
		while (tmp->content[j] != '\0')
		{
			result[i++] = tmp->content[j++];
			if (tmp->content[j - 1] == '\n')
				break ;
		}
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	result[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	char		*result;
	t_list		*lst;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stock[0] == '\0')
		lst = NULL;
	else
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			return (NULL);
		ft_add_stock(&lst, stock);
	}
	ft_new_line(&lst, fd, stock);
	if (!lst)
		return (NULL);
	result = ft_newtab(&lst);
	ft_stock(&lst, stock);
	ft_lstfree(&lst);
	return (result);
}
