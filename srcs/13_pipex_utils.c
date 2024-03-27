/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:46:50 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/27 08:37:27 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incs/minishell.h"

//Checks the joined paths and check if is the correct
int	ft_verify_cmd(char **paths, t_var_parsed_table *cmd, t_input **env)
{
	size_t	i;
	char	*str;
	char	*str_tmp;
	int		control;
	
	control = TRUE;
	i = -1;
	if (ft_strcmp(cmd->cmd_splited[0], ".") == 0)
		return(print_error(12, cmd->cmd_splited[0], env), FALSE);
	else if (ft_strcmp(cmd->cmd_splited[0], "..") == 0)
		return(print_error(10, cmd->cmd_splited[0], env), FALSE);
	while(paths[++i])
	{
		str_tmp = ft_strjoin("/", cmd->cmd_splited[0], 1);
		str = ft_strjoin(paths[i], str_tmp, 5);
		if (access(str, X_OK) == 0)
		{
			cmd->path = str;
			return (TRUE);
		}
	free(str);
	}
	print_error(10, cmd->cmd_splited[0], env);
	return (FALSE);
}

int	ft_close_pipes(int fd[2])
{
	if (close(fd[READ]) < 0)
		return (1);
	if (close(fd[WRITE]) < 0)
		return (1);
	return (0);
}

//Function for relative paths
int	relative_path(t_var_parsed_table *cmd, t_input **env)
{
	char		**path;
	char		*route;
	char		*route_tmp;
	size_t		i;

	i = -1;
	path = ft_split(cmd->cmd_splited[0], '/');
	route = getcwd(NULL, 0);
	while (path[++i])//rutas relativas
	{
		if((ft_strcmp(path[i], "..") == 0))
		{
			route = ft_substr(route, 0, ft_strrchr(route, '/') - route);
			chdir(route);
		}
		else if (!(path[i][0] == '.' && ft_strlen(path[i]) == 1))
		{
			route_tmp = ft_strjoin(route, "/", 3);
			route = ft_strjoin(route_tmp, path[i], 3);
			if (access(route, X_OK) != 0)
				return (print_error(8, cmd->cmd_splited[0], env), free(route), free_double(path), FALSE);
		}
	}
	cmd->path = route;
	return (free_double(path), TRUE);
}

//Joins the posible paths and checks if there is any available
// int	cmd_handle(t_var_parsed_table **cmd_list, t_input **env, t_step *step)//LA ORIGINAL
// {
// 	t_var_parsed_table	*cmd;
// 	char				*path_env;
// 	char				**posible_paths;
// 	int					control;
// 	struct stat			statbuf;

// 	cmd = *cmd_list;
// 	if (!cmd->cmd)
// 		return (FALSE);
// 	else if (ft_strlen(cmd->cmd_splited[0]) == 0)
// 		return (print_error(10, cmd->cmd_splited[0], env), FALSE);
// 	control = TRUE;
// 	path_env = ft_getenv(&(*env)->ent_var, "PATH");
// 	if (!path_env)
// 		return(FALSE);
// 	posible_paths = ft_split(path_env, ':');
// 	while(cmd)
// 	{
// 		if (cmd->cmd == NULL)
// 			break;
// 		if (ft_built_in(cmd, env, NULL, 0, step) == TRUE)
// 			control = TRUE;
// 		else if (cmd->cmd_splited[0][0] == '/')
// 		{
// 			if (stat(cmd->cmd_splited[0], &statbuf) == -1)
// 				return (print_error(8, cmd->cmd_splited[0], env), free_double(posible_paths), free(path_env), FALSE);
// 			if (access(cmd->cmd_splited[0], X_OK) != 0)
// 			{
// 				print_error(10, cmd->cmd_splited[0], env);
// 				control = FALSE;
// 			}
// 			if (S_ISDIR(statbuf.st_mode))
// 				return(print_error(14, NULL, env), free_double(posible_paths), free(path_env), FALSE);
// 			cmd->path = ft_strdup(cmd->cmd_splited[0]);
// 		}
// 		else if (cmd->cmd_splited[0][0] == '.' && cmd->cmd_splited[0][1] == '/')
// 		{
// 			if (relative_path(cmd, env) == FALSE)
// 				control = FALSE;
// 		}
// 		else
// 		{
// 			if (ft_verify_cmd(posible_paths, cmd, env) == FALSE)
// 				control = FALSE;
// 		}
// 		if (control == FALSE)
// 			return(free_double(posible_paths), free(path_env), FALSE);
// 		cmd = cmd->next;
// 	}
// 	return (free(path_env), free_double(posible_paths), TRUE);
// }


int	cmd_handle(t_var_parsed_table **cmd_list, t_input **env, t_step *step)
{
	t_var_parsed_table	*cmd;
	char				*path_env;
	char				**posible_paths;
	int					control;
	struct stat			statbuf;

	cmd = *cmd_list;
	if (!cmd->cmd)
		return (FALSE);
	else if (ft_strlen(cmd->cmd_splited[0]) == 0)
		return (print_error(10, cmd->cmd_splited[0], env), FALSE);
	control = TRUE;
	path_env = ft_getenv(&(*env)->ent_var, "PATH");
	if (!path_env)
		return(FALSE);
	posible_paths = ft_split(path_env, ':');
	while(cmd)
	{
		if (cmd->cmd == NULL)
			break;
		if (ft_is_built_in(cmd, env, NULL, 0, step) == TRUE)
			control = TRUE;
		else if (cmd->cmd_splited[0][0] == '/')
		{
			if (stat(cmd->cmd_splited[0], &statbuf) == -1)
				return (print_error(8, cmd->cmd_splited[0], env), free_double(posible_paths), free(path_env), FALSE);
			if (access(cmd->cmd_splited[0], X_OK) != 0)
			{
				print_error(10, cmd->cmd_splited[0], env);
				control = FALSE;
			}
			if (S_ISDIR(statbuf.st_mode))
				return(print_error(14, NULL, env), free_double(posible_paths), free(path_env), FALSE);
			cmd->path = ft_strdup(cmd->cmd_splited[0]);
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
			return(free_double(posible_paths), free(path_env), FALSE);
		cmd = cmd->next;
	}
	return (free(path_env), free_double(posible_paths), TRUE);
}

//Custom here doc function
int	ft_here_doc(char *end, int fd)
{
	char	*delimiter;
	char	*line;
	int		outfile;
	char	*output;
	char	*tmp;

	if (end == NULL)
		return (print_error(11, NULL, NULL), 1);
	remove_quotes_aux(&end);
	output = (char *)malloc(sizeof(char) * 1);
	output[0] = '\0';
	delimiter = ft_strjoin(end, "\n", 1);
	while (1)
	{
		write(1,"Minishell heredoc> ", 19);
		line = get_next_line(fd);
		if (ft_strcmp(delimiter, line) == 0)
			break ;
		output = ft_strjoin(output, line, 15);
	}
	free_here_doc(delimiter, output, line, &outfile);
	return (outfile);
}

//Free the here doc utils
void	free_here_doc(char *delimiter, char *output, char *line, int *outfile)
{
	*outfile = open(".tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		return ;
	if (write(*outfile, output, ft_strlen(output)) == -1)
		return ;
	free(delimiter);
	free(output);
	free(line);
	line = NULL;
	if (close(*outfile) < 0)
		return ;
	*outfile = open(".tempfile.txt", O_RDONLY);
}
