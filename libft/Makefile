# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davmendo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 21:03:07 by davmendo          #+#    #+#              #
#    Updated: 2024/11/09 22:06:31 by davmendo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_strlen.c \
       ft_memset.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strcmp.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_calloc.c \
       ft_strdup.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_putendl_fd.c \
       ft_split.c \
       ft_putnbr_fd.c \
       ft_itoa.c \
       ft_strmapi.c \
       ft_striteri.c \
       get_next_line.c \
       get_next_line_utils.c \
       ft_printf_utils.c \
       ft_printf.c

BONUS_SRCS = ft_lstnew.c \
	     ft_lstadd_front.c \
	     ft_lstsize.c \
	     ft_lstlast.c \
	     ft_lstadd_back.c \
	     ft_lstdelone.c \
	     ft_lstclear.c \
	     ft_lstiter.c \
	     ft_lstmap.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rc $(NAME) $(OBJS)

bonus: $(BONUS_OBJS) $(OBJS)
		ar rc $(NAME) $(BONUS_OBJS) $(OBJS)

clean:
		rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

so:
		$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BONUS_SRCS)
		$(CC) -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)
.SILENT:
