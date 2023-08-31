/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:25:58 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/07/25 13:14:07 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_space(int space)
{
	int	i;

	i = 15;
	while (i < space)
	{
		ft_printf(" ");
		i++;
	}
}

void	print_tree(t_mini *shell, t_tree *root, int space)
{
	int	i;

	i = -1;
	if (!root)
		return ;
	space += 15;
	print_tree(shell, root->right, space);
	print_space(space);
	ft_printf("\033[0;93mTYPE\033[0m: %s\n", get_tk_str(root->tktype));
	print_space(space);
	ft_printf("\033[0;93mFILE_NAME\033[0m: %s\n", root->file_name);
	print_space(space);
	ft_printf("\033[0;93mCMD\033[0m: ");
	if (root->exec.cmd_op == NULL)
		ft_printf("%s", NULL);
	while (root->exec.cmd_op && root->exec.cmd_op[++i])
		ft_printf("%s# ", root->exec.cmd_op[i]);
	ft_printf("\n");
	print_tree(shell, root->left, space);
}

char	*get_tk_str(int tktype)
{
	if (tktype == TK_WORD)
		return ("WORD");
	if (tktype == TK_VENV)
		return ("VAR_ENV");
	if (tktype == TK_PIPE)
		return ("PIPE");
	if (tktype == TK_INF)
		return ("INF");
	if (tktype == TK_SUP)
		return ("SUP");
	if (tktype == TK_DINF)
		return ("DOUBLE_INF");
	if (tktype == TK_DSUP)
		return ("DOUBLE_SUP");
	if (tktype == TK_SQUOTE)
		return ("SINGLE QUOTE");
	if (tktype == TK_DQUOTE)
		return ("DOUBLE QUOTE");
	if (tktype == TK_EXEC)
		return ("EXEC");
	if (tktype == TK_EOF)
		return ("TK_EOF");
	return ("");
}
