/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 23:30:31 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Sarting point of the execution process. It will check first if we need 
child processes for the current line and choose acordingly
*/
void	execution_time(t_mini *shell, t_tree *node)
{
	if (!node)
		return ;
	if (!node->right && check_parent_built_in(node))
		main_process_exec(shell, node);
	else
		multi_process_exec(shell, node);
	return ;
}

/*
This function will launch only the commands that need to be executed 
in the main process (specific minishell built-ins)
*/
void	main_process_exec(t_mini *shell, t_tree *node)
{
	t_tree	*iter;

	iter = node;
	while (iter && iter->tktype != TK_EXEC)
	{	
		check_redirections(shell, iter);
		iter = iter->left;
	}
	if (!iter || shell->hd_error)
		return ;
	exec_built_in(shell, iter);
}

/*
This function starts the multiprocess execution. It will fork n_pipes + 1 
times to have the correct number of precesses, one for each command. It will
launch the processes depending on their position and check the last child return
*/
void	multi_process_exec(t_mini *shell, t_tree *node)
{
	t_tree	*iter;
	int		i;

	i = 0;
	iter = node;
	create_pipes(shell, node);
	while ((i < (shell->n_pipes + 1) && iter))
	{
		init_child_signals();
		shell->pids[i] = fork();
		if (shell->pids[i] == -1)
			free_and_exit(shell, NULL, errno);
		if (shell->pids[i] == 0 && i == 0)
			first_process(shell, iter);
		else if (shell->pids[i] == 0 && i == shell->n_pipes)
			last_process(shell, iter);
		else if (shell->pids[i] == 0 && i != shell->n_pipes && i != 0)
			middle_process(shell, iter, i);
		iter = iter->right;
		shell->n_hd--;
		i++;
	}
	close_all_pipes(shell);
	wait_for_all(shell);
	check_child_return(shell->wstatus);
}

/*
This checks let us know if the current builtin needs
to be executed in the main or child process
*/
int	check_parent_built_in(t_tree *node)
{
	t_tree	*iter;

	iter = node;
	while (iter && iter->tktype != TK_EXEC)
		iter = iter->left;
	if (iter && iter->exec.cmd
		&& (!ft_strcmp(iter->exec.cmd, "exit")
			|| !ft_strcmp(iter->exec.cmd, "export")
			|| !ft_strcmp(iter->exec.cmd, "unset")
			|| !ft_strcmp(iter->exec.cmd, "cd")))
		return (1);
	return (0);
}

/*
This is the function that get for us the exit value from the last child
*/
void	check_child_return(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_error_value = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		g_error_value = signal_handler_child(WTERMSIG(wstatus));
}
