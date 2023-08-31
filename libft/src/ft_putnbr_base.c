/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:50:44 by ancolmen          #+#    #+#             */
/*   Updated: 2023/01/25 15:35:03 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_base(unsigned long nb, char *base)
{
	unsigned long	length;
	size_t			len;

	len = 0;
	length = ft_strlen(base);
	if (nb >= length)
		len += ft_putnbr_base(nb / length, base);
	len += ft_putchar(base[nb % length]);
	return (len);
}
