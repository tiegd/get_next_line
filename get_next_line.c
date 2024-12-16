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

int	ft_stock(char *buff, char *stock)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("buff = %s\n", buff);
	while (buff[i])
	{
		if (buff[i] == '\n' && buff[i + 1] != '\0')
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

void	ft_add_stock(t_list **lst, char *stock)
{
	int	i;

	i = 0;
	(*lst)->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(*lst)->content)
		ft_lstfree(lst);
	while (stock[i])
	{
		(*lst)->content[i] = stock[i];
		stock[i] = '\0';
		i++;
	}
	(*lst)->content[i] = '\0';
	(*lst)->next = NULL;
}

char	*newtab(t_list **lst)
{
	t_list	*tmp;
	char	*result;
	int		sizelst;
	int		i;
	int		j;

	sizelst = ft_lstsizechar(lst);
	printf("sizelst = %d\n", sizelst);
	result = malloc((sizelst + 1) * sizeof(char));
	if (!result)
		return (*ft_free_buff(&result));
	i = 0;
	tmp = *lst;
	while (tmp->next)
	{
		j = 0;
		while (tmp->content[i] != '\0' && tmp->content[i] != '\n')
		{
			result[i] = tmp->content[j];
			i++;
			j++;
		}
		printf("tmp->content = %s\n", tmp->content);
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
	// printf("stock apres premier appel = %s\n", stock);
	ft_new_line(&lst, fd, stock);
	// printf("Apres ft_checkread\n");
	result = newtab(&lst);
	return (result);
}
