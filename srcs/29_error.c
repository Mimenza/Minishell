/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   29_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:04:36 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/08 10:53:16 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	print_error_aux(int id, char *args, t_input **input)
{
	if (id == 9)
		printf("ERROR: failed opening the files\n");
	else if (id == 10)
	{
		ft_var_found(&(*input)->ent_var, "?", "127");
		printf("ERROR: command %s not found\n", args);
	}
	else if (id == 11)
		printf("ERROR: no valid limiter\n");
	else if (id == 12)
	{
		ft_var_found(&(*input)->ent_var, "?", "2");
		printf("ERROR: filename argument required\n");
	}
	else if (id == 13)
	{
		ft_var_found(&(*input)->ent_var, "?", "258");
		printf("ERROR: unexpected end of file\n");
	}
	else if (id == 14)
	{
		ft_var_found(&(*input)->ent_var, "?", "126");
		printf("ERROR: is a directory\n");
	}
}

//Main print error function
void	print_error(int id, char *args, t_input **input)
{
	if (id == 1)
	{
		ft_var_found(&(*input)->ent_var, "?", "1");
		printf("ERROR: Invalid input\n");
	}
	else if (id == 2)
		printf("ERROR: syntax error tokenization\n");
	else if (id == 3)
		printf("ERROR: open quotes\n");
	else if (id == 4)
		printf("ERROR: opening history file");
	else if (id == 5)
		printf("ERROR: reading the file(parsing table)\n");
	else if (id == 6)
		printf("ERROR: init the first failed\n");
	else if (id == 7)
	{
		ft_var_found(&(*input)->ent_var, "?", "258");
		printf("ERROR: syntax error near unexpected token\n");
	}
	else if (id == 8)
		printf("ERROR: no such file or directory: %s\n", args);
	else
		print_error_aux(id, args, input);
}
