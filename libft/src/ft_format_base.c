/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:23:56 by ancolmen          #+#    #+#             */
/*   Updated: 2023/01/25 15:43:18 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_base	*ft_format_base(const char *format, va_list ap)
{
	t_base	*base;

	base = malloc(sizeof(t_base));
	if (!base)
		return (NULL);
	base->str = format;
	va_copy(base->arg, ap);
	base->len = 0;
	base->i = 0;
	return (base);
}
