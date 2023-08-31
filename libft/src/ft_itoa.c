/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:34:57 by ancolmen          #+#    #+#             */
/*   Updated: 2022/11/24 22:02:52 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(long int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = n * (-1);
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	n_dec(int len)
{
	int	i;

	i = 1;
	while (len > 1)
	{
		i = i * 10;
		len--;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	int			len;
	int			len_const;
	char		*s;
	long int	nbr;

	i = 0;
	nbr = (long int)n;
	len = n_len(nbr);
	len_const = n_len(nbr);
	s = (char *)ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	if (nbr < 0)
	{
		nbr = nbr * (-1);
		s[i++] = '-';
		len--;
	}
	while (i < len_const)
		s[i++] = ((nbr / n_dec(len--)) % 10) + 48;
	return (s);
}
