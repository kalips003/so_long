NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
FLAGS = -Wextra -Wall -Werror -g -fPIE
# FLAGS = -g -fPIE

all: $(NAME)

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        TESTING                    	         │
# ╰──────────────────────────────────────────────────────────────────────╯

ARGS = in "wc -c" "wc -c" "wc -c" "wc -c" outfile
ARGS2 = here_doc STOP "wc -l" "ls -la" "wc -l" "ls -la" outfile
ARGS3 = in "ls -la" "wc -l" outfile

BASH1 = < in wc -c | wc -c | wc -c | wc -c > outfile

a: $(NAME)
	@$(call print_cat_test, $(COLOR_5R_0G_5B), $(COLOR_5R_2G_3B), "にゃ~", "~ teshing $@!~");
	./$(NAME) $(ARGS)
	@echo "\toutfile:\n"
	@cat outfile

b: $(NAME_BONUS)
	@echo > outfile
	@$(call print_cat_random, # $(COLOR_5R_3G_1B), # $(COLOR_5R_2G_3B), # $(COLOR_0R_2G_3B), "~ teshing $@! ~");
	./$(NAME_BONUS) $(ARGS2)
	@echo "\toutfile:\n"
	@cat outfile

c: $(NAME) $(NAME_BONUS)
	@echo > outfile
	@$(call print_cat_test, $(COLOR_5R_0G_5B), $(COLOR_5R_2G_3B), "にゃ~", "~ teshing $@!~");
	$(BASH1)
	@echo "\toutfile:\n"
	@cat outfile

d: $(NAME) $(NAME_BONUS)
	@echo > outfile
	@$(call print_cat_test, $(COLOR_5R_0G_5B), $(COLOR_5R_2G_3B), "にゃ~", "~ teshing $@!~");
	./$(NAME) $(ARGS)
	@echo "\toutfile:\n"
	@cat outfile

maieul: $(NAME) $(NAME_BONUS)
	@$(call print_cat_test, $(COLOR_5R_3G_1B), $(COLOR_0R_2G_3B), "にゃ~", "~ teshing $@! ~");
	@if [ ! -e traces ]; then\
		mkdir -p traces;\
	fi
	@rm -f traces/trace*
	strace -e dup2,dup,openat,clone,read,write,access,close,execve,pipe,pipe2 -tt -ff -o traces/trace \
	./pipex in 'ls -la' 'wc -l' /dev/stdout
	strace-log-merge traces/trace | batcat -lstrace

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - VALGRIND -
v: $(NAME) $(NAME_BONUS)
	@echo > outfile
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes \
	./$(NAME_BONUS) $(ARGS2)
	@echo "\toutfile:\n"
	@cat outfile

# lldb: clean all
# 	@lldb ./$(NAME) $(ARGS)

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        SOURCES                    	         │
# ╰──────────────────────────────────────────────────────────────────────╯

SRC_FOLDER = src
OBJ_FOLDER = src/obj
HEADER_FOLDER = include

# $(patsubst pattern,replacement,text)
# $(addprefix prefix, list)
SRC = $(wildcard src/*.c)
SRC_B = $(wildcard src_bonus/*.c)
OBJ = $(patsubst src/%.c, src/obj/%.o, $(SRC))
OBJ_B = $(patsubst src_bonus/%.c, src/obj/%.o, $(SRC_B))

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        Libft                      	         │
# ╰──────────────────────────────────────────────────────────────────────╯

# -s: silent
# -C: change folder before make

libft:
	@make -sC lib all;

libclean:
	@make -sC lib clean

relib:
	@make -sC lib re

libtest:
	@make -sC lib test_color

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       PROJECT                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

$(NAME): libft main.c $(OBJ)
	@if ! $(CC) $(FLAGS) $(OBJ) main.c -I$(HEADER_FOLDER) lib/libft.a -o $(NAME); then \
		$(call print_cat, "", $(GOLD), $(RED), $(RED), $(call pad_word, 10, "Problem⠀while"), $(call pad_word, 12, "Compiling..")); \
		exit 1; \
	fi
	@if [ ! -e in ]; then\
		echo > in;\
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(GOLD), $(call pad_word, 10, $(NAME)), $(call pad_word, 12, "Compiled~")); \

src/obj/%.o: src/%.c
	@if [ ! -e $(OBJ_FOLDER) ]; then\
		mkdir -p $(OBJ_FOLDER);\
	fi
	@if ! $(CC) -c $(FLAGS) -I$(HEADER_FOLDER) $< -o $@; then \
		$(call print_cat_error, $(RED), $(RED_L)); \
		exit 1; \
	fi

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       BONUS	                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

$(NAME_BONUS): libft main_bonus.c $(OBJ)
	@if ! $(CC) $(FLAGS) $(OBJ) main_bonus.c -I$(HEADER_FOLDER) lib/libft.a -o $(NAME_BONUS); then \
		$(call print_cat, "", $(GOLD), $(RED), $(RED), $(call pad_word, 10, "Problem⠀while"), $(call pad_word, 12, "Compiling..")); \
		exit 1; \
	fi
	@$(call print_cat, $(CLEAR), $(COLOR_5R_1G_5B), $(COLOR_1R_2G_4B), $(COLOR_5R_1G_0B), $(call pad_word, 10, $(NAME_BONUS)), $(call pad_word, 14, "All⠀ready~"));

bonus: $(NAME_BONUS)

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       OTHERS	                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

test:	libft
	@$(CC) ./lib/test.c ./lib/libft.a -o ./lib/a.out
	@$(call print_cat, $(CLEAR), $(COLOR_1R_0G_5B), $(COLOR_5R_1G_0B), $(COLOR_0R_2G_5B), $(call pad_word, 10, "Making"), $(call pad_word, 12, "Science"));
	@lib/a.out

test2:	libft ./src/b_exec.c
	@$(CC) ./lib/test.c ./src/b_exec.c ./lib/libft.a -o ./lib/a.out
	@$(call print_cat, $(CLEAR), $(COLOR_1R_2G_5B), $(COLOR_5R_1G_1B), $(COLOR_3R_2G_5B), $(call pad_word, 10, "Making"), $(call pad_word, 12, "Science"));
	@lib/a.out "ls -la"

vtest:	libft
	@$(CC) -g3 ./lib/test.c ./lib/libft.a -o ./lib/a.out
	@$(call print_cat, $(CLEAR), $(RED), $(GOLD), $(BLUE1), $(call pad_word, 10, "TESTING"), $(call pad_word, 12, "SCIENCE"));
	@valgrind lib/a.out

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - CLEANUP -
clean:
	@rm -rf $(OBJ_FOLDER) outfile
	@$(call print_cat, $(CLEAR), $(COLOR_2R_2G_5B), $(COLOR_3R_2G_0B), $(COLOR_4R_5G_0B), $(call pad_word, 10, "Objects"), $(call pad_word, 12, "Exterminated"));

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS) in
	@make -sC lib clean_silent
	@rm -rf traces
	@$(call print_cat, $(CLEAR), $(COLOR_1R_2G_0B), $(COLOR_3R_0G_0B), $(COLOR_2R_1G_0B), $(call pad_word, 10, "All⠀clean"), $(call pad_word, 12, "Miaster"));

re: fclean all bonus

# .PHONY target is typically used to declare targets that are not actual files but rather are just actions to be performed by make, like clean or all.
.PHONY: all clean fclean re bonus

.SILENT: $(NAME) bonus

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       PRINT                     	         │
# ╰──────────────────────────────────────────────────────────────────────╯

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

test_color:
	$(call print_cat, $(CLEAR), $(RED), $(RED1), $(RED_L), $(call pad_word, 12, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..."));

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

# $(call print_cat_error, $(RED), $(RED_L));
define print_cat_error
	echo "$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ somshin wen wong ~$(1)\n\
	\t\t⠀|、˜\\\\\n\
	\t\t⠀じしˍ)ノ\n$(RESET)"
endef

# $(call print_cat_test, $(COLOR_5R_3G_1B), $(COLOR_0R_2G_3B), $@, "~ teshing $@! ~");
define print_cat_test
	echo "$(CLEAR) $(2)\
	\t$(3)$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)$(4)$(1)\n\
	\t\t⠀|、˜\\\\\n\
	\t\t⠀じしˍ)ノ\n$(RESET)"
endef

# $(call print_cat_random, # $(random_color), # $(random_color), # $(random_color), "~ teshing $@! ~");
define print_cat_random
	echo "$(CLEAR) $(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(3)$(4)$(1)\n\
	\t\t⠀|、˜\\\\\n\
	\t\t⠀じしˍ)ノ\n$(RESET)"
endef

# //////////////////////////////////////
# @echo "Random color escape sequence: $(call random_color_escape)"
# Define a function to generate a random color code
define random_colora
	\033[38;5;$(shell echo $$((RANDOM % 256)))m
endef

random_number := $(shell od -An -N1 -tu1 /dev/urandom)

define random_number_func
	$(random_number)
endef

random_number:
	@echo $(random_number)

# //////////////////////////////////////
# 					Define all 256 colors
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
