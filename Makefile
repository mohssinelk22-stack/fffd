# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

NAME        := philo
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror
THREAD      := -pthread

INCDIR      := includes
SRCDIR      := src
OBJDIR      := obj

SRC         := \
	$(SRCDIR)/main.c \
	$(SRCDIR)/init.c \
	$(SRCDIR)/start.c \
	$(SRCDIR)/monitor.c \
	$(SRCDIR)/actions.c \
	$(SRCDIR)/print.c \
	$(SRCDIR)/utils_time.c \
	$(SRCDIR)/utils_num.c \
	$(SRCDIR)/cleanup.c

OBJ         := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS        := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(THREAD) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
-include $(DEPS)
