/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:46:17 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/05 08:12:49 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//This function checks if the txt is created
static int	check_history_file(void)
{
	int	file;

	file = open(".history.txt", O_RDONLY);
	if (file < 0)
	{
		file = open(".history.txt", O_WRONLY);
		if (file < 0)
			return (1);
		close(file);
	}
	else
		close(file);
	return (0);
}

//This function loads the history from the txt
void	load_history(void)
{
	char	*tmp;
	int		fd;

	if (check_history_file() != 0)
		return ;
	fd = open(".history.txt", O_RDONLY);
	if (fd == -1)
	{
		print_error(4, NULL, NULL);
		return ;
	}
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		add_history(tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}

//This function saves the input into the local and text history
void	save_history(char	*input)
{
	int	file;

	file = open(".history.txt", O_RDWR | O_APPEND);
	if (file == -1)
		check_history_file();
	ft_putstr_fd(input, file);
	ft_putstr_fd("\n", file);
	close(file);
	add_history(input);
	free(input);
}
