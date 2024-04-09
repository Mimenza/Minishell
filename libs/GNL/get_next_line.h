/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:22:02 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/30 17:55:28 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list_gnl
{
	char				*buffer;
	struct s_list_gnl	*next;
}				t_list_gnl;

int			ft_found_newline(t_list_gnl *list);
t_list_gnl	*ft_list_last_node(t_list_gnl *list);
char		*ft_get_line(t_list_gnl *list);
void		ft_copy_str(t_list_gnl *list, char *str);
int			ft_size_to_newline(t_list_gnl *list);
void		ft_clean_list(t_list_gnl **list);
char		*get_next_line(int fd);
void		ft_free_list(t_list_gnl **list, t_list_gnl \
*clean_node, char *buf, int mode);
void		ft_create_list(t_list_gnl **list, int fd);

#endif