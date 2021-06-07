/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:15:18 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/12 16:51:37 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static void	putstr(unsigned char flags, char *str, size_t len_str, int width)
{
	if (flags & FLG_MINUS)
	{
		while (len_str--)
			ft_putchar_fd(*str++, 1);
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
		while (len_str--)
			ft_putchar_fd(*str++, 1);
	}
}

int			ft_prints(t_struct arg, va_list ap)
{
	size_t	len;
	char	*str;
	size_t	len_str;

	if (!(str = va_arg(ap, char *)))
		str = "(null)";
	len = 0;
	len_str = (arg.flags & FLG_PREC && arg.prec >= 0 &&
		arg.prec < (int)ft_strlen(str)) ? arg.prec : ft_strlen(str);
	arg.width -= len_str;
	len += len_str;
	if (arg.width > 0)
		len += arg.width;
	putstr(arg.flags, str, len_str, arg.width);
	return (len);
}
