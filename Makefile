# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 15:33:15 by pnoutere          #+#    #+#              #
#    Updated: 2022/10/04 14:47:54 by pnoutere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
INCLUDE_DIR = src/libft/ src/ build/libsdl2/include/
BUILD_DIR = build/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(BUILD_DIR)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --libs`

FT_LIBRARY = src/libft/libft.a

SRC_FILES = $(addprefix $(SRC_DIR), main.c\
									vector_tools.c\
									colors.c\
									cylinders.c\
									spheres.c\
									planes.c\
									cones.c\
									rotations.c\
									shadow_hits.c\
									read_for_objects.c\
									check_read_values.c\
									check_if_inside.c\
									check_objects_and_draw.c\
									check_for_shadows.c\
									object_inits.c\
									object_amount.c\
									closest_objects.c\
									check_closest_objects.c\
									ray_direction_and_misc.c\
									vector_and_camera_assign.c\
									cylinder_shadows.c\
									vector_tools_2.c\
									translation_unit.c\
									sdl_utils.c\
									free.c)

OBJCT_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.o))

NAME = RTv1

DEPENDENCY_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.dep))
DEPENDENCY_FLAGS = -MT $(@) -MMD -MP -MF $(BUILD_DIR)$(*).dep

LD = gcc
LDFLAGS = $(libsdl2_ldflags)
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra $(addprefix -I, $(INCLUDE_DIR))\
	$(libsdl2_cflags)
CPPFLAGS = -D_REENTRANT

all: $(NAME)

$(NAME): $(FT_LIBRARY) $(OBJCT_FILES) | $(BUILD_DIR) 
	@ $(LD) $(FT_LIBRARY) $(OBJCT_FILES) $(LDFLAGS) -o $(NAME)

$(OBJCT_FILES): $(libsdl2_lib)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR)%.dep
	@ $(CC) $(CFLAGS) $(CPPFLAGS) $(DEPENDENCY_FLAGS) -o $(@) $(<)

$(DEPENDENCY_FILES):

$(libsdl2_makefile):
	if test -d $(BUILD_DIR); then echo exists; else mkdir $(BUILD_DIR); fi
	cd libsdl2 && ./configure --prefix=$(abspath $(BUILD_DIR)libsdl2)\
		--disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile) | $(BUILD_DIR)
	$(MAKE) --directory=libsdl2 install

$(FT_LIBRARY):
	make -C src/libft/
	
clean:
	@ rm -f $(OBJCT_FILES)
	make -C src/libft/ clean

fclean:
	rm -f RTv1
	if test -f $(libsdl2_makefile); then $(MAKE) AUTOMAKE=: --directory=libsdl2\
		distclean; fi
	rm -rf $(BUILD_DIR)
	make -C src/libft/ fclean
	
re: fclean all

.PHONY: all clean fclean re

include $(wildcard $(DEPENDENCY_FILES))