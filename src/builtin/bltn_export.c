/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/31 12:26:26 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
La commande export est une commande bash intégrée utilisée pour rendre les
variables disponibles pour les processus enfants du shell actuel.
Une fois que vous avez export une variable dans un shell, tout processus
exécuté à partir de ce shell pourra accéder à cette variable.

La commande export utilise la syntaxe suivante: export variable=value
*/

static char	*get_var(t_mini *shell, void *data)
{
	char	*var;
	int		pos;
	int		i;
	char	*tmp;

	i = -1;
	tmp = (char *)data;
	pos = ft_strchr_pos((char *)data, '=');
	if (!pos)
		pos = ft_strlen((char *)data);
	var = ft_calloc_gc(shell, END, sizeof(char), pos + 1);
	if (!var)
		return (NULL);
	while (++i < pos)
		var[i] = tmp[i];
	if (!var || !var[0])
		return (NULL);
	return (var);
}

static int	check_export(t_tree *node)
{
	int		i;

	i = 1;
	while (node->exec.cmd_op[0] && node->exec.cmd_op[i])
	{
		if (node->exec.cmd_op[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_path(t_mini *shell, void *data, int start)
{
	int		i;
	int		pos;
	char	*tmp;
	char	*path;

	i = -1;
	start++;
	pos = ft_strlen((char *)data) - start;
	tmp = (char *)data;
	path = ft_calloc_gc(shell, END, sizeof(char), pos + 1);
	if (!path)
		return (NULL);
	while (++i < pos)
		path[i] = tmp[start + i];
	return (path);
}

void	export_to_env(t_mini *shell, void *data)
{
	t_env	*new;
	int		i;

	new = (t_env *)ft_malloc_gc(shell, END, sizeof(t_env));
	if (!new)
		return ;
	new->content = NULL;
	new->path = NULL;
	new->var = NULL;
	if (valid_export((char *)data) == 3)
		new->content = ft_strjoin_gc(shell, END, data, "");
	else
		new->content = ft_strdup_gc(shell, END, data);
	new->var = get_var(shell, new->content);
	if (!new->var)
		return ;
	ft_lstdel_env(&shell->env, new->var);
	i = ft_strchr_pos((char *)data, '=');
	if (i == 0)
		new->path = NULL;
	else
		new->path = get_path(shell, data, i);
	new->next = NULL;
	ft_lstadd_front_env(&shell->env, new);
}

/*
1- d'abord on verifie qu'il y a un arg sinon on affiche tout l'envirionnement
2- on verifie si tentative d'option = erreur not option handling
3- on verifie le nom de variable
4- on check si la variable existe deja --> Si elle existe on unset cette variable
5- on ajoute a l'env
*/
int	bltn_export(t_mini *shell, t_tree *node)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (node->exec.cmd_op[i])
	{
		if (valid_export(node->exec.cmd_op[i]) < 0)
		{
			error++;
			error_handling_custom(node->exec.cmd_op[i], -6);
		}
		else
			export_to_env(shell, node->exec.cmd_op[i]);
		i++;
	}
	if (!check_export(node) && !node->exec.cmd_op[1])
		print_env(shell);
	if (error > 0)
		return (1);
	return (0);
}
