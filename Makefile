# =========================
# Project
# =========================
NAME            = cub3D
CC              = cc
CFLAGS          = -Wall -Werror -Wextra -MMD -MP
DEBUG_FLAGS     = -g -DVERBOSE=1

# =========================
# Libs / Includes
# =========================
LIBFT_DIR       = inc/libft
LIBFT           = $(LIBFT_DIR)/libft.a
LIBS            = -L/usr/include -lmlx -lX11 -lXext -lm
INCLUDES        = -I inc -I $(LIBFT_DIR)

# =========================
# Folders
# =========================
SRC_DIR         = src
OBJ_DIR         = obj
OBJ_DIR_BONUS   = obj_bonus

# =========================
# Build-Mode
# =========================
MODE ?= mandatory

# =========================
# Sources (MANDATORY base)
# =========================
SRCS_MAND = \
	main.c \
	parser/parser.c \
	parser/verbose.c \
	parser/check_walls.c \
	parser/extract_map.c \
	parser/extract_rgb.c \
	parser/check_player.c \
	parser/extract_file.c \
	parser/print_errors.c \
	parser/validate_map.c \
	parser/cleanup_parser.c \
	parser/extract_texture.c \
	render/init.c \
	render/render.c \
	render/raycasting.c \
	render/minimap.c \
	render/texture_mapping.c \
	render/hooks.c \
	render/utils.c \

# =========================
# Bonus replacements/additions
# =========================
# Diese Dateien ersetzen die gleichnamigen Mandatory-Dateien:
SRCS_BONUS_ONLY = \
	parser/extract_map_bonus.c \
	parser/check_walls_bonus.c

# Mandatory-Dateien, die im Bonus-Modus NICHT kompiliert werden sollen:
SRCS_MAND_REPLACED = \
	parser/extract_map.c \
	parser/check_walls.c

# =========================
# Mode selection
# =========================
ifeq ($(MODE),bonus)
  OBJDIR = $(OBJ_DIR_BONUS)
  SRCS   = $(filter-out $(SRCS_MAND_REPLACED),$(SRCS_MAND)) $(SRCS_BONUS_ONLY)
else
  OBJDIR = $(OBJ_DIR)
  SRCS   = $(SRCS_MAND)
endif

# =========================
# Objects / Deps
# =========================
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

# =========================
# Rules
# =========================
all: $(LIBFT) $(NAME)

verbose: CFLAGS += $(DEBUG_FLAGS)
verbose: re

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c inc/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

# 42 bonus rule
bonus:
	$(MAKE) MODE=bonus all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all verbose bonus clean fclean re
