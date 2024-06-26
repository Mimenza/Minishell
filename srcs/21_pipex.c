/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:13:42 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/08 19:13:07 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

extern int	g_exit;

//Custom function to get the env
char	*ft_getenv(t_var_list **list, char *name)
{
	t_var_list	*current;
	char		*content;

	current = *list;
	content = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			content = ft_strdup(current->content);
			return (content);
		}
		current = current->next;
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		diff;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	while ((s1[i] != '\0' || s2[i] != '\0') && s1[i] == s2[i])
		i++;
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (diff);
}

//Main pipex function
int	pipex(t_input **struct_input, t_step *step)
{
	int					fd[2];
	t_var_parsed_table	*cmd_list;
	int					control[2];

	control[0] = TRUE;
	control[1] = TRUE;
	cmd_list = (*struct_input)->parsed_table;
	exec_signal_receiver();
	if (!cmd_list->next)
		ft_built_in1(cmd_list, struct_input, &control, step);
	if (control[0] == FALSE)
		return (0);
	fd[READ] = 0;
	fd[WRITE] = 0;
	ft_make_process(cmd_list, fd, struct_input, step);
	if (access(".tempfile.txt", F_OK) == 0)
		unlink(".tempfile.txt");
	if (g_exit != 0)
		ft_var_found(&(*struct_input)->ent_var, "?", ft_itoa(g_exit));
	g_exit = 0;
	return (0);
}
