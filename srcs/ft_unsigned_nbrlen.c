/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 20:19:44 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/25 20:57:15 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int		ft_unsigned_nbrlen(unsigned long long nb, int base)
{
	size_t			count;

	count = 1;
	while (nb / base != 0)
	{
		nb = nb / base;
		count++;
	}
	return (count);
}
