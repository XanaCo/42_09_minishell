/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 21:11:35 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
The main process will ignore CTRL-Z and CTRL-\, and handle CTRL-C
*/
void	init_parent_signals(void)
{
	signal(SIGINT, &sigint_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

/*
This handler will re-print the prompt if CTRL-C is pressed, 
updating the global value to the correct error
*/
void	sigint_handler_parent(int signal)
{
	g_error_value = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_redisplay();
	(void)signal;
}
