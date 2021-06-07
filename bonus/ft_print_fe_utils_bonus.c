/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fe_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:57:40 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:57:44 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_partb_bonus.h"

static void	ft_put_exception(t_struct arg, t_long result)
{
	arg.flags &= (!ft_strncmp(result.reserve, "nan", 3)) ?
			~(FLG_SPACE | FLG_PLUS) : ~0x0;
	if (arg.flags & FLG_MINUS)
	{
		ft_putsign(result.sign, arg.flags);
		ft_putstr_fd(result.reserve, 1);
		while (arg.width-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (arg.width-- > 0)
			ft_putchar_fd(' ', 1);
		ft_putsign(result.sign, arg.flags);
		ft_putstr_fd(result.reserve, 1);
	}
}

size_t		ft_exception(t_struct arg, size_t l, t_long bigint)
{
	arg.width -= 3 + l;
	l += (arg.width > 0) ? arg.width + 3 : 3;
	ft_put_exception(arg, bigint);
	return (l);
}

void		ft_putsign(int sign, unsigned char flags)
{
	if (sign)
		ft_putchar_fd('-', 1);
	else if (flags & FLG_PLUS)
		ft_putchar_fd('+', 1);
	else if (flags & FLG_SPACE)
		ft_putchar_fd(' ', 1);
}

void		ft_put_exp(int e)
{
	ft_putchar_fd('e', 1);
	if (e < 0)
	{
		ft_putchar_fd('-', 1);
		e *= -1;
	}
	else
		ft_putchar_fd('+', 1);
	if (e < 10)
		ft_putchar_fd('0', 1);
	ft_putnbr_fd(e, 1);
}

size_t		ft_twenty_five_lines(size_t l, int dot)
{
	if (dot < 0)
		l += (ft_nbrlen(-dot - 1, 10) > 2) ? ft_nbrlen(-dot - 1, 10) + 2 : 4;
	else
		l += (ft_nbrlen(dot - 1, 10) > 2) ? ft_nbrlen(dot - 1, 10) + 2 : 4;
	return (l);
}
