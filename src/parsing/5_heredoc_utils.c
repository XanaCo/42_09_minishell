/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:01:03 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/29 19:36:29 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*/
static int	end_var(char *str, int start)
{
	if (str && str[start] && str[start] == '?')
		return (1);
	while (str && str[start])
	{
		if (!(ft_isalnum(str[start]) || str[start] == '_'))
			return (start);
		start++;
	}
	return (-1);
}

/*
*/
static char	*get_hd_line2(t_mini *shell, char *str, char *new, size_t start)
{
	char	*to_process;

	to_process = NULL;
	if (str[start + 1] && ft_isdigit(str[start + 1])
		&& str[start + 2])
		new = ft_strjoin_gc(shell, TMP, new, ft_substr_gc(shell, str,
					start + 2, end_var(str, start + 1) - 3));
	to_process = ft_substr_gc(shell, str, end_var(str, start + 1),
			ft_strlen(str));
	if (ft_strlen(to_process))
		new = ft_strjoin_gc(shell, TMP, new, get_hd_line(shell, to_process));
	return (new);
}

/*
*/
char	*get_hd_line(t_mini *shell, char *str)
{
	size_t	i;
	int		flag;
	char	*new;
	char	*to_find;

	i = -1;
	flag = 0;
	new = NULL;
	while (str[++i])
	{
		flag = quote_flag(flag, str[i]);
		if (str[i] == '$' && flag == 0)
			break ;
	}
	if (str[i] == '\0')
		return (str);
	new = ft_substr_gc(shell, str, 0, i);
	to_find = ft_substr_gc(shell, str, i + 1, end_var(str, i + 1) - (i + 1));
	new = ft_strjoin_gc(shell, TMP, new, ft_find_var(shell, to_find));
	new = get_hd_line2(shell, str, new, i);
	return (new);
}
