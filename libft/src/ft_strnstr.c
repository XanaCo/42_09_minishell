/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:29 by ancolmen          #+#    #+#             */
/*   Updated: 2022/11/15 18:17:57 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*l;

	i = 0;
	j = 0;
	b = (char *)big;
	l = (char *)little;
	if (!l[j])
		return (b);
	while (b[i] && l[j] && i < len)
	{
		while (b[i + j] == l[j] && b[i + j] && i + j < len)
			j++;
		if (!l[j])
			return (b + i);
		i++;
		j = 0;
	}
	return (0);
}
