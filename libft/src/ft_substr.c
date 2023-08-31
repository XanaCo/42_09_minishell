/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:36:49 by ancolmen          #+#    #+#             */
/*   Updated: 2022/11/23 17:57:51 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	sub_len;

	i = start;
	sub_len = 0;
	while (i < ft_strlen(s) && i < (start + len))
	{
		sub_len++;
		i++;
	}	
	new = (char *)ft_calloc(sub_len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (sub_len)
	{
		new[i] = s[start + i];
		i++;
		sub_len--;
	}
	return (new);
}
