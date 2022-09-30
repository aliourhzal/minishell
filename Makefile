NAME	=	minishell

HEADER	=	minishell.h color.h 

SRC		=	minishell.c lexer.c tokenize.c parser.c executor.c variable_expansion.c \
			cmd_manager.c echo_func.c ft_lst_utils.c cd_func.c pwd_func.c unset_func.c export_func.c \
			wildcard_expansion.c ft_revncmp.c

FLAGS	=	-Wall -Wextra -Werror -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include  -lreadline

libftX	=	libftX/libftX.a

$(NAME)	:	$(HEADER) $(SRC) $(libftX)
	@cc $(FLAGS) $(SRC) $(libftX) -lreadline -o $(NAME)

	@echo " __  __ _       _     _          _ _ "
	@echo "|  \/  (_)_ __ (_)___| |__   ___| | |"
	@echo "| |\/| | | '_ \| / __| '_ \ / _ \ | |"
	@echo "| |  | | | | | | \__ \ | | |  __/ | |"
	@echo "|_|  |_|_|_| |_|_|___/_| |_|\___|_|_|"
	@echo "       As beautiful as a shell       "

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
