/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:43:59 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/08 10:48:07 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Custom echo function
void	ft_echo(char **args, int fd)
{
	size_t	i;
	int		control;

	i = -1;
	control = FALSE;
	args++;
	while (args[0] && (ft_strcmp(args[0], "-n") == 0))
	{
		control = TRUE;
		args++;
	}
	while (args[++i])
	{
		if (i != 0)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(args[i], fd);
	}
	if (control == FALSE)
		ft_putstr_fd("\n", fd);
}

//Custom pwd function
int	ft_pwd(t_input **env)
{
	t_var_list	*current;

	current = (*env)->ent_var;
	while (ft_strcmp(current->name, "PWD") != 0)
		current = current->next;
	printf("%s\n", current->content);
	return (0);
}

int	get_path_utils(char **path, char **route, char *tmp, char *args)
{
	size_t	i;

	i = -1;
	path = ft_split(args, '/');
	if (!path)
		return (1);
	*route = getcwd(NULL, 0);
	while (path[++i])
	{
		if ((ft_strcmp(path[i], "..") == 0))
		{
			tmp = *route;
			*route = ft_substr(*route, 0, ft_strrchr(*route, '/') - *route);
			free(tmp);
		}
		else
		{
			*route = ft_strjoin(*route, "/", 3);
			*route = ft_strjoin(*route, path[i], 3);
			if (access(*route, X_OK) != 0)
				return (print_error(8, path[i], NULL), \
				free(*route), free_double(path), 1);
		}
	}
	return (free_double(path), 0);
}

//Custom path funcion
int	get_path(char *args, t_input **env)
{
	char		**path;
	char		*tmp;
	char		*route;
	t_var_list	*current;

	path = NULL;
	tmp = NULL;
	current = (*env)->ent_var;
	while (ft_strcmp(current->name, "PWD") != 0)
		current = current->next;
	if (args[0] == '/')
	{
		if (access(args, X_OK) != 0)
			return (print_error(8, args, NULL), 1);
		ft_var_found(&(*env)->ent_var, "OLDPWD", current->content);
		current->content = ft_strdup(args);
		return (chdir(args), 0);
	}
	if (get_path_utils(path, &route, tmp, args) != 0)
		return (1);
	tmp = current->content;
	ft_var_found(&(*env)->ent_var, "OLDPWD", current->content);
	current->content = ft_strdup(route);
	return (chdir(route), free(tmp), free(route), 0);
}

//Custom cd funcion
int	ft_cd(char **args, t_input **env)
{
	size_t		i;
	char		*home;
	t_var_list	*current;

	i = 0;
	current = (*env)->ent_var;
	while (ft_strcmp(current->name, "PWD") != 0)
		current = current->next;
	while (args[i])
		i++;
	if (i > 1)
		get_path(args[1], env);
	else
	{
		home = getenv("HOME");
		if (access(home, X_OK) == 0)
		{
			if (chdir(home) != 0)
				return (1);
		}
		ft_var_found(&(*env)->ent_var, "OLDPWD", current->content);
		free(current->content);
		current->content = ft_strdup(home);
	}
	return (0);
}
