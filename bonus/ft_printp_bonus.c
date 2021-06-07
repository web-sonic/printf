/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:58:28 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:55:55 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

static void	putstr(unsigned char flags, char *str, int width)
{
	if (flags & FLG_MINUS)
	{
		ft_putstr_fd("0x", 1);
		ft_putstr_fd(str, 1);
		while (width-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (width-- > 0)
			if (flags & FLG_ZERO)
				ft_putchar_fd('0', 1);
			else
				ft_putchar_fd(' ', 1);
		ft_putstr_fd("0x", 1);
		ft_putstr_fd(str, 1);
	}
}

int			ft_printp(t_struct arg, va_list ap)
{
	size_t	p;
	char	*str;
	size_t	len;

	p = va_arg(ap, size_t);
	str = ft_itoa_base(p, 16);
	len = ft_strlen(str) + 2;
	arg.width -= len;
	if (arg.width > 0)
		len += arg.width;
	if (arg.flags & FLG_PREC && arg.prec == 0 && *str == '0')
		ft_putstr_fd("0x", 1);
	else
		putstr(arg.flags, str, arg.width);
	free(str);
	return (len);
}
