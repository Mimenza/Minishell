/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:12:20 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/03 15:42:11 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	ft_reduce_utils(t_token *(*all)[7], \
t_step **c_step, t_options *options, int mode)
{
	(*all)[START_STACK] = (*c_step)->tree_stack;
	(*all)[JOIN_TOKEN] = (t_token *)malloc(sizeof(t_token));
	if ((*all)[JOIN_TOKEN] == NULL)
		return ;
	(*all)[JOIN_TOKEN]->data = ft_strdup("Joined token");
	(*all)[JOIN_TOKEN]->type = options->next_state;
	(*all)[JOIN_TOKEN]->left = NULL;
	(*all)[JOIN_TOKEN]->right = NULL;
	(*all)[JOIN_TOKEN]->middle = NULL;
	(*all)[JOIN_TOKEN]->next = NULL;
	(*all)[TOKEN_1] = last_node_stack((*all)[START_STACK]);
	(*all)[TOKEN_2] = (*all)[START_STACK];
	(*all)[TOKEN_3] = (*all)[START_STACK];
	if (mode == 1)
		(*all)[TOKEN_4] = (*all)[START_STACK];
}

static void	ft_reduce_utils1(t_token *(*all)[7], t_step **c_step)
{
	while ((*all)[TOKEN_2]->next != (*all)[TOKEN_1])
		(*all)[TOKEN_2] = (*all)[TOKEN_2]->next;
	while (((*all)[TOKEN_3]->next != (*all)[TOKEN_2]) && \
	((*all)[TOKEN_3] != (*all)[TOKEN_2]))
		(*all)[TOKEN_3] = (*all)[TOKEN_3]->next;
	while (((*all)[TOKEN_4]->next != (*all)[TOKEN_3]) && ((*all)[TOKEN_4] \
	!= (*all)[TOKEN_3]) && ((*all)[TOKEN_4] != (*all)[TOKEN_2]))
		(*all)[TOKEN_4] = (*all)[TOKEN_4]->next;
	(*all)[JOIN_TOKEN]->left = (*all)[TOKEN_3];
	(*all)[JOIN_TOKEN]->middle = (*all)[TOKEN_2];
	(*all)[JOIN_TOKEN]->right = (*all)[TOKEN_1];
	(*all)[JOIN_TOKEN]->left->next = NULL;
	(*all)[JOIN_TOKEN]->middle->next = NULL;
	(*all)[JOIN_TOKEN]->right->next = NULL;
	if ((*all)[TOKEN_3] == (*all)[TOKEN_4])
	{
		(*c_step)->tree_stack = NULL;
		(*c_step)->tree_stack = (*all)[JOIN_TOKEN];
	}
	else
		(*all)[TOKEN_4]->next = (*all)[JOIN_TOKEN];
}

static void	ft_reduce_utils2(t_token *(*all)[7], t_step **c_step)
{
	while ((*all)[TOKEN_2]->next != (*all)[TOKEN_1])
		(*all)[TOKEN_2] = (*all)[TOKEN_2]->next;
	while (((*all)[TOKEN_3]->next != (*all)[TOKEN_2]) && \
	((*all)[TOKEN_3] != (*all)[TOKEN_2]))
		(*all)[TOKEN_3] = (*all)[TOKEN_3]->next;
	(*all)[JOIN_TOKEN]->left = (*all)[TOKEN_2];
	(*all)[JOIN_TOKEN]->right = (*all)[TOKEN_1];
	(*all)[JOIN_TOKEN]->left->next = NULL;
	(*all)[JOIN_TOKEN]->right->next = NULL;
	if ((*all)[TOKEN_2] == (*all)[TOKEN_3])
	{
		(*c_step)->tree_stack = NULL;
		(*c_step)->tree_stack = (*all)[JOIN_TOKEN];
	}
	else
		(*all)[TOKEN_3]->next = (*all)[JOIN_TOKEN];
}

//Reduce the tokens of the stack
void	ft_reduce(t_options *options, t_step **c_step)
{
	t_token	*all[7];

	all[JOIN_TOKEN] = NULL;
	all[6] = NULL;
	if (options->nbr_red == 1)
	{
		all[TOKEN_1] = last_node_stack((*c_step)->tree_stack);
		all[TOKEN_1]->type = options->next_state;
	}
	else if (options->nbr_red == 2)
	{
		ft_reduce_utils(&all, c_step, options, 0);
		ft_reduce_utils2(&all, c_step);
	}
	else if (options->nbr_red == 3)
	{
		ft_reduce_utils(&all, c_step, options, 1);
		ft_reduce_utils1(&all, c_step);
	}
}

//Shifts the first node of the input to the last position of stack
void	ft_shift(t_token **stack, t_token **input)
{
	t_token	*c_token;
	t_token	*c_stack;

	if (*input == NULL)
		return ;
	c_token = *input;
	*input = c_token->next;
	c_token->next = NULL;
	c_stack = *stack;
	while (c_stack != NULL && (c_stack->next != NULL))
		c_stack = c_stack->next;
	if (c_stack == NULL)
		*stack = c_token;
	else
		c_stack->next = c_token;
}
