/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28_cmd_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:01:29 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/08 10:52:11 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	**cmd_handle_1(t_var_parsed_table *cmd, \
t_input **env, char **path_env)
{
	char	**posible_paths;

	posible_paths = NULL;
	if (!cmd->cmd)
		return (NULL);
	else if (ft_strlen(cmd->cmd_splited[0]) == 0)
		return (print_error(10, cmd->cmd_splited[0], env), NULL);
	*path_env = ft_getenv(&(*env)->ent_var, "PATH");
	if (!(*path_env))
		return (NULL);
	posible_paths = ft_split(*path_env, ':');
	return (posible_paths);
}

static int	cmd_handle2(t_var_parsed_table *cmd, t_input **env, int *control)
{
	struct stat	statbuf;

	if (stat(cmd->cmd_splited[0], &statbuf) == -1)
		return (print_error(8, cmd->cmd_splited[0], env), FALSE);
	if (access(cmd->cmd_splited[0], X_OK) != 0)
	{
		print_error(10, cmd->cmd_splited[0], env);
		*control = FALSE;
	}
	if (S_ISDIR(statbuf.st_mode))
		return (print_error(14, NULL, env), FALSE);
	cmd->path = ft_strdup(cmd->cmd_splited[0]);
	return (TRUE);
}

static int	cmd_handle3(t_var_parsed_table *cmd, char *path_env, \
t_input **env, char **posible_paths)
{
	int	control;

	control = TRUE;
	if (ft_is_built_in(cmd) == TRUE)
		control = TRUE;
	else if (cmd->cmd_splited[0][0] == '/')
	{
		if (cmd_handle2(cmd, env, &control) == FALSE)
			return (free_double(posible_paths), free(path_env), FALSE);
	}
	else if (cmd->cmd_splited[0][0] == '.' && cmd->cmd_splited[0][1] == '/')
	{
		if (relative_path(cmd, env) == FALSE)
			control = FALSE;
	}
	else
	{
		if (ft_verify_cmd(posible_paths, cmd, env) == FALSE)
			control = FALSE;
	}
	if (control == FALSE)
		return (free_double(posible_paths), free(path_env), FALSE);
	return (TRUE);
}

int	cmd_handle(t_var_parsed_table **cmd_list, t_input **env)
{
	t_var_parsed_table	*cmd;
	char				*path_env;
	char				**posible_paths;

	cmd = *cmd_list;
	posible_paths = cmd_handle_1(cmd, env, &path_env);
	if (!posible_paths)
		return (FALSE);
	while (cmd && (cmd->cmd != NULL))
	{
		if (cmd_handle3(cmd, path_env, env, posible_paths) == FALSE)
			return (FALSE);
		cmd = cmd->next;
	}
	return (free(path_env), free_double(posible_paths), TRUE);
}
