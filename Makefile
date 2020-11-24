NAME = miniRt.a
FUNCTIONS = ./srcs/camera.c \
			./srcs/camera_lists.c \
			./srcs/equations.c \
			./srcs/color_func.c \
			./srcs/executers.c \
			./srcs/geters.c \
			./srcs/handlers.c \
			./srcs/main.c \
			./srcs/ray.c \
			./srcs/rot_trs.c \
			./srcs/save.c \
			./srcs/shadow_handlers.c \
			./srcs/vector.c\
			./parsing/checkers.c \
			./parsing/checkers2.c \
			./parsing/data_checker_handler.c \
			./parsing/data_checkers.c \
			./parsing/data_checkers2.c \
			./parsing/data_initializer.c \
			./parsing/data_initializer2.c \
			./parsing/data_insertion_handler.c \
			./parsing/debuggers.c \
			./parsing/error_printer.c \
			./parsing/ft_lstfuncs.c \
			./parsing/ft_putchar_fd.c \
			./parsing/ft_putnbr_fd.c \
			./parsing/ft_putstr_fd.c \
			./parsing/ft_split.c \
			./parsing/ft_strncmp.c \
			./parsing/ft_white_spaces.c \
			./parsing/get_next_line.c \
			./parsing/get_next_line_utils.c \
			./parsing/parser_functions.c

FUNCTIONS_O = $(FUNCTIONS:.c=.o)


HEADERS = ./includes/

CC = gcc -I ${HEADERS}

$(NAME): $(HEADERS) $(FUNCTIONS_O)
	ar rc $(NAME) ${FUNCTIONS_O}
	@gcc -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGl -framework AppKit miniRt.a -o miniRT
	@clear
all: $(NAME)


clean:
	@rm -rf ./parsing/*.o
	@rm -rf ./srcs/*.o

fclean: clean
	@rm -rf $(NAME)
	@rm miniRT

re: fclean all