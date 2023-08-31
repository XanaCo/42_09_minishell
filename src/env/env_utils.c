/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:22:54 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/29 21:58:30 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Adds element at the starting point in the linked list
*/
void	ft_lstadd_front_env(t_env **lst, t_env *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

/*
Searches the '=' position inside the string and returns an int
*/
int	ft_strchr_pos(const char *s, char c)
{
	int		i;
	int		len;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[len])
		len++;
	while (i <= len)
	{
		if (c == s[i])
			return (i);
		i++;
	}
	return (0);
}

/*
Searches and increments SHLVL
*/
void	get_shlvl(t_mini *shell)
{
	char	*new_lvl;
	char	*new_shlvl;

	if (!ft_find_var(shell, "SHLVL"))
		return ;
	new_lvl = ft_itoa(ft_atoi(ft_find_var(shell, "SHLVL")) + 1);
	if (!new_lvl)
		free_and_exit(shell, NULL, ENOMEM);
	new_shlvl = ft_strjoin_gc(shell, END, "SHLVL=", new_lvl);
	free(new_lvl);
	if (!new_shlvl)
	{
		free_and_exit(shell, NULL, ENOMEM);
		return ;
	}
	export_to_env(shell, new_shlvl);
}
