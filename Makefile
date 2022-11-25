# Variables

NAME		= fdf
INCLUDE		= includes
LIBFT		= libft
MINILIBX	= minilibx-linux
SRC_DIR		= sources/
OBJ_DIR		= objects/
CC			= cc
CFLAGS		= -Wall -Wextra
RM			= rm -f

# Colors

DEF_COLOR 	=	\033[0;39m
GRAY		=	\033[0;90m
RED 		=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW 		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Sources

SRC_FILES	=	fdf parser utils


SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

bonus:		all

$(NAME):	$(OBJ)
			@make -C $(LIBFT) bonus
			@make -C ${MINILIBX}
			@$(CC) $(OBJ) -L $(LIBFT) -L $(MINILIBX) -lX11 -lXext  -lmlx -lft -lm -o $@
			@echo "$(GREEN)Fdf compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "\033[1A                                                     "
			@echo -n "\033[1A"
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIBFT) -I $(MINILIBX) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make -C $(LIBFT) clean
			@echo "$(BLUE)Fdf object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a
			@echo "$(CYAN)Fdf executable files cleaned!$(DEF_COLOR)"
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for Fdf!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) $(LIBFT) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm