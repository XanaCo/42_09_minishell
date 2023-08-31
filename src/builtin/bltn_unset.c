/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/29 19:54:09 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_export(char *str)
{
	size_t	i;

	i = 0;
	if (!str[0])
		return (-1);
	if (str && str[i] == '=')
		return (-1);
	while (str && str[i] && str[i] != '=')
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (-1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		if (str[i + 1] == '\0')
			return (3);
		i++;
	}
	return (1);
}

void	ft_lstdel_env(t_env **env, char *to_del)
{
	t_env	*prev;
	t_env	*cur;

	if (*env == NULL || !to_del)
		return ;
	prev = NULL;
	cur = *env;
	while (cur != NULL && cur->var && ft_strcmp(to_del, cur->var) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		return ;
	if (prev == NULL)
		*env = cur->next;
	else
		prev->next = cur->next;
}

/*
*/
int	bltn_unset(t_mini *shell, t_tree *node)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (node->exec.cmd_op[i])
	{
		if (!node->exec.cmd_op[i][0])
		{
			error++;
			error_handling_custom(node->exec.cmd_op[i], -6);
		}
		ft_lstdel_env(&shell->env, node->exec.cmd_op[i]);
		i++;
	}
	if (error > 0)
		return (1);
	return (0);
}
