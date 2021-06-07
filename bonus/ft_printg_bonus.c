/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:29:25 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:50:28 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_partb_bonus.h"

static t_long	round_zero(t_long bigint, int *prec, int tr)
{
	t_long	remaind;
	int		i;

	i = SIZE - 1;
	while (!bigint.values[i] && i)
		i--;
	remaind = ft_divbigsmall(bigint, 10);
	remaind = ft_multbig(remaind, ft_addbig(10));
	remaind = ft_subbig(bigint, remaind);
	while ((!remaind.values[0] && ft_biglen(bigint) > bigint.dot) ||
			(bigint.length == 301 && !remaind.values[0]
				&& ft_biglen(bigint) > 1))
	{
		bigint = ft_divbigsmall(bigint, 10);
		remaind = ft_divbigsmall(bigint, 10);
		remaind = ft_multbig(remaind, ft_addbig(10));
		remaind = ft_subbig(bigint, remaind);
	}
	if (!tr)
		*prec = (bigint.dot >= 0) ?
			ft_biglen(bigint) - bigint.dot : ft_biglen(bigint) - 1;
	else
		(*prec)--;
	return (bigint);
}

static size_t	gtof(t_long result, size_t l, t_struct arg, double nbr)
{
	result = round_zero(result, &(arg.prec), (arg.flags & FLG_HASH));
	if (nbr && result.dot >= 0)
		l += (arg.prec) ? ft_biglen(result) + 2 : result.dot + 1;
	else if (arg.prec)
		l += (result.dot) ? -result.dot + ft_biglen(result) + 2 : 1;
	else
		l += ft_biglen(result) - result.dot + 2;
	if (((arg.flags & FLG_HASH)))
	{
		l += arg.prec - ft_biglen(result) + result.dot;
		l -= (!nbr) ? 0 : 1;
	}
	l -= (result.dot <= 0 || arg.flags & FLG_HASH) ? 0 : 1;
	arg.width -= l;
	l += (arg.width > 0) ? arg.width : 0;
	ft_put_double_f(result, arg);
	return (l);
}

static size_t	gtoe(t_long result, size_t l, t_struct arg)
{
	int	dot;

	result.length = 301;
	result = round_zero(result, &(arg.prec), (arg.flags & FLG_HASH));
	if (result.dot > 0 && arg.prec < 0 && ft_biglen(result) > 1)
		l += 2 + result.dot + arg.prec - 1;
	else if (result.dot < 0 && ft_biglen(result) > 1)
		l += ft_biglen(result) + 1;
	else
		l += ft_biglen(result);
	if (arg.flags & FLG_HASH)
	{
		l += arg.prec + 1;
		(!arg.prec) ? arg.flags |= FLG_EMPTY : 0;
	}
	dot = (result.dot < 0) ? -result.dot : result.dot;
	if (dot - 1 && ft_biglen(result) - dot)
		l += (ft_nbrlen(dot - 1, 10) > 2 && dot > 0) ?
			ft_nbrlen(dot - 1, 10) + 2 : 4;
	arg.width -= l;
	l += (arg.width > 0) ? arg.width : 0;
	ft_put_double_e(result, arg);
	if (result.dot - 1 && ft_biglen(result) - result.dot)
		ft_put_exp(result.dot - 1);
	return (l);
}

int				ft_print_g(t_struct arg, va_list ap)
{
	double		nbr;
	t_long		res;
	size_t		l;

	nbr = va_arg(ap, double);
	(!(arg.flags & FLG_PREC) || arg.prec < 0) ? arg.prec = 6 : 0;
	arg.prec += (!arg.prec) ? 1 : 0;
	res = ft_check_double(nbr);
	l = ((res.sign || arg.flags & FLG_PLUS || arg.flags & FLG_SPACE) &&
		(!res.reserve || !ft_strncmp(res.reserve, "inf", 3))) ? 1 : 0;
	if (res.reserve)
		return (ft_exception(arg, l, res));
	if ((res.dot >= 0 && res.dot < arg.prec) || (res.dot < 0 && res.dot >= -3))
	{
		res = (res.dot < 0 && !arg.prec) ?
			ft_round_double(res, ft_biglen(res) + res.dot + 2) :
			ft_round_double(res, ft_biglen(res) - arg.prec);
		return (gtof(res, l, arg, nbr));
	}
	else
	{
		res = ft_round_double(res, ft_biglen(res) - arg.prec);
		res = (ft_biglen(res) > arg.prec + 1) ? ft_divbigsmall(res, 10) : res;
		return (gtoe(res, l, arg));
	}
}
