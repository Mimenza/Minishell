/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:50:00 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/05 08:50:15 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	free_states(t_states *states)
{
	t_states	*current_state;

	while (states != NULL)
	{
		current_state = states;
		states = states->next;
		free_options(current_state->options);
		free(current_state);
	}
}

void	free_double(char **double_ptr)
{
	char	**temp;

	if (double_ptr == NULL)
		return ;
	temp = double_ptr;
	while (*double_ptr != NULL)
	{
		free(*double_ptr);
		*double_ptr = NULL;
		double_ptr++;
	}
	free(temp);
}

static void	free_tokens(t_token *token)
{
	t_token	*tmp_token;

	while (token != NULL)
	{
		tmp_token = token->next;
		free(token->data);
		free(token);
		token = tmp_token;
	}
}

void	free_steps(t_step *steps, int mode)
{
	t_step	*tmp_step;

	free_tokens(steps->input);
	free_token_tree(steps->tree_stack);
	if (mode == 1)
	{
		while (steps)
		{
			tmp_step = steps->prev;
			free(steps);
			steps = tmp_step;
		}
	}
	else
	{
		while (steps)
		{
			tmp_step = steps->next;
			free(steps);
			steps = tmp_step;
		}
	}
}

//Function to clear all
void	free_all(t_input *struct_input, char *history)
{
	t_var_list			*tmp_env;
	t_var_parsed_table	*tmp_parsed;

	free(history);
	while ((struct_input)->ent_var)
	{
		tmp_env = (struct_input)->ent_var->next;
		free((struct_input)->ent_var->name);
		free((struct_input)->ent_var->content);
		free((struct_input)->ent_var);
		(struct_input)->ent_var = tmp_env;
	}
	free_parsed_table(&(struct_input)->parsed_table);
	free_states((struct_input)->parsing_table);
	free_double((struct_input)->token_raw);
	free(struct_input);
}
