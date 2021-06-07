/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 17:34:59 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/12 16:00:18 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_printc(t_struct arg, va_list ap)
{
	int	c;
	int	width;

	arg.width -= 1;
	c = (arg.type == '%') ? '%' : va_arg(ap, int);
	if (arg.length & LNG_L)
		if (c > 255)
			return (-1);
	width = arg.width;
	if (arg.flags & FLG_MINUS)
	{
		ft_putchar_fd(c, 1);
		while (width-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (width-- > 0)
			if (arg.flags & FLG_ZERO)
				ft_putchar_fd('0', 1);
			else
				ft_putchar_fd(' ', 1);
		ft_putchar_fd(c, 1);
	}
	return ((arg.width > 0) ? 1 + arg.width : 1);
}
