/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:55:04 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/26 14:55:08 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*/
void	init_child_signals(void)
{
	signal(SIGINT, &sigint_handler_child);
	signal(SIGQUIT, &sigquit_handler_child);
	signal(SIGTSTP, SIG_IGN);
}

/*
*/
void	sigint_handler_child(int signal)
{
	g_error_value = 130;
	(void)signal;
}

/*
*/
void	sigquit_handler_child(int signal)
{
	g_error_value = 131;
	(void)signal;
}

/*
*/
int	signal_handler_child(int signal)
{
	if (signal == SIGINT)
	{	
		ft_putstr_fd("\n", 2);
		return (130);
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		return (131);
	}
	return (signal);
}
