/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:18:18 by ancolmen          #+#    #+#             */
/*   Updated: 2022/11/21 20:03:20 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	size_t	i;
	int		overflow;

	i = 0;
	overflow = (int)(nmemb * size);
	if (size != 0 && nmemb != (size_t)overflow / size)
		return (NULL);
	p = (char *)malloc(nmemb * size);
	if (!p)
		return (NULL);
	while (i < (nmemb * size))
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
