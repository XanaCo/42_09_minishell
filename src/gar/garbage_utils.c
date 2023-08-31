/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/06/29 15:04:41 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
malloc() adding the allocated space 
to the garbage collector linked list
*/
void	*ft_malloc_gc(t_mini *shell, int id, size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (NULL);
	if (add_to_garbage(shell, res, id))
		return (NULL);
	return (res);
}

/*
LIBFT ft_calloc() adding the allocated space 
to the garbage collector linked list
*/
void	*ft_calloc_gc(t_mini *shell, int id, size_t nmemb, size_t size)
{
	void	*res;

	res = ft_calloc(nmemb, size);
	if (!res)
		return (NULL);
	if (add_to_garbage(shell, res, id))
		return (NULL);
	return (res);
}

/*
LIBFT ft_strdup() adding the allocated space 
to the garbage collector linked list
*/
char	*ft_strdup_gc(t_mini *shell, int id, const char *s)
{
	char	*res;

	res = ft_strdup(s);
	if (!res)
		return (NULL);
	if (add_to_garbage(shell, res, id))
		return (NULL);
	return (res);
}

/*
LIBFT ft_strjoin() adding the allocated space 
to the garbage collector linked list
*/
char	*ft_strjoin_gc(t_mini *shell, int id, char const *s1, char const *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	if (add_to_garbage(shell, res, id))
		return (NULL);
	return (res);
}

/*
LIBFT ft_substr() adding the allocated space 
to the garbage collector linked list
*/
char	*ft_substr_gc(t_mini *shell, char const *s, unsigned int st, size_t len)
{
	char	*res;

	res = ft_substr(s, st, len);
	if (!res)
		return (NULL);
	if (add_to_garbage(shell, res, shell->gc_id))
		return (NULL);
	return (res);
}
