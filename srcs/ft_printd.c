/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:40:02 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:49:37 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static void			putsigns(unsigned char flags, long long nbr)
{
	if (nbr < 0)
		ft_putchar_fd('-', 1);
	else if (flags & FLG_PLUS)
		ft_putchar_fd('+', 1);
	else if (flags & FLG_SPACE)
		ft_putchar_fd(' ', 1);
}

static void			putprecision(int len_n, long long nbr)
{
	if (len_n)
	{
		while (len_n-- > ft_nbrlen(nbr, 10))
			ft_putchar_fd('0', 1);
		ft_putnbr_sign(nbr);
	}
}

static void			putnbr(unsigned char flags, long long nbr,
							int len_n, int width)
{
	int	t;

	t = 0;
	if (flags & FLG_MINUS)
	{
		putsigns(flags, nbr);
		putprecision(len_n, nbr);
		while (width-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (width-- > 0)
			if (flags & FLG_ZERO)
			{
				if (!(t++))
					putsigns(flags, nbr);
				ft_putchar_fd('0', 1);
			}
			else
				ft_putchar_fd(' ', 1);
		if (!(t))
			putsigns(flags, nbr);
		putprecision(len_n, nbr);
	}
}

static long long	get_num(unsigned char length, va_list ap)
{
	long long	n;

	if (length & LNG_L)
		n = va_arg(ap, long);
	else if (length & LNG_LL)
		n = va_arg(ap, long long);
	else if (length & LNG_HH)
		n = (char)va_arg(ap, int);
	else if (length & LNG_H)
		n = (short)va_arg(ap, int);
	else
		n = va_arg(ap, int);
	return (n);
}

int					ft_printd(t_struct arg, va_list ap)
{
	long long			num;
	int					len_nbr;
	size_t				len;
	unsigned long long	nbr;

	num = get_num(arg.length, ap);
	if (arg.flags & FLG_PREC && arg.prec >= 0)
		arg.flags &= ~FLG_ZERO;
	nbr = num;
	if (num < 0 && ((nbr = -1 * num) || !nbr))
		arg.flags &= (~FLG_PLUS & ~FLG_SPACE);
	if (arg.prec > ft_nbrlen(nbr, 10))
		len_nbr = (num < 0) ? arg.prec + 1 : arg.prec;
	else
		len_nbr = (!num && !arg.prec && arg.flags & FLG_PREC) ?
			0 : ft_nbrlen(num, 10);
	arg.prec = (arg.prec < 0) ? 0 : arg.prec;
	arg.width -= len_nbr;
	len = (arg.width > 0) ? arg.width + len_nbr : len_nbr;
	if (arg.flags & FLG_PLUS || arg.flags & FLG_SPACE)
		(arg.width > 0) ? arg.width-- : len++;
	putnbr(arg.flags, num, len_nbr, arg.width);
	return (len);
}
