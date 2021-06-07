/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_partb_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:00:36 by ctragula          #+#    #+#             */
/*   Updated: 2020/12/26 07:07:16 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_PARTB_BONUS_H
# define FT_PRINTF_PARTB_BONUS_H

# include "ft_printf_bonus.h"

# define BASE 1000000000
# define SIZE 231
# define SHIFT 1023
# define MANTISA 52

typedef struct			s_long
{
	unsigned long long	values[SIZE];
	int					length;
	int					dot;
	int					sign;
	char				*reserve;
}						t_long;

typedef union			u_union
{
	double				fl;
	struct
	{
		unsigned long	m : 52;
		unsigned int	exp : 11;
		unsigned int	sign : 1;
	}					parts;
}						t_union;

long long				ft_recursive_power(long long nb, int power);
t_long					ft_addbig(long num);
t_long					ft_sumbig(t_long a, t_long b);
t_long					ft_subbig(t_long a, t_long b);
t_long					ft_multbig(t_long a, t_long b);
t_long					ft_divbigsmall(t_long a, long b);
t_long					ft_check_double(double nbr);
int						ft_biglen(t_long bigint);
void					print_bigint(t_long bigint);
void					ft_putsign(int sign, unsigned char flags);
t_long					ft_round_double(t_long bigint, int rnd);
void					ft_put_exp(int e);
size_t					ft_exception(t_struct arg, size_t l, t_long bigint);
int						ft_print_g(t_struct arg, va_list ap);
void					ft_put_double_f(t_long result, t_struct arg);
void					ft_put_double_e(t_long result, t_struct arg);
size_t					ft_twenty_five_lines(size_t l, int dot);

#endif
