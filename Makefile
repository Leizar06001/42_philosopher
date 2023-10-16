#COLORS
GREEN = \033[0;32m
RED = \e[1;31;43m
NOC = \033[0m

CC := gcc
CCFLAGS := -Werror -Wextra -Wall

SRCSDIR = srcs
SRCSFILES = main.c threads.c time_fnc.c init.c philo_life.c\
			ft_atoi.c philo_tests.c visuals.c mutexs.c\
			print_info.c
SRCS = $(addprefix $(SRCSDIR)/, $(SRCSFILES))

OBJSDIR := objs
OBJSFILES = $(SRCSFILES:%.c=%.o)
OBJS = $(addprefix $(OBJSDIR)/, $(OBJSFILES))

DEPS := ./include

NAME := philo

RM := rm -f

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)/philo.h | $(OBJSDIR)
	@echo "> Making exec"
	@$(CC) -pthread $^ -o $(NAME) $(CCFLAGS) -I $(DEPS)
	@echo "\e[1m>>  Done \e[0m"

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c | $(OBJSDIR)
	@echo "> Compiling" $@
	@$(CC) -c $< -o $@ $(CCFLAGS)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

clean:
	@echo "$(RED) > Removing objects..  $(NOC)"
	@$(RM) $(OBJS)

fclean:
	@echo "$(RED) > Removing objects and exec..  $(NOC)"
	@$(RM) $(OBJS) $(NAME)

re: fclean all
