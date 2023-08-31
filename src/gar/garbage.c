/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/29 15:05:36 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Adds node to garbage collector
*/
int	add_to_garbage(t_mini *shell, void *ptr, int id)
{
	t_gcol	*new;

	new = (t_gcol *)malloc(sizeof(t_gcol));
	if (!new)
		return (1);
	new->ptr = ptr;
	new->id = id;
	new->next = NULL;
	if (!shell->gc)
		shell->gc = new;
	else
	{
		new->next = shell->gc;
		shell->gc = new;
	}
	return (0);
}

/*
Adds node[i] to garbage collector 
when we allocate tabs and arrays
*/
int	add_matrix_to_garbage(t_mini *shell, int id, void **ptr)
{
	int	i;

	i = 0;
	while (ptr + i)
	{
		if (add_to_garbage(shell, ptr + i, id))
			return (1);
		i++;
	}
	return (0);
}

/*
Cleans all the garbage list
*/
void	clean_all(t_mini *shell)
{
	t_gcol	*tmp;
	t_gcol	*iter;

	iter = shell->gc;
	while (iter)
	{
		if (iter->ptr)
			free(iter->ptr);
		tmp = iter->next;
		free(iter);
		iter = tmp;
	}
	shell->gc = NULL;
}

/*
Cleans only the TMP garbage, rearranging the list
*/
void	clean_tmp(t_mini *shell)
{
	t_gcol	*tmp;
	t_gcol	*iter;
	t_gcol	*prev;

	prev = NULL;
	iter = shell->gc;
	while (iter)
	{
		if (iter->id == END)
		{
			prev = iter;
			iter = iter->next;
			continue ;
		}
		if (prev)
			prev->next = iter->next;
		else
			shell->gc = iter->next;
		tmp = iter;
		iter = iter->next;
		free(tmp->ptr);
		free(tmp);
	}
}

/*
Goes through the linked list and frees 
all allocated memory depending on id
*/
void	clean_garbage(t_mini *shell, int flag)
{
	if (!shell->gc)
		return ;
	if (flag == TMP)
		clean_tmp(shell);
	if (flag == END)
		clean_all(shell);
}
