NAME = cub3D

# Variables generales
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -DCMAKE_OSX_ARCHITECTURES=arm64
RM = rm
RMFLAGS = -rf
MKDIR = mkdir -p
INCLUDE = -I ${INCLUDE_DIR} -I $(LIBMLX)/include
# Directorios

LIBFT_DIR = Libft/
LIBFT_BIN = Libft/bin/
LIBFT_NAME = $(LIBFT_BIN)libft.a
SRC_DIR = src/
OBJ_DIR = bin/obj/
BIN_DIR = bin/
INCLUDE_DIR = Include/
LIBMLX = ./MLX42

#Files
FILES = main\
		init/init\
		init/read_map\
		parser/parse\
		parser/valid_map\
		parser/validate_textures\
		parser/parse_color\
		parser/parse_textures\
		parser/normalize_map\
		error/error\
		error/frees\
		exec/exec\
		exec/render\
		exec/player\
		exec/hooks\
		exec/orientation\
		exec/draw\
		exec/background\

# FILES_ADD
LIBS = $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/lib -ldl -lglfw -pthread -lm

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# 1ª RULE
all: $(NAME)

# Compilar libft solo si no existe el .a
$(LIBFT_NAME):
	@echo "compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1

# Compilar mlx solo si no existe el .a
$(LIBMLX)/build/libmlx42.a:
	@echo "compiling mlx42..."
	@cmake $(LIBMLX) -B $(LIBMLX)/build --log-level=ERROR -DCMAKE_OSX_ARCHITECTURES=arm64 > /dev/null 2>&1
	@cmake --build $(LIBMLX)/build --target mlx42 -j4 > /dev/null 2>&1

# Comp bin
$(NAME): $(OBJ) $(LIBFT_NAME) $(LIBMLX)/build/libmlx42.a
	@$(MKDIR) $(BIN_DIR)
	@echo "linking $(NAME)..."
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBFT_NAME) -o $(NAME) $(LIBS)
	@echo "done ✓"

# Comp .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# clean OBJ
clean:
	@echo "cleaning objects..."
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1

# clean binary OBJ
fclean: clean
	@echo "cleaning binaries..."
	@$(RM) $(RMFLAGS) $(BIN_DIR) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null 2>&1
	@$(RM) $(RMFLAGS) $(LIBMLX)/build

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re
