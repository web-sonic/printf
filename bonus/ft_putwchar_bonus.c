/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 03:59:29 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 05:58:41 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

static void	put_four_bytes(wchar_t wc)
{
	wchar_t	first;
	wchar_t	second;
	wchar_t	third;
	wchar_t fourth;

	first = 0x80 + wc % 0x40;
	wc = wc / 0x40;
	second = 0x80 + wc % 0x40;
	wc = wc / 0x40;
	third = 0x80 + wc % 0x40;
	wc = wc / 0x40;
	fourth = 0xF0 + wc % 0x80;
	write(1, &fourth, 1);
	write(1, &third, 1);
	write(1, &second, 1);
	write(1, &first, 1);
}

static void	put_three_bytes(wchar_t wc)
{
	wchar_t	first;
	wchar_t	second;
	wchar_t	third;

	first = 0x80 + wc % 0x40;
	wc = wc / 0x40;
	second = 0x80 + wc % 0x40;
	wc = wc / 0x40;
	third = 0xE0 + wc;
	write(1, &third, 1);
	write(1, &second, 1);
	write(1, &first, 1);
}

static void	put_two_bytes(wchar_t wc)
{
	wchar_t	first;
	wchar_t	second;

	first = 0x80 + wc % 0x40;
	wc = wc / 0x40;
	second = 0xC0 + wc;
	write(1, &second, 1);
	write(1, &first, 1);
}

void		ft_putwchar(wchar_t wc)
{
	if (wc < 0x80)
		write(1, &wc, 1);
	else if (wc < 0x800)
		put_two_bytes(wc);
	else if (wc < 0x10000)
		put_three_bytes(wc);
	else
		put_four_bytes(wc);
}
