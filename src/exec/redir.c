/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 22:03:48 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function will check if there are redirection nodes in the tree
*/
void	check_redirections(t_mini *shell, t_tree *node)
{
	if (node->tktype == TK_DINF)
		redir_hd(shell, node);
	if (node->tktype == TK_INF)
		redir_in(shell, node);
	if (node->tktype == TK_SUP || node->tktype == TK_DSUP)
		redir_out(shell, node);
}

/*
*/
void	redir_hd(t_mini *shell, t_tree *node)
{
	if (pipe(node->hd_fd) == -1)
		free_and_exit(shell, NULL, errno);
	if (node->heredoc)
	{
		while (node->heredoc)
		{
			ft_putstr_fd(node->heredoc->content, node->hd_fd[1]);
			node->heredoc = node->heredoc->next;
		}
	}
	close(node->hd_fd[1]);
	if (dup2(node->hd_fd[0], STDIN_FILENO) == -1)
		free_and_exit(shell, NULL, errno);
	close(node->hd_fd[0]);
}

/*
*/
void	redir_in(t_mini *shell, t_tree *node)
{
	int	i_fd;

	i_fd = open(node->file_name, O_RDONLY, 0755);
	if (i_fd == -1)
	{
		g_error_value = 1;
		if (!access(node->file_name, F_OK))
			free_and_exit(shell, node->file_name, EACCES);
		else
			free_and_exit(shell, node->file_name, ENOENT);
	}
	if (dup2(i_fd, STDIN_FILENO) == -1)
		free_and_exit(shell, node->file_name, errno);
	close(i_fd);
}

/*
*/
void	redir_out(t_mini *shell, t_tree *node)
{
	int	o_fd;

	if (node->tktype == TK_SUP)
		o_fd = open(node->file_name, O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (node->tktype == TK_DSUP)
		o_fd = open(node->file_name, O_RDWR | O_CREAT | O_APPEND, 0755);
	if (o_fd == -1)
	{
		g_error_value = 1;
		free_and_exit(shell, node->file_name, EACCES);
	}
	if (dup2(o_fd, STDOUT_FILENO) == -1)
		free_and_exit(shell, node->file_name, errno);
	close(o_fd);
}
