/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/29 19:53:44 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	bltn_echo_option(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	bltn_echo_nb_option(t_tree *node)
{
	int	i;
	int	j;

	i = 0;
	while (node->exec.cmd_op[++i] && node->exec.cmd_op[i][0] == '-')
	{
		j = 0;
		if (!node->exec.cmd_op[i][++j])
			return (i);
		while (node->exec.cmd_op[i][j])
		{
			if (node->exec.cmd_op[i][j] != 'n')
				return (i);
			j++;
		}
	}
	return (i);
}

static void	print_echo(t_mini *shell, char *str)
{
	t_env	*iter;
	int		i;

	i = -1;
	iter = shell->env;
	if (str && !ft_strcmp(str, "~"))
	{	
		while (iter)
		{
			if (iter->var && !ft_strcmp(iter->var, "HOME"))
				ft_putstr_fd(iter->path, 1);
			iter = iter->next;
		}
	}
	else if (str)
	{
		while (str[++i])
			ft_putchar_fd(str[i], 1);
	}
}

/*
This function is an implementation of echo from bash, 
only with option -n
*/
int	bltn_echo(t_mini *shell, t_tree *node)
{
	int	opt;
	int	i;

	i = 1;
	opt = bltn_echo_option(node->exec.cmd_op[1]);
	if (opt == 1)
		i = bltn_echo_nb_option(node);
	while (node->exec.cmd_op[i])
	{
		print_echo(shell, node->exec.cmd_op[i]);
		if (node->exec.cmd_op[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if ((node->exec.cmd_op[1] && !opt) || !node->exec.cmd_op[1])
		ft_putstr_fd("\n", 1);
	return (0);
}
