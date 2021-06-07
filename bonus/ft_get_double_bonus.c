/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_double_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:04:44 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:54:37 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_partb_bonus.h"

static t_long	get_exponent(int exponent, int nbr, int power)
{
	long long	num;
	t_long		bigint;

	if (exponent >= 0)
	{
		num = ft_recursive_power(nbr, exponent % power);
		bigint = ft_addbig(num);
		num = ft_recursive_power(nbr, power);
		while ((exponent -= power) >= 0)
		{
			bigint = (!bigint.values[0]) ? (ft_addbig(1)) : bigint;
			bigint = ft_multbig(bigint, ft_addbig(num));
		}
	}
	else
	{
		bigint = ft_addbig(1);
		while (exponent++ && (num = ft_biglen(bigint)))
		{
			bigint = ft_divbigsmall(ft_multbig(bigint, ft_addbig(10)), 2);
			if (num == ft_biglen(bigint))
				bigint.dot--;
		}
	}
	return (bigint);
}

static t_long	get_mantisa(unsigned long mantisa)
{
	t_long		result;
	t_long		base;
	t_long		bigint;
	char		*num;
	size_t		last_unit;

	result = ft_addbig(0);
	base = ft_addbig(1);
	num = ft_itoa_base(mantisa, 2);
	if (!(last_unit = 0) && ft_strrchr(num, '1'))
		last_unit = MANTISA - ft_strlen(ft_strrchr(num, '1')) + 1;
	while (last_unit--)
		base = ft_multbig(base, ft_addbig(10));
	while (ft_strrchr(num, '1'))
	{
		bigint = ft_divbigsmall(base, 2);
		last_unit = MANTISA - ft_strlen(ft_strrchr(num, '1')) + 1;
		num[ft_strlen(num) - ft_strlen(ft_strrchr(num, '1'))] = '0';
		while (--last_unit)
			bigint = ft_divbigsmall(bigint, 2);
		result = ft_sumbig(result, bigint);
	}
	result = ft_sumbig(result, base);
	free(num);
	return (result);
}

int				ft_biglen(t_long bigint)
{
	size_t	i;
	int		len;

	i = SIZE - 1;
	while (!bigint.values[i] && i)
		i--;
	len = ft_nbrlen(bigint.values[i], 10);
	if (i > 0)
		len += i * 9;
	return (len);
}

static t_long	get_double(unsigned int exp, unsigned long mant)
{
	t_long	exponent;
	t_long	mantisa;
	t_long	result;

	exponent = get_exponent(exp - SHIFT, 2, 29);
	mantisa = get_mantisa(mant);
	result = ft_multbig(exponent, mantisa);
	if (exp >= SHIFT)
		result.dot = ft_biglen(exponent);
	if (ft_biglen(result) == ft_biglen(exponent) + ft_biglen(mantisa))
		result.dot++;
	if (result.dot <= 0)
		result.dot += 2;
	return (result);
}

t_long			ft_check_double(double nbr)
{
	t_union		f;
	t_long		result;

	f.fl = nbr;
	if (!nbr)
	{
		result = ft_addbig(0);
		result.dot = 1;
		result.reserve = NULL;
	}
	else if (f.parts.exp == 2047 && f.parts.m)
		result.reserve = "nan";
	else if (f.parts.exp == 2047)
		result.reserve = "inf";
	else
	{
		result = get_double(f.parts.exp, f.parts.m);
		result.reserve = NULL;
	}
	result.sign = f.parts.sign;
	return (result);
}
