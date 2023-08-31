/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/31 10:29:01 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function will create all pipes needed for the execution. 
If there are no pipes in the current line, n_pipes will stay 0
*/
void	create_pipes(t_mini *shell, t_tree *node)
{
	int		i;
	t_tree	*iter;

	i = 0;
	iter = node;
	shell->n_pipes = 0;
	while (iter && iter->tktype == TK_PIPE)
	{	
		iter = iter->right;
		shell->n_pipes++;
	}
	while (i < shell->n_pipes)
	{
		if (pipe(shell->pipe[i]) == -1)
			free_and_exit(shell, NULL, errno);
		i++;
	}
}

/*
This function closes all the pipes in the current process
*/
void	close_all_pipes(t_mini *shell)
{
	int		i;

	i = 0;
	while (i < shell->n_pipes)
	{
		close(shell->pipe[i][0]);
		close(shell->pipe[i][1]);
		i++;
	}
}

/*
This function will wait for every child process generated
*/
void	wait_for_all(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_pipes)
	{
		waitpid(shell->pids[i], NULL, 0);
		i++;
	}
	waitpid(shell->pids[shell->n_pipes], &shell->wstatus, 0);
}
