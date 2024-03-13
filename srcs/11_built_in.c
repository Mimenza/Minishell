/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:43:59 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/13 16:01:37 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


void	ft_echo(char **args, int fd)
{
	size_t	i;

	i = 1;
	while(args[++i])
	{
		// printf("lo que hay para escirbir es %s\ni vale %zu\n", args[i], i);
		if (i != 2)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(args[i], fd);
	}
}

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return(1);
	printf("%s\n", path);
	return (0);
}

int	get_path(char *args, t_input **env)
{
	char		**path;
	char		*tmp;
	char		*route;
	size_t		i;
	t_var_list	*current;

	i =  -1;
	current = (*env)->ent_var;
	while(ft_strncmp(current->name, "PWD", 3) != 0)
		current = current->next;
	if(args[0] == '/')//rutas absolutas
	{
		if (access(args, X_OK) != 0)
			return(printf("no such file or directory: %s\n", args), 1);
		chdir(args);
		ft_pwd();
		current->content = ft_strdup(args);
		return(0);
	}
	path = ft_split(args, '/');
	route = getcwd(NULL, 0);
	if (!path)
		return(1);
	while (path[++i])//rutas relativas
	{
		if((ft_strncmp(path[i], "..", 2) == 0) && ft_strlen(path[i]) == 2)
		{
			route = ft_substr(route, 0, ft_strrchr(route, '/') - route);
			chdir(route);
		}
		else if (!(path[i][0] == '.' && ft_strlen(path[i]) == 1))
		{
			route = ft_strjoin(route, "/");
			route = ft_strjoin(route, path[i]);
			if (access(route, X_OK) != 0)
				return(printf("no such file or directory: %s\n", args), 1);
		}
	}
	chdir(route);
	current->content = ft_strdup(route);
	// printf("donde petas get path?\n");
	return(0);
}

int	ft_cd(char **args, t_input **env)
{
	size_t		i;
	char		*home;
	t_var_list	*current;

	i = 0;
	current = (*env)->ent_var;
	while(ft_strncmp(current->name, "PWD", 3) != 0)
		current = current->next;
	while (args[i])
	{
		// printf("tenemos %s\n", args[i]);
		i++;
	}
	if (i > 1)
		get_path(args[1], env);
	else
	{
		home = getenv("HOME");
		if(access(home, X_OK) == 0)
		{
			if (chdir(home) != 0)
			{
				printf("error\n");
				return(1);
			}
		}
		current->content = ft_strdup(home);
	}
	ft_pwd();
	return(0);
}

void add_var(char *name, t_var_list **env, char *content)
{
	t_var_list	*current;
	t_var_list	*new;

	current = *env;
	while(current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(current->name)) == 0)
		{
			if(content)
				current->content = ft_strdup(content);
			return ;
		}
		current = current->next;
	}
	new = (t_var_list *)malloc(sizeof(t_var_list));
	if(!new)
		return ;
	current = *env;
	while(current->next)
		current = current->next;
	new->name = ft_strdup(name);
	if (content)
		new->content = ft_strdup(content);
	current->next = new;
}

void ft_empty_export(t_var_list **env)
{
	t_var_list	*current;
	t_var_list	*name;
	int			size;

	size = 0;
	current = *env;
	while(current)
	{
		size++;
		current = current->next;
	}
	while(size > 0)
	{
		current = *env;
		name = current;
		while(current)
		{
			if(ft_strncmp(name->name, current->name, ft_strlen(name->name)) > 0 && current->is_printed == 0)
				name = current;
			current = current->next;
		}
		name->is_printed = 1;
		printf("declare -x %s=%s\n", name->name, name->content);
		size--;
	}
	current = *env;
	while(current)
	{
		current->is_printed = 0;
		current = current->next;
	}
}

int ft_export(char	*var, t_input **struct_input)
{
	char		*equal;
	char		*name;
	char		*content;

	if (var)
		equal = ft_strchr(var, '=');
	if(!var)
		ft_empty_export(&(*struct_input)->ent_var);
	else if (equal)
	{
		name = ft_substr(var, 0, equal - var);
		// printf("el nombre es %s\nel contenido %s\n", name, (equal + 1));
		add_var(name, &(*struct_input)->ent_var, (equal + 1));
	}
	else
		add_var(var, &(*struct_input)->ent_var, NULL);
}

void	ft_unset(char *name, t_input **struct_input)
{
	t_var_list *current;
	t_var_list *tmp;

	if (!name)
	{
		printf("No se hace nada\n");
		return ;
	}
	current = (*struct_input)->ent_var;
	// printf("Vamos a intentar quitar el primero a ver si funtxiona\n%s\n", name);
	printf("La primera variable es %s\n", current->name);
	if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)//seria para verificar si el primero 
	{
		printf("Llegamos a entrar aqui?\n");
		(*struct_input)->ent_var = current->next;
		free(current);
		return ;
	}
	while(current->next)
	{
		if (ft_strncmp(current->next->name, name, ft_strlen(name)) == 0)
		{
			tmp = current->next;
			if(current->next->next)
				current->next = current->next->next;
			else
				current->next = NULL;
			free(tmp);
			return ;
		}
		current = current->next;
	}
}

int	ft_built_in(char **argv, t_input **struct_input)
{
	if (ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0 && ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
		ft_echo(argv, 1);
	else if(ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) == 0)
		ft_pwd();
	else if(ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) == 0)
		ft_cd(argv, struct_input);
	else if(ft_strncmp(argv[0], "export", ft_strlen(argv[0])) == 0)
		ft_export(argv[1], struct_input);
	else if(ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
		ft_unset(argv[1], struct_input);
	else if(ft_strncmp(argv[0], "env", ft_strlen(argv[0])) == 0)
		ft_print_var(*struct_input);
	return (0);	
}
