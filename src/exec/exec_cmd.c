/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/31 12:13:40 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function simply executes the command,
choosing between builtin execution or execve
*/
void	exec_cmd(t_mini *shell, t_tree *node)
{
	if (!node || shell->hd_error)
		free_and_exit(shell, NULL, 0);
	if (check_built_in(node))
	{
		exec_built_in(shell, node);
		free_and_exit(shell, NULL, 0);
	}
	else
	{
		prepare_execve(shell, node);
		if (!node->exec.cmd_path)
		{
			if (errno == 2)
				free_and_exit(shell, node->exec.cmd, -1);
			free_and_exit(shell, node->exec.cmd, -10);
		}
		else if (execve(node->exec.cmd_path, node->exec.cmd_op,
				shell->env_t) == -1)
		{
			if (errno == 13)
				free_and_exit(shell, node->exec.cmd, -8);
			free_and_exit(shell, node->exec.cmd, -10);
		}	
	}
}

/*
This check does what it its name says, it checks if the command is a built-in
*/
int	check_built_in(t_tree *node)
{
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "echo")
			|| !ft_strcmp(node->exec.cmd, "cd")
			|| !ft_strcmp(node->exec.cmd, "pwd")
			|| !ft_strcmp(node->exec.cmd, "export")
			|| !ft_strcmp(node->exec.cmd, "unset")
			|| !ft_strcmp(node->exec.cmd, "env")
			|| !ft_strcmp(node->exec.cmd, "exit")))
		return (1);
	return (0);
}

/*
This function executes the builtin and updates the global value
*/
void	exec_built_in(t_mini *shell, t_tree *node)
{
	int	res;

	res = 0;
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "echo")))
		res = bltn_echo(shell, node);
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "cd")))
		res = bltn_cd(shell, node);
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "pwd")))
		res = bltn_pwd(shell, node);
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "export")))
		res = bltn_export(shell, node);
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "unset")))
		res = bltn_unset(shell, node);
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "env")))
		res = bltn_env(shell, node);
	if (node->exec.cmd && (!ft_strcmp(node->exec.cmd, "exit")))
		res = bltn_exit(shell, node);
	g_error_value = res;
}
