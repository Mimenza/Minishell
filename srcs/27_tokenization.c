/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 07:08:36 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/09 12:38:35 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Assigns the tokens to the struct
int	tokenization(char *input, t_input **struct_input)
{
	int					control[2];
	char				**tokens;
	int					array[2];

	control[0] = TRUE;
	control[1] = TRUE;
	array[0] = SPACE_M;
	array[1] = TAB_M;
	tokens = ft_bash_split(input, array, control);
	if (control[0] == TRUE && control[1] == TRUE)
	{
		(*struct_input)->token_raw = tokens;
		return (TRUE);
	}
	else
		return (FALSE);
}
