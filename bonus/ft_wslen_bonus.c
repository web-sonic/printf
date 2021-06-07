/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wslen_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:48:56 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 14:50:37 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils_bonus.h"

size_t	ft_wslen(wchar_t *s)
{
	size_t	count;

	count = 0;
	while (*s++ != '\0')
		count++;
	return (count);
}
