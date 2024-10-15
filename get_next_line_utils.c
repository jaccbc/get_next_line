/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:05:06 by joandre-          #+#    #+#             */
/*   Updated: 2024/10/15 15:49:35 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*clean_buffer(size_t len)
{
	char	*buffer;

	if (!len)
		return (NULL);
	buffer = malloc(len);
	if (!buffer)
		return (NULL);
	while (len--)
		buffer[len] = '\0';
	return (buffer);
}

bool	is_newline(t_line *lst)
{
	size_t	i;

	while (lst)
	{
		i = 0;
		while (lst->buff[i])
			if (lst->buff[i++] == '\n')
				return (true);
		lst = lst->next;
	}
	return (false);
}

size_t	get_line_size(t_line *lst)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->buff[i])
		{
			if (lst->buff[i++] == '\n')
				return (len + 1);
			++len;
		}
		lst = lst->next;
	}
	return (len);
}

void	copy_line(t_line *lst, char *line)
{
	size_t	i;
	size_t	k;

	if (!lst || !line)
		return ;
	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->buff[i])
		{
			if (lst->buff[i] == '\n')
			{
				line[k] = lst->buff[i];
				return ;
			}
			line[k++] = lst->buff[i++];
		}
		lst = lst->next;
	}
}

t_line	*last_node(t_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
