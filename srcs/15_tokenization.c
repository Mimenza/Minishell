/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:08:36 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/29 16:43:21 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Assigns the tokens to the struct
int	tokenization(char *input, t_input **struct_input)
{
	int					control[2];
	char				**tokens;
	static t_var_list	*variable_list;
	int					i;
	char				*tmp;

	i = -1;
	control[0] = TRUE;
	control[1] = TRUE;
	tokens = ft_bash_split(input, SPACE_M, control);
	if (control[0] == TRUE && control[1] == TRUE)
	{
		(*struct_input)->token_raw = tokens;
		return (TRUE);
	}
	else
		return (FALSE);
}
