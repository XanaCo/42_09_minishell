/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:39:45 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/30 18:15:47 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction test_dredir: Verifie s'il s'agit d'un heredoc 
ou d'une double redirection
*/
static size_t	test_dredir(t_mini *shell, size_t cur)
{
	if (shell->line.content[cur] == '\0')
		return (cur);
	if (cur + 1 < shell->line.len && shell->line.content[cur + 1]
		&& (shell->line.content[cur] == '<' || shell->line.content[cur] == '>')
		&& shell->line.content[cur] == shell->line.content[cur + 1])
		cur++;
	if (!ft_iswspace(shell->line.content[cur]))
		cur++;
	return (cur);
}

/*
Fonction get_tk: fonction qui jete un coup d'oeil 
à la str et determine le token correspondant 
et avance jusqu'au prochain char
*/
char	*get_tk(t_mini *shell)
{
	char	*token;
	size_t	cur;
	size_t	start;

	cur = shell->line.cur;
	while (cur < shell->line.len && shell->line.content[cur] != '\0'
		&& ft_iswspace(shell->line.content[cur]))
		cur++;
	if (cur >= shell->line.len)
		return (NULL);
	start = cur;
	while (cur < shell->line.len && !ft_iswspace(shell->line.content[cur])
		&& !ft_strchr(PARSING_STOPPER, shell->line.content[cur]))
	{
		if (shell->line.content[cur + 1] != '\0'
			&& (ft_iswspace(shell->line.content[cur + 1])
				|| ft_strchr(PARSING_STOPPER, shell->line.content[cur + 1])))
			break ;
		cur++;
	}
	cur = test_dredir(shell, cur);
	token = ft_substr_gc(shell, shell->line.content, start, cur - start);
	shell->line.cur = cur;
	return (token);
}

/*
Fonction peek_tk: fonction qui jete un coup d'oeil à la str 
et determine le token correspondant
*/
t_token	peek_tk(t_mini *shell)
{
	char		*token;
	size_t		cur;
	size_t		start;

	cur = shell->line.cur;
	if (!shell->line.content)
		return (TK_ERROR);
	while (cur < shell->line.len
		&& shell->line.content[cur] && ft_iswspace(shell->line.content[cur]))
		cur++;
	if (cur >= shell->line.len)
		return (TK_EOF);
	start = cur;
	while (cur < shell->line.len && !ft_iswspace(shell->line.content[cur])
		&& !ft_strchr(PARSING_STOPPER, shell->line.content[cur]))
	{
		if (shell->line.content[cur + 1]
			&& (ft_iswspace(shell->line.content[cur + 1])
				|| ft_strchr(PARSING_STOPPER, shell->line.content[cur + 1])))
			break ;
		cur++;
	}
	cur = test_dredir(shell, cur);
	token = ft_substr_gc(shell, shell->line.content, start, cur - start);
	return (give_tk(token));
}

/*
Fonction give_tk: Complémentaire à la fonction peek_tk
*/
t_token	give_tk(char *token)
{
	if (token == NULL)
		return (TK_ERROR);
	if (token[0] == '\0')
		return (TK_EOF);
	if (!ft_strncmp(token, "|", 2))
		return (TK_PIPE);
	if (!ft_strncmp(token, "<", 2))
		return (TK_INF);
	if (!ft_strncmp(token, ">", 2))
		return (TK_SUP);
	if (!ft_strncmp(token, "<<", 2))
		return (TK_DINF);
	if (!ft_strncmp(token, ">>", 2))
		return (TK_DSUP);
	if (!ft_strncmp(token, "\'", 1))
		return (TK_SQUOTE);
	if (!ft_strncmp(token, "\"", 1))
		return (TK_DQUOTE);
	if (ft_strchr(token, '$'))
		return (TK_VENV);
	return (TK_WORD);
}
