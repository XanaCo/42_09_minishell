/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:07:09 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/28 18:10:38 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction get_endheredoc: Permet de récupérer le LIMITER du heredoc
*/
char	*get_endheredoc(t_mini *shell)
{
	t_token	peek;
	char	*token;
	char	*word;

	peek = peek_tk(shell);
	if (!(peek == TK_WORD || peek == TK_SQUOTE || peek == TK_VENV
			|| peek == TK_DQUOTE))
		return (NULL);
	token = get_tk(shell);
	if (give_tk(token) == TK_WORD || TK_VENV)
		word = token;
	if (give_tk(token) == TK_SQUOTE)
		word = get_squotes(shell);
	if (give_tk(token) == TK_DQUOTE)
		word = get_dquotes(shell);
	if (shell->line.cur < shell->line.len
		&& ft_iswspace(shell->line.content[shell->line.cur]))
		return (word);
	else
		return (ft_strjoin_gc(shell, TMP, word, get_endheredoc(shell)));
}

/*
Fonction add_to_list_heredoc: Fonction qui ajoute la ligne lue à
la struct t_list heredoc
*/
static void	add_to_list_hd(t_mini *shell, t_tree *branch, char *str)
{
	t_list	*new;

	new = (t_list *)ft_calloc_gc(shell, TMP, 1, sizeof(t_list));
	if (!new)
		free_and_exit(shell, NULL, ENOMEM);
	new->content = ft_strdup_gc(shell, TMP, str);
	if (ft_strchr(new->content, '$'))
		new->content = get_hd_line(shell, str);
	new->next = NULL;
	ft_lstadd_back(&branch->heredoc, new);
	free(str);
}

/*
Fonction is_heredoc: Permet de lancer un heredoc et récupérer celui-ci
*/
void	init_heredoc(t_mini *shell, t_tree *branch, char *key_word)
{
	char	*tmp;
	char	*line;

	init_hd_child_signal();
	shell->hd_fd = dup(0);
	while (1)
	{
		if (g_error_value == 130)
		{	
			close(shell->hd_fd);
			return ;
		}
		ft_putstr_fd("> ", 1);
		line = get_next_line(shell->hd_fd);
		tmp = ft_strtrim(line, "\n");
		if (!line)
			return (here_doc_signal(shell));
		if (!ft_strncmp(tmp, key_word, ft_strlen(key_word) + 1))
		{	
			close(shell->hd_fd);
			return (free(line), free(tmp));
		}
		add_to_list_hd(shell, branch, line);
		free(tmp);
	}
}

/*
*/
void	here_doc_signal(t_mini *shell)
{
	if (g_error_value == 130)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (dup2(shell->hd_fd, 0) == -1)
		free_and_exit(shell, NULL, errno);
	close(shell->hd_fd);
	ft_putstr_fd("\nminishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file\n", 2);
	g_error_value = 0;
}
