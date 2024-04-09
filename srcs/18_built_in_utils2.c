/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_built_in_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:18:21 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/03 15:10:41 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	add_var_utils(char *name, char *content, \
t_var_list	*current, t_var_list *new)
{
	while (current->next)
		current = current->next;
	new->name = ft_strdup(name);
	if (content)
		new->content = ft_strdup(content);
	else
		new->content = NULL;
	current->next = new;
	new->next = NULL;
	new->is_printed = 0;
}

//Adds a variable to the list
void	add_var(char *name, t_var_list **env, char *content)
{
	t_var_list	*current;
	t_var_list	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
		{
			free(current->content);
			if (content)
				current->content = ft_strdup(content);
			return ;
		}
		current = current->next;
	}
	new = (t_var_list *)malloc(sizeof(t_var_list));
	if (!new)
		return ;
	current = *env;
	add_var_utils(name, content, current, new);
}

//Main built in function
static int	ft_built_in2(t_var_parsed_table	*cmd_list, \
t_input **struct_input, int (*control)[2], t_step *step)
{
	if (ft_strcmp(cmd_list->cmd_splited[0], "export") == 0)
	{
		(*control)[0] = FALSE;
		ft_export(cmd_list->cmd_splited[1], struct_input);
	}
	else if (ft_strcmp(cmd_list->cmd_splited[0], "unset") == 0)
	{
		(*control)[0] = FALSE;
		ft_unset(cmd_list->cmd_splited[1], struct_input);
	}
	else if (ft_strcmp(cmd_list->cmd_splited[0], "env") == 0)
	{
		(*control)[0] = FALSE;
		ft_print_var(*struct_input);
	}
	else if (ft_strcmp(cmd_list->cmd_splited[0], "exit") == 0)
	{
		(*control)[0] = FALSE;
		ft_eexit(cmd_list->cmd_splited, struct_input, step);
	}
	return (0);
}

int	ft_built_in1(t_var_parsed_table	*cmd_list, \
t_input **struct_input, int (*control)[2], t_step *step)
{
	if (ft_strcmp(cmd_list->cmd_splited[0], "echo") == 0)
	{
		if ((*control)[1] == FALSE)
			ft_echo(cmd_list->cmd_splited, 1);
		else
			ft_echo(cmd_list->cmd_splited, cmd_list->fd_out);
		(*control)[0] = FALSE;
	}
	else if (ft_strcmp(cmd_list->cmd_splited[0], "pwd") == 0)
	{
		(*control)[0] = FALSE;
		ft_pwd(struct_input);
	}
	else if (ft_strcmp(cmd_list->cmd_splited[0], "cd") == 0)
	{
		(*control)[0] = FALSE;
		ft_cd(cmd_list->cmd_splited, struct_input);
	}
	else
		ft_built_in2(cmd_list, struct_input, control, step);
	return (0);
}

int	ft_is_built_in(t_var_parsed_table *cmd_list)
{
	if (ft_strcmp(cmd_list->cmd_splited[0], "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd_list->cmd_splited[0], "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd_list->cmd_splited[0], "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd_list->cmd_splited[0], "export") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd_list->cmd_splited[0], "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd_list->cmd_splited[0], "env") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd_list->cmd_splited[0], "exit") == 0)
		return (TRUE);
	return (FALSE);
}
