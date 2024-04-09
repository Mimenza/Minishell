/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:55 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/08 18:57:17 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Analize the input looking for errors
static int	analyze_input(char **input, t_input **struct_input)
{
	size_t	control;

	control = TRUE;
	beyond_pipe(*input, &control);
	if (open_quotes(*input) == FALSE)
		return (FALSE);
	while (control == FALSE)
	{
		*input = join_line(*input, &control, struct_input);
		if (!(*input))
			return (FALSE);
	}
	if (add_space(input, '>', struct_input) == FALSE)
		return (FALSE);
	if (add_space(input, '<', struct_input) == FALSE)
		return (FALSE);
	return (TRUE);
}

//Prepares the variables and structures for the program
static void	prepare_program(t_input **struct_input, char **envp)
{
	*struct_input = (t_input *)malloc(sizeof(t_input));
	load_history();
	save_env(envp, struct_input);
	signal_receiver();
	read_table(struct_input);
}

//Checks the input 
static int	check_input(char **line, t_input **struct_input)
{
	(*struct_input)->input = *line;
	if (ft_strlen(*line) == 0)
		return (FALSE);
	if (analyze_input(line, struct_input) == FALSE)
		return (FALSE);
	if (tokenization(*line, struct_input) == FALSE)
		return (print_error(2, NULL, NULL), FALSE);
	if (ft_strcmp(*line, "clear") == 0)
		printf("\033[H\033[2J");
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_input	*struct_input;

	if (argc > 1)
		return (print_error(1, NULL, NULL), 2);
	(void)argv;
	input = NULL;
	prepare_program(&struct_input, envp);
	while (1)
	{
		input = readline("custom_bash$");
		if (input == NULL)
			break ;
		if (check_input(&input, &struct_input) == TRUE)
			create_tokens_analyzer(&struct_input);
		if (input)
			save_history(input);
		free_double(struct_input->token_raw);
		struct_input->token_raw = NULL;
	}
	free_all(struct_input, input);
	return (0);
}
