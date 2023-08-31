/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/31 10:24:00 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cd_var(t_mini *shell, char *var)
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

static int	change_var(t_mini *shell, t_env *iter, char *path)
{
	iter->path = path;
	iter->content = ft_strjoin_gc(shell, END, iter->var, "=");
	iter->content = ft_strjoin_gc(shell, END, iter->content, path);
	if (!iter->content || !iter->path)
		return (1);
	export_to_env(shell, iter->content);
	return (0);
}

static void	change_env_list(t_mini *shell, char *old_pwd)
{
	t_env	*iter;
	char	*new_pwd;

	iter = shell->env;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	if (add_to_garbage(shell, new_pwd, TMP))
		free_and_exit(shell, NULL, ENOMEM);
	while (iter)
	{
		if (iter->var && !ft_strcmp(iter->var, "OLDPWD"))
			change_var(shell, iter, old_pwd);
		else if (iter->var && !ft_strcmp(iter->var, "PWD"))
			change_var(shell, iter, new_pwd);
		iter = iter->next;
	}
}

static int	check_options(t_mini *shell, t_tree *node, char **pwd)
{
	if (node->exec.cmd_op[1] && node->exec.cmd_op[2])
		return (cd_error_msg(1));
	if (!node->exec.cmd_op[1] || !ft_strcmp(node->exec.cmd_op[1], "~"))
	{
		*pwd = get_cd_var(shell, "HOME");
		if (!*pwd)
			return (cd_error_msg(2));
	}
	else if (!ft_strcmp(node->exec.cmd_op[1], "-"))
	{	
		*pwd = get_cd_var(shell, "OLDPWD");
		if (!*pwd)
			return (cd_error_msg(4));
		ft_putstr_fd(*pwd, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		*pwd = ft_strdup_gc(shell, TMP, node->exec.cmd_op[1]);
		if (!*pwd)
			free_and_exit(shell, NULL, ENOMEM);
	}
	return (0);
}

/*
This builtin will work as the bash version,
but only with relative or absolute paths
*/
int	bltn_cd(t_mini *shell, t_tree *node)
{
	char	*new_pwd;
	char	*old_pwd;
	int		error;

	new_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd && node->exec.cmd_op[1])
		return (cd_error_msg(4));
	if (add_to_garbage(shell, old_pwd, TMP))
		free_and_exit(shell, NULL, ENOMEM);
	error = check_options(shell, node, &new_pwd);
	if (error)
		return (1);
	if (chdir(new_pwd) == -1)
		return (cd_error_msg(3));
	change_env_list(shell, old_pwd);
	return (0);
}
