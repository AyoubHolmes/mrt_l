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

FUNCTIONS_O = ./srcs/camera.o \
			./srcs/camera_lists.o \
			./srcs/equations.o \
			./srcs/color_func.o \
			./srcs/executers.o \
			./srcs/geters.o \
			./srcs/handlers.o \
			./srcs/main.o \
			./srcs/ray.o \
			./srcs/rot_trs.o \
			./srcs/save.o \
			./srcs/shadow_handlers.o \
			./srcs/vector.o\
			./parsing/checkers.o \
			./parsing/checkers2.o \
			./parsing/data_checker_handler.o \
			./parsing/data_checkers.o \
			./parsing/data_checkers2.o \
			./parsing/data_initializer.o \
			./parsing/data_initializer2.o \
			./parsing/data_insertion_handler.o \
			./parsing/debuggers.o \
			./parsing/error_printer.o \
			./parsing/ft_lstfuncs.o \
			./parsing/ft_putchar_fd.o \
			./parsing/ft_putnbr_fd.o \
			./parsing/ft_putstr_fd.o \
			./parsing/ft_split.o \
			./parsing/ft_strncmp.o \
			./parsing/ft_white_spaces.o \
			./parsing/get_next_line.o \
			./parsing/get_next_line_utils.o \
			./parsing/parser_functions.o


HEADERS = ./includes/

CC = gcc -I ${HEADERS}

all: $(NAME)

$(NAME): $(FUNCTIONS_O)
	ar rc $(NAME) ${FUNCTIONS_O}
	mv ./srcs/*.o objects
	mv ./parsing/*.o objects

clean:
	rm -rf ./objects/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all