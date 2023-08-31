/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/29 19:50:17 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exit_error(t_mini *shell, t_tree *node)
{
	long long	res;

	ft_putstr_fd("exit\n", 1);
	if (node->exec.cmd_op[1]
		&& ft_atoi_ptr(node->exec.cmd_op[1], &res))
		free_and_exit(shell, node->exec.cmd_op[1], -4);
	else if (node->exec.cmd_op[2])
	{
		error_handling_custom(node->exec.cmd, -5);
		return (1);
	}
	else if (node->exec.cmd_op[1]
		&& !ft_atoi_ptr(node->exec.cmd_op[1], &res))
	{	
		g_error_value = res;
		free_and_exit(shell, NULL, 0);
	}
	return (0);
}

/*
The exit function will make an exit depending on the state of the line
and the arguments given. The builtin will work as exit in bash,
with no options but taking numeric arguments to exit minishell
*/
int	bltn_exit(t_mini *shell, t_tree *node)
{
	if (!shell->line.content || !node
		|| !ft_strcmp(shell->line.content, "exit"))
	{	
		ft_putstr_fd("exit\n", 1);
		free_and_exit(shell, NULL, 0);
	}
	else if (shell->tree && shell->tree->tktype != TK_EXEC)
		free_and_exit(shell, NULL, 0);
	return (exit_error(shell, node));
}
