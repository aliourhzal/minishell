NAME	=	minishell

HEADER	=	minishell.h color.h 

SRC		=	minishell.c lexer.c tokenize.c parser.c executor.c variable_expansion.c \
			cmd_manager.c echo_func.c ft_lst_utils.c cd_func.c pwd_func.c unset_func.c export_func.c \
			wildcard_expansion.c ft_revncmp.c error_check.c general_utils.c tokenize_utils.c wildcard_utils.c \
			redirect_utils.c cmd_path_utils.c redirect_hundler.c variable_utils.c
			

FLAGS	=	-Wall -Wextra -Werror -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include  -lreadline

libftX	=	libftX/libftX.a

$(NAME)	:	$(HEADER) $(SRC) $(libftX)
	@cc $(FLAGS) $(SRC) $(libftX) -lreadline -o $(NAME)

	@echo "                                                     "
	@echo "█████████████████████████████████████████████████████"
	@echo "█▄─▀█▀─▄█▄─▄█▄─▀█▄─▄█▄─▄█─▄▄▄▄█─█─█▄─▄▄─█▄─▄███▄─▄███"
	@echo "██─█▄█─███─███─█▄▀─███─██▄▄▄▄─█─▄─██─▄█▀██─██▀██─██▀█"
	@echo "▀▄▄▄▀▄▄▄▀▄▄▄▀▄▄▄▀▀▄▄▀▄▄▄▀▄▄▄▄▄▀▄▀▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀"
	@echo "               as beautiful as a shell               "

$(libftX)	:	libftX
			@$(MAKE) -C libftX

all		:	$(NAME)

clean	:	
	@rm -f $(NAME)
	@$(MAKE) clean -C libftX

fclean	:	clean
	@$(MAKE) fclean -C libftX

re		:	fclean all

bonus	:	re
