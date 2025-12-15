NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Werror -Wextra
DEBUG_FLAGS = -g -DVERBOSE=1
ALLOC_FLAG =  -g -DDEBUG_ALLOC

LIBFT_DIR   = inc/libft
LIBFT       = $(LIBFT_DIR)/libft.a

INCLUDES    = -I inc -I $(LIBFT_DIR)

SRC_DIR     = src
OBJ_DIR     = obj

SRCS = \
	main.c \
	parser/parser.c \


# baue aus z.B. "executor/landing_file.c" -> "obj/executor/landing_file.o"
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ==========================
# Build rules
# ==========================

all: $(LIBFT) $(NAME)

# Debug-Build: CFLAGS erweitern und komplett neu bauen
verbose: CFLAGS += $(DEBUG_FLAGS)
verbose: re

alloc: CFLAGS += $(ALLOC_FLAGS)
alloc: re

# Objektdateien
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/cub3d.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Libft bauen
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

# ==========================
# Clean rules
# ==========================

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all debug clean fclean re
