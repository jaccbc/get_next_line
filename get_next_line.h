/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:38:32 by joandre-          #+#    #+#             */
/*   Updated: 2024/10/15 15:22:52 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_line
{
	char			*buff;
	struct s_line	*next;
}	t_line;

void	*clean_buffer(size_t len);
bool	is_newline(t_line *node);
size_t	get_line_size(t_line *node);
void	copy_line(t_line *node, char *line);
t_line	*last_node(t_line *node);
char	*get_next_line(int fd);

#endif
