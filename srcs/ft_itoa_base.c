/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:55:55 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/25 21:36:31 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

char	*ft_itoa_base(unsigned long num, size_t base)
{
	char	*numbers;
	char	*str;
	size_t	i;

	i = 0;
	numbers = "0123456789abcdef";
	if (base < 2 || base > 16 || (base != 10 && num < 0))
		return (0);
	i = ft_unsigned_nbrlen(num, base);
	str = ft_calloc(ft_nbrlen(num, base) + 1, sizeof(char));
	while (num / base != 0)
	{
		str[--i] = numbers[(num % base)];
		num = num / base;
	}
	str[0] = numbers[num];
	return (str);
}
