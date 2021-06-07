/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_double_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:01:19 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:54:57 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_partb_bonus.h"

static t_long	get_remaind(t_long bigint)
{
	t_long	remaind;

	remaind = ft_divbigsmall(bigint, 10);
	remaind = ft_multbig(remaind, ft_addbig(10));
	remaind = ft_subbig(bigint, remaind);
	return (remaind);
}

static t_long	plus_one(t_long bigint, int remaind, int biggest)
{
	int	len;
	int	i;

	i = SIZE - 1;
	while (!bigint.values[i] && i)
		i--;
	len = (!bigint.values[i]) ? 0 : ft_biglen(bigint);
	if (remaind > 5)
		bigint = ft_sumbig(bigint, ft_addbig(1));
	else if (remaind == 5 && biggest)
		bigint = ft_sumbig(bigint, ft_addbig(1));
	else if (remaind == 5 && bigint.values[0] % 2 == 1)
		bigint = ft_sumbig(bigint, ft_addbig(1));
	if (len < ft_biglen(bigint))
		bigint.dot += 1;
	return (bigint);
}

t_long			ft_round_double(t_long bigint, int rnd)
{
	t_long		remaind;
	int			len;
	int			biggest;

	biggest = 0;
	if (rnd > 0)
	{
		len = ft_biglen(bigint);
		remaind = ft_addbig(0);
		while (rnd-- > 0)
		{
			remaind = get_remaind(bigint);
			bigint = ft_divbigsmall(bigint, 10);
			len--;
			if (!biggest && rnd)
				biggest = remaind.values[0];
		}
		bigint = plus_one(bigint, remaind.values[0], biggest);
	}
	else
		while (rnd++)
			bigint = ft_multbig(bigint, ft_addbig(10));
	return (bigint);
}
