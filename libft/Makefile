# Variables

NAME		= libft.a
INCLUDE		= .
SRC_DIR		= ./
OBJ_DIR		= objects/
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
AR			= ar rcs

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

SRC_FILES	=	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii \
				ft_isdigit ft_isprint ft_memchr ft_memcmp ft_memcpy ft_memmove \
				ft_memset ft_strchr ft_strdup ft_strlcpy ft_strlen ft_strncmp \
				ft_strnstr ft_strtrim ft_tolower ft_toupper ft_substr ft_strjoin \
				ft_itoa ft_split ft_strmapi ft_strlcat ft_striteri ft_putendl_fd \
				ft_putnbr_fd ft_putstr_fd ft_putchar_fd ft_strrchr \
				get_next_line get_next_line_utils

SRC_B_FILES	=	ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
				ft_lstdelone ft_lstclear ft_lstiter ft_lstmap


SRC			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
SRC_B		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_B_FILES)))
OBJ			= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJ_B		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_B_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

bonus:		$(OBJ) $(OBJ_B)
			@$(AR) $(NAME) $(OBJ) $(OBJ_B)
			@echo "$(GREEN)libft compiled with bonus!$(DEF_COLOR)"

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@echo "$(GREEN)libft compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "\033[1A                                                     "
			@echo -n "\033[1A"
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -r $(OBJ_DIR)
			@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm