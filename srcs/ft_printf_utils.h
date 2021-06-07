/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:07:15 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 07:03:09 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <stdarg.h>
# include <wctype.h>
# include "../Libft/libft.h"

# define FLG_MINUS	0x01
# define FLG_PLUS	0x02
# define FLG_SPACE	0x04
# define FLG_HASH	0x08
# define FLG_ZERO	0x10
# define FLG_PREC	0x20
# define LNG_L		0x01
# define LNG_LL		0x02
# define LNG_H		0x04
# define LNG_HH		0x08

typedef struct		s_struct
{
	unsigned char	flags;
	int				width;
	int				prec;
	unsigned char	length;
	char			type;
}					t_struct;

int					ft_putformat(char *format, va_list ap);
t_struct			*ft_parser(char **format, va_list ap);
int					ft_router(t_struct arg, va_list ap);
int					ft_printc(t_struct arg, va_list ap);
int					ft_prints(t_struct arg, va_list ap);
int					ft_printp(t_struct arg, va_list ap);
int					ft_printd(t_struct arg, va_list ap);
int					ft_printu(t_struct arg, va_list ap);
int					ft_printx(t_struct arg, va_list ap);
int					ft_nbrlen(long long num, int base);
int					ft_unsigned_nbrlen(unsigned long long nb, int base);
char				*ft_itoa_base(unsigned long num, size_t base);
void				ft_putnbr_sign(long long n);

#endif
