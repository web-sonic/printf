/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:56:41 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/25 20:56:56 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int		ft_nbrlen(long long num, int base)
{
	size_t			count;
	unsigned long	nb;

	count = 1;
	if (num < 0)
	{
		count++;
		nb = (unsigned long)num * (-1);
	}
	else
		nb = (unsigned long)num;
	while (nb / base != 0)
	{
		nb = nb / base;
		count++;
	}
	return (count);
}
