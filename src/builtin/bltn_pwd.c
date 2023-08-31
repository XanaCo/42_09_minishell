/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 23:05:22 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_pwd_var(t_mini *shell, char *var)
{
	t_env	*iter;

	iter = shell->env;
	while (iter)
	{
		if (iter->var && !ft_strcmp(iter->var, var))
			return (iter->path);
		iter = iter->next;
	}
	return (0);
}

/*
The PWD builtin will get and print the actual working directory,
exactly as th pwd command in bash, with no options
*/
int	bltn_pwd(t_mini *shell, t_tree *node)
{
	char	*dir;
	char	*pwd;

	if (node->exec.cmd_op[1] && node->exec.cmd_op[1][0] == '-')
		free_and_exit(shell, node->exec.cmd_op[1], -3);
	dir = get_pwd_var(shell, "PWD");
	if (!dir)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			ft_putstr_fd("minishell: pwd: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n ", 2);
			return (1);
		}
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		free(pwd);
		return (0);
	}
	ft_putstr_fd(dir, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
