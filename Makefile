SRCDIR := srcs
INCDIR := incs
OBJDIR := objs
DEPDIR := $(OBJDIR)/.deps

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(SRCS:%.c=%.o)))

NAME := test

CC := gcc
LDFLAGS := -L/Users/nnamor/.brew/opt/readline/lib
IFLAGS := -I/Users/nnamor/.brew/opt/readline/include -I $(INCDIR)
CFLAGS := -Wall -Wextra -Werror -g $(IFLAGS)
DEPFLAGS = -MT $@ -MMD -MF $(DEPDIR)/$*.tmpd
COMPILE.c = $(CC) $(CFLAGS) $(DEPFLAGS) -c -o
LINK.c = $(CC) $(CFLAGS) -lreadline $(LDFLAGS) -o
POSTCOMPILE = mv -f $(DEPDIR)/$*.tmpd $(DEPDIR)/$*.d && touch $@

MKDIR = mkdir -p $@
RM := rm -rf

#-------------------------------------------------------------------------------#

$(NAME): $(OBJS)
	$(LINK.c) $@ $^

all: $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $@ $<
	@$(POSTCOMPILE)

$(DEPDIR):
	@$(MKDIR)

DEPS := $(addprefix $(DEPDIR)/,$(notdir $(SRCS:%.c=%.d)))
$(DEPS):
include $(wildcard $(DEPS))

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
