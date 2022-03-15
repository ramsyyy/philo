/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_long.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:30:38 by raaga             #+#    #+#             */
/*   Updated: 2021/12/14 20:07:28 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base_long(unsigned long long nb, char *base)
{
	int			z;
	size_t		size;

	z = 0;
	size = ft_strlen(base);
	if (nb >= size)
		z += ft_putnbr_base_long(nb / size, base);
	z += ft_putchar(base[nb % size]);
	return (z);
}
