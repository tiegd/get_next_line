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

#ifndef BUFFERSIZE
# define BUFFERSIZE 25
#endif

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char	*get_next_line(int fd);

#endif