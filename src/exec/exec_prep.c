/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 12:37:54 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*/
static int	no_path(t_env *root)
{
	t_env	*iter;

	iter = root;
	while (iter)
	{
		if (!ft_strcmp(iter->var, "PATH"))
			return (0);
		iter = iter->next;
	}
	return (1);
}

/*
*/
void	init_env_tab(t_mini *shell)
{
	t_env	*iter;
	int		i;

	i = 0;
	iter = shell->env;
	while (iter)
	{	
		iter = iter->next;
		i++;
	}
	shell->env_t = ft_calloc_gc(shell, TMP, i + 1, sizeof(char *));
	if (!shell->env_t)
		free_and_exit(shell, NULL, ENOMEM);
}

/*
*/
int	stock_envp(t_mini *shell)
{
	t_env	*iter;
	int		i;

	i = 0;
	iter = shell->env;
	init_env_tab(shell);
	while (iter)
	{
		if ((!ft_strcmp(iter->var, "PATH") && !iter->path))
			return (1);
		shell->env_t[i] = ft_strdup_gc(shell, TMP, iter->content);
		if (!shell->env_t[i])
			free_and_exit(shell, NULL, ENOMEM);
		iter = iter->next;
		i++;
	}
	return (0);
}

/*
*/
static void	check_other_cases(t_mini *shell, t_tree *node)
{
	if (ft_strchr(node->exec.cmd, '/') && !access(node->exec.cmd, F_OK))
			node->exec.cmd_path = ft_strdup_gc(shell, TMP, node->exec.cmd);
	else if (!ft_strcmp(node->exec.cmd, ":"))
	{	
		g_error_value = 0;
		free_and_exit(shell, NULL, 0);
	}
	else if (!ft_strcmp(node->exec.cmd, "!"))
	{	
		g_error_value = 1;
		free_and_exit(shell, NULL, 0);
	}
}

/*
This function will prepare and check the path needed 
to execute, testing existence and access, to be passed to execve
*/
void	prepare_execve(t_mini *shell, t_tree *node)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = node->exec.cmd;
	check_other_cases(shell, node);
	if (stock_envp(shell))
		return ;
	if (!ft_strchr(cmd, '/') && !no_path(shell->env))
	{
		cmd = ft_strjoin_gc(shell, TMP, "/", cmd);
		while (shell->path[i])
		{
			errno = 0;
			node->exec.cmd_path = ft_strjoin_gc(shell, TMP,
					shell->path[i], cmd);
			if (!access(node->exec.cmd_path, F_OK | X_OK))
				return ;
			i++;
		}
		node->exec.cmd_path = NULL;
	}
}
