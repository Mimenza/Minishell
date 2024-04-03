/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:41:16 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/03 15:41:55 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Main function to remove the quotes
void	remove_quotes(t_var_parsed_table **head)
{
	t_var_parsed_table	*first;
	int					i;

	first = *head;
	while ((*head) != NULL)
	{
		i = 0;
		if ((*head)->cmd_splited != NULL)
		{
			while ((*head)->cmd_splited[i] != NULL)
			{
				remove_quotes_aux(&(*head)->cmd_splited[i], 0);
				i++;
			}
		}
		(*head) = (*head)->next;
	}
	*head = first;
}

//Handles the simple quotes
static void	single_quote(char **cmd_ptr, int *control, \
int *a, char **joined_tmp)
{
	char	*tmp;

	tmp = NULL;
	if ((*cmd_ptr)[a[CUR]] == '\'' && control[DOUBLE] == FALSE)
	{
		if (control[SIMPLE] == FALSE)
		{
			a[START] = a[CUR];
			control[SIMPLE] = TRUE;
			if (a[QUOTES] == 1)
				tmp = ft_substr(*cmd_ptr, a[END] + 1, a[START] - a[END] - 1);
			else
				tmp = ft_substr(*cmd_ptr, a[END], a[START] - a[END]);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 15);
		}
		else
		{
			a[QUOTES] = 1;
			a[END] = a[CUR];
			control[SIMPLE] = FALSE;
			tmp = ft_substr(*cmd_ptr, a[START] + 1, a[END] - a[START] - 1);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 15);
		}
	}
}

//Handles the double quotes
static void	double_quote(char **cmd_ptr, int *control, \
int *a, char **joined_tmp)
{
	char	*tmp;

	tmp = NULL;
	if ((*cmd_ptr)[a[CUR]] == '\"' && control[SIMPLE] == FALSE)
	{
		if (control[DOUBLE] == FALSE)
		{
			a[START] = a[CUR];
			control[DOUBLE] = TRUE;
			if (a[QUOTES] == 1)
				tmp = ft_substr(*cmd_ptr, a[END] + 1, a[START] - a[END] - 1);
			else
				tmp = ft_substr(*cmd_ptr, a[END], a[START] - a[END]);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 15);
		}
		else
		{
			a[QUOTES] = 1;
			a[END] = a[CUR];
			control[DOUBLE] = FALSE;
			tmp = ft_substr(*cmd_ptr, a[START] + 1, a[END] - a[START] - 1);
			*joined_tmp = ft_strjoin(*joined_tmp, tmp, 15);
		}
	}
}

//Handles the remaining quotes(last one)
static void	process_remaining_quotes(char **cmd_ptr, \
char **joined_tmp, int *vault)
{
	char	*tmp;

	tmp = NULL;
	if (vault[QUOTES] == 1)
	{
		tmp = ft_substr(*cmd_ptr, vault[END] + 1, vault[SIZE] - vault[END]);
		*joined_tmp = ft_strjoin(*joined_tmp, tmp, 15);
		free(*cmd_ptr);
		*cmd_ptr = *joined_tmp;
	}
	else
		free(*joined_tmp);
}

//Aux function to remove the quotes
void	remove_quotes_aux(char **cmd_ptr, int mode)
{
	int		control[2];
	int		vault[5];
	char	*tmp;
	char	*joined_tmp;

	tmp = NULL;
	if (mode == 1)
		joined_tmp = ft_strdup("$");
	else
		joined_tmp = ft_strdup("");
	vault[QUOTES] = 0;
	vault[SIZE] = ft_strlen(*cmd_ptr) - 1;
	vault[START] = 0;
	vault[CUR] = 0;
	vault[END] = 0;
	control[SIMPLE] = FALSE;
	control[DOUBLE] = FALSE;
	while (vault[CUR] <= vault[SIZE])
	{
		single_quote(cmd_ptr, control, vault, &joined_tmp);
		double_quote(cmd_ptr, control, vault, &joined_tmp);
		vault[CUR]++;
	}
	process_remaining_quotes(cmd_ptr, &joined_tmp, vault);
}
