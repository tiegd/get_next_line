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
**	Return the total number of char in a list.
*/

int	ft_lstsizechar(t_list **lst)
{
	t_list	*tmp;
	int		size;
	int		i;

	size = 1;
	tmp = *lst;
	if (!lst)
		return (0);
	tmp = *lst;
	while (tmp->next)
	{
		if (!tmp->content)
			return(-1);
		i = 0;
		while (tmp->content[i] != '\0')
		{
			if (tmp->content[i] == '\n')
				return (size);
			size++;
			i++;
		}
		tmp = tmp->next;
	}
	return (size);
}

/*
**	Free a linked list.
*/

char	*ft_lstfree(t_list **lst)
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
	return (NULL);
}

/*
**	Creat a new element of list with a content in parameter.
*/

t_list	*ft_lstnew_content(t_list **lst, char *str)
{
	t_list	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_list));
	if (!new)
		ft_lstfree(lst);
	new->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new->content)
		ft_free_buff(&new->content);
	while (str[i] && str[i] != '\n')
	{
		new->content[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		new->content[i] = '\n';
		i++;
	}
	new->content[i] = '\0';
	new->next = NULL;
	ft_lstaddback(lst, new);
	return (*lst);
}

/*
**	Add an element at the end of list.
*/

void	ft_lstaddback(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!(*lst))
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
**	Free a string.
*/

char	**ft_free_buff(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	return (NULL);
}

/*
**	Copy the characters after '\n', in stock.
*/

int	ft_stock(char *buff, char *stock)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i])
	{
		// if (buff[i] == '\n' && buff[i + 1] != '\0')
		if (buff[i] == '\n')
		{
			i++;
			while (buff[i])
			{
				stock[j++] = buff[i];
				i++;
			}
			stock[j] = '\0';
			printf("stock = %s\n", stock);
			return (0);
		}
		i++;
	}
	stock[0] = '\0';
	return (1);
}

/*
**	Read n elements of the first line with read() and copy in buff[].
*/

void	ft_new_line(t_list **lst, int fd, char *stock)
{
	int		rd;
	int		i;
	char	*buff;
	char	*end_line;

	i = 0;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	end_line = buff;
	if (!buff || !end_line)
		return;
	while (ft_stock(buff, stock))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = 0;
		if (rd < 0)
		{
			ft_free_buff(&buff);
			return;
		}
		ft_lstnew_content(lst, buff);
	}
}

/*
**	Copy stock in the first list element.
*/

void	ft_add_stock(t_list **lst, char *stock)
{
	int	i;

	i = 0;
	(*lst)->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(*lst)->content)
		ft_lstfree(lst);
	while (i < BUFFER_SIZE && stock[i])
	{
		(*lst)->content[i] = stock[i];
		stock[i] = '\0';
		i++;
	}
	(*lst)->content[i] = '\0';
	(*lst)->next = NULL;
}

/*
**	Copy each list element in the result tab.
*/

char	*newtab(t_list **lst)
{
	t_list	*tmp;
	char	*result;
	int		i;
	int		j;

	result = malloc((ft_lstsizechar(lst) + 1) * sizeof(char));
	if (!result)
		return (*ft_free_buff(&result));
	i = 0;
	tmp = *lst;
	while (tmp)
	{
		j = 0;
		// while (tmp->content[j] != '\0' && tmp->content[j] != '\n')
		while (tmp->content[j] != '\0')
		{
			result[i++] = tmp->content[j++];
			if (tmp->content[j - 1] == '\n')
				break;
		}
		tmp = tmp->next;
	}
	return (result);
}

char	*get_next_line(int fd)
{
    static char	stock[BUFFER_SIZE + 1];
	char		*result;
	t_list		*lst;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (stock[0] == '\0')
		lst = NULL;
	else
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			return (ft_lstfree(&lst));
		ft_add_stock(&lst, stock);
	}
	ft_new_line(&lst, fd, stock);
	result = newtab(&lst);
	return (result);
}
