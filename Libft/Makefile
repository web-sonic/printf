# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 08:48:35 by ctragula          #+#    #+#              #
#    Updated: 2020/12/25 21:15:16 by ctragula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \

BSRC =	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \

HEADERS = libft.h

ifeq ($(MAKECMDGOALS),bonus)
	OBJ = $(SRC:.c=.o) $(BSRC:.c=.o)
else
	OBJ = $(SRC:.c=.o)
endif

NAME = libft.a

CFLAGS = -c -Wall -Wextra -Werror -MD

.PHONY: all clean fclean re bonus

%.o : %.c $(HEADERS)
			gcc $(CFLAGS) $< -o $(<:.c=.o)

all:	$(NAME)

bonus:	$(NAME)


$(NAME):	$(OBJ)
		$(AR) rcs $@ $?

clean:
		$(RM) *.o *.d
fclean:	clean
		$(RM) $(NAME)

re:	fclean all
