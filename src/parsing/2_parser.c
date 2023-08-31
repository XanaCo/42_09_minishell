/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:30:34 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/31 11:13:14 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction init_struct_line: Initialise toute la structure "line",
taille, erreurs, position start (cur) + nb de here_docs
*/
static int	init_struct_line(t_mini *shell)
{
	shell->line.cur = 0;
	shell->line.error = 0;
	if (shell->line.content == NULL)
		return (1);
	shell->line.len = ft_strlen(shell->line.content);
	if (peek_tk(shell) == TK_EOF)
		return (1);
	shell->n_hd = 0;
	shell->hd_error = 0;
	return (0);
}

/*
Fonction parsing: Crée l'arbre binaire pour l'exécution
	print_tree(shell, root, 0);
*/
t_tree	*parsing(t_mini *shell, char *line)
{
	t_tree	*root;

	root = NULL;
	if (check_unclosed_quotes(line) == 2)
	{
		error_handling_custom(NULL, -2);
		return (NULL);
	}
	shell->line.content = line;
	if (init_struct_line(shell))
		return (NULL);
	root = parse_data(shell);
	if (shell->line.error == 3)
	{
		error_handling_custom(NULL, -2);
		return (NULL);
	}
	return (root);
}

/*
Fonction parse_data: Analyse la structure de la ligne de commande
et envoie les infos aux fonctions de parsing (exec, pipe, redir)
*/
t_tree	*parse_data(t_mini *shell)
{
	t_tree	*branch;

	if (!is_word(peek_tk(shell)) && !is_redir(peek_tk(shell)))
	{
		shell->line.error = 3;
		return (NULL);
	}
	branch = parse_exec(shell);
	if (peek_tk(shell) == TK_PIPE)
	{
		if (get_tk(shell) && peek_tk(shell) == TK_EOF)
		{
			shell->line.error = 3;
			return (NULL);
		}
		branch = create_pipe_branch(shell, branch, parse_data(shell));
	}
	return (branch);
}

/*
Fonction parse_exec: Récupère la commande et ses arguments
*/
t_tree	*parse_exec(t_mini *shell)
{
	t_tree	*branch;
	char	**cmd;
	char	*arg;

	branch = NULL;
	cmd = NULL;
	arg = NULL;
	if (shell->line.cur == 0 && peek_tk(shell) == TK_EOF)
		return (create_exec_branch(shell, add_cmd_arg(shell, cmd, "")));
	if (is_redir(peek_tk(shell)))
		branch = parse_redir(shell);
	while (is_word(peek_tk(shell)) || is_redir(peek_tk(shell)))
	{
		if (is_word(peek_tk(shell)))
		{
			cmd = get_cmd(shell, cmd, arg);
			if (!cmd)
				return (NULL);
		}
		else
			add_left_branch(&branch, parse_redir(shell));
	}
	if (cmd)
		add_left_branch(&branch, create_exec_branch(shell, cmd));
	return (branch);
}

/*
Fonction parse_redir: Récupère les données de redirection (in or out + nom du fd)
Reste a vérifier la gestion des heredocs
*/
t_tree	*parse_redir(t_mini *shell)
{
	t_tree	*branch;
	t_token	token;
	t_token	peek;
	char	*file_name;

	token = give_tk(get_tk(shell));
	peek = peek_tk(shell);
	if (!(peek == TK_WORD || peek == TK_SQUOTE
			|| peek == TK_DQUOTE || peek == TK_VENV))
	{
		shell->line.error = 3;
		return (NULL);
	}
	if (token == TK_DINF)
		file_name = get_endheredoc(shell);
	if (token == TK_INF || token == TK_SUP || token == TK_DSUP)
		file_name = get_word(shell);
	if (file_name == NULL)
		shell->line.error = 3;
	if (shell->line.error)
		return (NULL);
	branch = create_redir_branch(shell, NULL, token, file_name);
	return (branch);
}
