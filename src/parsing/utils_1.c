/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:55:50 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/30 21:14:07 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*/
char	**add_cmd_arg(t_mini *shell, char **cmd, char *arg)
{
	char	**new_cmd;
	int		nb_arg;
	int		i;

	i = -1;
	nb_arg = 0;
	while (cmd && cmd[nb_arg])
		nb_arg++;
	new_cmd = (char **)ft_malloc_gc(shell, TMP,
			(nb_arg + 2) * sizeof(char *));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd[nb_arg] = ft_strdup_gc(shell, TMP, arg);
	if (new_cmd[nb_arg] == NULL)
		return (NULL);
	new_cmd[nb_arg + 1] = NULL;
	while (++i < nb_arg)
		new_cmd[i] = cmd[i];
	return (new_cmd);
}

static int	init_save(t_mini *shell)
{
	size_t	i;

	i = shell->line.cur;
	while (ft_iswspace(shell->line.content[i]))
		i++;
	return (i);
}

/*
*/
char	**get_cmd(t_mini *shell, char **cmd, char *arg)
{
	char	**var;
	int		i;
	t_token	save_tk;
	size_t	save_cur;

	save_tk = peek_tk(shell);
	save_cur = 0;
	save_cur = init_save(shell);
	arg = get_word(shell);
	if (arg == NULL)
		return (NULL);
	if (save_tk == TK_VENV && (shell->line.content[save_cur + 1]
			&& shell->line.content[save_cur + 1] != '"'))
	{
		var = ft_split(arg, ' ');
		i = -1;
		while (var && var[++i])
			cmd = add_cmd_arg(shell, cmd, var[i]);
		ft_free_matrix((void **)var);
		if (arg[0] == '\0')
			cmd = add_cmd_arg(shell, cmd, arg);
	}
	else
		cmd = add_cmd_arg(shell, cmd, arg);
	return (cmd);
}

/*
*/
char	*get_word(t_mini *shell)
{
	t_token	peek;
	char	*token;
	char	*word;

	peek = peek_tk(shell);
	if (!(peek == TK_WORD || peek == TK_SQUOTE || peek == TK_VENV
			|| peek == TK_DQUOTE))
		return (NULL);
	token = get_tk(shell);
	word = NULL;
	if (give_tk(token) == TK_WORD && ft_strncmp(token, "$", ft_strlen(token)))
			word = token;
	if (give_tk(token) == TK_VENV)
		word = get_var_env(shell, token);
	if (give_tk(token) == TK_SQUOTE)
		word = get_squotes(shell);
	if (give_tk(token) == TK_DQUOTE)
		word = get_dquotes(shell);
	if (shell->line.cur < shell->line.len
		&& ft_iswspace(shell->line.content[shell->line.cur]))
		return (word);
	else
		return (ft_strjoin_gc(shell, TMP, word, get_word(shell)));
}
