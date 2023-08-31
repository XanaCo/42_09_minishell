/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/07/30 17:59:18 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Prints garbage collector linked list
*/
void	print_garbage(t_mini *shell)
{
	t_gcol	*iter;

	iter = shell->gc;
	if (!iter)
		printf("Garbage empty...\n");
	while (iter)
	{
		printf("Garbage NODE : %d - %p \n",
			iter->id,
			iter->ptr);
		iter = iter->next;
	}
}

/*
Prints ENV linked list
*/
void	print_list(t_mini *shell)
{
	t_env	*iter;

	iter = shell->env;
	if (!iter)
		printf("Empty list\n");
	while (iter)
	{
		printf("::::List NODE::::: \n> %s\n> %s\n> %s\n> %p\n",
			(char *)iter->content,
			iter->var,
			iter->path,
			iter->next);
		iter = iter->next;
	}
}

/*
Prints received node
*/
void	print_node_for_exec(t_mini *shell, t_tree *node)
{
	int	i;

	(void)shell;
	i = -1;
	printf("NODE :\nCMD -> %s\n", node->exec.cmd);
	while (node->exec.cmd_op[++i])
		printf("CMD_OP -> %s\n", node->exec.cmd_op[i]);
	printf("PATH -> %s\n", node->exec.cmd_path);
}

void	print_env(t_mini *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd((char *)env->content, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

// int	only_space(char *line)
// {
// 	int	i;
// 	int	ws;

// 	i = -1;
// 	ws = 0;
// 	while (line[++i])
// 	{
// 		if (ft_iswspace(line[i]))
// 			ws++;
// 	}
// 	printf ("i = %d | ws = %d\n", i, ws);
// 	if (i == ws)
// 		return (0);
// 	return (1);
// }
