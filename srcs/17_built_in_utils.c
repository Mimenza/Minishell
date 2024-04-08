/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_built_in_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:09:49 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/08 10:02:29 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	ft_empty_export_utils(t_var_list *current, \
t_var_list **env, t_var_list	*name, int *size)
{
	current = *env;
	name = current;
	while (name->is_printed == 1 && name->next)
		name = name->next;
	while (current)
	{
		if (ft_strcmp(name->name, current->name) > \
		0 && current->is_printed == 0)
			name = current;
		current = current->next;
	}
	name->is_printed = 1;
	if (name->content)
		printf("declare -x %s=%s\n", name->name, name->content);
	else
		printf("declare -x %s\n", name->name);
	(*size)--;
}

static void	ft_empty_export(t_var_list **env)
{
	t_var_list	*save;
	t_var_list	*current;
	t_var_list	*name;
	int			size;

	size = 0;
	current = *env;
	while (current)
	{
		size++;
		current = current->next;
	}
	while (size > 1)
		ft_empty_export_utils(current, env, name, &size);
	current = *env;
	while (current)
	{
		current->is_printed = 0;
		current = current->next;
	}
}

//Exports the var to the env
int	ft_export(char *var, t_input **struct_input)
{
	char	*equal;
	char	*name;
	char	*content;

	if (var && (var[0] == '_' || ft_isalpha(var[0]) == 0 || var[0] == '?'))
		return (print_error(1, NULL, struct_input), FALSE);
	if (var)
		equal = ft_strchr(var, '=');
	if (!var)
		ft_empty_export(&(*struct_input)->ent_var);
	else if (equal)
	{
		name = ft_substr(var, 0, equal - var);
		add_var(name, &(*struct_input)->ent_var, (equal + 1));
		free(name);
	}
	else
		add_var(var, &(*struct_input)->ent_var, NULL);
	return (TRUE);
}

//Custom exit funcion
void	ft_eexit(char **arg, t_input **struct_input, t_step *step)
{
	int	num;
	int	i;

	i = -1;
	if (!arg[1])
	{
		free_all(*struct_input, (*struct_input)->input);
		free_steps(step, 0);
		exit(0);
	}
	while (arg[1][++i])
	{
		if (!ft_isdigit((int)arg[1][i]))
		{
			printf("exit: %s: numeric argument required\n", arg[1]);
			free_all(*struct_input, (*struct_input)->input);
			free_steps(step, 0);
			exit(255);
		}
	}
	num = ft_atoi(arg[1]);
	free_all(*struct_input, (*struct_input)->input);
	free_steps(step, 0);
	printf("exit\n");
	exit(num % 256);
}

//Custom unset function
void	ft_unset(char *name, t_input **struct_input)
{
	t_var_list	*current;
	t_var_list	*tmp;

	if (!name || ft_strlen(name) == 0)
		return ;
	current = (*struct_input)->ent_var;
	if (ft_strcmp(current->name, name) == 0)
	{
		(*struct_input)->ent_var = current->next;
		return (free(current->content), free(current->name), free(current));
	}
	while (current->next)
	{
		if (ft_strcmp(current->next->name, name) == 0)
		{
			tmp = current->next;
			if (current->next->next)
				current->next = current->next->next;
			else
				current->next = NULL;
			return (free(tmp->name), free(tmp->content), free(tmp));
		}
		current = current->next;
	}
}
