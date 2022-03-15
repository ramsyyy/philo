/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:27:39 by raaga             #+#    #+#             */
/*   Updated: 2021/12/14 20:09:17 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned int nb, char *base)
{
	int			z;
	size_t		size;

	z = 0;
	size = ft_strlen(base);
	if (nb >= size)
		z += ft_putnbr_base(nb / size, base);
	z += ft_putchar(base[nb % size]);
	return (z);
}
