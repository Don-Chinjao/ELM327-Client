# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momadani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 16:19:50 by momadani          #+#    #+#              #
#    Updated: 2023/03/20 03:57:37 by momadani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#                          M A K E F I L E                                     #
################################################################################

.DELETE_ON_ERROR:
.DEFAULT_GOAL			:=	all
SHELL					:=	$(shell which bash)
.SHELLFLAGS				:=	-eu -o pipefail -c

### F I L E S ##################################################################

NAME					:=	cub3D
NAME_BONUS				:=	cub3D_bonus

override FILES			:=	$(addsuffix .c,				\
							main						\
							ft_parsefile				\
							ft_statfile					\
							ft_initgame					\
							ft_parsemap					\
							ft_parsemap_utils			\
							ft_extract_textcol			\
							get_color					\
							minimap						\
							exec						\
							events						\
							move						\
							rotate						\
							check						\
							intersection				\
							raycasting					\
							utils						\
							ft_free_game				\
							ft_memptr					\
							ft_memset					\
							ft_strcmp					\
							ft_strncmp					\
							ft_putstr_fd				\
							ft_strchr					\
							ft_strrchr					\
							ft_split					\
							ft_strcat					\
							ft_strcpy					\
							ft_mega_join				\
							ft_free_strs				\
							free_text_path				\
							ft_strdup					\
							ft_strs_len					\
							ft_exit_error				\
							get_next_line				\
							get_next_line_utils			\
							ft_strlen					)


### D I R E C T O R I E S ######################################################

SRCDIR					:=	../sources
INCDIR					:=	../includes
MLXDIR					:=	$$HOME/usr/lib/minilibx
OBJDIR					:=	../.objects
DEPDIR					:=	../.dependencies
UTLDIR					:=	../.utils

### L I B R A R I E S ##########################################################

LIBMLX					:= mlx

### C O M P I L E R   F L A G S ################################################

CC						:=	cc
STD						:=	-std=gnu99
CFLAGS					:=	-Wall -Wextra -Werror -g3
IFLAGS					:=	-I{$(INCDIR),$(MLXDIR)}
LDFLAGS					:=	-L$(MLXDIR)
LDLIBS					:=	-l{$(LIBMLX),X11,Xext,m}

override MKDIR			:=	mkdir -pv
override RM				:=	rm -rvf

### P A T T E R N   R U L E S ##################################################

override SUB			:=	$(shell find $(SRCDIR) -type d)
override OBJ			:=	$(FILES:%.c=$(OBJDIR)/%.o)
override DEP			:=	$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ))
#override OBJ_BONUS		:=	$(FILES:%.c=$(OBJDIR)/bonus_%.o)
#override DEP_BONUS		:=	$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJ_BONUS))

### U T I L I T Y #############################################################$#

#.SECONDEXPANSION:
#DEL_BONUS_PREFIX = $$(subst bonus_,,%)

### C O M P I L A T I O N   F U N C T I O N S ##################################

define COMPILE_RULE
$(OBJDIR)/%.o:	$(1)/%.c | $(OBJDIR) $(DEPDIR)
	$$(CC) $$(STD) $$(IFLAGS) $$(CFLAGS)	\
	-c $$< -o $$@							\
	-MMD -MF $$(DEPDIR)/$$(*F).d
endef

### R E C I P E S ##############################################################

.PHONY:	all clean bclean fclean verbose re

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

#bonusflag:
#	$(eval DFLAGS := -D BONUS) 

-include $(DEP)
$(foreach DIR, $(SUB), $(eval $(call COMPILE_RULE,$(DIR))))

$(OBJDIR) $(DEPDIR):
	$(MKDIR) $@

clean:	;
	$(RM) $(OBJDIR) $(DEPDIR)

bclean:
	$(RM) $(NAME)

fclean:	clean bclean

verbose:	;

re:		fclean all
