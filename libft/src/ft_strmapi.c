/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:29:56 by ancolmen          #+#    #+#             */
/*   Updated: 2022/11/21 17:24:30 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = ft_strdup(s);
	while (dup[i])
	{
		dup[i] = (*f)(i, dup[i]);
		i++;
	}
	return (dup);
}
