/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:29:46 by joandre-          #+#    #+#             */
/*   Updated: 2024/07/22 12:41:22 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_line	*free_node(t_line **node, t_line *new, char *buffer)
{
	t_line	*linx;

	if (!node || !new || !buffer)
		return (NULL);
	while (*node)
	{
		linx = (*node)->next;
		free((*node)->buff);
		free(*node);
		*node = linx;
	}
	if (new->buff[0])
		*node = new;
	else
	{
		free(buffer);
		free(new);
		return (NULL);
	}
	return (new);
}

static t_line	*clear_list(t_line **node)
{
	t_line	*last;
	t_line	*new;
	char	*buffer;
	size_t	i;
	size_t	k;

	if (!(*node))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_line));
	if (!buffer || !new)
		return (NULL);
	clean_buffer(buffer, BUFFER_SIZE + 1);
	last = last_node(*node);
	i = 0;
	while (last->buff[i] && last->buff[i] != '\n')
		i++;
	k = 0;
	if (last->buff[i])
		while (last->buff[++i])
			buffer[k++] = last->buff[i];
	new->buff = buffer;
	new->next = NULL;
	return (free_node(node, new, buffer));
}

static void	create_list(t_line **node, int fd)
{
	char	*buffer;
	t_line	*new;

	while (!is_newline(*node))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		clean_buffer(buffer, BUFFER_SIZE + 1);
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			free(buffer);
			return ;
		}
		new = malloc(sizeof(t_line));
		if (!new)
			return ;
		if (!(last_node(*node)))
			*node = new;
		else
			(last_node(*node))->next = new;
		new->buff = buffer;
		new->next = NULL;
	}
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_line	*node = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&node, fd);
	if (!node)
		return (NULL);
	line = malloc(get_line_size(node) + 1);
	if (!line)
		return (NULL);
	clean_buffer(line, get_line_size(node) + 1);
	copy_line(node, line);
	node = clear_list(&node);
	return (line);
}
