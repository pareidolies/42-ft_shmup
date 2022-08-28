NAME := ft_shmup

CC := cc
FLAGS := -Wall -Wextra -Werror
LINK := -lncurses

SRCDIR := srcs
OBJDIR := objs

SRCS_ := main.c two_players.c scenery.c boss.c

SRCS := $(patsubst %,$(SRCDIR)/%,$(SRCS_))


OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS_))

INC := ft_shmup.h

LIBS :=

green = /bin/echo -e "\x1b[32m$1\x1b[0m"
red = /bin/echo -e "\x1b[31m$1\x1b[0m"


all : $(NAME)


$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@


$(NAME) : $(OBJ) $(LIBS) Makefile
	$(call green,"Compiling...")
	$(CC) -g  $(OBJ) -o $(NAME) $(LIBS) $(LINK)
	$(call green,"Done.")


clean:
	$(call red,"Cleaning...")
	rm -fd $(OBJ) $(OBJDIR)
	$(call red,"Done.")


fclean:
	$(call red,"Cleaning everything...")
	rm -fd $(OBJ) $(NAME) $(OBJDIR)
	$(call red,"Done.")


%.a: 
	make -C $(dir $@)


re:
	make fclean
	make all


.PHONY: clean fclean re all

.SILENT :
