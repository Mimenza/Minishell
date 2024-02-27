/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:43:59 by anurtiag          #+#    #+#             */
/*   Updated: 2024/02/27 15:49:10 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_echo(char *args, int fd)
{
	while(*args != '\0')
	{
		write(fd, *args, 1);
		args++;
	}
}

int main (void)
{
	
}