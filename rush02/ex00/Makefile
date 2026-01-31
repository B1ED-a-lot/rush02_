# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seu_login <seu_login@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/30 00:00:00 by seu_login         #+#    #+#              #
#    Updated: 2026/01/30 00:00:00 by seu_login        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                 RUSH-02                                      #
# ============================================================================ #
#
# 📋 REGRAS OBRIGATÓRIAS:
#    - all     : Compila o programa (regra padrão)
#    - clean   : Remove arquivos objeto (.o)
#    - fclean  : Remove .o E o executável
#    - re      : fclean + all (recompila tudo)
#
# 🔧 FLAGS DE COMPILAÇÃO:
#    -Wall    : Ativa todos os warnings comuns
#    -Wextra  : Ativa warnings extras
#    -Werror  : Trata warnings como erros (não compila se houver warning!)
#
# 💡 DICA: Durante desenvolvimento, comente -Werror para ver warnings sem parar
#          Mas NUNCA entregue sem -Werror!
#
# ============================================================================ #

# Nome do executável
NAME		= rush-02

# Compilador e flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# Diretórios
SRCS_DIR	= srcs
INCL_DIR	= includes

# Arquivos fonte (IMPORTANTE: Liste TODOS explicitamente, não use *.c)
SRCS		= $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/ft_dict_parsing.c \
			  $(SRCS_DIR)/ft_dict_utils.c \
			  $(SRCS_DIR)/ft_number_converter.c \
			  $(SRCS_DIR)/ft_utils.c

# Arquivos objeto (substitui .c por .o)
OBJS		= $(SRCS:.c=.o)

# ============================================================================ #
#                                  REGRAS                                      #
# ============================================================================ #

# Regra padrão (executada com 'make' ou 'make all')
all: $(NAME)

# Regra para criar o executável
# $@ = nome do alvo (rush-02)
# $^ = todas as dependências (os .o)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "✅ Compilação concluída: $(NAME)"

# Regra padrão para compilar .c em .o
# $< = primeira dependência (o arquivo .c)
# $@ = nome do alvo (o arquivo .o)
# -I$(INCL_DIR) = adiciona includes/ ao caminho de busca de headers
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

# Remove arquivos objeto
clean:
	rm -f $(OBJS)
	@echo "🧹 Arquivos objeto removidos"

# Remove objetos E executável
fclean: clean
	rm -f $(NAME)
	@echo "🧹 Executável removido"

# Recompila tudo do zero
re: fclean all

# Declara que estas regras não são arquivos
.PHONY: all clean fclean re

# ============================================================================ #
#                              DICAS DE USO                                    #
# ============================================================================ #
#
# make          → Compila o programa
# make clean    → Remove arquivos .o
# make fclean   → Remove .o e rush-02
# make re       → Recompila tudo do zero
#
# 🧪 TESTE RÁPIDO APÓS COMPILAR:
#    ./rush-02 42
#    ./rush-02 data/numbers.dict 42
#
# ============================================================================ #
