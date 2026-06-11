# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                 dP   Yb 88__dP  8I  Yb "' dP'    #
#                                                     +:+ +:+         +:+      #
#    By: momadani <momadani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 16:19:50 by momadani          #+#    #+#              #
#    Updated: 2026/06/01 22:11:53 by momadafun                                 #
#                                                                              #
# **************************************************************************** #

################################################################################

.DELETE_ON_ERROR:
.DEFAULT_GOAL		:=	all
SHELL			:=	$(shell which bash)
.SHELLFLAGS		:=	-eu -o pipefail -c

### A S C I I   A R T ##########################################################

ART_NAME_1		=   █▀▀  █░█ ████████ ████▇▆▄  ████▆▄  \n
ART_NAME_2		=   █▄▄  █▄█ ██░    █ ██░  ▕█▋ ██░  ▐█▏\n
ART_NAME_3		= \40        ██░    █ ███████  ██░  ▕█▌\n
ART_NAME_4		=   █▄▄  █▀▀ ██░    █ ██░   █▋ ██░  ▐█▏\n
ART_NAME_5		=   █▄█  ██▄ ████████ ██████▀  █████▀  \n

ART_CLN1		=   █▀▀ █░░ █▀▀ ▄▀█ █▄░█\n
ART_CLN2		=   █▄▄ █▄▄ ██▄ █▀█ █░▀█\n

### D I S P L A Y   F U N C T I O N ############################################

PROGRESS_BAR	= $(UTLDIR)/ProgressBar.sh

PRINT_NAME		= printf "\n $(YELLOW1)$(ART_NAME_1)$(RESET)	\
							 $(YELLOW2)$(ART_NAME_2)$(RESET)	\
							 $(YELLOW3)$(ART_NAME_3)$(RESET)	\
							 $(YELLOW4)$(ART_NAME_4)$(RESET)	\
							 $(YELLOW5)$(ART_NAME_5)$(RESET)\n"

define PRINT_ASCII_ART
	printf "\n $(1)$(2)$(RESET) $(3)$(4)$(RESET)\n"
endef

### C O L O R S ################################################################

COUNT					=	1
CC_GREEN				=	\e[38;5;46;1m
CC_RED					=	\e[31;1m
CC_WHITE				=	\e[38;5;15;1m
YELLOW					=	\e[38;5;3m
YELLOW1					=	\e[38;2;255;254;0m
YELLOW2					=	\e[38;2;245;242;3m
YELLOW3					=	\e[38;2;236;230;6m
YELLOW4					=	\e[38;2;227;218;9m
YELLOW5					=	\e[38;2;227;206;12m
GREEN1					=	\e[38;5;46m
GREEN2					=	\e[38;2;0;235;0m
RED1					=	\e[38;5;196m
RED2					=	\e[38;5;160m
RESET					=	\e[0m

### F I L E S ##################################################################

NAME					:=	elm

override FILES				:=	$(addsuffix .c,		\
						main			\
						elm_parser		\
						elm_transport		\
						split_response		)

### D I R E C T O R I E S ######################################################

SRCDIR					:=	./sources
INCDIR					:=	./includes
OBJDIR					:=	./.objects
DEPDIR					:=	./.dependencies
UTLDIR					:=	./.utils

### L I B R A R I E S ##########################################################

### C O M P I L E R   F L A G S ################################################

CC					:=	cc
STD					:=	-std=gnu99
CFLAGS					:=	-Wall -Wextra -Werror -g3 -O3
IFLAGS					:=	-I$(INCDIR)
LDFLAGS					:=	-L
LDLIBS					:=	-l

override MKDIR				:=	mkdir -pv
override RM				:=	rm -rvf

### P A T T E R N   R U L E S ##################################################

override SUB			:=	$(shell find $(SRCDIR) -type d)
override OBJ			:=	$(FILES:%.c=$(OBJDIR)/%.o)
override DEP			:=	$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ))

### C O M P I L A T I O N   F U N C T I O N S ##################################

define COMPILE_RULE
$(OBJDIR)/%.o:	$(1)/%.c | $(OBJDIR) $(DEPDIR)
	@$$(CC) $$(STD) $$(IFLAGS) $$(CFLAGS)	\
	-c $$< -o $$@				\
	-MMD -MF $$(DEPDIR)/$$(*F).d
	@$$(PROGRESS_BAR) $$(shell basename $$<) $$(words $$(FILES)) $$(COUNT) $$(lastword $$(FILES))
	@$$(eval COUNT = $$(shell echo $$$$(($$(COUNT) + 1))))
endef

### R E C I P E S ##############################################################

.PHONY:	all clean bclean fclean verbose re

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@printf "\n\n $(CC_WHITE)Creating binary	: $(CC_GREEN)%s$(RESET)\n" $(NAME)
	@$(PRINT_NAME)

-include $(DEP)
$(foreach DIR, $(SUB), $(eval $(call COMPILE_RULE,$(DIR))))

$(OBJDIR) $(DEPDIR):
	@$(if $(findstring $@,$(OBJDIR)),$(eval MSG=object))
	@$(if $(findstring $@,$(DEPDIR)),$(eval MSG=dependency))
	@printf " $(CC_WHITE)Creating %s directory	: $(RESET)$(YELLOW)" $(MSG)
	@$(MKDIR) $@
	@printf "$(RESET)"

clean:	;
	@printf " $(CC_WHITE)Deleting object files	: $(CC_RED)\e[31;9m*.o *.d\n"	
	@$(RM) $(OBJDIR) $(DEPDIR)
	@printf "$(RESET)"

bclean:
	@printf " $(CC_WHITE)Deleting binary files	: $(CC_RED)\e[31;9m$(NAME)\n"
	@$(RM) $(NAME)
	@printf "$(RESET)"

fclean:	clean bclean
	@$(call PRINT_ASCII_ART,$(RED1),$(ART_CLN1),$(RED2),$(ART_CLN2))

verbose:	;
	$(MAKE) -C .utils $(filter-out verbose,$(MAKECMDGOALS))

kamikaze:
	@clear
	@(cd $(UTLDIR) ; ./kamikaze.sh)
	@$(RM) ../$(shell basename `pwd`) ; pkill cat ; clear

re:		fclean all
