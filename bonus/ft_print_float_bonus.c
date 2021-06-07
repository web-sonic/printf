/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:25:12 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:52:20 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_partb_bonus.h"

static void	putnbr_with_dot(t_long bigint, size_t i, size_t l_nbr, int first)
{
	unsigned long long	div;
	unsigned long long	int_nbr;
	unsigned long long	prec_nbr;
	int					zero_len;

	div = (bigint.dot >= 0) ? ft_recursive_power(10, l_nbr - bigint.dot) : 1;
	int_nbr = (div > 1) ? bigint.values[i] / div : 0;
	prec_nbr = (div > 1) ? bigint.values[i] % div : bigint.values[i];
	zero_len = (int_nbr) ? bigint.dot - ft_nbrlen(int_nbr, 10) : bigint.dot;
	while (zero_len-- > 0)
		ft_putchar_fd('0', 1);
	if (!first && !int_nbr)
		ft_putchar_fd('0', 1);
	if (int_nbr)
		ft_putnbr_fd(int_nbr, 1);
	zero_len = (div > 1) ? ft_nbrlen(div, 10) - ft_nbrlen(prec_nbr, 10)
				: -bigint.dot + 1;
	ft_putchar_fd('.', 1);
	while (--zero_len > 0)
		ft_putchar_fd('0', 1);
	ft_putnbr_fd(prec_nbr, 1);
}

static void	put_parts(t_long big, int i)
{
	int		f;
	int		nbr_len;
	int		zero_len;

	f = i;
	while (i >= 0)
	{
		nbr_len = (i == f) ? ft_nbrlen(big.values[i], 10) : 9;
		if (((big.dot >= 0 && big.dot < nbr_len) || (big.dot < 0)) && f >= 0)
		{
			putnbr_with_dot(big, i, nbr_len, f - i);
			f = -1;
			big.dot -= nbr_len;
		}
		else
		{
			zero_len = nbr_len - ft_nbrlen(big.values[i], 10);
			if (zero_len)
				while (zero_len-- > 0)
					ft_putchar_fd('0', 1);
			ft_putnbr_fd(big.values[i], 1);
			big.dot -= nbr_len;
		}
		i--;
	}
}

void		ft_putbigint(t_long bigint, int precision, unsigned char flags)
{
	size_t	i;

	i = SIZE - 1;
	while (!bigint.values[i] && i)
		i--;
	if (!bigint.values[i])
	{
		ft_putchar_fd('0', 1);
		if (precision > 0)
		{
			ft_putchar_fd('.', 1);
			while (precision-- > 0)
				ft_putchar_fd('0', 1);
		}
	}
	else
	{
		put_parts(bigint, i);
		precision -= (ft_biglen(bigint) - bigint.dot);
		while (precision-- > 0)
			ft_putchar_fd('0', 1);
	}
	if ((flags & FLG_EMPTY) && (flags & FLG_HASH))
		ft_putchar_fd('.', 1);
}

void		ft_put_double_f(t_long result, t_struct arg)
{
	if (arg.flags & FLG_MINUS)
	{
		ft_putsign(result.sign, arg.flags);
		ft_putbigint(result, arg.prec, arg.flags);
		while (arg.width-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		if (arg.flags & FLG_ZERO)
		{
			ft_putsign(result.sign, arg.flags);
			while (arg.width-- > 0)
				ft_putchar_fd('0', 1);
			ft_putbigint(result, arg.prec, arg.flags);
		}
		else
		{
			while (arg.width-- > 0)
				ft_putchar_fd(' ', 1);
			ft_putsign(result.sign, arg.flags);
			ft_putbigint(result, arg.prec, arg.flags);
		}
	}
}

int			ft_print_double(t_struct arg, va_list ap)
{
	double		nbr;
	t_long		result;
	size_t		l;

	nbr = va_arg(ap, double);
	(!(arg.flags & FLG_PREC) || arg.prec < 0) ? arg.prec = 6 : 0;
	result = ft_check_double(nbr);
	l = ((result.sign || arg.flags & FLG_PLUS || arg.flags & FLG_SPACE) &&
		(!result.reserve || !ft_strncmp(result.reserve, "inf", 3))) ? 1 : 0;
	if (result.reserve)
		return (ft_exception(arg, l, result));
	result =
		ft_round_double(result, ft_biglen(result) - result.dot - arg.prec);
	if (nbr && result.dot >= 0)
		l += (arg.prec) ? ft_biglen(result) + 1 : result.dot;
	else
		l += (arg.prec) ? arg.prec + 2 : 1;
	l += (result.dot) ? 0 : 1;
	if (((arg.flags & FLG_HASH) && (arg.flags & FLG_EMPTY)))
		l += 1;
	arg.width -= l;
	l += (arg.width > 0) ? arg.width : 0;
	ft_put_double_f(result, arg);
	return (l);
}
