/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_steps_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:58:27 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/03 15:42:06 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Returns to the prev step
void	ret_to_prev(t_step **c_step)
{
	t_step	*prev_step;

	prev_step = (*c_step)->prev;
	prev_step->tree_stack = (*c_step)->tree_stack;
	prev_step->input = (*c_step)->input;
	free(*c_step);
	*c_step = prev_step;
}

//Configs the parsed table (fd OUT fd IN)
void	config_parsed_table(t_var_parsed_table **current)
{
	int					array[2];
	int					control[2];
	t_var_parsed_table	*f_node;

	array[I] = 0;
	array[MAX] = 0;
	control[0] = TRUE;
	control[1] = TRUE;
	while ((*current)->prev != NULL)
	{
		array[MAX]++;
		(*current) = (*current)->prev;
	}
	f_node = *current;
	while (f_node != NULL)
	{
		if (array[I] == 0 && (f_node->fd_in == -1))
			f_node->fd_in = 0;
		if (f_node->cmd != NULL)
			f_node->cmd_splited = ft_bash_split(f_node->cmd, SPACE_M, control);
		if (array[I] == array[MAX] && f_node->fd_out == -1)
			f_node->fd_out = 1;
		f_node = f_node->next;
		array[I]++;
	}
}

//Inits the first step of the analizer
t_step	*init_first_step(t_input **struct_input, t_token *input_token)
{
	t_step		*first_step;
	t_states	*state;

	first_step = NULL;
	first_step = (t_step *)malloc(sizeof(t_step));
	if (first_step == NULL)
		return (first_step);
	first_step->step_nbr = 0;
	first_step->state_nbr = 0;
	if (find_state((*struct_input)->parsing_table, 0, &state) == FALSE)
	{
		free(first_step);
		return (first_step);
	}
	first_step->state = state;
	first_step->option_nbr = 0;
	first_step->tree_stack = NULL;
	first_step->input = input_token;
	first_step->next = NULL;
	first_step->prev = NULL;
	return (first_step);
}

int	special_case(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (FALSE);
	}
	return (TRUE);
}
