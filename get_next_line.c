/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:29:46 by joandre-          #+#    #+#             */
/*   Updated: 2024/10/15 15:36:05 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_line	*free_node(t_line *lst, t_line *new)
{
	t_line	*linx;

	if (!lst)
		return (NULL);
	while (lst)
	{
		linx = lst->next;
		free(lst->buff);
		free(lst);
		lst = linx;
	}
	if (new)
	{
		if (new->buff && new->buff[0])
			lst = new;
		else
			return (free(new->buff), free(new), NULL);
	}
	return (new);
}

static t_line	*clear_list(t_line *lst)
{
	t_line	*last;
	t_line	*new;
	char	*buffer;
	size_t	i;
	size_t	k;

	if (!lst)
		return (NULL);
	buffer = clean_buffer(BUFFER_SIZE + 1);
	new = clean_buffer(sizeof(t_line));
	if (!buffer || !new)
		return (free(buffer), free(new), NULL);
	last = last_node(lst);
	i = 0;
	while (last->buff[i] && last->buff[i] != '\n')
		i++;
	k = 0;
	if (last->buff[i])
		while (last->buff[++i])
			buffer[k++] = last->buff[i];
	new->buff = buffer;
	new->next = NULL;
	return (free_node(lst, new));
}

static void	create_list(t_line **lst, int fd)
{
	char	*buffer;
	t_line	*new;

	while (!is_newline(*lst))
	{
		buffer = clean_buffer(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			free(buffer);
			return ;
		}
		new = clean_buffer(sizeof(t_line));
		if (!new)
			return ;
		if (!(last_node(*lst)))
			*lst = new;
		else
			(last_node(*lst))->next = new;
		new->buff = buffer;
		new->next = NULL;
	}
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_line	*lst = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&lst, fd);
	if (!lst)
		return (NULL);
	line = clean_buffer(get_line_size(lst) + 1);
	copy_line(lst, line);
	lst = clear_list(lst);
	return (line);
}
