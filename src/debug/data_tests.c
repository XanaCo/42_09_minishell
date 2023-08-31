/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 17:58:30 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// // /*
// // Fills node with data test
// // */
// // t_tree	*fill_node_test(t_mini *shell)
// // {
// // 	t_tree	*new;

// // 	new = ft_calloc_gc(shell, TMP, 1, sizeof(t_tree));
// // 	if (!new)
// // 		return (NULL);
// // 	ft_bzero(new, sizeof(t_tree));
// // 	new->tktype = TK_INF;
// // 	new->token = ft_strdup_gc(shell, TMP, shell->line.content);
// // 	new->file_name = "infile";
// // 	new->exec.cmd = NULL;
// // 	new->exec.cmd_op = NULL;
// // 	new->exec.cmd_path = NULL;
// // 	new->right = NULL;
// // 	new->left = NULL;
// // 	new->lst_heredoc = NULL;
// // 	return (new);
// // }

// /*
// Fills node with data test
// */
// t_tree	*fill_node_test(t_mini *shell)
// {
// 	t_tree	*one;
// 	t_tree	*two;
// 	t_tree	*cmd;
// 	t_tree	*three;
// 	//t_tree	*four;
// 	//t_tree	*five;

// 	one = ft_calloc_gc(shell, TMP, 1, sizeof(t_tree));
// 	two = ft_calloc_gc(shell, TMP, 1, sizeof(t_tree));
// 	three = ft_calloc_gc(shell, TMP, 1, sizeof(t_tree));
// 	cmd = ft_calloc_gc(shell, TMP, 1, sizeof(t_tree));
// 	if (!one || !two || !three || !cmd) // || !four || !five)
// 		return (NULL);
// 	ft_bzero(one, sizeof(t_tree));
// 	ft_bzero(two, sizeof(t_tree));
// 	ft_bzero(three, sizeof(t_tree));
// 	ft_bzero(cmd, sizeof(t_tree));
// 	//ft_bzero(four, sizeof(t_tree));
// 	//ft_bzero(five, sizeof(t_tree));
// 	one->tktype = TK_DINF;
// 	one->token = "<<";
// 	one->file_name = "infile";
// 	one->exec.cmd = NULL;
// 	one->key_w = "END";
// 	one->right = NULL;
// 	one->left = two;
// 	one->lst_heredoc = NULL;

// 	two->tktype = TK_SUP;
// 	two->token = ">";
// 	two->file_name = "outfile1";
// 	two->exec.cmd = NULL;
// 	two->right = NULL;
// 	two->left = three;
// 	two->lst_heredoc = NULL;

// 	three->tktype = TK_DSUP;
// 	three->token = ">>";
// 	three->file_name = "outfile2";
// 	three->exec.cmd = NULL;
// 	three->right = NULL;
// 	three->left = cmd;
// 	three->lst_heredoc = NULL;

// 	cmd->tktype = TK_EXEC;
// 	cmd->token = "CMD";
// 	cmd->file_name = NULL;
// 	cmd->exec.cmd = "wc";
// 	cmd->exec.cmd_op = ft_calloc_gc(shell, TMP, sizeof(char *), 3);
// 	cmd->exec.cmd_op[0] = cmd->exec.cmd; // cmd
// 	cmd->exec.cmd_op[1] = "-l"; // option 1
// 	cmd->exec.cmd_op[2] = NULL;
// 	cmd->exec.cmd_path = NULL; // rempli with acces plus tard
// 	cmd->right = NULL;
// 	cmd->left = NULL;
// 	cmd->lst_heredoc = NULL;
// 	return (one);
// }