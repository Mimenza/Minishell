/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:08:36 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/08 10:51:39 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Assigns the tokens to the struct
int	tokenization(char *input, t_input **struct_input)
{
	int					control[2];
	char				**tokens;

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
