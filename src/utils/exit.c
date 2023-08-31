/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 22:03:30 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function assures a clean exit if something goes wrong in the while loop main
*/
void	end_program_failsafe(t_mini *shell)
{
	rl_clear_history();
	if (shell->path)
		free(shell->path);
	ft_putstr_fd("\n\033[0;94m", 1);
	ft_putstr_fd("You've exited minishell.\n", 1);
	ft_putstr_fd("See you soon!\033[0m\n\n", 1);
	close_all_pipes(shell);
	clean_garbage(shell, TMP);
	clean_garbage(shell, END);
}

/*
This function will clean all the allocated memory, 
clean the readline history and the stocked path and check for errors. 
If there are, it will print them before exit
	printf("ERROR = %d\n", g_error_value); //
*/
void	free_and_exit(t_mini *shell, char *str, int error)
{
	rl_clear_history();
	if (shell->path)
		free(shell->path);
	if (error > 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(str);
	}
	if (error < 0)
		error_handling_custom(str, error);
	close_all_pipes(shell);
	clean_garbage(shell, TMP);
	clean_garbage(shell, END);
	exit(g_error_value);
}
