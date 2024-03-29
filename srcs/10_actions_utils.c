/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_actions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:21:30 by anurtiag          #+#    #+#             */
/*   Updated: 2024/03/29 14:22:05 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Apply the action received 
void	apply_action(t_options *opts, t_step **c_step, \
t_token *c_token, int *end)
{
	int	action_type;

	action_type = opts->action;
	if (action_type == 0)
		ft_shift(&(*c_step)->tree_stack, &(*c_step)->input);
	else if (action_type == 1)
	{
		ft_reduce(opts, c_step);
		ret_to_prev(c_step);
	}
	else if (action_type == 2)
		*end = TRUE;
}
