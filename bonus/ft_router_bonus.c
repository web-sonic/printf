/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_router_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 17:27:18 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:21:19 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

int	ft_router(t_struct arg, va_list ap, size_t len)
{
	if (arg.type == 'c' || arg.type == '%')
		return (ft_router_c(arg, ap));
	if (arg.type == 's')
		return (ft_router_s(arg, ap));
	if (arg.type == 'p')
		return (ft_printp(arg, ap));
	if (arg.type == 'd' || arg.type == 'i')
		return (ft_printd(arg, ap));
	if (arg.type == 'u')
		return (ft_printu(arg, ap));
	if (arg.type == 'x' || arg.type == 'X')
		return (ft_printx(arg, ap));
	if (arg.type == 'n')
		return (ft_setn(arg, ap, len));
	if (arg.type == 'f')
		return (ft_print_double(arg, ap));
	if (arg.type == 'e')
		return (ft_print_e(arg, ap));
	if (arg.type == 'g')
		return (ft_print_g(arg, ap));
	else
		return (-1);
}
