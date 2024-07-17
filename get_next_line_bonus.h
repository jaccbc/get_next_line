/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:38:32 by joandre-          #+#    #+#             */
/*   Updated: 2024/05/31 23:07:07 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*buff;
	struct s_list	*next;
}	t_line;

void	clean_buffer(char *buffer, size_t len);
bool	is_newline(t_line *node);
size_t	get_line_size(t_line *node);
void	copy_line(t_line *node, char *line);
t_line	*last_node(t_line *node);
char	*get_next_line(int fd);

#endif
