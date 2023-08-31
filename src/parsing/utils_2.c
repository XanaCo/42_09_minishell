/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:50:19 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/29 19:37:12 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*/
int	is_redir(t_token tktype)
{
	if (tktype == TK_INF || tktype == TK_SUP
		|| tktype == TK_DINF || tktype == TK_DSUP)
		return (1);
	return (0);
}

/*
*/
int	is_word(t_token tktype)
{
	if (tktype == TK_WORD || tktype == TK_VENV
		|| tktype == TK_SQUOTE || tktype == TK_DQUOTE)
		return (1);
	return (0);
}

/*
*/
int	pos_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
