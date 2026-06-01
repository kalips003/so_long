# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 14:57:56 by agallon           #+#    #+#              #
#    Updated: 2024/06/11 18:22:05 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# COMPIL
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fPIE -I$(HEADER_FOLDER) -lm

# PATHs
HEADER_FOLDER = ../include
FILES_PATH = files
PRINTF_PATH = ft_printf
OBJ_FOLDER = obj

SRC_1 = $(wildcard files/*.c)
SRC_2 = $(wildcard ft_printf/*.c)

OBJ_1 = $(patsubst files/%.c, obj/%.o, $(SRC_1))
OBJ_2 = $(patsubst ft_printf/%.c, obj/%.o, $(SRC_2))

# RULES - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# $< = represents the first dependencies of a rule
# $@ = represents the target of a rule
# $^ = represents all dependencies
# $(word 2,$^) = represents the second dependencies of a rule
# $(lastword $^) = represents the last dependencies of a rule
# $? = Represents all the dependencies that are newer than the target
# $(@D) = Represents the directory part of the target file
# $(@F) = Represents the file part of the target file

# -I"header folder"
# -c: create object, no linking
# -p: create all middle folders
# -g: debugging option

obj/%.o: files/%.c
	@if [ ! -e $(OBJ_FOLDER) ]; then \
		mkdir -p $(OBJ_FOLDER); \
	fi
	@if ! $(CC) -c $(CFLAGS) $< -o $@; then \
		$(call print_cat_error, $(RED), $(RED1)); \
		exit 1; \
	fi

obj/%.o: ft_printf/%.c
	@if [ ! -e $(OBJ_FOLDER) ]; then \
		mkdir -p $(OBJ_FOLDER); \
	fi
	@if ! $(CC) -c $(CFLAGS) $< -o $@; then \
		$(call print_cat_error, $(RED), $(RED1)); \
		exit 1; \
	fi

all: $(NAME)

# ar: create archive (lib)
# rcs: replace, create if not, write index

$(NAME): $(OBJ_1) $(OBJ_2)
	@rm -f libft.a
	@ar rcs $(NAME) $(OBJ_1) $(OBJ_2)
	@if [ -f libft.a ]; then \
		$(call print_cat, $(CLEAR), $(BLUE1), $(GREEN1), $(GREEN1), $(call pad_word, 10, "LIBFT"), $(call pad_word, 12, "Compiled~")); \
	else \
		$(call print_cat, "", $(GOLD), $(RED), $(RED), $(call pad_word, 10, "Problem⠀while"), $(call pad_word, 12, "Compiling..")); \
	fi

clean:
		@rm -f $(NAME)
		@rm -rf $(OBJ_FOLDER)
		@rm -f a.out
		$(call print_cat, $(CLEAR), $(BLUE1), $(GREEN1), $(GOLD), $(call pad_word, 10, "LIBFT⠀..."), $(call pad_word, 14, "Cleaned⠀!")); \

clean_silent:
		@rm -f $(NAME)
		@rm -rf $(OBJ_FOLDER)
		@rm -f a.out

re: clean_silent all

.PHONY: all clean fclean re
#---------------------------------------------------------------------

# U+2800 to U+28FF Braile
# <Esc>[38;5;ColorNumberm

CLEAR = \033[2J\033[H
RESET = \033[0m
BLINK = \033[5m

# COLOR_2R_1G_3B
PURPLE = \033[38;5;97m
# COLOR_4R_3G_0B
GOLD = \033[38;5;178m
# COLOR_0R_4G_0B
GREEN1 = \033[38;5;40m
# COLOR_0R_4G_5B
BLUE1 = \033[38;5;45m
# COLOR_5R_0G_0B
RED1 = \033[38;5;196m

COLOR1 = \033[38;5;19m
COLOR2 = \033[38;5;29m
COLOR3 = \033[38;5;39m

test_color:
	$(call print_cat, $(CLEAR), $(COLOR1), $(COLOR2), $(COLOR3), $(call pad_word, 10, "color..."), $(call pad_word, 12, "COLOR!"));

pad_word = $(BLINK)$(shell printf "%$(1)s" "$(2)")$(RESET)
# print_cat (resest?)(color_cat)(color_eyes)(color_text)($(padded_txt_top))($(padded_txt_bot))
define print_cat
    echo "$(1)$(2)\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠒⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠘⡄⠀⠀⠀⠀⠀⠀⣀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠁⠉⠉⠉⠒⠊⠉⠀⡇⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜$(3)$(BLINK)⣀⡀$(RESET)$(2)⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⢴⠁$(3)$(BLINK)⠛⠁$(RESET)$(2)$(3)$(BLINK)⢀⣄$(RESET)$(2)⠀⠀⠀⢸⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠺⡀⠀⠀⢶⠤$(3)$(BLINK)⠈⠋$(RESET)$(2)⠀⠀⠀⡘⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⡀⠀⠀⠀⠠⣉⠑⠂⠀⢠⠃⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠊⠀⠀⠀⠀⠀⠀⠁⠀⠀⠈⢆⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⠒⠒⠃⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀\n\
	\t\t\t\t\t\t\t	⠀⠔⠑⠄⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠸⡀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⡇$(4)$(5)$(2)⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠀⠱⡀⠀⠳⡀⠀⠀⠀⠀⠀⠀⢃$(4)$(6)$(2)⠀⠀⡸⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠑⢄⠀⠈⠒⢄⡀⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠑⠦⣀⠀⠈⠉⠐⠒⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⢢⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠉⠐⠒⠠⠤⠤⠤⠤⠔⠂⠠⠤⠤⠤⠄⠐⠒⠂⠉⠉⠉⠉⠉⠁\n$(RESET)"
endef

define print_cat_error
	echo "$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ somshin wen wong ~$(1)\n\
	\t\t⠀|、˜\\\\\n\
	\t\t⠀じしˍ)ノ\n$(RESET)"
endef

BLACK = \033[38;5;0m
RED = \033[38;5;1m
GREEN = \033[38;5;2m
YELLOW = \033[38;5;3m
BLUE = \033[38;5;4m
MAGENTA = \033[38;5;5m
CYAN = \033[38;5;6m
GRAY = \033[38;5;7m

BLACK_L = \033[38;5;8m
RED_L = \033[38;5;9m
GREEN_L = \033[38;5;10m
YELLOW_L = \033[38;5;11m
BLUE_L = \033[38;5;12m
MAGENTA_L = \033[38;5;13m
CYAN_L = \033[38;5;14m
GRAY_L = \033[38;5;15m
