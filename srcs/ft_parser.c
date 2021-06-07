/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:23:05 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 15:13:35 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static unsigned char	get_flags(char **format)
{
	unsigned char	flags;

	flags = 0;
	while (ft_strchr("-+ #0", **format))
	{
		if (**format == '-')
		{
			flags |= FLG_MINUS;
			flags &= ~FLG_ZERO;
		}
		if (**format == '+')
		{
			flags |= FLG_PLUS;
			flags &= ~FLG_SPACE;
		}
		if (**format == ' ' && !(flags & FLG_PLUS))
			flags |= FLG_SPACE;
		if (**format == '#')
			flags |= FLG_HASH;
		if (**format == '0' && !(flags & FLG_MINUS))
			flags |= FLG_ZERO;
		(*format)++;
	}
	return (flags);
}

static size_t			get_width(char **format, unsigned char *flg, va_list ap)
{
	size_t	width;

	width = 0;
	if (ft_isdigit(**format))
	{
		width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	if (**format == '*')
	{
		width = va_arg(ap, int);
		if (width < 0)
		{
			*flg |= FLG_MINUS;
			width *= -1;
		}
		(*format)++;
	}
	return (width);
}

static int				get_prec(char **format, unsigned char *flg, va_list ap)
{
	int	presicion;

	presicion = 0;
	if (**format == '.')
	{
		(*format)++;
		*flg |= FLG_PREC;
		if (**format == '*')
		{
			presicion = va_arg(ap, int);
			(*format)++;
		}
		else
		{
			presicion = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
	}
	return (presicion);
}

static unsigned char	get_length(char **format)
{
	size_t			len_l;
	size_t			len_h;
	unsigned char	length;

	len_l = 0;
	len_h = 0;
	length = 0;
	while (**format == 'l' || **format == 'h')
		(*(*format)++ == 'l') ? len_l++ : len_h++;
	if (len_l && len_l % 2 == 0)
		length |= LNG_LL;
	else if (len_l)
		length |= LNG_L;
	if (len_h && len_h % 2 == 0)
		length |= LNG_HH;
	else if (len_h)
		length |= LNG_H;
	return (length);
}

t_struct				*ft_parser(char **format, va_list ap)
{
	t_struct	*struct_arg;
	char		*arguments;

	arguments = "%cspdiuxXnfge";
	if (!(struct_arg = malloc(sizeof(t_struct))))
		return (NULL);
	struct_arg->flags = get_flags(format);
	struct_arg->width = get_width(format, &(struct_arg->flags), ap);
	struct_arg->prec = get_prec(format, &(struct_arg->flags), ap);
	struct_arg->length = get_length(format);
	if (!(ft_strchr(arguments, **format)))
	{
		free(struct_arg);
		return (NULL);
	}
	struct_arg->type = *(*format)++;
	if (struct_arg->width < 0)
	{
		struct_arg->width *= -1;
		struct_arg->flags |= FLG_MINUS;
		struct_arg->flags &= ~FLG_ZERO;
	}
	return (struct_arg);
}
