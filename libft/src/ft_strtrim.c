/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:03:14 by ancolmen          #+#    #+#             */
/*   Updated: 2023/05/07 20:44:55 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	trim_is_possible(const char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}	
	return (0);
}

static size_t	trim_len(const char *s1, char const *set)
{
	size_t	i;
	size_t	size;	

	i = 0;
	size = ft_strlen(s1);
	while (trim_is_possible(s1[size - i - 1], set))
		i++;
	return (size - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s3;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (trim_is_possible(s1[i], set))
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	size = trim_len(s1 + i, set) + 1;
	s3 = (char *)ft_calloc((size), sizeof(char));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1 + i, size);
	return (s3);
}
