/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:46:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/01 23:50:32 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Creation of a node
t_var_parsed_table *init_parsed_table(t_var_parsed_table *prev_table)
{
	t_var_parsed_table *node;

	node = (t_var_parsed_table *)malloc(sizeof(t_var_parsed_table));
	if (node)
	{
		node->cmd = NULL;
		node->cmd_splited = NULL;
		node->env = NULL;
		node->fd_error = -1;
		node->fd_in = -1;
		node->fd_out = -1;
		node->next = NULL;
		node->path = NULL;
	}
	else
		return (node);
}

//Recursive function to read the data of the tree
void read_tree(t_token *tree, t_var_parsed_table **table_node, int mode)
{
	static int first_time = 1;
	static int red_to_flag = 0;
	static int red_from_flag = 0;
	static int fd = -1;

	if (tree == NULL)
		return;
	
	if (mode == 1)
	{
		//reset of the variables
		first_time = 1;
		red_to_flag = 0;
		red_from_flag = 0;
		fd = -1;
		return ;
	}
	if (tree->type == 100 || tree->type == 101)
	{
		if (first_time == 1)
		{
			//printf("CREAMOS NODO PRINCIPAL\n");
			*table_node = init_parsed_table(*table_node);
			first_time = 0;
		}
		else
		{
			//printf("\nCREAMOS NODO SECUNDARIO\n");
			(*table_node)->next = init_parsed_table(*table_node);
			*table_node = (*table_node)->next;
		}
	}
	
	if (tree->type == 2)
		red_from_flag = 1;
		
	if (tree->type == 1)
		//printf("RED TO FOUND\n");
		red_to_flag = 1;
	
	if (tree->type == 108)
		fd = open(tree->data, O_RDONLY);

	// Process left child
	if (tree->left != NULL)
		read_tree(tree->left, table_node, 0);
		
	// Process middle child
	if (tree->middle != NULL)
		read_tree(tree->middle, table_node, 0);
		
	// Process right child
	if (tree->right != NULL)
		read_tree(tree->right, table_node, 0);

	//Is the type of data we are looking for
	if ((tree->type == 0 || tree->type == 102 || tree->type == 103 || tree->type == 105) && (tree->left == NULL && tree->middle == NULL && tree->right == NULL))
	{		
		if ((*table_node)->cmd == NULL)
			(*table_node)->cmd = strdup(tree->data);
		else
		{
		(*table_node)->cmd = realloc((*table_node)->cmd, ft_strlen((*table_node)->cmd) + ft_strlen(tree->data) + 2);
		ft_strlcat((*table_node)->cmd, " ", ft_strlen(" "));
		ft_strlcat((*table_node)->cmd, tree->data, ft_strlen(tree->data));
		}
		//printf("cmd: %s\n", (*table_node)->cmd);
	}
	if (red_from_flag == 1)
		(*table_node)->fd_in = fd;
	if (red_to_flag == 1)
		(*table_node)->fd_out = fd;
}

void	walk_tree(t_var_parsed_table **parsed_table, t_token *tree)
{	
	if (tree->left && tree->left->type == 100)
		walk_tree(parsed_table, tree->left);

	if (tree->left->type == 100)
		read_tree(tree->right, parsed_table, 0);
	else
		read_tree(tree, parsed_table, 0);
		
	//Calling the function again to clear the static variables (mode 1)
	read_tree(tree, parsed_table, 1);
}