/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putformat_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:10:25 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:57:22 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

int	ft_putformat(char *format, va_list ap)
{
	size_t		len;
	int			check;
	t_struct	*arg_struct;

	len = 0;
	while (*format)
	{
		while (*format && *format != '%')
		{
			ft_putchar_fd(*format, 1);
			len++;
			format++;
		}
		if (*format == '%')
		{
			format++;
			if (!(arg_struct = ft_parser(&format, ap)))
				return (-1);
			((check = ft_router(*arg_struct, ap, len)) == -1) ?
				len = -1 : (len += check);
			free(arg_struct);
		}
	}
	return (len);
}
