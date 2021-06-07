/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:09:15 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:54:00 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

static void					putsigns(unsigned char flags, char *str, char type)
{
	if (ft_strlen(str) && ft_strncmp(str, "0", 2))
		if (flags & FLG_HASH)
		{
			if (type == 'X')
				ft_putstr_fd("0X", 1);
			else
				ft_putstr_fd("0x", 1);
		}
}

static void					putprecision(size_t len_n, char *str)
{
	if (len_n)
	{
		while (len_n-- > ft_strlen(str))
			ft_putchar_fd('0', 1);
		ft_putstr_fd(str, 1);
	}
}

static void					putx(char *str, size_t len_x, t_struct arg)
{
	int	t;

	t = 0;
	if (arg.flags & FLG_MINUS)
	{
		putsigns(arg.flags, str, arg.type);
		putprecision(len_x, str);
		while (arg.width-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (arg.width-- > 0)
			if (arg.flags & FLG_ZERO)
			{
				if (!(t++))
					putsigns(arg.flags, str, arg.type);
				ft_putchar_fd('0', 1);
			}
			else
				ft_putchar_fd(' ', 1);
		if (!(t))
			putsigns(arg.flags, str, arg.type);
		putprecision(len_x, str);
	}
}

static unsigned long long	get_num(unsigned char length, va_list ap)
{
	unsigned long long	n;

	if (length & LNG_L)
		n = va_arg(ap, unsigned long);
	else if (length & LNG_LL)
		n = va_arg(ap, unsigned long long);
	else if (length & LNG_HH)
		n = (unsigned char)va_arg(ap, size_t);
	else if (length & LNG_H)
		n = (unsigned short)va_arg(ap, size_t);
	else
		n = va_arg(ap, unsigned int);
	return (n);
}

int							ft_printx(t_struct arg, va_list ap)
{
	char	*x;
	int		len;
	size_t	l_x;
	int		i;

	x = ft_itoa_base(get_num(arg.length, ap), 16);
	i = -1;
	if (arg.type == 'X')
		while (x[++i])
			x[i] = ft_toupper(x[i]);
	if (arg.flags & FLG_PREC && arg.prec >= 0)
		arg.flags &= ~FLG_ZERO;
	if (arg.prec > (int)ft_strlen(x))
		l_x = arg.prec;
	else
		l_x = ((*x == '0') && !arg.prec && arg.flags & FLG_PREC) ?
			0 : ft_strlen(x);
	arg.width -= l_x;
	arg.width -= (l_x && arg.flags & FLG_HASH && ft_strncmp(x, "0", 2)) ? 2 : 0;
	len = (arg.width > 0) ? arg.width + l_x : l_x;
	putx(x, l_x, arg);
	len += (l_x && arg.flags & FLG_HASH && ft_strncmp(x, "0", 2)) ? 2 : 0;
	free(x);
	return (len);
}
