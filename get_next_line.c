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

static t_list	*ft_lstnew_addback(t_list *lst, char *str)
{
	t_list	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (str[i])
	{
		new->content[i] = str[i];
		i++;
	}
	new->next = NULL;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (lst);
}

static void	ft_checkread(t_list **lst, int fd)
{
	int		rd;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd = read(fd, buff, BUFFER_SIZE);
	if (rd < 0)
		ft_free_buff(buff);
	else
		ft_lstnew_addback(&lst, buff);
}

static void	ft_addrest(t_list **lst, char *stock)
{
	int	i;

	i = 0;
	(*lst)->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(*lst)->content)
		return (NULL);
	while (stock[i])
	{
		(*lst)->content[i] = stock[i];
		i++;
	}
	(*lst)->content[i] = '\0';
	(*lst)->next = NULL;
}

static char	*newtab(t_list *lst, char *stock)
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
		while (lst->content)
		{
			result[i] = lst->content[j];
			i++;
			j++;
		}
	}
	return (result);
}

static char	*ft_free_buff(char *buffer)
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
    static char	*stock[BUFFER_SIZE + 1];
	char		*result;
	t_list		*lst;
	int			i;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (stock[0] == '\0')
		lst = NULL;
	else
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			return (NULL);
		ft_addrest(&lst, stock);
	}
	ft_checkread(&lst, fd);
	if (!lst)
		return (NULL);
	result = newtab(&lst, stock);
	return (result);
}
