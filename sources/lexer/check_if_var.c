/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:40:24 by alexa             #+#    #+#             */
/*   Updated: 2024/12/09 17:31:55 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->str[i])
	{
		if ((*token_node)->str[i] == '$')
		{	
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

int	check_if_var(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE)
	{
		errmsg("syntax error near unexpected token", temp->str, true);
		return (FAILURE);
	}
	while (temp)
	{
		variable_check(&temp);
		if (check_consecutives(&temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}
