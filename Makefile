# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seu_usuario <seu_email@exemplo.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 00:00:00 by seu_usuario       #+#    #+#              #
#    Updated: 2025/06/01 00:00:00 by seu_usuario      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================
# 1. Variáveis principais
# ========================

NAME        = fractol

# 1.1. Lista de fontes do projeto (sem usar wildcard)
SRCS        = main.c args.c render.c hooks.c
OBJS        = main.o args.o render.o hooks.o

# 1.2. MiniLibX
MLX_DIR     = minilibx-linux
MLX_REPO    = https://github.com/42paris/minilibx-linux.git
# Atenção: verifique dentro de minilibx-linux/ qual .a realmente é gerado.
MLX_LIB     = $(MLX_DIR)/libmlx_Linux.a

# 1.3. libft (se existir; caso contrário, remova as linhas abaixo e as referências a LIBFT)
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# 1.4. Compilador e flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(MLX_DIR)
# Inclui pthread para o uso de threads em renderização
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lm -lX11 -lXext -lpthread

# =========================
# 2. Regras principais
# =========================

.PHONY: all clean fclean re

all: $(LIBFT) $(MLX_LIB) $(NAME)

# 2.1. Clona o repositório da MiniLibX apenas se não existir a pasta
$(MLX_DIR):
	@git clone $(MLX_REPO) $(MLX_DIR)

# 2.2. Compila a MiniLibX dentro de minilibx-linux/
$(MLX_LIB): $(MLX_DIR)
	@echo "→ Compiling MiniLibX (em $(MLX_DIR))..."
	@make -C $(MLX_DIR)

# 2.3. (Opcional) Compila a sua libft se o diretório existir
$(LIBFT):
	@echo "→ Compiling libft (em $(LIBFT_DIR))..."
	@make -C $(LIBFT_DIR)

# 2.4. Linka o executável final, depende de todos os .o + libft + MiniLibX
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "→ Linking $(NAME)..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

# =========================
# 3. Regras de compilação
# =========================

# main.o
main.o: main.c fractol.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# args.o
args.o: args.c fractol.h
	$(CC) $(CFLAGS) -c args.c -o args.o

# render.o
render.o: render.c fractol.h
	$(CC) $(CFLAGS) -c render.c -o render.o

# hooks.o
hooks.o: hooks.c fractol.h
	$(CC) $(CFLAGS) -c hooks.c -o hooks.o

# =======================
# 4. Regras de limpeza
# =======================

clean:
	@echo "→ Removing project object files..."
	@rm -f $(OBJS)
	@echo "→ Cleaning libft..."
	@make -C $(LIBFT_DIR) clean
	@echo "→ Cleaning MiniLibX..."
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "→ Removing binary '$(NAME)'..."
	@rm -f $(NAME)
	@echo "→ Removing libft.a..."
	@make -C $(LIBFT_DIR) fclean
	@echo "→ Removing libmlx_Linux.a..."
	@rm -f $(MLX_LIB)

re: fclean all
