/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:29:46 by joandre-          #+#    #+#             */
/*   Updated: 2024/05/31 23:13:16 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*free_node(t_list **node, t_list *new, char *buffer)
{
	t_list	*linx;

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

static t_list	*clear_list(t_list **node)
{
	t_list	*last;
	t_list	*new;
	char	*buffer;
	size_t	i;
	size_t	k;

	if (!(*node))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_list *));
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

static void	create_list(t_list **node, int fd)
{
	char	*buffer;
	t_list	*new;

	while (!is_newline(node[fd]))
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
		new = malloc(sizeof(t_list *));
		if (!new)
			return ;
		if (!(last_node(node[fd])))
			node[fd] = new;
		else
			(last_node(node[fd]))->next = new;
		new->buff = buffer;
		new->next = NULL;
	}
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	*node[4242];

	if (fd < 0 || fd > 4241 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(node, fd);
	if (!node[fd])
		return (NULL);
	line = malloc(get_line_size(node[fd]) + 1);
	if (!line)
		return (NULL);
	clean_buffer(line, get_line_size(node[fd]) + 1);
	copy_line(node[fd], line);
	node[fd] = clear_list(&node[fd]);
	return (line);
}
