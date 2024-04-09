/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_read_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:33:58 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/09 15:49:30 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Función para crear un nuevo nodo de opción
static t_options	*create_option_node(int array[7])
{
	t_options	*new_node;

	new_node = (t_options *)malloc(sizeof(t_options));
	if (new_node == NULL)
		return (new_node);
	new_node->index = array[OPTION_INDEX];
	new_node->state = array[STATE];
	new_node->t_type = array[T_TYPE];
	new_node->action = array[ACTION];
	new_node->next_state = array[NEXT_STATE];
	new_node->nbr_red = array[NBR_RED];
	new_node->next = NULL;
	return (new_node);
}

// Función para crear un nuevo nodo de estado
static t_states	*create_state_node(int state)
{
	t_states	*new_node;

	new_node = (t_states *)malloc(sizeof(t_states));
	if (new_node == NULL)
		return (new_node);
	new_node->state = state;
	new_node->options = NULL;
	new_node->next = NULL;
	return (new_node);
}

// Función para agregar una opción a la lista de opciones de un estado
static void	add_option_to_state(t_states *state, t_options *option)
{
	t_options	*current;

	if (state->options == NULL)
		state->options = option;
	else
	{
		current = state->options;
		while (current->next != NULL)
			current = current->next;
		current->next = option;
	}
}

static void	read_table_utils(int (*array)[7], t_states *(*states)[3], \
char ***tokens, char *line)
{
	*tokens = ft_split(line, '\t');
	(*array)[T_TYPE] = ft_atoi((*tokens)[1]);
	(*array)[ACTION] = ft_atoi((*tokens)[2]);
	(*array)[NEXT_STATE] = ft_atoi((*tokens)[3]);
	(*array)[NBR_RED] = ft_atoi((*tokens)[4]);
	(*array)[STATE] = ft_atoi((*tokens)[0]);
	free_double(*tokens);
	if ((*states)[C_STATE] == NULL || \
	(*states)[C_STATE]->state != (*array)[STATE])
	{
		(*states)[C_STATE] = create_state_node((*array)[STATE]);
		(*states)[C_STATE]->next = (*states)[STATE_LIST];
		(*states)[STATE_LIST] = (*states)[C_STATE];
		(*array)[OPTION_INDEX] = 0;
	}
}

//Main function that reads the table with the instructions
void	read_table(t_input **struct_input)
{
	t_states	*states[3];
	char		**line;
	char		**tokens;
	t_options	*new_option;
	int			array[7];

	states[STATE_LIST] = NULL;
	states[C_STATE] = NULL;
	array[OPTION_INDEX] = 0;
	array[I] = 0;
	line = custom_function();
	while (line[array[I]] != NULL)
	{
		read_table_utils(&array, &states, &tokens, line[array[I]]);
		new_option = create_option_node(array);
		add_option_to_state(states[C_STATE], new_option);
		array[I]++;
	}
	free(line);
	(*struct_input)->parsing_table = states[STATE_LIST];
	return ;
}
