/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:17:49 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/02 15:48:03 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Función para liberar un árbol de tokens recursivamente
static void	free_tree(t_token *root)
{
	if (root == NULL || (root->type < -2 || root->type > 110))
		return ;
	free_tree(root->left);
	free_tree(root->middle);
	free_tree(root->right);
	if (root->data)
		free(root->data);
	root->data = NULL;
	free(root);
	root = NULL;
}

void	free_token_tree(t_token *head)
{
	t_token	*temp;
	int		flag;

	flag = 0;
	while (head != NULL && flag != 1)
	{
		temp = head->next;
		if (temp && temp->type && (temp->type == -2))
			flag = 1;
		free_tree(head);
		head = temp;
	}
}

void	free_options(t_options *options)
{
	t_options	*current_option;

	while (options != NULL)
	{
		current_option = options;
		options = options->next;
		free(current_option);
	}
}
