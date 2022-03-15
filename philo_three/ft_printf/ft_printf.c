/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:36:18 by raaga             #+#    #+#             */
/*   Updated: 2021/12/14 20:07:45 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_param(char c, va_list param)
{
	int	i;

	i = 0;
	if (c == 'd' || c == 'i')
		i += ft_putnbr((int)va_arg(param, int));
	else if (c == 'c')
		i += ft_putchar((char)va_arg(param, int));
	else if (c == 's')
		i += ft_putstr((char *)va_arg(param, char *));
	else if (c == 'x')
		i += ft_putnbr_base(va_arg(param, int), "0123456789abcdef");
	else if (c == '%')
		i += ft_putchar('%');
	else if (c == 'p')
	{
		i += ft_putstr("0x");
		i += ft_putnbr_base_long(va_arg(param, unsigned long int),
				"0123456789abcdef");
	}
	else if (c == 'u')
		i += ft_putnbr_unsigned((unsigned int)va_arg(param, unsigned int));
	else if (c == 'X')
		i += ft_putnbr_base(va_arg(param, unsigned int), "0123456789ABCDEF");
	return (i);
}

int	ft_printf(const char	*str, ...)
{
	int		i;
	va_list	param;

	i = 0;
	va_start(param, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			i += check_param(*str, param);
			str++;
		}
		else
		{
			ft_putchar(*str);
			i++;
			str++;
		}
	}
	va_end(param);
	return (i);
}
