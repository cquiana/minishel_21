NAME = minishell

SRCS_DIR = srcs/
OBJ_DIR = obj/
INC_DIR = includes/

INCLUDES = -I$(INC_DIR)

CC = gcc
FLAGS = -g

LIBFT_DIR = ./libft
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft

FILES = main\
		minishell_pwd\
		minishell_echo\
		minishell_utils\
		minishell_utils2\
		minishell_utils3\
		minishell_error\
		minishell_export\
		minishell_unset\
		minishell_env\
		minishell_start\
		minishell_cd\
		minishell_exit\
		minishell_execve\
		parse_path\
		parser_input\
		parser_utils\
		parser_utils2\
		parser_utils_check\
		parser_create_lst\
		parser_quote_util\
		parser_prevalid\
		parser_prevalid2\
		get_line\
		free_cmd

SRCS_FILES = $(addsuffix .c, $(addprefix $(SRCS_DIR), $(FILES)))

OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))


all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	@make -C $(LIBFT_DIR)
	@$(CC) -o $(NAME) $(INCLUDES) $(OBJ_FILES) $(LIBFT_FLAGS)

$(OBJ_FILES): $(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_FILES)
	@make -C $(LIBFT_DIR) clean
	@echo "Project has been cleaned"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(NAME) and Libs has been removed"

norm:
	norminette ./$(SRCS_DIR)*
	norminette ./$(INC_DIR)*

re: fclean all
