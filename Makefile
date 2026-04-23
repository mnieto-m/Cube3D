NAME = cub3D

# Variables generales
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
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
LIBMLX	= ./MLX42

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
		error/frees
# FILES_ADD
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# 1ª RULE
all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Comp bin
$(NAME): $(OBJ) $(LIBFT_NAME)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBFT_NAME) -o $(NAME) $(LIBS)

# Comp .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
# Compilar la libft
$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

# clean OBJ
clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(RMFLAGS) $(LIBMLX)/build

# clean binary OBJ
fclean: clean
	$(RM) $(RMFLAGS) $(BIN_DIR) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(RMFLAGS) $(LIBMLX)/build

# Recompilar todo
re: fclean all 

.PHONY: all clean fclean libmlx