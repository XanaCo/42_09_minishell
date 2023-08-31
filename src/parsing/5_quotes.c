/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:10:06 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/30 16:35:23 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction get_squotes: Récupère ce qu'il y a entre simples quotes
*/
char	*get_squotes(t_mini *shell)
{
	char	*word;
	size_t	pos_start;

	word = NULL;
	pos_start = shell->line.cur;
	while (peek_tk(shell) != TK_SQUOTE && peek_tk(shell) != TK_EOF)
		get_tk(shell);
	if (peek_tk(shell) == TK_SQUOTE)
		get_tk(shell);
	word = ft_substr_gc(shell, shell->line.content, pos_start,
			shell->line.cur - pos_start - 1);
	return (word);
}

/*
Fonction get_spaces: récupère une str comprenant tous les espaces
se trouvant entre guillemets.
*/
static char	*get_spaces(t_mini *shell)
{
	size_t	start;
	size_t	cur;
	char	*space;

	start = shell->line.cur;
	cur = shell->line.cur;
	while (cur < shell->line.len && ft_iswspace(shell->line.content[cur]))
		cur++;
	space = ft_substr_gc(shell, shell->line.content, start, cur - start);
	return (space);
}

/*
Fonction get_dquotes: Récupère ce qu'il y a entre doubles quotes
*/
char	*get_dquotes(t_mini *shell)
{
	char	*word;
	char	*to_find;

	word = NULL;
	while (!(peek_tk(shell) == TK_DQUOTE || peek_tk(shell) == TK_EOF))
	{
		word = ft_strjoin_gc(shell, TMP, word, get_spaces(shell));
		if (peek_tk(shell) == TK_VENV)
		{
			to_find = get_tk(shell);
			if (!ft_strcmp(to_find, "$"))
				word = ft_strjoin_gc(shell, TMP, word, "$");
			else
				word = ft_strjoin_gc(shell, TMP, word,
						get_var_env(shell, to_find));
		}
		else
			word = ft_strjoin_gc(shell, TMP, word, get_tk(shell));
	}
	word = ft_strjoin_gc(shell, TMP, word, get_spaces(shell));
	get_tk(shell);
	return (word);
}

/*
Fonction check_unclosed_quotes: Appelle la fonction quote_flag pour
vérifier si toutes les quotes sont fermées.
*/
int	check_unclosed_quotes(const char *line)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (line[++i])
		flag = quote_flag(flag, line[i]);
	if (flag == 1 || flag == 2)
		return (2);
	return (0);
}

/*
*/
int	quote_flag(int flag, char c)
{
	if (c == '\'')
	{
		if (flag == 1)
			return (0);
		if (flag == 0)
			return (1);
	}
	if (c == '\"')
	{
		if (flag == 2)
			return (0);
		if (flag == 0)
			return (2);
	}
	return (flag);
}
