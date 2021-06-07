/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_arifmetics_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:45:17 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:55:36 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_partb_bonus.h"

t_long	ft_addbig(long num)
{
	int		i;
	t_long	bigint;

	bigint.length = SIZE - 1;
	bigint.dot = -1;
	bigint.sign = 0;
	bigint.values[0] = num;
	i = 1;
	while (i < SIZE)
		bigint.values[i++] = 0;
	i = -1;
	while (++i < bigint.length)
	{
		bigint.values[i + 1] += bigint.values[i] / BASE;
		bigint.values[i] %= BASE;
	}
	return (bigint);
}

t_long	ft_sumbig(t_long a, t_long b)
{
	int	i;

	i = -1;
	while (++i < SIZE - 1)
		a.values[i] += b.values[i];
	i = -1;
	while (++i < SIZE - 1)
	{
		if (a.values[i] >= BASE)
		{
			a.values[i] -= BASE;
			a.values[i + 1]++;
		}
	}
	return (a);
}

t_long	ft_subbig(t_long a, t_long b)
{
	int			i;

	i = -1;
	while (++i < b.length)
		a.values[i] -= b.values[i];
	while (++i < b.length - 1)
	{
		if (a.values[i] < 0)
		{
			a.values[i] += BASE;
			a.values[i + 1]--;
		}
	}
	return (a);
}

t_long	ft_multbig(t_long a, t_long b)
{
	int			i;
	int			j;
	t_long		result;

	result = ft_addbig(0);
	i = -1;
	while (++i < b.length)
	{
		j = -1;
		while (++j < b.length - i)
			result.values[i + j] += a.values[i] * b.values[j];
	}
	i = -1;
	while (++i < b.length)
	{
		result.values[i + 1] += result.values[i] / BASE;
		result.values[i] %= BASE;
	}
	result.dot = a.dot;
	result.sign = ((a.sign && !b.sign) || (!a.sign && b.sign)) ? 1 : 0;
	return (result);
}

t_long	ft_divbigsmall(t_long a, long b)
{
	int	i;

	i = SIZE;
	while (--i >= 0)
	{
		if (i)
			a.values[i - 1] += (a.values[i] % b) * BASE;
		a.values[i] /= b;
	}
	return (a);
}
