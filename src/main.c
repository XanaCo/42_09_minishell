/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:58:36 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 21:09:42 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
# MINISHELL #
Allowed functions
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
add_history, printf, malloc, free, write, access, open, read, close, fork,
wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill,
exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
*/

unsigned char	g_error_value = 0;

static char	*ft_readline(t_mini *shell, char *prompt)
{
	char	*res;

	res = NULL;
	if (isatty(0))
		res = readline(prompt);
	if (add_to_garbage(shell, res, TMP))
		free_and_exit(shell, NULL, ENOMEM);
	return (res);
}

static void	start_program(t_mini *shell, char *line)
{
	if (!ft_strcmp(shell->line.content, ""))
		return ;
	if (!ft_strcmp(shell->line.content, "$?"))
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putnbr_fd(g_error_value, 1);
		ft_putstr_fd(": command not found\n", 1);
		g_error_value = 127;
		return ;
	}
	shell->gc_id = TMP;
	shell->tree = parsing(shell, line);
	execution_time(shell, shell->tree);
}

/*
	rl_outstream = stderr;
*/
int	main(int argc, char **argv, char **envp)
{
	t_mini	shell;

	(void)argv;
	ft_bzero(&shell, sizeof(t_mini));
	if (argc != 1)
		return (ft_putstr_fd("minishell: Too many arguments\n", 2), 1);
	ft_copy_env(&shell, envp);
	locate_shell(&shell, 1);
	print_title();
	while (1)
	{
		init_parent_signals();
		shell.prompt = get_prompt();
		shell.line.content = ft_readline(&shell, shell.prompt);
		if (!shell.line.content || !ft_strcmp(shell.line.content, "exit"))
			return (bltn_exit(&shell, NULL));
		if (ft_strlen(shell.line.content) > 0)
			add_history(shell.line.content);
		start_program(&shell, shell.line.content);
		clean_garbage(&shell, TMP);
	}
	end_program_failsafe(&shell);
	return (g_error_value);
}
