#COLORS
GREEN = \033[0;32m
RED = \e[1;31;43m
NOC = \033[0m

CC := gcc
CCFLAGS := -Werror -Wextra -Wall

SRCSDIR = srcs
SRCSFILES = main_bonus.c threads_bonus.c time_fnc_bonus.c init_bonus.c\
			philo_life_bonus.c ft_atoi.c philo_tests_bonus.c visuals_bonus.c\
			print_info_bonus.c mutexs_bonus.c
SRCS = $(addprefix $(SRCSDIR)/, $(SRCSFILES))

OBJSDIR := objs
OBJSFILES = $(SRCSFILES:%.c=%.o)
OBJS = $(addprefix $(OBJSDIR)/, $(OBJSFILES))

DEPS := ./include

NAME := philo_bonus

RM := rm -f

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)/philo_bonus.h | $(OBJSDIR)
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
