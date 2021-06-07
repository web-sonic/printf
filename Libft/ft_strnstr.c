/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:15:17 by ctragula          #+#    #+#             */
/*   Updated: 2020/11/08 11:25:29 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	slen;
	char	cs;
	char	c;
	char	*front;

	slen = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	cs = *needle;
	front = (char *)haystack;
	while (((c = *front) != '\0') && (len-- >= slen))
	{
		if (c == cs)
			if (ft_strncmp(front, needle, slen) == 0)
				return ((char *)front);
		front++;
	}
	return (NULL);
}
