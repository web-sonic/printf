/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:40:47 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:53:17 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_partb_bonus.h"

static void	putnbr_with_dot(long long nbr, size_t l_nbr, int precision)
{
	unsigned long long	divider;
	unsigned long long	int_nbr;
	unsigned long long	prec_nbr;
	int					zero_len;

	divider = ft_recursive_power(10, l_nbr - 1);
	int_nbr = nbr / divider;
	prec_nbr = nbr % divider;
	ft_putnbr_fd(int_nbr, 1);
	zero_len = ft_nbrlen(divider, 10) - ft_nbrlen(prec_nbr, 10) - 1;
	if (precision > 0 || prec_nbr)
	{
		ft_putchar_fd('.', 1);
		while (zero_len-- > 0)
			ft_putchar_fd('0', 1);
		if (divider != 1)
			ft_putnbr_fd(prec_nbr, 1);
	}
}

static void	put_parts(t_long bigint, int i, int precision)
{
	int		first;
	int		nbr_len;
	int		zero_len;

	first = i;
	while (i >= 0)
	{
		nbr_len = (i == first) ? ft_nbrlen(bigint.values[i], 10) : 9;
		if ((i == first && bigint.length != 301) ||
			(precision && bigint.length == 301))
		{
			putnbr_with_dot(bigint.values[i], nbr_len, precision);
			bigint.dot -= nbr_len;
			bigint.length = 0;
		}
		else
		{
			zero_len = nbr_len - ft_nbrlen(bigint.values[i], 10);
			while (zero_len-- > 0)
				ft_putchar_fd('0', 1);
			ft_putnbr_fd(bigint.values[i], 1);
			bigint.dot -= nbr_len;
		}
		i--;
	}
}

static void	putbigint(t_long bigint, int precision, unsigned char flags)
{
	size_t	i;

	i = SIZE - 1;
	while (!bigint.values[i] && i)
		i--;
	if (!bigint.values[i])
	{
		ft_putchar_fd('0', 1);
		if (precision)
		{
			ft_putchar_fd('.', 1);
			while (precision-- > 0)
			{
				ft_putchar_fd('0', 1);
			}
		}
	}
	else
	{
		put_parts(bigint, i, precision);
		precision -= (ft_biglen(bigint) - 1);
		while (precision-- > 0)
			ft_putchar_fd('0', 1);
	}
	(flags & FLG_HASH && flags & FLG_EMPTY) ? ft_putchar_fd('.', 1) : 0;
}

void		ft_put_double_e(t_long result, t_struct arg)
{
	if (arg.flags & FLG_MINUS)
	{
		ft_putsign(result.sign, arg.flags);
		putbigint(result, arg.prec, arg.flags);
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
			putbigint(result, arg.prec, arg.flags);
		}
		else
		{
			while (arg.width-- > 0)
				ft_putchar_fd(' ', 1);
			ft_putsign(result.sign, arg.flags);
			putbigint(result, arg.prec, arg.flags);
		}
	}
}

int			ft_print_e(t_struct arg, va_list ap)
{
	double		nbr;
	t_long		res;
	size_t		l;

	nbr = va_arg(ap, double);
	(!(arg.flags & FLG_PREC) || arg.prec < 0) ? arg.prec = 6 : 0;
	res = ft_check_double(nbr);
	l = ((res.sign || arg.flags & FLG_PLUS || arg.flags & FLG_SPACE) &&
		(!res.reserve || !ft_strncmp(res.reserve, "inf", 3))) ? 1 : 0;
	if (res.reserve)
		return (ft_exception(arg, l, res));
	res = ft_round_double(res, ft_biglen(res) - arg.prec - 1);
	res = (ft_biglen(res) > arg.prec + 1) ? ft_divbigsmall(res, 10) : res;
	if (nbr && res.dot >= 0)
		l += (arg.prec) ? ft_biglen(res) + 1 : ft_biglen(res);
	else
		l += (arg.prec) ? arg.prec + 2 : 1;
	l += (((arg.flags & FLG_HASH) && (arg.flags & FLG_EMPTY))) ? 1 : 0;
	l = ft_twenty_five_lines(l, res.dot);
	arg.width -= l;
	l += (arg.width > 0) ? arg.width : 0;
	ft_put_double_e(res, arg);
	ft_put_exp(res.dot - 1);
	return (l);
}
