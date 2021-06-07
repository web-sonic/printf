/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 17:34:59 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 07:15:50 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

int			ft_lenwc(wint_t wc)
{
	if (wc < 0x80)
		return (1);
	else if (wc < 0x800)
		return (2);
	else if (wc < 0x10000)
		return (3);
	else
		return (4);
}

static int	ft_printlc(t_struct arg, va_list ap)
{
	wint_t	c;
	int		width;
	int		c_len;

	arg.width -= 1;
	c = va_arg(ap, wint_t);
	c_len = ft_lenwc(c);
	width = arg.width;
	if (arg.flags & FLG_MINUS)
	{
		ft_putwchar(c);
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
		ft_putwchar(c);
	}
	return ((arg.width > 0) ? c_len + arg.width : c_len);
}

static int	ft_printc(t_struct arg, va_list ap)
{
	int	c;
	int	width;

	arg.width -= 1;
	c = (arg.type == '%') ? '%' : va_arg(ap, int);
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

int			ft_router_c(t_struct arg, va_list ap)
{
	if (arg.length & LNG_L)
		return (ft_printlc(arg, ap));
	else
		return (ft_printc(arg, ap));
}
