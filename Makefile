NAME = so_long
NAME_BONUS = so_long_bonus

CC = cc
FLAGS = -Wall -Werror -g -fPIE -I$(HEADER_FOLDER)
# FLAGS = -Wextra -Wall -Werror -g -fPIE -I$(HEADER_FOLDER)

all: $(NAME)

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        TESTING                    	         │
# ╰──────────────────────────────────────────────────────────────────────╯

# 	big map, 4 pika 4 collec
MAPG = good_map.ber
# 	big map, 3 pika
MAP1 = map1.ber
# 	medium square, no pika
MAP2 = map2.ber
# 	medium square, lots of pika
MAP3 = map3.ber
# 	small square, 1 pika
MAP4 = map_simplest.ber
# 	only balls
MAP5 = map5.ber

aaa:
	git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux
	
# BIG MAP WITH PIKA, BONUS + CONTROLS
a: libft mlx $(NAME_BONUS) include/so_long_bonus.h
	@$(call random_shmol_cat, "\'tis good map", 'hav fun ね? (make m for testeur mandatory)', $(CLS), );
	@echo -e "\tuse -WASD- or →↓←↑ to move around"
	@echo -e "\tuse -SPACE- to throw ball"
	@echo -e "\tpress -CTRL-l- (while stationnary) to toogle run"
	@echo -e "\tpress -E- to print memory"
	@echo -e "\n\t$(BLINK)~ Press Enter to start, and good luck... ~$(RESET)"
	@read -p "" key
	./$(word 3, $^) map/$(MAPG)

v: libft mlx $(NAME_BONUS)
	@$(call random_shmol_cat, "vlgrininnng ... $(NAME_BONUS)!", "$@: $(MAP1)", $(CLS), );
	-$(VALGRIND) ./$(word 3, $^) map/$(MAP4)
	@echo $(RESET);

# ---------------------------------------------------------------------- >
BAD_MAPS = map_bad_not_rect1.ber map_bad_not_rect2.ber map_no_collec.ber map_no_player.ber \
			map_no_exit.ber map_many_exit.ber \
			map_many_player.ber map_bad_wall.ber \
			map_bad_enclosed_e.ber map_bad_enclosed_c.ber \
			map_bad_tile.ber

# map=$$($(eval echo $$arg));
m: libft mlx $(NAME)
	@for map in $(BAD_MAPS); do \
	$(call random_shmol_cat, teshting lots of bad miaps:, $$map shouldt run..., $(CLS), ); \
	$(VALGRIND) ./$(word 3, $^) map/map_bad/$$map; \
	echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"; \
	read -p "" key; \
	done
#
	@$(call shmol_cat_color, $(COLOR_5R_0G_5B), $(COLOR_5R_2G_3B), teshing with bad map name!, map_multiplayer.be, $(CLS), );
	-$(VALGRIND) ./$(word 3, $^) map/map_multiplayer.be
	@echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"
	@read -p "" key;
	@$(call shmol_cat_color, $(COLOR_5R_0G_5B), $(COLOR_5R_2G_3B), teshing with bad map name!, mapzzzzz.ber, $(CLS), );
	-$(VALGRIND) ./$(word 3, $^) map/mapzzzzz.ber
	@echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"
	@read -p "" key
#
	@$(call random_shmol_cat, teshing too much args, "$(MAP1) abc", $(CLS), );
	-$(VALGRIND) ./$(word 3, $^) map/$(MAP1) map/$(MAP2)
	@echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"
	@read -p "" key
#
	@$(call shmol_cat_color, $(COLOR_5R_0G_5B), $(COLOR_5R_2G_3B), teshing with empty file, map_blank.ber, $(CLS), );
	@echo "$(RED)"
	touch ./map/map_blank.ber
	@echo "$(COLOR_5R_0G_5B)"
	-$(VALGRIND) ./$(word 3, $^) map/map_blank.ber
	@echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"
	@read -p "" key
#
	@$(call shmol_cat_color, $(COLOR_5R_4G_0B), $(COLOR_5R_2G_3B), teshing with a sprite file renamed!!!, , $(CLS), );
	@echo "$(RED)"
	mv ./img/player/player_0.xpm ./img/player/player_007.xpm
	@echo "$(COLOR_5R_4G_0B)"
	-$(VALGRIND) ./$(word 3, $^) map/$(MAP2)
	@echo "$(RED)"
	mv ./img/player/player_007.xpm ./img/player/player_0.xpm
	@echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"
	@read -p "" key
#
	@$(call random_shmol_cat, "\'tis good map Mandatory", "try n break it.. にゃ?", $(CLS), );
	@echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"
	@read -p "" key
	-$(VALGRIND) ./$(word 3, $^) map/$(MAP2)

m2: libft mlx $(NAME)
	@$(call random_shmol_cat, "\'tis good map Mandatory", "try n break it.. にゃ?", $(CLS), );
	@echo -e "\t$(BLINK)~ Press Enter to continue...$(RESET)"
	@read -p "" key
	@(ulimit -s 14; ./$(word 3, $^) map/$(MAP2))
	ulimit -s 8192


# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        SOURCES                    	         │
# ╰──────────────────────────────────────────────────────────────────────╯

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, src/obj/%.o, $(SRC))

SRC_FOLDER = src
OBJ_FOLDER = src/obj
HEADER_FOLDER = include

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        Libft                      	         │
# ╰──────────────────────────────────────────────────────────────────────╯

libft:
	@make -sC lib all;

libclean:
	@make -sC lib clean

relib:
	@make -sC lib re

libtest:
	@make -sC lib test_color

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       MLX		                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

mlx:
	@make -sC ./mlx_linux/

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       PROJECT                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

$(NAME): mlx libft $(OBJ) main.c
	@clear
	@if ! $(CC) $(FLAGS) $(OBJ) main.c lib/libft.a ./mlx_linux/libmlx.a $(FLAGS_MLX) -lm -o $(NAME); then \
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "ERROR"), $(call pad_word, 12, "COMPILING..")); \
		exit 1; \
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(GREEN1), $(call pad_word, 10, $(NAME)), $(call pad_word, 12, "Compiled~"));


src/obj/%.o: src/%.c
	@if [ ! -e $(OBJ_FOLDER) ]; then\
		mkdir -p $(OBJ_FOLDER);\
	fi
	@if ! $(CC) -c $(FLAGS) $< -o $@; then \
		$(call shmol_cat_error, $(RED), $(RED_L)); \
		exit 1; \
	fi

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       BONUS	                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

FLAGS_MLX = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lz
SRC_B = $(wildcard src_bonus/*.c)
OBJ_B = $(patsubst src_bonus/%.c, src_bonus/obj/%.o, $(SRC_B))

OBJ_FOLDER_B = src_bonus/obj

$(NAME_BONUS): bonus

bonus: mlx libft $(OBJ_B) main_bonus.c include/so_long.h
	@clear
	@if ! $(CC) $(FLAGS) $(OBJ_B) main_bonus.c lib/libft.a ./mlx_linux/libmlx.a $(FLAGS_MLX) -lm -o $(NAME_BONUS); then \
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "ERROR"), $(call pad_word, 12, "COMPILING..")); \
		exit 1; \
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(COLOR_4R_1G_5B), $(call pad_word, 10, $(NAME_BONUS)), $(call pad_word, 12, "Compiled~"));

src_bonus/obj/%.o: src_bonus/%.c include/so_long_bonus.h
	@clear
	@if [ ! -e $(OBJ_FOLDER_B) ]; then\
		mkdir -p $(OBJ_FOLDER_B);\
	fi
	@if ! $(CC) -c $(FLAGS) -Imlx_linux -O3 -c $< -o $@; then \
		$(call shmol_cat_error, $(RED), $(RED_L)); \
		exit 1; \
	fi

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       OTHERS	                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

test:	libft
	@rm -f ./lib/a.out
	-@cc ./lib/test.c ./lib/libft.a -o ./lib/a.out -lm
	@if [ ! -e ./lib/a.out ]; then\
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..")); \
		exit 3; \
	fi
	@$(call random_cat, $(call pad_word, 12, "Making"), $(call pad_word, 14, "Science"), $(CLS), $(RESET));
	@lib/a.out

test2:	mlx libft $(OBJ_B) include/so_long.h
	@rm -f ./lib/a.out
	@cc ./lib/test.c $(OBJ_B) -I$(HEADER_FOLDER) lib/libft.a ./mlx_linux/libmlx.a -lX11 -lXext -lm -o ./lib/a.out
	@$(call random_cat, $(call pad_word, 12, "TESTING"), $(call pad_word, 14, "SCIENCE"), $(CLS), $(RESET));
	-@$(VALGRIND) lib/a.out map/map4.ber

vtest:	libft
	@cc -g3 ./lib/test.c ./lib/libft.a -o ./lib/a.out -lm
	$(call print_cat, "", $(RED), $(GOLD), $(BLUE1), $(call pad_word, 10, "TESTING"), $(call pad_word, 12, "SCIENCE.."));
	@$(VALGRIND) lib/a.out

clean:
	@rm -rf $(OBJ_FOLDER)
	$(call print_cat, $(CLEAR), $(COLOR_2R_2G_5B), $(COLOR_3R_2G_0B), $(COLOR_4R_5G_0B), $(call pad_word, 10, "Objects"), $(call pad_word, 12, "Exterminated"));

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -sC lib clean_silent;
	$(call print_cat, $(CLEAR), $(COLOR_1R_2G_0B), $(COLOR_3R_0G_0B), $(COLOR_2R_1G_0B), $(call pad_word, 10, "All⠀clean"), $(call pad_word, 12, "Miaster"));

re: fclean all bonus

re_bonus: fclean

.PHONY: all clean fclean re bonus

.SILENT: $(NAME) bonus

# - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - -  - VALGRIND
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes
# VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes
#
# lldb: clean all
# 	@lldb ./$(NAME) $(ARGS)
#
# ↑さ↓ぎょう  を  ↓ほ↑ぞん
# 																	GITHUB
git: fclean
	@$(call random_shmol_cat_blink, 作業を保存してるかな.., いいね、いいねえー , $(CLS), );
	@current_date=$$(date); \
	git add .; \
	git commit -m "$$current_date"; \
	git push

NORM_FILE = src_bonus/

norm: fclean
	@$(call random_shmol_cat_blink, 掃除してるかな..、いいね、いいねえー, giv file to norm, $(CLS), );
	-@read -p 'file...:' path; \
	if [ -z "$$path" ]; then \
		watch norminette $(NORM_FILE); \
	else \
		watch norminette $$path; \
	fi

#
# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       PRINT                     	         │
# ╰──────────────────────────────────────────────────────────────────────╯

# COLOR_2R_1G_3B
PURPLE = \033[38;5;97m
# COLOR_4R_3G_0B
GOLD = \033[38;5;178m
# COLOR_0R_4G_0B
GREEN1 = \033[38;5;40m
# COLOR_0R_4G_5B
BLUE1 = \033[38;5;45m

# $(COLOR_1R_0G_5B), $(COLOR_5R_1G_0B), $(COLOR_0R_2G_5B)
# $(RED), $(GOLD), $(BLUE1)

test_color666:
	@$(call random_cat, $(call pad_word, 12, The⠀Cake), $(call pad_word, 14, Is⠀A⠀Lie⠀...), $(CLS), $(RESET));
	@$(call random_cat, $(call pad_word, 13, The⠀Cake), $(call pad_word, 15, Is⠀A⠀Lie⠀...), , $(RESET));


# $(call pad_word, 12, The⠀Cake)
pad_word = $(BLINK)$(shell printf "%$(1)s" "$(2)")$(RESET)
# improve with: STRING1=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1));

# --------------------------------------------------------------------------------- >
# @$(call print_cat, $(CLEAR), $(body), $(eye), $(txt), $(call pad_word, 12, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..."));
# print_cat (resest?)(color_cat)(color_eyes)(color_text)($(padded_txt_top))($(padded_txt_bot))
define print_cat
    echo -e "$(1)$(2)\
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

# --------------------------------------------------------------------------------- >
# @$(call random_cat, $(call pad_word, 12, txt1), $(call pad_word, 12, txt2), $(CLS), $(RESET));
# print_cat (resest?)(color_cat)(color_eyes)(color_text)($(padded_txt_top))($(padded_txt_bot))
define random_cat
	COLOR=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR3=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
    echo -e "$(3)$${COLOR}\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠒⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠘⡄⠀⠀⠀⠀⠀⠀⣀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠁⠉⠉⠉⠒⠊⠉⠀⡇⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀$${COLOR2}$(BLINK)⣀⡀$(RESET)$${COLOR}⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⢴⠁⠀$${COLOR2}$(BLINK)⠛⠁$(RESET)$${COLOR}$${COLOR2}$(BLINK)⠀⠀⢀⣄$(RESET)$${COLOR}⠀⠀⠀⠀⢸⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠺⡀⠀⠀⢶⠤$${COLOR2}$(BLINK)⠀⠈⠋$(RESET)$${COLOR}⠀⠀⠀⠀⡘⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⡀⠀⠀⠀⠠⣉⠑⠂⠀⢠⠃⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠊⠀⠀⠀⠀⠀⠀⠁⠀⠀⠈⢆⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⠒⠒⠃⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀\n\
	\t\t\t\t\t\t\t	⠀⠔⠑⠄⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠸⡀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⡇$${COLOR3}$(1)$${COLOR}⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠀⠱⡀⠀⠳⡀⠀⠀⠀⠀⠀⠀⢃$${COLOR3}$(2)$${COLOR}⠀⠀⡸⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠑⢄⠀⠈⠒⢄⡀⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠑⠦⣀⠀⠈⠉⠐⠒⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⢢⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠉⠐⠒⠠⠤⠤⠤⠤⠔⠂⠠⠤⠤⠤⠄⠐⠒⠂⠉⠉⠉⠉⠉⠁\n$(4)"
endef

# --------------------------------------------------------------------------------- >
# @$(call shmol_cat_color, $(color_cat), $(color_txt), text1, txt2, $(CLS), $(RESET));
define shmol_cat_color
	echo -e "$(5)$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ $(3) ~$(1)\n\
	\t\t⠀|、˜\\\\\t\t$(2)$(4)$(1)\n\
	\t\t⠀じしˍ)ノ\n$(6)"
endef
# --------------------------------------------------------------------------------- >
# @$(call random_shmol_cat, text 1, text 2, $(CLS), $(RESET));
# $(1)= $(CLEAR); $(2)= text1; $(3)= text2; $(4)= $(RESET)
define random_shmol_cat
	COLOR=$$(printf "\033[38;5;%dm" $$(shuf -i 1-255 -n 1)); \
	COLOR2=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo -e "$(3)$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef

# // <!> - - - - - - - - - - - </!>
# --------------------------------------------------------------------------------- >
rscs:
	@$(call random_shmol_cat_surligne, text 1, text 2, $(CLS), $(RESET));

define random_shmol_cat_surligne
	COLOR=$$(printf "\033[0m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\033[48;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo -e "$(3)$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef

rscb:
	@$(call random_shmol_cat_blink, text 1, text 2, $(CLS), $(RESET));

define random_shmol_cat_blink
	COLOR=$$(printf "\033[0m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\e[5m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo -e "$(3)\n$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef
# // <!> - - - - - - - - - - - </!>
# --------------------------------------------------------------------------------- >
# @$(call shmol_cat_error, $(RED), $(RED_L));
# $(1) = $(color_cat), $(2) = $(color_text)	NO CLS
define shmol_cat_error
	echo -e "$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ somshin wen wong ~$(1)\n\
	\t\t⠀|、˜\\\\\n\
	\t\t⠀じしˍ)ノ\n$(RESET)"
endef

# 					Define all 256 colors
CLEAR = \033[2J\033[H
CLS = \033[2J\033[H
RESET = \033[0m
BLINK = \033[5m
# U+2800 to U+28FF Braile
# <Esc>[38;5;ColorNumberm
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
WHITE = \033[38;5;15m

COLOR_0R_0G_0B = \033[38;5;16m
COLOR_0R_0G_1B = \033[38;5;17m
COLOR_0R_0G_2B = \033[38;5;18m
COLOR_0R_0G_3B = \033[38;5;19m
COLOR_0R_0G_4B = \033[38;5;20m
COLOR_0R_0G_5B = \033[38;5;21m
COLOR_0R_1G_0B = \033[38;5;22m
COLOR_0R_1G_1B = \033[38;5;23m
COLOR_0R_1G_2B = \033[38;5;24m
COLOR_0R_1G_3B = \033[38;5;25m
COLOR_0R_1G_4B = \033[38;5;26m
COLOR_0R_1G_5B = \033[38;5;27m
COLOR_0R_2G_0B = \033[38;5;28m
COLOR_0R_2G_1B = \033[38;5;29m
COLOR_0R_2G_2B = \033[38;5;30m
COLOR_0R_2G_3B = \033[38;5;31m
COLOR_0R_2G_4B = \033[38;5;32m
COLOR_0R_2G_5B = \033[38;5;33m
COLOR_0R_3G_0B = \033[38;5;34m
COLOR_0R_3G_1B = \033[38;5;35m
COLOR_0R_3G_2B = \033[38;5;36m
COLOR_0R_3G_3B = \033[38;5;37m
COLOR_0R_3G_4B = \033[38;5;38m
COLOR_0R_3G_5B = \033[38;5;39m
COLOR_0R_4G_0B = \033[38;5;40m
COLOR_0R_4G_1B = \033[38;5;41m
COLOR_0R_4G_2B = \033[38;5;42m
COLOR_0R_4G_3B = \033[38;5;43m
COLOR_0R_4G_4B = \033[38;5;44m
COLOR_0R_4G_5B = \033[38;5;45m
COLOR_0R_5G_0B = \033[38;5;46m
COLOR_0R_5G_1B = \033[38;5;47m
COLOR_0R_5G_2B = \033[38;5;48m
COLOR_0R_5G_3B = \033[38;5;49m
COLOR_0R_5G_4B = \033[38;5;50m
COLOR_0R_5G_5B = \033[38;5;51m
COLOR_1R_0G_0B = \033[38;5;52m
COLOR_1R_0G_1B = \033[38;5;53m
COLOR_1R_0G_2B = \033[38;5;54m
COLOR_1R_0G_3B = \033[38;5;55m
COLOR_1R_0G_4B = \033[38;5;56m
COLOR_1R_0G_5B = \033[38;5;57m
COLOR_1R_1G_0B = \033[38;5;58m
COLOR_1R_1G_1B = \033[38;5;59m
COLOR_1R_1G_2B = \033[38;5;60m
COLOR_1R_1G_3B = \033[38;5;61m
COLOR_1R_1G_4B = \033[38;5;62m
COLOR_1R_1G_5B = \033[38;5;63m
COLOR_1R_2G_0B = \033[38;5;64m
COLOR_1R_2G_1B = \033[38;5;65m
COLOR_1R_2G_2B = \033[38;5;66m
COLOR_1R_2G_3B = \033[38;5;67m
COLOR_1R_2G_4B = \033[38;5;68m
COLOR_1R_2G_5B = \033[38;5;69m
COLOR_1R_3G_0B = \033[38;5;70m
COLOR_1R_3G_1B = \033[38;5;71m
COLOR_1R_3G_2B = \033[38;5;72m
COLOR_1R_3G_3B = \033[38;5;73m
COLOR_1R_3G_4B = \033[38;5;74m
COLOR_1R_3G_5B = \033[38;5;75m
COLOR_1R_4G_0B = \033[38;5;76m
COLOR_1R_4G_1B = \033[38;5;77m
COLOR_1R_4G_2B = \033[38;5;78m
COLOR_1R_4G_3B = \033[38;5;79m
COLOR_1R_4G_4B = \033[38;5;80m
COLOR_1R_4G_5B = \033[38;5;81m
COLOR_1R_5G_0B = \033[38;5;82m
COLOR_1R_5G_1B = \033[38;5;83m
COLOR_1R_5G_2B = \033[38;5;84m
COLOR_1R_5G_3B = \033[38;5;85m
COLOR_1R_5G_4B = \033[38;5;86m
COLOR_1R_5G_5B = \033[38;5;87m
COLOR_2R_0G_0B = \033[38;5;88m
COLOR_2R_0G_1B = \033[38;5;89m
COLOR_2R_0G_2B = \033[38;5;90m
COLOR_2R_0G_3B = \033[38;5;91m
COLOR_2R_0G_4B = \033[38;5;92m
COLOR_2R_0G_5B = \033[38;5;93m
COLOR_2R_1G_0B = \033[38;5;94m
COLOR_2R_1G_1B = \033[38;5;95m
COLOR_2R_1G_2B = \033[38;5;96m
COLOR_2R_1G_3B = \033[38;5;97m
COLOR_2R_1G_4B = \033[38;5;98m
COLOR_2R_1G_5B = \033[38;5;99m
COLOR_2R_2G_0B = \033[38;5;100m
COLOR_2R_2G_1B = \033[38;5;101m
COLOR_2R_2G_2B = \033[38;5;102m
COLOR_2R_2G_3B = \033[38;5;103m
COLOR_2R_2G_4B = \033[38;5;104m
COLOR_2R_2G_5B = \033[38;5;105m
COLOR_2R_3G_0B = \033[38;5;106m
COLOR_2R_3G_1B = \033[38;5;107m
COLOR_2R_3G_2B = \033[38;5;108m
COLOR_2R_3G_3B = \033[38;5;109m
COLOR_2R_3G_4B = \033[38;5;110m
COLOR_2R_3G_5B = \033[38;5;111m
COLOR_2R_4G_0B = \033[38;5;112m
COLOR_2R_4G_1B = \033[38;5;113m
COLOR_2R_4G_2B = \033[38;5;114m
COLOR_2R_4G_3B = \033[38;5;115m
COLOR_2R_4G_4B = \033[38;5;116m
COLOR_2R_4G_5B = \033[38;5;117m
COLOR_2R_5G_0B = \033[38;5;118m
COLOR_2R_5G_1B = \033[38;5;119m
COLOR_2R_5G_2B = \033[38;5;120m
COLOR_2R_5G_3B = \033[38;5;121m
COLOR_2R_5G_4B = \033[38;5;122m
COLOR_2R_5G_5B = \033[38;5;123m
COLOR_3R_0G_0B = \033[38;5;124m
COLOR_3R_0G_1B = \033[38;5;125m
COLOR_3R_0G_2B = \033[38;5;126m
COLOR_3R_0G_3B = \033[38;5;127m
COLOR_3R_0G_4B = \033[38;5;128m
COLOR_3R_0G_5B = \033[38;5;129m
COLOR_3R_1G_0B = \033[38;5;130m
COLOR_3R_1G_1B = \033[38;5;131m
COLOR_3R_1G_2B = \033[38;5;132m
COLOR_3R_1G_3B = \033[38;5;133m
COLOR_3R_1G_4B = \033[38;5;134m
COLOR_3R_1G_5B = \033[38;5;135m
COLOR_3R_2G_0B = \033[38;5;136m
COLOR_3R_2G_1B = \033[38;5;137m
COLOR_3R_2G_2B = \033[38;5;138m
COLOR_3R_2G_3B = \033[38;5;139m
COLOR_3R_2G_4B = \033[38;5;140m
COLOR_3R_2G_5B = \033[38;5;141m
COLOR_3R_3G_0B = \033[38;5;142m
COLOR_3R_3G_1B = \033[38;5;143m
COLOR_3R_3G_2B = \033[38;5;144m
COLOR_3R_3G_3B = \033[38;5;145m
COLOR_3R_3G_4B = \033[38;5;146m
COLOR_3R_3G_5B = \033[38;5;147m
COLOR_3R_4G_0B = \033[38;5;148m
COLOR_3R_4G_1B = \033[38;5;149m
COLOR_3R_4G_2B = \033[38;5;150m
COLOR_3R_4G_3B = \033[38;5;151m
COLOR_3R_4G_4B = \033[38;5;152m
COLOR_3R_4G_5B = \033[38;5;153m
COLOR_3R_5G_0B = \033[38;5;154m
COLOR_3R_5G_1B = \033[38;5;155m
COLOR_3R_5G_2B = \033[38;5;156m
COLOR_3R_5G_3B = \033[38;5;157m
COLOR_3R_5G_4B = \033[38;5;158m
COLOR_3R_5G_5B = \033[38;5;159m
COLOR_4R_0G_0B = \033[38;5;160m
COLOR_4R_0G_1B = \033[38;5;161m
COLOR_4R_0G_2B = \033[38;5;162m
COLOR_4R_0G_3B = \033[38;5;163m
COLOR_4R_0G_4B = \033[38;5;164m
COLOR_4R_0G_5B = \033[38;5;165m
COLOR_4R_1G_0B = \033[38;5;166m
COLOR_4R_1G_1B = \033[38;5;167m
COLOR_4R_1G_2B = \033[38;5;168m
COLOR_4R_1G_3B = \033[38;5;169m
COLOR_4R_1G_4B = \033[38;5;170m
COLOR_4R_1G_5B = \033[38;5;171m
COLOR_4R_2G_0B = \033[38;5;172m
COLOR_4R_2G_1B = \033[38;5;173m
COLOR_4R_2G_2B = \033[38;5;174m
COLOR_4R_2G_3B = \033[38;5;175m
COLOR_4R_2G_4B = \033[38;5;176m
COLOR_4R_2G_5B = \033[38;5;177m
COLOR_4R_3G_0B = \033[38;5;178m
COLOR_4R_3G_1B = \033[38;5;179m
COLOR_4R_3G_2B = \033[38;5;180m
COLOR_4R_3G_3B = \033[38;5;181m
COLOR_4R_3G_4B = \033[38;5;182m
COLOR_4R_3G_5B = \033[38;5;183m
COLOR_4R_4G_0B = \033[38;5;184m
COLOR_4R_4G_1B = \033[38;5;185m
COLOR_4R_4G_2B = \033[38;5;186m
COLOR_4R_4G_3B = \033[38;5;187m
COLOR_4R_4G_4B = \033[38;5;188m
COLOR_4R_4G_5B = \033[38;5;189m
COLOR_4R_5G_0B = \033[38;5;190m
COLOR_4R_5G_1B = \033[38;5;191m
COLOR_4R_5G_2B = \033[38;5;192m
COLOR_4R_5G_3B = \033[38;5;193m
COLOR_4R_5G_4B = \033[38;5;194m
COLOR_4R_5G_5B = \033[38;5;195m
COLOR_5R_0G_0B = \033[38;5;196m
COLOR_5R_0G_1B = \033[38;5;197m
COLOR_5R_0G_2B = \033[38;5;198m
COLOR_5R_0G_3B = \033[38;5;199m
COLOR_5R_0G_4B = \033[38;5;200m
COLOR_5R_0G_5B = \033[38;5;201m
COLOR_5R_1G_0B = \033[38;5;202m
COLOR_5R_1G_1B = \033[38;5;203m
COLOR_5R_1G_2B = \033[38;5;204m
COLOR_5R_1G_3B = \033[38;5;205m
COLOR_5R_1G_4B = \033[38;5;206m
COLOR_5R_1G_5B = \033[38;5;207m
COLOR_5R_2G_0B = \033[38;5;208m
COLOR_5R_2G_1B = \033[38;5;209m
COLOR_5R_2G_2B = \033[38;5;210m
COLOR_5R_2G_3B = \033[38;5;211m
COLOR_5R_2G_4B = \033[38;5;212m
COLOR_5R_2G_5B = \033[38;5;213m
COLOR_5R_3G_0B = \033[38;5;214m
COLOR_5R_3G_1B = \033[38;5;215m
COLOR_5R_3G_2B = \033[38;5;216m
COLOR_5R_3G_3B = \033[38;5;217m
COLOR_5R_3G_4B = \033[38;5;218m
COLOR_5R_3G_5B = \033[38;5;219m
COLOR_5R_4G_0B = \033[38;5;220m
COLOR_5R_4G_1B = \033[38;5;221m
COLOR_5R_4G_2B = \033[38;5;222m
COLOR_5R_4G_3B = \033[38;5;223m
COLOR_5R_4G_4B = \033[38;5;224m
COLOR_5R_4G_5B = \033[38;5;225m
COLOR_5R_5G_0B = \033[38;5;226m
COLOR_5R_5G_1B = \033[38;5;227m
COLOR_5R_5G_2B = \033[38;5;228m
COLOR_5R_5G_3B = \033[38;5;229m
COLOR_5R_5G_4B = \033[38;5;230m
COLOR_5R_5G_5B = \033[38;5;231m
