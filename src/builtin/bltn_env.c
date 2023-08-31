/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 15:14:57 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*/
int	bltn_env(t_mini *shell, t_tree *node)
{
	t_env	*iter;

	iter = shell->env;
	if (!iter || !node->exec.cmd)
		return (127);
	if (node->exec.cmd_op[1]
		|| ft_strncmp(node->exec.cmd, "env", 3) != 0)
	{	
		g_error_value = 127;
		free_and_exit(shell, node->exec.cmd_op[1], -9);
	}
	while (iter)
	{
		if (ft_strchr(iter->content, '='))
		{
			ft_putstr_fd((char *)iter->content, 1);
			ft_putstr_fd("\n", 1);
		}
		iter = iter->next;
	}
	return (0);
}
