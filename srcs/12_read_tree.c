/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:46:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/30 15:03:27 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Frees the parsed table node
void	free_parsed_table(t_var_parsed_table **table)
{
	t_var_parsed_table	*temp;

	while ((*table) != NULL)
	{
		temp = (*table)->next;
		free_double((*table)->cmd_splited);
		free((*table)->cmd);
		free((*table)->path);
		free(*table);
		(*table) = temp;
	}
}

//Inits and creates node for parsed table
t_var_parsed_table	*init_parsed_table(t_var_parsed_table *prev_table)
{
	t_var_parsed_table	*node;

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
		node->pid = 0;
		node->prev = prev_table;
	}
	return (node);
}

//Recursive function to read the data of the tree
// void	read_tree(t_token *tree, t_var_parsed_table **table_node, int mode)
// {
// 	static int array[7] = {1, 0, 0 , 0, 0, 0, -1};

// 	if (tree == NULL)
// 		return ;
// 	reset_statics(mode, array, table_node);
// 	init_append_tree(tree, &array[FIRST], table_node);
// 	set_flags(tree, array);
// 	if (tree && tree->right && (tree->right->type == 108 || tree->right->type == 110))
// 	{
// 		if (tree->left && tree->left->type == 1)
// 			array[FD] = open(tree->right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else if (tree->left && tree->left->type == 2)
// 			array[FD] = open(tree->right->data, O_RDONLY);
// 		else if (tree->left && tree->left->type == 3)
// 			array[FD] = ft_here_doc(tree->right->data, 0);
// 		else if (tree->left && tree->left->type == 4)
// 			array[FD] = open(tree->right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	}
// 	if (tree->left != NULL)
// 		read_tree(tree->left, table_node, 0);
// 	if (tree->middle != NULL)
// 		read_tree(tree->middle, table_node, 0);
// 	if (tree->right != NULL)
// 		read_tree(tree->right, table_node, 0);
// 	create_table(tree, table_node);
// 	set_fds(array, table_node);
// }

//Looks for sub_trees in the main tree
void	walk_tree(t_var_parsed_table **parsed_table, t_token *tree)
{
	int	control;

	control = TRUE;
	if (tree->left && tree->left->type == 100)
		walk_tree(parsed_table, tree->left);
	if (tree->left && tree->left->type == 100)
		read_tree(tree->right, parsed_table, 0);
	else
		read_tree(tree, parsed_table, 0);
	read_tree(tree, parsed_table, 1);
}

void	read_tree(t_token *tree, t_var_parsed_table **table_node, int mode)
{
	static int array[7] = {1, 0, 0, 0, 0, 0, -1};

	if (tree == NULL)
		return ;
	reset_statics(mode, &array, table_node);
	//-----------------------
	// printf("1: estamos leyendo %p\n->%d<- ->%d<- ->%d<- ->%d<- ->%d<- ->%d<- ->%d<-\n",tree, array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
	init_append_tree(tree, &array[FIRST], table_node);

	// set_flags(tree, &array);
	if (tree->type == 2)
		array[RFF] = 1;
	if (tree->type == 3)
		array[HDF] = 1;
	if (tree->type == 4)
		array[APPF] = 1;
	if (tree->type == 1)
	{
		array[RTF] = 1;
		if (ft_strcmp(tree->data, "2>") == 0)
			array[EF] = 1;
	}
	//-----------------------
	// printf("2: estamos leyendo %p\n->%d<- ->%d<- ->%d<- ->%d<- ->%d<- ->%d<- ->%d<-\n",tree, array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
	if (tree && tree->right && (tree->right->type == 108 || tree->right->type == 110))
	{
		if (tree->left && tree->left->type == 1)
			array[FD] = open(tree->right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tree->left && tree->left->type == 2)
			array[FD] = open(tree->right->data, O_RDONLY);
		else if (tree->left && tree->left->type == 3)
			array[FD] = ft_here_doc(tree->right->data, 0);
		else if (tree->left && tree->left->type == 4)
			array[FD] = open(tree->right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (tree->left != NULL)
		read_tree(tree->left, table_node, 0);
	if (tree->middle != NULL)
		read_tree(tree->middle, table_node, 0);
	if (tree->right != NULL)
		read_tree(tree->right, table_node, 0);

	create_table(tree, table_node);

	// set_fds(&array, table_node);
	if (array[RFF] == 1 || array[HDF] == 1)
		(*table_node)->fd_in = array[FD];
	if (array[RTF] == 1 || array[APPF] == 1)
	{
		if (array[EF] == 1)
			(*table_node)->fd_error = array[FD];
		else
			(*table_node)->fd_out = array[FD];
	}
	//-----------------------
	// printf("3: estamos leyendo %p\n->%d<- ->%d<- ->%d<- ->%d<- ->%d<- ->%d<- ->%d<-\n",tree, array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
}

//////////LA ORIGINAL
// void	read_tree(t_token *tree, t_var_parsed_table **table_node, int mode)
// {
// 	static int	first_time = 1;
// 	static int	red_to_flag = 0;
// 	static int	red_from_flag = 0;
// 	static int	here_doc = 0;
// 	static int	append = 0;
// 	static int	error_flag = 0;
// 	static int	fd = -1;

// 	if (tree == NULL)
// 		return ;
// 	//reset_statics(mode, &first_time, &red_to_flag, &red_from_flag, &error_flag, &fd, table_node);
// 	if (mode == 2)
// 	{
// 		first_time = 1;
// 		free_parsed_table(table_node);
// 		return ;
// 	}
// 	if (mode == 1)
// 	{
// 		red_to_flag = 0;
// 		red_from_flag = 0;
// 		error_flag = 0;
// 		fd = -1;
// 		return ;
// 	}
// 	//-----------------------
	
// 	init_append_tree(tree, &first_time, table_node);
	
// 	//set_flags(tree, &red_from_flag, &here_doc, &append, &red_to_flag, &error_flag);
// 	if (tree->type == 2)
// 		red_from_flag = 1;
// 	if (tree->type == 3)
// 		here_doc = 1;
// 	if (tree->type == 4)
// 		append = 1;
// 	if (tree->type == 1)
// 	{
// 		red_to_flag = 1;
// 		if (ft_strcmp(tree->data, "2>") == 0)
// 			error_flag = 1;
// 	}
// 	//-----------------------
	
// 	if (tree && tree->right && (tree->right->type == 108 || tree->right->type == 110))
// 	{
// 		if (tree->left && tree->left->type == 1)
// 			fd = open(tree->right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else if (tree->left && tree->left->type == 2)
// 			fd = open(tree->right->data, O_RDONLY);
// 		else if (tree->left && tree->left->type == 3)
// 			fd = ft_here_doc(tree->right->data, 0);
// 		else if (tree->left && tree->left->type == 4)
// 			fd = open(tree->right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	}
// 	if (tree->left != NULL)
// 		read_tree(tree->left, table_node, 0);
// 	if (tree->middle != NULL)
// 		read_tree(tree->middle, table_node, 0);
// 	if (tree->right != NULL)
// 		read_tree(tree->right, table_node, 0);
		
// 	create_table(tree, table_node);
	
// 	//set_fds(red_from_flag, red_from_flag, here_doc, append, error_flag, table_node, fd);
// 	if (red_from_flag == 1 || here_doc == 1)
// 		(*table_node)->fd_in = fd;
// 	if (red_to_flag == 1 || append == 1)
// 	{
// 		if (error_flag == 1)
// 			(*table_node)->fd_error = fd;
// 		else
// 			(*table_node)->fd_out = fd;
// 	}
// 	//-----------------------
// }

