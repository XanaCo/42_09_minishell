/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/31 12:18:00 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function will launch the first process, 
checking redirections and duping to pipes if necessary
*/
void	first_process(t_mini *shell, t_tree *node)
{
	t_tree	*iter;
	int		is_redir_out;

	is_redir_out = 0;
	iter = node;
	while (iter && iter->tktype != TK_EXEC)
	{	
		if (iter->tktype == TK_SUP || iter->tktype == TK_DSUP)
			is_redir_out = 1;
		check_redirections(shell, iter);
		iter = iter->left;
	}
	if (shell->n_pipes != 0 && !is_redir_out)
	{
		if (dup2(shell->pipe[0][1], STDOUT_FILENO) == -1)
			free_and_exit(shell, NULL, errno);
	}
	close_all_pipes(shell);
	exec_cmd(shell, iter);
}

/*
This function will launch the last process, 
checking redirections and duping to pipes if necessary
*/
void	last_process(t_mini *shell, t_tree *node)
{
	t_tree	*iter;
	int		is_redir_in;

	is_redir_in = 0;
	iter = node;
	while (iter && iter->tktype != TK_EXEC)
	{	
		if (iter->tktype == TK_INF || iter->tktype == TK_DINF)
			is_redir_in = 1;
		check_redirections(shell, iter);
		iter = iter->left;
	}
	if (!is_redir_in)
	{
		if (dup2(shell->pipe[shell->n_pipes - 1][0], STDIN_FILENO) == -1)
			free_and_exit(shell, NULL, errno);
	}
	close_all_pipes(shell);
	exec_cmd(shell, iter);
}

static void	dup_middle_in(t_mini *shell, int i)
{
	if (dup2(shell->pipe[i - 1][0], STDIN_FILENO) == -1)
		free_and_exit(shell, NULL, errno);
}

static void	dup_middle_out(t_mini *shell, int i)
{
	if (dup2(shell->pipe[i][1], STDOUT_FILENO) == -1)
		free_and_exit(shell, NULL, errno);
}

/*
This function will launch the middle tourning process, 
checking redirections and duping to pipes if necessary as the others do
*/
void	middle_process(t_mini *shell, t_tree *node, int i)
{
	t_tree	*iter;
	int		is_redir_out;
	int		is_redir_in;

	is_redir_out = 0;
	is_redir_in = 0;
	iter = node;
	while (iter && iter->tktype != TK_EXEC)
	{	
		if (iter->tktype == TK_SUP || iter->tktype == TK_DSUP)
			is_redir_out = 1;
		if (iter->tktype == TK_INF || iter->tktype == TK_DINF)
			is_redir_in = 1;
		check_redirections(shell, iter);
		iter = iter->left;
	}
	if (!is_redir_in)
		dup_middle_in(shell, i);
	if (!is_redir_out)
		dup_middle_out(shell, i);
	close_all_pipes(shell);
	exec_cmd(shell, iter);
}
