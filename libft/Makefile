NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC = ft_atoi.c ft_isprint.c ft_memset.c \
	ft_strlcpy.c ft_strrchr.c ft_bzero.c ft_calloc.c \
	ft_itoa.c ft_strlen.c ft_strtrim.c ft_isalnum.c \
	ft_memchr.c ft_strchr.c ft_substr.c ft_isalpha.c \
	ft_memcmp.c ft_strdup.c ft_striteri.c ft_tolower.c \
	ft_isascii.c ft_memcpy.c ft_strjoin.c ft_strncmp.c \
	ft_toupper.c ft_isdigit.c ft_memmove.c ft_strlcat.c \
	ft_strnstr.c ft_split.c ft_strmapi.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c\
	ft_print_format.c ft_putchar.c ft_putnbr.c \
	get_next_line.c get_next_line_utils.c ft_strcmp.c

BONUS = ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	  ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	  ft_lstdelone_bonus.c ft_lstclear_bonus.c \
	  ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar -r $(NAME) $(OBJ)

bonus: $(BOBJ)
	@ar -r $(NAME) $(BOBJ)
clean:
	$(RM) $(OBJ) $(BOBJ)


fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : clean re all fclean
