/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_look_for_dollars_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:53:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/05 08:18:11 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Trims the token looking for the var name
static int	ft_trim_var_dollar(char *token, t_var_list **v_list, \
char **content, int index)
{
	char	*match_var_name;
	char	*tmp;
	char	*src[3];

	src[BEFORE] = NULL;
	src[AFTER] = NULL;
	src[2] = NULL;
	tmp = NULL;
	ft_trim_var_dollar_aux(token, &src, &match_var_name, index);
	ft_find_variable(match_var_name, v_list, content);
	tmp = ft_strjoin((*content), src[AFTER], 15);
	(*content) = ft_strjoin(src[BEFORE], tmp, 15);
	free(match_var_name);
	return (FALSE);
}

static void	ft_trim_var_dollar_aux(char *token, char *(*src)[3], \
char **var_name, int index)
{
	int		size;
	int		size1;
	int		size2;

	size2 = 0;
	size1 = -1;
	size = 0;
	while (token[size] && ((size != index) || ((token[size] != '$') && \
	(!(isalpha(token[size + 1])) || (token[size + 1] == '?')))))
		size++;
	(*src)[BEFORE] = malloc(sizeof(char) * (size + 1));
	while (++size1 < size)
		(*src)[BEFORE][size1] = token[size1];
	(*src)[BEFORE][size1++] = '\0';
	while (token[size1] && ((token[size1] != '\'') && (token[size1] != '\"') && \
	(token[size1] != '$') && (token[size1] != '/') && (token[size1] != ' ')))
		size1++;
	(*src)[AFTER] = malloc(sizeof(char) * (ft_strlen(token) - size1 + 1));
	while (token[size1])
		(*src)[AFTER][size2++] = token[size1++];
	(*src)[AFTER][size2] = '\0';
	*var_name = ft_substr(token, (size + 1), (size1 - size - size2 - 1));
}

//Check in the given input if a variable call is detected
int	ft_look_4_dollar(char const *token, t_var_list **v_list, char **content)
{
	int	i;
	int	max;
	int	quotes[3];

	quotes[SIMPLE] = FALSE;
	quotes[DOUBLE] = FALSE;
	quotes[RES] = 0;
	max = ft_strlen(*content);
	i = 0;
	while (i < max)
	{
		ft_look_4_d_aux(content, &i, v_list, &quotes);
		max = ft_strlen(*content);
		i++;
	}
	return (FALSE);
}

static void	ft_look_4_d_aux(char **content, int *i, \
t_var_list **v_list, int (*quotes)[3])
{
	if ((*content)[*i] == '\'')
	{
		(*quotes)[SIMPLE] = !(*quotes)[SIMPLE];
		(*quotes)[RES] = 1;
	}
	if ((*content)[*i] == '\"')
	{
		(*quotes)[DOUBLE] = !(*quotes)[DOUBLE];
		(*quotes)[RES] = 2;
	}
	if ((*quotes)[DOUBLE] == 0 && (*quotes)[SIMPLE] == 0 && \
	(*content)[*i] == '$' && ((*content)[*i + 1] == '\'' || \
	(*content)[*i + 1] == '\"'))
	{
		del_char(content, *i);
		*i = -1;
	}
	else if (((*quotes)[SIMPLE] == 0 || ((*quotes)[SIMPLE] == 1 && \
	(*quotes)[DOUBLE] == 1 && (*quotes)[RES] == 1)) && \
	((*content)[*i] == '$' && (isalpha((*content)[*i + 1]) || \
	(*content)[*i + 1] == '_' || (*content)[*i + 1] == '?')))
	{
		ft_trim_var_dollar(*content, v_list, content, *i);
		*i = -1;
	}
}
