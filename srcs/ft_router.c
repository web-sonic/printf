/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 17:27:18 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 01:43:33 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	ft_router(t_struct arg, va_list ap)
{
	if (arg.type == 'c' || arg.type == '%')
		return (ft_printc(arg, ap));
	if (arg.type == 's')
		return (ft_prints(arg, ap));
	if (arg.type == 'p')
		return (ft_printp(arg, ap));
	if (arg.type == 'd' || arg.type == 'i')
		return (ft_printd(arg, ap));
	if (arg.type == 'u')
		return (ft_printu(arg, ap));
	if (arg.type == 'x' || arg.type == 'X')
		return (ft_printx(arg, ap));
	return (-1);
}
