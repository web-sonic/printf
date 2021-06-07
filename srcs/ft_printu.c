/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:56:46 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:49:09 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void						ft_putunbr(unsigned long long nb)
{
	if (nb >= 10)
	{
		ft_putunbr((nb / 10));
		ft_putchar_fd((nb % 10) + '0', 1);
	}
	else
		ft_putchar_fd((nb % 10) + '0', 1);
}

static void					putprecision(int len_n, unsigned long long nbr)
{
	if (len_n)
	{
		while (len_n-- > ft_unsigned_nbrlen(nbr, 10))
			ft_putchar_fd('0', 1);
		ft_putunbr(nbr);
	}
}

static void					putnbr(unsigned char flags,
					unsigned long long nbr, int len_n, int width)
{
	if (flags & FLG_MINUS)
	{
		putprecision(len_n, nbr);
		while (width-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (width-- > 0)
			if (flags & FLG_ZERO)
			{
				ft_putchar_fd('0', 1);
			}
			else
				ft_putchar_fd(' ', 1);
		putprecision(len_n, nbr);
	}
}

static unsigned long long	get_num(unsigned char length, va_list ap)
{
	unsigned long long	n;

	if (length & LNG_L)
		n = va_arg(ap, unsigned long);
	else if (length & LNG_LL)
		n = va_arg(ap, unsigned long long);
	else if (length & LNG_HH)
		n = (unsigned char)va_arg(ap, size_t);
	else if (length & LNG_H)
		n = (unsigned short)va_arg(ap, size_t);
	else
		n = va_arg(ap, unsigned int);
	return (n);
}

int							ft_printu(t_struct arg, va_list ap)
{
	unsigned long long	num;
	int					len_nbr;
	size_t				len;

	num = get_num(arg.length, ap);
	if (arg.flags & FLG_PREC && arg.prec >= 0)
		arg.flags &= ~FLG_ZERO;
	if (arg.prec > ft_unsigned_nbrlen(num, 10))
		len_nbr = arg.prec;
	else
		len_nbr = (!num && !arg.prec && arg.flags & FLG_PREC) ?
			0 : ft_unsigned_nbrlen(num, 10);
	arg.width -= len_nbr;
	len = (arg.width > 0) ? arg.width + len_nbr : len_nbr;
	putnbr(arg.flags, num, len_nbr, arg.width);
	return (len);
}
