/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:12:05 by ancolmen          #+#    #+#             */
/*   Updated: 2023/04/06 17:47:32 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	size_t	i;
	char	*dup;

	size = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[size])
		size++;
	dup = (char *)ft_calloc((size + 1), sizeof(char));
	if (!dup)
		return (0);
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
