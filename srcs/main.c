/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/01/24 12:35:34 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
 
void	print_history(char *line)
{
	if(tokenization(line) == 0)
		printf("la linea es correcta\n");
	else
		printf("syntax error\n");
}
 
 int main(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("Minishell>");
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			printf("%s\n", input);
			break ;
		}
		print_history(input);
		add_history(input);
	}
	return (0);
}
