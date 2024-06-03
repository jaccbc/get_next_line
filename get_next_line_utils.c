/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:05:06 by joandre-          #+#    #+#             */
/*   Updated: 2024/05/31 23:22:04 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_buffer(char *buffer, size_t len)
{
	if (!buffer || len == 0)
		return ;
	while (len--)
		buffer[len] = '\0';
}

bool	is_newline(t_list *node)
{
	size_t	i;

	while (node)
	{
		i = 0;
		while (node->buff[i])
		{
			if (node->buff[i++] == '\n')
				return (true);
		}
		node = node->next;
	}
	return (false);
}

size_t	get_line_size(t_list *node)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (node)
	{
		i = 0;
		while (node->buff[i])
		{
			if (node->buff[i++] == '\n')
				return (len + 1);
			++len;
		}
		node = node->next;
	}
	return (len);
}

void	copy_line(t_list *node, char *line)
{
	size_t	i;
	size_t	k;

	if (!node || !line)
		return ;
	k = 0;
	while (node)
	{
		i = 0;
		while (node->buff[i])
		{
			if (node->buff[i] == '\n')
			{
				line[k] = node->buff[i];
				return ;
			}
			line[k++] = node->buff[i++];
		}
		node = node->next;
	}
}

t_list	*last_node(t_list *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
