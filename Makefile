
#=== VARIABLES ===
NAME = AquaSS
INC_DIR = includes/
SRCS_DIR = srcs/
SRCS =	main.c ft_init.c ft_render.c ft_graphics.c ft_errors.c
OBJ = $(SRCS:.c=.o)
OBJ_DIR = obj/
INCLUDE = 
LIBS = 

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -I $(INC_DIR) $(INCLUDE)

#=== SPECIAL ===
.PHONY: all, clean, mrproper, re, cls
.SUFFIXES:

#=== REGLES BINAIRES ===
all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJ))
	@echo "building app"
	@$(CC) $(CFLAGS) $(LIBS) $^ -o $@

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC_DIR)constantes.h $(INC_DIR)%.h
	@echo "building $@"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)main.o: $(SRCS_DIR)main.c $(INC_DIR)constantes.h
	@echo "building $@"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

#=== REGLES SPECIALES ===
cls:
	clear

clean:
	@echo "cleaning directory (*.obj)"
	@rm -f $(addprefix $(OBJ_DIR), $(OBJ))

mrproper: clean
	@echo "cleaning directory (app + *.obj)"
	@rm -f $(NAME)

re: cls mrproper all
	@echo "re"

