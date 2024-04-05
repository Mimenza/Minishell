/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_look_for_dollars_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:19:28 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/05 08:17:01 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Deletes the char on the N position
void	del_char(char **cadena, int position)
{
	char	*before;
	char	*after;
	int		size1;
	int		size2;
	int		tmp;

	size1 = 0;
	size2 = 0;
	tmp = 0;
	before = NULL;
	after = NULL;
	while (size1 != position)
		size1++;
	before = ft_substr((*cadena), 0, size1);
	tmp = size1;
	while ((*cadena)[++size1] != '\0')
		size2++;
	after = ft_substr(*cadena, (tmp + 1), size2);
	free((*cadena));
	*cadena = ft_strjoin(before, after, 15);
}

//Looks for a variable with the name vien
int	ft_find_variable(char *var_name, t_var_list **v_list, char **content)
{
	t_var_list	*current;

	current = *v_list;
	while (current)
	{
		if ((ft_strcmp(var_name, current->name) == 0 && \
		(ft_strlen(var_name) == ft_strlen(current->name))))
		{
			free(*content);
			(*content) = ft_strdup(current->content);
			return (TRUE);
		}
		current = current->next;
	}
	free(*content);
	(*content) = ft_strdup("");
	return (FALSE);
}

//Looks into the cmd looking for dollars and equals
void	expand_var_ent(t_var_parsed_table **table, t_input **struct_input)
{
	t_var_parsed_table	*current;
	int					i;
	char				**cmd;

	current = *table;
	if (!current->cmd)
		return ;
	while (current != NULL)
	{
		i = 0;
		if (current->cmd == NULL)
			break ;
		cmd = current->cmd_splited;
		while (cmd[i])
		{
			ft_look_4_dollar(cmd[i], &(*struct_input)->ent_var, &cmd[i]);
			ft_look_4_equal(cmd[i], &(*struct_input)->ent_var, 0);
			i++;
		}
		current = current->next;
	}
}
