# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 15:54:46 by ctragula          #+#    #+#              #
#    Updated: 2020/12/26 14:56:23 by ctragula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIB = Libft/libft.a

SRC = srcs/

SRCS = srcs/ft_printf.c \
		srcs/ft_nbrlen.c \
		srcs/ft_itoa_base.c \
		srcs/ft_unsigned_nbrlen.c \
		srcs/ft_putformat.c \
		srcs/ft_parser.c \
		srcs/ft_printc.c \
		srcs/ft_printd.c \
		srcs/ft_printp.c \
		srcs/ft_prints.c \
		srcs/ft_printu.c \
		srcs/ft_printx.c \
		srcs/ft_router.c \
		srcs/ft_putnbr_sign.c \

B_SRCS = bonus/ft_printf_bonus.c \
		bonus/ft_nbrlen_bonus.c \
		bonus/ft_itoa_base_bonus.c \
		bonus/ft_unsigned_nbrlen_bonus.c \
		bonus/ft_putformat_bonus.c \
		bonus/ft_get_double_bonus.c \
		bonus/ft_long_arifmetics_bonus.c \
		bonus/ft_parser_bonus.c \
		bonus/ft_print_fe_utils_bonus.c \
		bonus/ft_printc_bonus.c \
		bonus/ft_printd_bonus.c \
		bonus/ft_prints_bonus.c \
		bonus/ft_printe_bonus.c \
		bonus/ft_print_float_bonus.c \
		bonus/ft_printg_bonus.c \
		bonus/ft_printp_bonus.c \
		bonus/ft_printu_bonus.c \
		bonus/ft_printx_bonus.c \
		bonus/ft_recursive_power_bonus.c \
		bonus/ft_round_double_bonus.c \
		bonus/ft_router_bonus.c \
		bonus/ft_setn_bonus.c \
		bonus/ft_putnbr_sign_bonus.c \
		bonus/ft_putwchar_bonus.c \
		bonus/ft_wslen_bonus.c \
		bonus/ft_putws_bonus.c \


ifeq ($(MAKECMDGOALS),bonus)
	OBJ = $(patsubst %_bonus.c,%.o,$(B_SRCS))
	HEADERS = bonus/ft_printf_utils_bonus.h \
		bonus/ft_printf_bonus.h \
		bonus/ft_printf_partb_bonus.h
else
	OBJ = $(SRCS:.c=.o)
	HEADERS = srcs/ft_printf_utils.h srcs/ft_printf.h
endif

CFLAGS = -Wall -Wextra -Werror

CC = gcc

ARFLAGS = rcs

.PHONY: all clean fclean re bonus

all:	$(NAME)

bonus:	$(NAME)


%.o : %_bonus.c
	$(CC) $(CFLAGS) -c $< -o $(<:_bonus.c=.o)


$(LIB):
		$(MAKE) -C libft
		cp libft/libft.a libftprintf.a

$(OBJ): $(HEADERS)

$(NAME):	$(LIB) $(OBJ) $(NAME)($(OBJ))

clean:
	$(MAKE) -C libft clean
	$(RM) $(SRCS:.c=.o) $(patsubst %_bonus.c,%.o,$(B_SRCS))

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) libftprintf.a

re:	fclean all
