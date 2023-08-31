/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:42:08 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/28 14:42:13 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*/
void	init_hd_child_signal(void)
{
	signal(SIGINT, &sigint_handler_hd);
	signal(SIGQUIT, &sigquit_handler_hd);
	signal(SIGTSTP, SIG_IGN);
}

/*
*/
void	sigint_handler_hd(int signal)
{
	t_mini	*shell;

	g_error_value = 130;
	shell = locate_shell(NULL, 0);
	if (dup2(shell->hd_fd, 0) == -1)
		free_and_exit(shell, NULL, errno);
	close(shell->hd_fd);
	(void)signal;
}

/*
*/
void	sigquit_handler_hd(int signal)
{
	g_error_value = 130;
	(void)signal;
}

/*
*/
t_mini	*locate_shell(t_mini *ptr, int status)
{
	static t_mini	*shell;

	if (status)
		shell = ptr;
	return (shell);
}
