/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setn_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:58:58 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 01:50:35 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

static void	set_long(va_list ap, size_t len)
{
	long int	*ld;

	ld = va_arg(ap, long int *);
	*ld = len;
}

static void	set_longlong(va_list ap, size_t len)
{
	long long int	*lld;

	lld = va_arg(ap, long long int *);
	*lld = len;
}

static void	set_char(va_list ap, size_t len)
{
	signed char	*c;

	c = va_arg(ap, signed char *);
	*c = (signed char)len;
}

static void	set_short(va_list ap, size_t len)
{
	short int	*c;

	c = va_arg(ap, short int *);
	*c = len;
}

int			ft_setn(t_struct arg, va_list ap, size_t len)
{
	int	*d;

	d = 0;
	if (arg.length & LNG_H)
		set_short(ap, len);
	else if (arg.length & LNG_HH)
		set_char(ap, len);
	else if (arg.length & LNG_L)
		set_long(ap, len);
	else if (arg.length & LNG_LL)
		set_longlong(ap, len);
	else
	{
		d = va_arg(ap, int *);
		*d = len;
	}
	return (0);
}
