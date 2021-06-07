/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_sign_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 03:17:11 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 06:47:27 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	ft_putnbr_sign(long long n)
{
	unsigned long	nb;

	if (n < 0)
		nb = (unsigned long)(n * (-1));
	else
		nb = (unsigned long)n;
	if (nb >= 10)
	{
		ft_putnbr_fd((nb / 10), 1);
		ft_putchar_fd((nb % 10) + '0', 1);
	}
	else
		ft_putchar_fd((nb % 10) + '0', 1);
}
