/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_var_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:58:16 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/30 18:26:34 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction get_var_errno: Récupère le code erreur
*/
static char	*get_var_errno(t_mini *shell)
{
	char	*error;
	char	*error_value;

	error = NULL;
	error_value = ft_itoa(g_error_value);
	error = ft_strjoin_gc(shell, TMP, error, error_value);
	free(error_value);
	return (error);
}

/*
Fonction ft_find_var: Va chercher dans l'environnement le nom de la
variable et renvoie son contenu.
*/
char	*ft_find_var(t_mini *shell, char *to_find)
{
	char	*path;
	t_env	*env;

	if (!to_find[0])
		return ("$");
	if (ft_strcmp(to_find, "?") == 0)
		return (get_var_errno(shell));
	env = shell->env;
	while (env)
	{
		if (!ft_strncmp(env->var, to_find, ft_strlen(env->var) + 1))
		{
			path = env->path;
			return (path);
		}
		env = env->next;
	}
	return ("");
}

/*
Fonction pos_end_var: Récupère la longueur du nom de variable
*/
static int	pos_end_var(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] && str[0] == '?')
		return (1);
	while (str && str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (i);
		i++;
	}
	return (-1);
}

/*
*/
static char	*get_var_env2(t_mini *shell, char *word, char *new)
{
	char	*to_process;
	int		len;

	len = ft_strlen(word) - pos_str(word, '$') - 1;
	if (pos_end_var(word + pos_str(word, '$') + 1) != -1)
		len = pos_end_var(word + pos_str(word, '$') + 1);
	if (word[pos_str(word, '$') + 1] && ft_isdigit(word[pos_str(word, '$') + 1])
		&& word[pos_str(word, '$') + 2])
		new = ft_strjoin_gc(shell, TMP, new, ft_substr_gc(shell, word,
					pos_str(word, '$') + 2, len -1));
	if (word[pos_str(word, '$') + 1] && word[pos_str(word, '$') + 1] == '$')
	{
		new = ft_strjoin_gc(shell, TMP, new, "$$");
		new = ft_strjoin_gc(shell, TMP, new, ft_substr_gc(shell, word,
					pos_str(word, '$') + 2, len -1));
		len++;
	}
	else
		new = ft_strjoin_gc(shell, TMP, new, ft_find_var(shell,
					ft_substr_gc(shell, word, pos_str(word, '$') + 1, len)));
	to_process = ft_substr_gc(shell, word, pos_str(word, '$') + 1 + len,
			ft_strlen(word));
	if (ft_strlen(to_process))
		new = ft_strjoin_gc(shell, TMP, new, get_var_env(shell, to_process));
	return (new);
}

/*
Fonction get_var_env: Récupère une chaine de caractère composée de '$' 
et analyse celle-ci afin de la remplacer par les variables d'environnement
ex: $USER -> lkoletzk / $? -> error_value, etc.
*/
char	*get_var_env(t_mini *shell, char *word)
{
	char	*new;

	new = NULL;
	if (word == NULL || pos_str(word, '$') == -1)
		return (word);
	new = ft_strjoin_gc(shell, TMP, new, ft_substr_gc(shell, word, 0,
				pos_str(word, '$')));
	if (pos_str(word, '$') + 1 == (int)ft_strlen(word))
	{
		if (shell->line.content[shell->line.cur] == '\0'
			|| ft_iswspace(shell->line.content[shell->line.cur]))
			new = ft_strjoin_gc(shell, TMP, new, "$");
		else
			return (new);
	}
	else
		new = get_var_env2(shell, word, new);
	return (new);
}
