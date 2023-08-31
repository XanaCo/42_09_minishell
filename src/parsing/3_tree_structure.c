/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_tree_structure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:53:50 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/29 16:32:18 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction create_branch : Crée une branche sur l'arbre binaire
*/
t_tree	*create_branch(t_mini *shell, int tktype, char *token)
{
	t_tree	*branch;

	branch = ft_malloc_gc(shell, TMP, sizeof(t_tree));
	if (branch == NULL)
		return (NULL);
	ft_memset(branch, 0, sizeof(t_tree));
	branch->tktype = tktype;
	branch->token = token;
	return (branch);
}

/*
Fonction create_pipe_branch: Crée une branche de PIPE
*/
t_tree	*create_pipe_branch(t_mini *shell, t_tree *left, t_tree *right)
{
	t_tree	*branch;

	branch = ft_malloc_gc(shell, TMP, sizeof(t_tree));
	if (branch == NULL)
		return (NULL);
	ft_memset(branch, 0, sizeof(t_tree));
	branch->tktype = TK_PIPE;
	branch->token = "|";
	branch->left = left;
	branch->right = right;
	return (branch);
}

/*
Fonction create_redir_branch: Crée une branche de REDIRECTION
*/
t_tree	*create_redir_branch(t_mini *shell, t_tree *left,
	int tktype, char *file_name)
{
	t_tree	*branch;

	branch = ft_malloc_gc(shell, TMP, sizeof(t_tree));
	if (branch == NULL)
		return (NULL);
	ft_memset(branch, 0, sizeof(t_tree));
	branch->tktype = tktype;
	branch->token = get_tk_str(tktype);
	if (tktype == TK_DINF)
	{
		shell->n_hd++;
		branch->key_w = file_name;
		if (g_error_value == 130 && shell->n_hd == 1)
			g_error_value = 0;
		init_heredoc(shell, branch, branch->key_w);
		if (g_error_value == 130)
			shell->hd_error = 1;
	}
	branch->file_name = file_name;
	branch->left = left;
	return (branch);
}

/*
Fonction create_exec_branch: Crée une branche d'EXECUTION
*/
t_tree	*create_exec_branch(t_mini *shell, char **cmd)
{
	t_tree	*branch;

	branch = ft_malloc_gc(shell, TMP, sizeof(t_tree));
	if (branch == NULL)
		return (NULL);
	ft_memset(branch, 0, sizeof(t_tree));
	branch->tktype = TK_EXEC;
	branch->token = get_tk_str(TK_EXEC);
	branch->exec.cmd_op = cmd;
	branch->exec.cmd = cmd[0];
	return (branch);
}

/*
Fonction add_left_branch: Ajoute la branche envoyée (branch)
à gauche de l'arbre (root)
*/
void	add_left_branch(t_tree **root, t_tree *branch)
{
	t_tree	*elem;

	elem = *root;
	if (elem == NULL)
		*root = branch;
	else
	{
		while (elem->left)
			elem = elem->left;
		elem->left = branch;
	}
}
