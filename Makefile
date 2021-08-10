SRCDIR := srcs
OBJDIR := objs
DEPDIR := $(OBJDIR)/.deps
INCDIR := $(shell find incs -type d)

SRCS := $(shell find $(SRCDIR) -name \*.c)
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(SRCS:%.c=%.o)))

VPATH := $(dir $(SRCS))

NAME := test

CC := gcc
LDFLAGS := -lreadline -L/Users/nnamor/.brew/opt/readline/lib/
IFLAGS := $(addprefix -I ,$(INCDIR)) -I/Users/nnamor/.brew/opt/readline/include/
CFLAGS = -Wall -Wextra -Werror -g $(IFLAGS) -o $@
DEPFLAGS = -MT $@ -MMD -MF $(DEPDIR)/$*.tmpd
COMPILE.c = $(CC) $(CFLAGS) $(DEPFLAGS) -c
LINK.c = $(CC) $(CFLAGS) $(LDFLAGS)
POSTCOMPILE = mv -f $(DEPDIR)/$*.tmpd $(DEPDIR)/$*.d && touch $@

MKDIR = mkdir -p $@
RM := rm -rf

#-------------------------------------------------------------------------------#

$(NAME): $(OBJS)
	$(LINK.c) $^

all: $(NAME)

$(OBJDIR)/%.o : %.c $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $<
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
