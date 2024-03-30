/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_read_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:33:58 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/30 18:46:01 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Función para imprimir las opciones de un estado dado
// void print_options_for_state(t_states *states_list, int state_number)
// {
// 	t_states *current_state = states_list;

// 	// Busca el estado con el número especificado
// 	while (current_state != NULL && current_state->state != state_number)
// 		current_state = current_state->next;
// 	// Si se encontró el estado
// 	if (current_state != NULL)
// 	{
// 		//printf("Opciones para el estado %d:\n", current_state->state);
// 		t_options *current_option = current_state->options;
// 		while (current_option != NULL)
// 		{
// 			printf("Index: %d, State: %d, Type: %d, Action:\ 
//%d, Next State: %d, Red: %d\n",
// 				current_option->index, current_option->state,\
// current_option->t_type,
// 				current_option->action, current_option->next_state,\
// current_option->nbr_red);
// 			current_option = current_option->next;
// 		}
// 	}
// }

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
char ***tokens, char **line)
{
	*tokens = ft_split(*line, '\t');
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
	char		*line;
	char		**tokens;
	t_options	*new_option;
	int			array[7];

	states[STATE_LIST] = NULL;
	states[C_STATE] = NULL;
	array[OPTION_INDEX] = 0;
	array[F_D] = open("parsing_table", O_RDONLY);
	if (array[F_D] == -1)
		return (print_error(5, NULL, NULL));
	line = get_next_line(array[F_D]);
	while (line != NULL)
	{
		read_table_utils(&array, &states, &tokens, &line);
		new_option = create_option_node(array);
		add_option_to_state(states[C_STATE], new_option);
		free(line);
		line = get_next_line(array[F_D]);
	}
	close (array[F_D]);
	(*struct_input)->parsing_table = states[STATE_LIST];
	return ;
}

/////////////////DEJO LO QUE TENIAS POR ABAJO
// void read_table(t_input **struct_input)
// {
// 	int			fd;
// 	int			option_index;
// 	int			state;
// 	int			t_type;
// 	int			action;
// 	int			next_state;
// 	int			nbr_red;
// 	t_states	*states_list;
// 	t_states	*current_state;
// 	char		*line;
// 	char		**tokens;
// 	t_options	*new_option;

// 	states_list = NULL;
// 	current_state = NULL;
// 	option_index = 0;
// 	fd = open("parsing_table", O_RDONLY);
// 	if (fd == -1)
// 		return(print_error(5, NULL, NULL));
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		tokens = ft_split(line, '\t');
// 		state = ft_atoi(tokens[0]);
// 		t_type = ft_atoi(tokens[1]);
// 		action = ft_atoi(tokens[2]);
// 		next_state = ft_atoi(tokens[3]);
// 		nbr_red = ft_atoi(tokens[4]);
// 		free_double(tokens);
// 		if (current_state == NULL || current_state->state != state)
// 		{
// 			current_state = create_state_node(state);
// 			current_state->next = states_list;
// 			states_list = current_state;
// 			option_index = 0;
// 		}
// 		new_option = create_option_node(option_index++, state,\\
// t_type, action, next_state, nbr_red);
// 		add_option_to_state(current_state, new_option);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	(*struct_input)->parsing_table = states_list;
// 	return;
// }

// static t_options *create_option_node(int index, int state, \
// t_type, int action, int next_state, int nbr_red)
// {
// 	t_options *new_node;

// 	new_node = (t_options *)malloc(sizeof(t_options));
// 	if (new_node == NULL)
// 		return (new_node);
// 	new_node->index = index;
// 	new_node->state = state;
// 	new_node->t_type = t_type;
// 	new_node->action = action;
// 	new_node->next_state = next_state;
// 	new_node->nbr_red = nbr_red;
// 	new_node->next = NULL;
// 	return (new_node);
// }