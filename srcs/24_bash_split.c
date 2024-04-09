/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_bash_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 06:51:35 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/09 12:50:00 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	ignore_separator(char const *s, int *control, int *i, int mode)
{
	if (mode == 1)
		(*i)++;
	if ((control[0] == TRUE && control[1] == TRUE) && s[*i] == '\'')
		control[0] = FALSE;
	else if (control[0] == FALSE && s[*i] == '\'')
		control[0] = TRUE;
	else if ((control[1] == TRUE && control[0] == TRUE) && s[*i] == '\"')
		control[1] = FALSE;
	else if (control[1] == FALSE && s[*i] == '\"')
		control[1] = TRUE;
}

static int	ft_count(char const *s, int array[2], int *control)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if ((s[i] != array[0] && s[i] != '\0') && \
	(s[i] != array[1] && s[i] != '\0'))
		count++;
	while (s[i])
	{
		ignore_separator(s, control, &i, 0);
		if (((control[0] == TRUE && control[1] == TRUE) \
		&& ((s[i] == array[0]) && (s[i + 1] != array[0]))) || \
		(((s[i] == array[1]) && (s[i + 1] != array[1])) && (s[i + 1])))
			count++;
		i++;
	}
	return (count);
}

static int	check_str(char **str, int j)
{
	if (str[j - 1] == NULL)
	{
		free_double(str);
		return (TRUE);
	}
	return (FALSE);
}

static void	ft_bash_split_aux(char const *s, int *c, int array[2], int (*a)[4])
{
	ignore_separator(s, c, a[I], 0);
	while (((s[(*a)[I]] == array[0]) || (s[(*a)[I]] == array[1])) && \
	(c[1] == TRUE && c[0] == TRUE))
		ignore_separator(s, c, (a[I]), 1);
	(*a)[START_] = (*a)[I];
	while ((((s[(*a)[I]] != array[0]) && (s[(*a)[I]] != array[1])) && \
	s[(*a)[I]]) || (c[1] == FALSE || c[0] == FALSE))
		ignore_separator(s, c, a[I], 1);
	(*a)[END_] = (*a)[I];
}

char	**ft_bash_split(char const *s, int array[2], int *c)
{
	int		a[4];
	char	**str;

	a[I] = 0;
	a[J] = 0;
	str = ft_calloc(ft_count(s, array, c) + 1, sizeof(char *));
	if (!s || !str)
		return (NULL);
	while (s[a[I]] && (c[1] == TRUE && c[0] == TRUE))
	{
		ft_bash_split_aux(s, c, array, &a);
		if ((a[END_] > a[START_]))
		{
			str[a[J]++] = ft_substr(s, a[START_], a[END_] - a[START_]);
			if (check_str(str, a[J]))
				return (NULL);
		}
	}
	return (str);
}
