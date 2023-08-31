/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:47:40 by ancolmen          #+#    #+#             */
/*   Updated: 2023/01/25 15:56:03 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_checkandprint(t_base *base)
{
	base->i++;
	if (base->str[base->i] == 'c')
		base->len += ft_putchar(va_arg(base->arg, int));
	else if (base->str[base->i] == 's')
		base->len += ft_putstr(va_arg(base->arg, char *));
	else if (base->str[base->i] == 'p')
		base->len += ft_putptr(va_arg(base->arg, void *));
	else if (base->str[base->i] == 'd' || base->str[base->i] == 'i')
		base->len += ft_putnbr(va_arg(base->arg, int));
	else if (base->str[base->i] == 'u')
		base->len += ft_putnbr_u(va_arg(base->arg, unsigned int));
	else if (base->str[base->i] == 'x')
		base->len += ft_putnbr_base(va_arg(base->arg, unsigned int), HEX_LB);
	else if (base->str[base->i] == 'X')
		base->len += ft_putnbr_base(va_arg(base->arg, unsigned int), HEX_UB);
	else if (base->str[base->i] == '%')
		base->len += ft_putchar('%');
	else
	{
		base->len += ft_putchar('%');
		base->len += ft_putchar(base->str[base->i]);
	}
	base->i++;
}	

static int	ft_var_printf(const char *format, va_list ap)
{
	t_base	*base;
	size_t	len;

	len = 0;
	base = ft_format_base(format, ap);
	if (!base)
		return (0);
	while (base->str[base->i])
	{
		if (base->str[base->i] == '%')
			ft_checkandprint(base);
		else
			base->len += write(1, &base->str[base->i++], 1);
	}
	len = base->len;
	free(base);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	len;

	len = 0;
	if (!format)
		return (0);
	va_start(ap, format);
	len = ft_var_printf(format, ap);
	va_end(ap);
	return (len);
}
