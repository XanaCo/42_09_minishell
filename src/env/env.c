/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:22:54 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/29 22:06:38 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Checks for the '=' and stocks the variable name
*/
static char	*get_var(t_mini *shell, void *data)
{
	char	*var;
	int		pos;

	pos = ft_strchr_pos((char *)data, '=');
	if (!pos)
		pos = ft_strlen((char *)data);
	var = ft_substr((char *)data, 0, pos);
	if (!var)
		free_and_exit(shell, NULL, ENOMEM);
	return (var);
}

/*
Adds a brand new element to the env linked list
*/
static void	add_to_env(t_mini *shell, void *data)
{
	t_env		*new;

	new = (t_env *)ft_malloc_gc(shell, END, sizeof(t_env));
	if (!new)
		return ;
	new->content = ft_strdup_gc(shell, END, data);
	new->var = get_var(shell, new->content);
	if (add_to_garbage(shell, new->var, END))
		free_and_exit(shell, new->var, ENOMEM);
	new->path = getenv(new->var);
	new->next = NULL;
	ft_lstadd_front_env(&shell->env, new);
}

/*
*/
static char	**get_env_i(t_mini *shell)
{
	char	**env;

	env = ft_calloc_gc(shell, TMP, 3, sizeof(char *));
	if (!env)
		free_and_exit(shell, NULL, ENOMEM);
	env[0] = ft_strjoin_gc(shell, TMP, "PWD=", getcwd(NULL, 0));
	if (!env[0])
		return (NULL);
	env[1] = "_=/usr/bin/env";
	return (env);
}

/*
A small loop to comply with the Norm
*/
static int	add_to_env_loop(t_mini *shell, char *envp[])
{
	int		i;
	char	**envi;

	i = -1;
	if (!*envp)
	{
		envi = get_env_i(shell);
		if (!envi)
			free_and_exit(shell, NULL, -3);
		while (envi[++i])
			add_to_env(shell, envi[i]);
		get_shlvl(shell);
		return (0);
	}
	while (envp[++i])
		add_to_env(shell, envp[i]);
	get_shlvl(shell);
	return (0);
}

/*
Copies the environment variables in a linked list and
stocks each variable name and its path or paths
Stocks also splited path lines from variable $PATH from the 5th character
(P.A.T.H.=) in a char** in the main structure, with ":" as separator
*/
void	ft_copy_env(t_mini *shell, char *envp[])
{
	t_env	*iter;
	int		i;

	i = -1;
	if (add_to_env_loop(shell, envp))
		return ;
	iter = shell->env;
	while (iter)
	{
		i = -1;
		if (!ft_strcmp(iter->var, "PATH"))
		{	
			shell->path = ft_split(iter->path, ':');
			if (!shell->path)
				free_and_exit(shell, NULL, ENOMEM);
			while (shell->path[++i])
			{
				if (add_to_garbage(shell, shell->path[i], END))
					free_and_exit(shell, shell->path[i], ENOMEM);
			}
			break ;
		}
		iter = iter->next;
	}
}
